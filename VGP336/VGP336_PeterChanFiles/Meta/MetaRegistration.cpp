//====================================================================================================
// Filename:	MetaRegistration.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MetaRegistration.h"
#include "MetaRegistry.h"

#include "Camera.h"

// Components
#include "Component.h"
#include "CameraComponent.h"
#include "CameraControllerComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

//====================================================================================================
// Functions Definitions
//====================================================================================================

void MetaRegistration()
{
#define REGISTER(x) MetaRegistry::Register(x::StaticGetMetaClass())

	REGISTER(Camera);

	// Components
	REGISTER(Component);
	REGISTER(CameraComponent);
	REGISTER(CameraControllerComponent);
	REGISTER(ColliderComponent);
	REGISTER(TransformComponent);

#undef REGISTER
}