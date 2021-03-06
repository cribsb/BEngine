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
#include "AnimatedModel.h"
#include "Game.h"
#include "GameException.h"
#include "MatrixHelper.h"
#include "Camera.h"
#include "Utility.h"
#include "Model.h"
#include "Mesh.h"
#include "ModelMaterial.h"
#include "PointLight.h"
#include "Keyboard.h"
#include "SkinnedModelMaterial.h"
#include "SpotLightSkinnedModelMaterial.h"
#include "DirectionalLightSkinnedModelMaterial.h"
#include "UltimateSkinnedModelMaterial.h"
#include "VectorHelper.h"
#include "ColorHelper.h"
#include "AnimationPlayer.h"
#include "AnimationClip.h"
#include "ProxyModel.h"
#include <WICTextureLoader.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <sstream>
#include <iomanip>
#include "Shlwapi.h"
#include <fstream>
#include "DirectionalLight.h"
#include "SpotLight.h"

namespace Rendering
{
	RTTI_DEFINITIONS( AnimatedModel )

		//const float AnimatedModel::LightModulationRate = UCHAR_MAX;
		//const float AnimatedModel::LightMovementRate = 10.0f;

		AnimatedModel::AnimatedModel( Game& game, Camera& camera )
		: DrawableGameComponent( game, camera ),
		mMaterial( nullptr ), mEffect( nullptr ), mWorldMatrix( MatrixHelper::Identity ),
		mVertexBuffers(), mIndexBuffers(), mIndexCounts(), mColorTextures(),
		mKeyboard( nullptr ), mAmbientColor( reinterpret_cast<const float*>(&ColorHelper::White) ), mSpecularColor( 1.0f, 1.0f, 1.0f, 1.0f ), mSpecularPower( 25.0f ), mAnimationPlayer( nullptr ),
		/*mPointLight( nullptr ), mProxyModel( nullptr ), mSpriteBatch( nullptr ), mSpriteFont( nullptr ), mTextPosition( 0.0f, 40.0f ), */
		mRenderStateHelper( game ), mManualAdvanceMode( false ), mSkinnedModel( nullptr )
	{ }

	AnimatedModel::~AnimatedModel()
	{
		for ( ID3D11Buffer* vertexBuffer : mVertexBuffers )
		{
			ReleaseObject( vertexBuffer );
		}

		for ( ID3D11Buffer* indexBuffer : mIndexBuffers )
		{
			ReleaseObject( indexBuffer );
		}

		for ( ID3D11ShaderResourceView* colorTexture : mColorTextures )
		{
			ReleaseObject( colorTexture );
		}

		//DeleteObject( mSpriteFont );
		//DeleteObject( mSpriteBatch );
		DeleteObject( mSkinnedModel );
		DeleteObject( mAnimationPlayer );
		//DeleteObject( mProxyModel );
		//DeleteObject( mPointLight );
		DeleteObject( mMaterial );
		DeleteObject( mEffect );
	}

	LuaScript* ps;

	void AnimatedModel::Initialize( LuaScript* s, btDiscreteDynamicsWorld* world, std::vector<GameComponent*> Components, XMCOLOR ambientColor )
	{
		SetCurrentDirectory( Utility::ExecutableDirectory().c_str() );
		mComponents.reserve( Components.size() );
		mComponents = Components;
		mAmbientColor = ambientColor;

		unsigned int d = mComponents.size();

		for ( unsigned int i = 0; i < d; ++i )
		{
			if ( mComponents.at( i )->As<PointLight>() )
			{
				//mColorVector = mComponents.at(i)->As<PointLight>()->ColorVector();
				//mLightPositionVector = mComponents.at(i)->As<PointLight>()->PositionVector();
				mPLColorVectors[mNumPointLights] = mComponents.at( i )->As<PointLight>()->ColorVector();
				mPLPosVectors[mNumPointLights] = mComponents.at( i )->As<PointLight>()->PositionVector();
				mPointLightCVs[mNumPointLights] = mComponents.at( i )->As<PointLight>()->Color();
				mPointLights.push_back( mComponents.at( i )->As<PointLight>());
				//mLightType = PointLightType;
				mNumPointLights++;
			}
			if ( mComponents.at( i )->As<DirectionalLight>() )
			{
				mDLColorVectors[mNumDirLights] = mComponents.at( i )->As<DirectionalLight>()->ColorVector();
				mDirLightCVs[mNumDirLights] = mComponents.at( i )->As<DirectionalLight>()->Color();
				mDirLightDirs[mNumDirLights] = mComponents.at( i )->As<DirectionalLight>()->Direction();
				//mLightType = DirectionalLightType;
				mNumDirLights++;
			}
			if ( mComponents.at( i )->As<SpotLight>() )
			{
				mSLColorVectors[mNumSpotLights] = mComponents.at( i )->As<SpotLight>()->ColorVector();
				mSpotLightCVs[mNumSpotLights] = mComponents.at( i )->As<SpotLight>()->Color();
				mSLInnerRadia[mNumSpotLights] = mComponents.at( i )->As<SpotLight>()->InnerAngle();
				mSLOuterRadia[mNumSpotLights] = mComponents.at( i )->As<SpotLight>()->OuterAngle();
				mSLRads[mNumSpotLights] = mComponents.at( i )->As<SpotLight>()->Radius();
				mSLDirs[mNumSpotLights] = mComponents.at( i )->As<SpotLight>()->Direction();
				//mLightType = SpotLightType;
				mNumSpotLights++;
			}
		}

		// Load the model
		ps = s;
		mSkinnedModel = new Model( *mGame, s->get<std::string>( "player.filename" ), true );
		mXOffset = s->get<float>( "player.pos.x" );
		mYOffset = s->get<float>( "player.pos.y" );
		mZOffset = s->get<float>( "player.pos.z" );

		// Initialize the material
		mEffect = new Effect( *mGame );
		mEffect->LoadCompiledEffect( L"Content\\Effects\\SkinnedModel.cso" );
		mMaterial = new UltimateSkinnedModelMaterial();
		mMaterial->Initialize( *mEffect );
		for ( int i = 0; i < mNumDirLights; i++ )
		{
			DirectionalLightSkinnedModelMaterial* mat = new DirectionalLightSkinnedModelMaterial();
			mat->Initialize( *mEffect );
			mDirLightMats[i] = mat;
		}
		for ( int i = 0; i < mNumPointLights; i++ )
		{
			SkinnedModelMaterial* mat = new SkinnedModelMaterial();
			mat->Initialize( *mEffect );
			mPointLightMats[i] = mat;
		}
		for ( int i = 0; i < mNumSpotLights; i++ )
		{
			SpotLightSkinnedModelMaterial* mat = new SpotLightSkinnedModelMaterial();
			mat->Initialize( *mEffect );
			mSpotLightMats[i] = mat;
		}

		// Create the vertex and index buffers
		mVertexBuffers.resize( mSkinnedModel->Meshes().size() );
		mIndexBuffers.resize( mSkinnedModel->Meshes().size() );
		mIndexCounts.resize( mSkinnedModel->Meshes().size() );
		mColorTextures.resize( mSkinnedModel->Meshes().size() );
		for ( UINT i = 0; i < mSkinnedModel->Meshes().size(); i++ )
		{
			Mesh* mesh = mSkinnedModel->Meshes().at( i );

			ID3D11Buffer* vertexBuffer = nullptr;
			mMaterial->CreateVertexBuffer( mGame->Direct3DDevice(), *mesh, &vertexBuffer );
			mVertexBuffers[i] = vertexBuffer;

			ID3D11Buffer* indexBuffer = nullptr;
			mesh->CreateIndexBuffer( &indexBuffer );
			mIndexBuffers[i] = indexBuffer;

			mIndexCounts[i] = mesh->Indices().size();

			ID3D11ShaderResourceView* colorTexture = nullptr;
			ModelMaterial* material = mesh->GetMaterial();

			if ( material != nullptr && material->Textures().find( TextureTypeDifffuse ) != material->Textures().cend() )
			{
				std::vector<std::wstring>* diffuseTextures = material->Textures().at( TextureTypeDifffuse );
				std::wstring filename = PathFindFileName( diffuseTextures->at( 0 ).c_str() );

				std::wostringstream textureName;
				textureName << L"Content\\Models\\" << filename.substr( 0, filename.length() - 4 ) << L".png";
				HRESULT hr = DirectX::CreateWICTextureFromFile( mGame->Direct3DDevice(), mGame->Direct3DDeviceContext(), textureName.str().c_str(), nullptr, &colorTexture );
				if ( FAILED( hr ) )
				{
					throw GameException( "CreateWICTextureFromFile() failed.", hr );
				}
			}
			mColorTextures[i] = colorTexture;
		}

		XMStoreFloat4x4( &mWorldMatrix, XMMatrixScaling( 0.05f, 0.05f, 0.05f ) );

		// Create the rigid body
		btCollisionShape* colShape = new btBoxShape( btVector3( mSkinnedModel->GetMaxCornerBB().x - mSkinnedModel->GetMinCornerBB().x, mSkinnedModel->GetMaxCornerBB().y - mSkinnedModel->GetMinCornerBB().y, mSkinnedModel->GetMaxCornerBB().z - mSkinnedModel->GetMinCornerBB().z ) );
		btVector3 fallInertia( 0, 0, 0 );
		colShape->calculateLocalInertia( 1, fallInertia );
		motionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 10, 0 ) ) );
		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			1,						// mass
			motionState,			// initial position
			colShape,				// collision shape of body
			fallInertia				// local inertia
			);
		btRigidBody* rigidBody = new btRigidBody( rigidBodyCI );
		world->addRigidBody( rigidBody );

		//mPointLight = new PointLight( *mGame );
		//mPointLight->SetRadius( 500.0f );
		//mPointLight->SetPosition( 5.0f, 0.0f, 10.0f );

		mKeyboard = (Keyboard*)mGame->Services().GetService( Keyboard::TypeIdClass() );
		assert( mKeyboard != nullptr );

		mAnimationPlayer = new AnimationPlayer( *mGame, *mSkinnedModel, true );
		mAnimationPlayer->StartClip( *(mSkinnedModel->Animations().at( 0 )) );

		//mProxyModel = new ProxyModel( *mGame, *mCamera, "Content\\Models\\PointLightProxy.obj", 0.5f );
		//mProxyModel->Initialize();

		//mSpriteBatch = new SpriteBatch( mGame->Direct3DDeviceContext() );
		//mSpriteFont = new SpriteFont( mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont" );
	}

	XMFLOAT4X4 AnimatedModel::getWorldMatrix()
	{
		return mWorldMatrix;
	}

	void AnimatedModel::Update( const GameTime& gameTime )
	{
		//UpdateOptions();
		//UpdateAmbientLight( gameTime );
		//UpdatePointLight( gameTime );
		//UpdateSpecularLight( gameTime );

		if ( mManualAdvanceMode == false )
		{
			mAnimationPlayer->Update( gameTime );
		}

		//mProxyModel->Update( gameTime );
	}

	void AnimatedModel::Draw( const GameTime& gameTime )
	{
		btTransform trans;
		motionState->getWorldTransform( trans );
		ps->setLuaVariable( "player.pos.x", trans.getOrigin().getX() );
		ps->setLuaVariable( "player.pos.y", trans.getOrigin().getY() );
		ps->setLuaVariable( "player.pos.z", trans.getOrigin().getZ() );

		mXOffset = ps->get<float>( "player.pos.x" );
		mYOffset = ps->get<float>( "player.pos.y" );
		mZOffset = ps->get<float>( "player.pos.z" );

		ID3D11DeviceContext* direct3DDeviceContext = mGame->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		Pass* pass = mMaterial->CurrentTechnique()->Passes().at( 0 );
		ID3D11InputLayout* inputLayout = mMaterial->InputLayouts().at( pass );
		direct3DDeviceContext->IASetInputLayout( inputLayout );

		XMMATRIX worldMatrix = XMLoadFloat4x4( &mWorldMatrix );
		MatrixHelper::SetTranslation( worldMatrix, /*XMFLOAT3( mXOffset, mYOffset, mZOffset ) );//*/XMFLOAT3( trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() ) );
		XMMATRIX wvp = worldMatrix * mCamera->ViewMatrix() * mCamera->ProjectionMatrix();
		XMVECTOR ambientColor = XMLoadColor( &mAmbientColor );
		XMVECTOR specularColor = XMLoadColor( &mSpecularColor );

		UINT stride = mMaterial->VertexSize();
		UINT offset = 0;

		for ( UINT i = 0; i < mVertexBuffers.size(); i++ )
		{
			ID3D11Buffer* vertexBuffer = mVertexBuffers[i];
			ID3D11Buffer* indexBuffer = mIndexBuffers[i];
			UINT indexCount = mIndexCounts[i];
			ID3D11ShaderResourceView* colorTexture = mColorTextures[i];

			direct3DDeviceContext->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );
			direct3DDeviceContext->IASetIndexBuffer( indexBuffer, DXGI_FORMAT_R32_UINT, 0 );

			mMaterial->WorldViewProjection() << wvp;
			mMaterial->World() << worldMatrix;
			mMaterial->SpecularColor() << specularColor;
			mMaterial->SpecularPower() << mSpecularPower;
			mMaterial->AmbientColor() << ambientColor;
			//mMaterial->LightColor() << mColorVector;
			//mMaterial->LightPosition() << mLightPositionVector;
			//mMaterial->LightRadius() << 500000.0f;
			mMaterial->ColorTexture() << colorTexture;
			mMaterial->CameraPosition() << mCamera->PositionVector();
			mMaterial->BoneTransforms() << mAnimationPlayer->BoneTransforms();
			
			for ( int i = 0; i < mPointLights.size(); i++ )
			{
				PointLight* pointLight = mPointLights[i];
				mMaterial->inited = true;
				mMaterial->LightPosition() << pointLight->PositionVector();
				//mMaterial->PointLights[i]->Position << pointLight->PositionVector();
				//mMaterial->PointLights[i]->Radius << 50.0f;//pointLight->Radius();
				//mMaterial->PointLights[i]->Color << pointLight->ColorVector();
			}

			for ( int j = 0; j < mNumDirLights; j++ )
			{
				mDirLightMats[i]->WorldViewProjection() << wvp;
				mDirLightMats[i]->World() << worldMatrix;
				mDirLightMats[i]->AmbientColor() << ambientColor;
				mDirLightMats[i]->LightDirection() << XMLoadFloat3(&mDirLightDirs[i]);
				mDirLightMats[i]->ColorTexture() << colorTexture;
				mDirLightMats[i]->BoneTransforms() << mAnimationPlayer->BoneTransforms();
			}
			for ( int k = 0; k < mNumPointLights; k++ )
			{
				mPointLightMats[i]->WorldViewProjection() << wvp;
				mPointLightMats[i]->World() << worldMatrix;
				mPointLightMats[i]->SpecularColor() << specularColor;
				mPointLightMats[i]->SpecularPower() << mSpecularPower;
				mPointLightMats[i]->AmbientColor() << ambientColor;
				mPointLightMats[i]->LightColor() << mPLColorVectors[i];
				mPointLightMats[i]->LightPosition() << mPLPosVectors[i];
				mPointLightMats[i]->LightRadius() << 500000.0f;
				mPointLightMats[i]->ColorTexture() << colorTexture;
				mPointLightMats[i]->CameraPosition() << mCamera->PositionVector();
				mPointLightMats[i]->BoneTransforms() << mAnimationPlayer->BoneTransforms();
			}
			for ( int l = 0; l < mNumSpotLights; l++ )
			{
				mSpotLightMats[i]->WorldViewProjection() << wvp;
				mSpotLightMats[i]->World() << worldMatrix;
				mSpotLightMats[i]->SpecularColor() << specularColor;
				mSpotLightMats[i]->SpecularPower() << mSpecularPower;
				mSpotLightMats[i]->AmbientColor() << ambientColor;
				mSpotLightMats[i]->SpotLightInnerAngle() << mSLInnerRadia[i];
				mSpotLightMats[i]->SpotLightOuterAngle() << mSLOuterRadia[i];
				mSpotLightMats[i]->LightLookAt() << XMLoadFloat3(&mSLDirs[i]);
				mSpotLightMats[i]->ColorTexture() << colorTexture;
				mSpotLightMats[i]->CameraPosition() << mCamera->PositionVector();
				mSpotLightMats[i]->BoneTransforms() << mAnimationPlayer->BoneTransforms();
			}

			pass->Apply( 0, direct3DDeviceContext );

			direct3DDeviceContext->DrawIndexed( indexCount, 0, 0 );
		}

		//mProxyModel->Draw( gameTime );

		mRenderStateHelper.SaveAll();
		//mSpriteBatch->Begin();

		//std::wostringstream helpLabel;
		//helpLabel << std::setprecision( 5 ) << L"Ambient Intensity (+PgUp/-PgDn): " << mAmbientColor.a << "\n";
		//helpLabel << L"Point Light Intensity (+Home/-End): " << mPointLight->Color().a << "\n";
		//helpLabel << L"Specular Power (+Insert/-Delete): " << mSpecularPower << "\n";
		//helpLabel << L"Move Point Light (8/2, 4/6, 3/9)\n";
		//helpLabel << "Frame Advance Mode (Enter): " << (mManualAdvanceMode ? "Manual" : "Auto") << "\nAnimation Time: " << mAnimationPlayer->CurrentTime()
		//<< "\nFrame Interpolation (I): " << (mAnimationPlayer->InterpolationEnabled() ? "On" : "Off") << "\nGo to Bind Pose (B)";

		//if ( mManualAdvanceMode )
		//{
		//helpLabel << "\nCurrent Keyframe (Space): " << mAnimationPlayer->CurrentKeyframe();
		//}
		//else
		//{
		//helpLabel << "\nPause / Resume(P)";
		//}

		//mSpriteFont->DrawString( mSpriteBatch, helpLabel.str().c_str(), mTextPosition );

		//mSpriteBatch->End();
		mRenderStateHelper.RestoreAll();
	}

	/*void AnimatedModel::UpdateOptions()
	{
	if ( mKeyboard != nullptr )
	{
	if ( mKeyboard->WasKeyPressedThisFrame( DIK_P ) )
	{
	if ( mAnimationPlayer->IsPlayingClip() )
	{
	mAnimationPlayer->PauseClip();
	}
	else
	{
	mAnimationPlayer->ResumeClip();
	}
	}

	if ( mKeyboard->WasKeyPressedThisFrame( DIK_B ) )
	{
	// Reset the animation clip to the bind pose
	mAnimationPlayer->StartClip( *(mSkinnedModel->Animations().at( 0 )) );
	}

	if ( mKeyboard->WasKeyPressedThisFrame( DIK_I ) )
	{
	// Enable/disabled interpolation
	mAnimationPlayer->SetInterpolationEnabled( !mAnimationPlayer->InterpolationEnabled() );
	}

	if ( mKeyboard->WasKeyPressedThisFrame( DIK_RETURN ) )
	{
	// Enable/disable manual advance mode
	mManualAdvanceMode = !mManualAdvanceMode;
	mAnimationPlayer->SetCurrentKeyFrame( 0 );
	}

	if ( mManualAdvanceMode && mKeyboard->WasKeyPressedThisFrame( DIK_SPACE ) )
	{
	// Advance the current keyframe
	UINT currentKeyFrame = mAnimationPlayer->CurrentKeyframe();
	currentKeyFrame++;
	if ( currentKeyFrame >= mAnimationPlayer->CurrentClip()->KeyframeCount() )
	{
	currentKeyFrame = 0;
	}

	mAnimationPlayer->SetCurrentKeyFrame( currentKeyFrame );
	}
	}
	}

	void AnimatedModel::UpdateAmbientLight( const GameTime& gameTime )
	{
	static float ambientIntensity = mAmbientColor.a;

	if ( mKeyboard != nullptr )
	{
	if ( mKeyboard->IsKeyDown( DIK_PGUP ) && ambientIntensity < UCHAR_MAX )
	{
	ambientIntensity += LightModulationRate * (float)gameTime.ElapsedGameTime();
	mAmbientColor.a = (UCHAR)XMMin<float>( ambientIntensity, UCHAR_MAX );
	}

	if ( mKeyboard->IsKeyDown( DIK_PGDN ) && ambientIntensity > 0 )
	{
	ambientIntensity -= LightModulationRate * (float)gameTime.ElapsedGameTime();
	mAmbientColor.a = (UCHAR)XMMax<float>( ambientIntensity, 0 );
	}
	}
	}

	void AnimatedModel::UpdateSpecularLight( const GameTime& gameTime )
	{
	static float specularIntensity = mSpecularPower;

	if ( mKeyboard != nullptr )
	{
	if ( mKeyboard->IsKeyDown( DIK_INSERT ) && specularIntensity < UCHAR_MAX )
	{
	specularIntensity += LightModulationRate * (float)gameTime.ElapsedGameTime();
	specularIntensity = XMMin<float>( specularIntensity, UCHAR_MAX );

	mSpecularPower = specularIntensity;;
	}

	if ( mKeyboard->IsKeyDown( DIK_DELETE ) && specularIntensity > 0 )
	{
	specularIntensity -= LightModulationRate * (float)gameTime.ElapsedGameTime();
	specularIntensity = XMMax<float>( specularIntensity, 0 );

	mSpecularPower = specularIntensity;
	}
	}
	}

	void AnimatedModel::UpdatePointLight( const GameTime& gameTime )
	{
	static float pointLightIntensity = mPointLight->Color().a;
	float elapsedTime = (float)gameTime.ElapsedGameTime();

	// Update point light intensity
	if ( mKeyboard->IsKeyDown( DIK_HOME ) && pointLightIntensity < UCHAR_MAX )
	{
	pointLightIntensity += LightModulationRate * elapsedTime;

	XMCOLOR pointLightLightColor = mPointLight->Color();
	pointLightLightColor.a = (UCHAR)XMMin<float>( pointLightIntensity, UCHAR_MAX );
	mPointLight->SetColor( pointLightLightColor );
	}
	if ( mKeyboard->IsKeyDown( DIK_END ) && pointLightIntensity > 0 )
	{
	pointLightIntensity -= LightModulationRate * elapsedTime;

	XMCOLOR pointLightLightColor = mPointLight->Color();
	pointLightLightColor.a = (UCHAR)XMMax<float>( pointLightIntensity, 0.0f );
	mPointLight->SetColor( pointLightLightColor );
	}

	// Move point light
	XMFLOAT3 movementAmount = Vector3Helper::Zero;
	if ( mKeyboard != nullptr )
	{
	if ( mKeyboard->IsKeyDown( DIK_NUMPAD4 ) )
	{
	movementAmount.x = -1.0f;
	}

	if ( mKeyboard->IsKeyDown( DIK_NUMPAD6 ) )
	{
	movementAmount.x = 1.0f;
	}

	if ( mKeyboard->IsKeyDown( DIK_NUMPAD9 ) )
	{
	movementAmount.y = 1.0f;
	}

	if ( mKeyboard->IsKeyDown( DIK_NUMPAD3 ) )
	{
	movementAmount.y = -1.0f;
	}

	if ( mKeyboard->IsKeyDown( DIK_NUMPAD8 ) )
	{
	movementAmount.z = -1.0f;
	}

	if ( mKeyboard->IsKeyDown( DIK_NUMPAD2 ) )
	{
	movementAmount.z = 1.0f;
	}
	}

	XMVECTOR movement = XMLoadFloat3( &movementAmount ) * LightMovementRate * elapsedTime;
	//mPointLight->SetPosition(mPointLight->PositionVector() + movement);
	mPointLight->SetPosition( XMVectorAdd( mPointLight->PositionVector(), movement ) );
	mProxyModel->SetPosition( mPointLight->Position() );
	}*/
}