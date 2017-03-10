#ifndef INCLUDED_ENGINE_H
#define INCLUDED_ENGINE_H

//====================================================================================================
// Filename:	Engine.h
// Created by:	Peter Chan
// Description:	3D Engine.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Common.h"

//Game system header
#include "GameSystems.h"

// Core headers
#include "Application.h"
#include "Delegate.h"
#include "Random.h"

//Component Headers
#include "Component.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "CameraControllerComponent.h"
#include "RTSCameraControllerComponent.h"
#include "SpriteComponent.h"
#include "CursorComponent.h"
#include "SpawnerComponent.h"
#include "AIComponent.h"
#include "TerrainComponent.h"
#include "ModelComponent.h"
#include "TowerComponent.h"
#include "TeamComponent.h"
#include "HealthComponent.h"
#include "BulletComponent.h"
#include "BuilderComponent.h"

//GameObject Headers
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "World.h"

// Graphics headers
#include "AnimationClip.h"
#include "AnimationController.h"
#include "Bone.h"
#include "BoneAnimation.h"
#include "Camera.h"
#include "Color.h"
#include "ConstantBuffer.h"
#include "Font.h"
#include "GraphicsSystem.h"
#include "Heightmap.h"
#include "Keyframe.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "MeshBuilder.h"
#include "MeshRenderer.h"
#include "MeshUtil.h"
#include "Model.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "SimpleDraw.h"
#include "SpriteRenderer.h"
#include "Terrain.h"
#include "Texture.h"
#include "VertexShader.h"

// Memory Headers
#include "BlockAllocator.h"
#include "Handle.h"

// Input headers
#include "InputEvent.h"
#include "InputSystem.h"
#include "InputTypes.h"

// Math headers
#include "EngineMath.h"

// Physics headers
#include "Constraints.h"
#include "Particle.h"
#include "PhysicsWorld.h"

// Platform headers
#include "Timer.h"
#include "Window.h"

// Memory headers
#endif // #ifndef INCLUDED_ENGINE_H