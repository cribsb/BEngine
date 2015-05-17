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
#pragma once

#include "Common.h"
#include "BufferContainer.h"

struct aiMesh;

namespace Library
{
    class Material;
    class ModelMaterial;
	class BoneVertexWeights;

    class Mesh
    {
        friend class Model;

    public:
        ~Mesh();

        Model& GetModel();
        ModelMaterial* GetMaterial();
        const std::string& Name() const;

        const std::vector<XMFLOAT3>& Vertices() const;
        const std::vector<XMFLOAT3>& Normals() const;
        const std::vector<XMFLOAT3>& Tangents() const;
        const std::vector<XMFLOAT3>& BiNormals() const;
        const std::vector<std::vector<XMFLOAT3>*>& TextureCoordinates() const;
        const std::vector<std::vector<XMFLOAT4>*>& VertexColors() const;
        UINT FaceCount() const;
        const std::vector<UINT>& Indices() const;
		const std::vector<BoneVertexWeights>& BoneWeights() const;

		BufferContainer& VertexBuffer();
		BufferContainer& IndexBuffer();

		bool HasCachedVertexBuffer() const;
		bool HasCachedIndexBuffer() const;

        void CreateIndexBuffer(ID3D11Buffer** indexBuffer);
		void CreateCachedVertexAndIndexBuffers(ID3D11Device& device, const Material& material);

    private:
        Mesh(Model& model, aiMesh& mesh);
        Mesh(const Mesh& rhs);
        Mesh& operator=(const Mesh& rhs);

        Model& mModel;
        ModelMaterial* mMaterial;
        std::string mName;
        std::vector<XMFLOAT3> mVertices;
        std::vector<XMFLOAT3> mNormals;
        std::vector<XMFLOAT3> mTangents;
        std::vector<XMFLOAT3> mBiNormals;
        std::vector<std::vector<XMFLOAT3>*> mTextureCoordinates;
        std::vector<std::vector<XMFLOAT4>*> mVertexColors;
        UINT mFaceCount;
        std::vector<UINT> mIndices;
		std::vector<BoneVertexWeights> mBoneWeights;

		BufferContainer mVertexBuffer;
		BufferContainer mIndexBuffer;

		//void CreateBoundingVolumes(std::vector<XMFLOAT3> &vertPosArray, std::vector<XMFLOAT3> &boundingBoxVerts, std::vector<DWORD> &boundingBoxIndex, float &boundingSphere, XMVECTOR &objectCenterOffset);
    };
}