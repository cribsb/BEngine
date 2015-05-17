/*
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Model.h"
#include "Game.h"
#include "GameException.h"
#include "Mesh.h"
#include "ModelMaterial.h"
#include "AnimationClip.h"
#include "Bone.h"
#include "MatrixHelper.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <DirectXCollision.h>

namespace Library
{
	const aiScene* scene;

	void get_bounding_box(const aiNode* nd, aiVector3D* min, aiVector3D* max)

	{
		unsigned int n = 0;

		if (nd->mNumMeshes) {

			// Get node transformation matrix
			aiMatrix4x4 m = nd->mTransformation;

			// OpenGL matrices are column major
			m.Transpose();

			// apply node transformation
			float aux[16];
			memcpy(aux, &m, sizeof(float) * 16);


			for (; n < nd->mNumMeshes; ++n) {
				const struct aiMesh* mesh =
					scene->mMeshes[nd->mMeshes[n]];
				for (unsigned int t = 0; t < mesh->mNumVertices; ++t) {

					aiVector3D tmp = mesh->mVertices[t];
					float a[4], res[4];

					a[0] = tmp.x;
					a[1] = tmp.y;
					a[2] = tmp.z;
					a[3] = 1.0f;

					min->x = min(min->x, res[0]);
					min->y = min(min->y, res[1]);
					min->z = min(min->z, res[2]);

					max->x = max(max->x, res[0]);
					max->y = max(max->y, res[1]);
					max->z = max(max->z, res[2]);
				}
			}
		}

		for (n = 0; n < nd->mNumChildren; ++n) {
			get_bounding_box(nd->mChildren[n], min, max);
		}
	}

	XMFLOAT3 aiVec3ToXMFloat3(const aiVector3D* vector)
	{
		XMFLOAT3 out;
		out.x = vector->x;
		out.y = vector->y;
		out.z = vector->z;

		return out;
	}

    Model::Model(Game& game, const std::string& filename, bool flipUVs)
		: mGame(game), mMeshes(), mMaterials(), mAnimations(), mBones(), mBoneIndexMapping(), mRootNode(nullptr)
    {
        Assimp::Importer importer;

		UINT flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_FlipWindingOrder;
        if (flipUVs)
        {
            flags |= aiProcess_FlipUVs;
        }

        scene = importer.ReadFile(filename, flags);
        if (scene == nullptr)
        {
            throw GameException(importer.GetErrorString());
        }

        if (scene->HasMaterials())
        {
            for (UINT i = 0; i < scene->mNumMaterials; i++)
            {
                mMaterials.push_back(new ModelMaterial(*this, scene->mMaterials[i]));
            }
        }

        if (scene->HasMeshes())
        {
            for (UINT i = 0; i < scene->mNumMeshes; i++)
            {	
				Mesh* mesh = new Mesh(*this, *(scene->mMeshes[i]));
                mMeshes.push_back(mesh);
            }
        }

		if (scene->HasAnimations())
		{
			assert(scene->mRootNode != nullptr);
			mRootNode = BuildSkeleton(*scene->mRootNode, nullptr);
			
			mAnimations.reserve(scene->mNumAnimations);
			for (UINT i = 0; i < scene->mNumAnimations; i++)
			{
				AnimationClip* animationClip = new AnimationClip(*this, *(scene->mAnimations[i]));
				mAnimations.push_back(animationClip);
				mAnimationsByName.insert(std::pair<std::string, AnimationClip*>(animationClip->Name(), animationClip));
			}
		}

		aiVector3D min = aiVector3D();
		aiVector3D max = aiVector3D();
		min.x = 1e10f;
		min.y = 1e10f;
		min.z = 1e10f;
		max.x = -1e10f;
		max.y = -1e10f;
		max.z = -1e10f;
		get_bounding_box(scene->mRootNode, &min, &max);

		BoundingBox bb;
		BoundingBox::CreateFromPoints(bb, XMLoadFloat3(&aiVec3ToXMFloat3(&min)), XMLoadFloat3(&aiVec3ToXMFloat3(&max)));
		

#if defined( DEBUG ) || defined( _DEBUG )
		ValidateModel();
#endif
    }

    Model::~Model()
    {
        for (Mesh* mesh : mMeshes)
        {
            delete mesh;
        }

        for (ModelMaterial* material : mMaterials)
        {
            delete material;
        }

		for (AnimationClip* animation: mAnimations)
		{
			delete animation;
		}

		if (mRootNode != nullptr)
		{
			DeleteSceneNode(mRootNode);
		}		
    }

	void Model::DeleteSceneNode(SceneNode* sceneNode)
	{
		for (SceneNode* childNode : sceneNode->Children())
		{
			DeleteSceneNode(childNode);
		}

		DeleteObject(sceneNode);
	}

    Game& Model::GetGame()
    {
        return mGame;
    }

    bool Model::HasMeshes() const
    {
        return (mMeshes.size() > 0);
    }

    bool Model::HasMaterials() const
    {
        return (mMaterials.size() > 0);
    }

	bool Model::HasAnimations() const
	{
		return (mAnimations.size() > 0);
	}

    const std::vector<Mesh*>& Model::Meshes() const
    {
        return mMeshes;
    }

    const std::vector<ModelMaterial*>& Model::Materials() const
    {
        return mMaterials;
    }

	const std::vector<AnimationClip*>& Model::Animations() const
	{
		return mAnimations;
	}

	const std::map<std::string, AnimationClip*>& Model::AnimationsbyName() const
	{
		return mAnimationsByName;
	}

	const std::vector<Bone*> Model::Bones() const
	{
		return mBones;
	}

	const std::map<std::string, UINT> Model::BoneIndexMapping() const
	{
		return mBoneIndexMapping;
	}

	SceneNode* Model::RootNode()
	{
		return mRootNode;
	}

	SceneNode* Model::BuildSkeleton(aiNode& node, SceneNode* parentSceneNode)
	{
		SceneNode* sceneNode = nullptr;

		auto boneMapping = mBoneIndexMapping.find(node.mName.C_Str());
		if (boneMapping == mBoneIndexMapping.end())
		{
			sceneNode = new SceneNode(node.mName.C_Str());
		}
		else
		{
			sceneNode = mBones[boneMapping->second];
		}

		XMMATRIX transform = XMLoadFloat4x4(&(XMFLOAT4X4(reinterpret_cast<const float*>(node.mTransformation[0]))));
		sceneNode->SetTransform(XMMatrixTranspose(transform));
		sceneNode->SetParent(parentSceneNode);

		for (UINT i = 0; i < node.mNumChildren; i++)
		{
			SceneNode* childSceneNode = BuildSkeleton(*(node.mChildren[i]), sceneNode);
			sceneNode->Children().push_back(childSceneNode);			
		}

		return sceneNode;
	}

	void Model::ValidateModel()
	{
		// Validate bone weights
		for (Mesh* mesh : mMeshes)
		{
			for (BoneVertexWeights boneWeight : mesh->mBoneWeights)
			{
				float totalWeight = 0.0f;

				for (BoneVertexWeights::VertexWeight vertexWeight : boneWeight.Weights())
				{
					totalWeight += vertexWeight.Weight;
					assert(vertexWeight.BoneIndex >= 0);
					assert(vertexWeight.BoneIndex < mBones.size());
				}

				assert(totalWeight <= 1.05f);
				assert(totalWeight >= 0.95f);
			}
		}
	}
}
