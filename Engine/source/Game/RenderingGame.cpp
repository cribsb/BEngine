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
#include "RenderingGame.h"
#include "GameException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "FpsComponent.h"
#include "ColorHelper.h"
#include "FirstPersonCamera.h"
#include "RenderStateHelper.h"
#include "RasterizerStates.h"
#include "SamplerStates.h"
#include "Skybox.h"
#include "Grid.h"

#include "AnimatedModel.h"
#include "LuaScript.h"
#include "VectorHelper.h"

#include "btBulletDynamicsCommon.h"

namespace Rendering
{


	const XMVECTORF32 RenderingGame::BackgroundColor = ColorHelper::CornflowerBlue;

	LuaScript player( "Content\\Scripts\\test.lua", true );

	RenderingGame::RenderingGame( HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand )
		: Game( instance, windowClass, windowTitle, showCommand ),
		mFpsComponent( nullptr ), mGrid( nullptr ),
		mDirectInput( nullptr ), mKeyboard( nullptr ), mMouse( nullptr ), mRenderStateHelper( nullptr ), mSkybox( nullptr ),
		mAnimationDemo( nullptr ), dynamicsWorld( nullptr )
	{
		// All bullet stuff
		// Build the broadphase
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();

		// Set up the collision configuration and dispatcher
		btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher( collisionConfiguration );

		// The actual physics solver
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

		// The world.
		dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, broadphase, solver, collisionConfiguration );
		dynamicsWorld->setGravity( btVector3( 0, -1, 0 ) );

		btCollisionShape* groundShape = new btBoxShape( btVector3( 100, 1, 100 ) );


		btDefaultMotionState* groundMotionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, -1, 0 ) ) );
		btRigidBody::btRigidBodyConstructionInfo
			groundRigidBodyCI( 0, groundMotionState, groundShape, btVector3( 0, 0, 0 ) );
		btRigidBody* groundRigidBody = new btRigidBody( groundRigidBodyCI );
		dynamicsWorld->addRigidBody( groundRigidBody );

		inited = true;
		// end of bullet stuff

		mMultiSamplingCount = 8;
		mWindowTitle = L"Menata";

		mDepthStencilBufferEnabled = true;
		mMultiSamplingEnabled = true;

		AllocConsole();
		freopen( "CONIN$", "r", stdin );
		freopen( "CONOUT$", "w", stdout );
		freopen( "CONOUT$", "w", stderr );
	}

	RenderingGame::~RenderingGame()
	{ }

	void RenderingGame::Initialize()
	{
		if ( FAILED( DirectInput8Create( mInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr ) ) )
		{
			throw GameException( "DirectInput8Create() failed" );
		}

		mKeyboard = new Keyboard( *this, mDirectInput );
		mComponents.push_back( mKeyboard );
		mServices.AddService( Keyboard::TypeIdClass(), mKeyboard );

		mMouse = new Mouse( *this, mDirectInput );
		mComponents.push_back( mMouse );
		mServices.AddService( Mouse::TypeIdClass(), mMouse );
		player.InitInput( mKeyboard, mMouse );

		mCamera = new FirstPersonCamera( *this );
		mComponents.push_back( mCamera );
		mServices.AddService( Camera::TypeIdClass(), mCamera );

		mFpsComponent = new FpsComponent( *this );
		mFpsComponent->Initialize();

		mSkybox = new Skybox( *this, *mCamera, L"Content\\Textures\\Maskonaive2_1024.dds", 500.0f );
		mComponents.push_back( mSkybox );

		//mGrid = new Grid(*this, *mCamera);
		//mComponents.push_back(mGrid);

		RasterizerStates::Initialize( mDirect3DDevice );
		SamplerStates::BorderColor = ColorHelper::Black;
		SamplerStates::Initialize( mDirect3DDevice );

		mRenderStateHelper = new RenderStateHelper( *this );

		mPoint = new PointLight( *this );
		mPoint->SetRadius( 5000.0f );
		mPoint->SetPosition( 0.0f, 0.0f, 10.0f );
		mPoint->SetColor( 1.0f, 10.0f, 0.0f, 1.0f );
		mComponents.push_back( mPoint );
		mPoint->SetPosition( 0.0f, 0.0f, -10.0f );
		mComponents.push_back( mPoint );

		SpotLight* sl = new SpotLight( *this );
		sl->SetColor( 1.0f, 0.0f, 0.0f, 1.0f );
		sl->SetRadius( 500.0f );
		sl->SetInnerAngle( 10.0f );
		sl->SetOuterAngle( 25.0f );
		sl->SetPosition( 0.0f, 5.0f, 5.0f );
		//mComponents.push_back( sl );

		DirectionalLight* dl = new DirectionalLight( *this );
		dl->SetColor( 0.0f, 0.0f, 1.0f, 1.0f );
		//dl->Direction = XMFLOAT3( 0.0f, 0.0f, 0.0f );
		mComponents.push_back( dl );

		Game::Initialize();

		mAnimationDemo = new AnimatedModel( *this, *mCamera );
		mAnimationDemo->Initialize( &player, dynamicsWorld, mComponents );
		mComponents.push_back( mAnimationDemo );

		mCamera->SetPosition( player.get<float>( "player.pos.x" ), player.get<float>( "player.pos.y" ), player.get<float>( "player.pos.z" ) );
	}

	void RenderingGame::Shutdown()
	{
		DeleteObject( mAnimationDemo );
		DeleteObject( mRenderStateHelper );
		DeleteObject( mKeyboard );
		DeleteObject( mMouse );
		DeleteObject( mSkybox )
			DeleteObject( mGrid );
		DeleteObject( mFpsComponent );
		DeleteObject( mCamera );

		ReleaseObject( mDirectInput );
		RasterizerStates::Release();
		SamplerStates::Release();

		Game::Shutdown();
	}

	void RenderingGame::Update( const GameTime &gameTime )
	{
		mFpsComponent->Update( gameTime );

		if ( mKeyboard->WasKeyPressedThisFrame( DIK_ESCAPE ) )
		{
			Exit();
		}
		if ( mKeyboard->WasKeyPressedThisFrame( DIK_C ) )
		{
			mPoint->SetPosition( mPoint->Position().x, mPoint->Position().y, mPoint->Position().z + 1 );
		}
		Game::Update( gameTime );
		player.L_Update( gameTime.ElapsedGameTime() );
		mCamera->SetPosition( player.get<float>( "player.pos.x" ), player.get<float>( "player.pos.y" ) + 8, player.get<float>( "player.pos.z" ) + 10 );
		mCamera->ApplyRotation( mAnimationDemo->getWorldMatrix() );
		dynamicsWorld->stepSimulation( 1 / 60.0f );
	}

	void RenderingGame::Draw( const GameTime &gameTime )
	{
		mDirect3DDeviceContext->ClearRenderTargetView( mRenderTargetView, reinterpret_cast<const float*>(&BackgroundColor) );
		mDirect3DDeviceContext->ClearDepthStencilView( mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );

		Game::Draw( gameTime );

		mRenderStateHelper->SaveAll();
		mFpsComponent->Draw( gameTime );
		mRenderStateHelper->RestoreAll();

		HRESULT hr = mSwapChain->Present( 0, 0 );
		if ( FAILED( hr ) )
		{
			throw GameException( "IDXGISwapChain::Present() failed.", hr );
		}
	}
}