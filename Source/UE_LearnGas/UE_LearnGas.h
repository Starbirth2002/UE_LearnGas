// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define WL_DEBUG_BEGIN UE_DISABLE_OPTIMIZATION
#define WL_DEBUG_END UE_ENABLE_OPTIMIZATION

#define CUSTOM_DEPTH_RED 250.f

#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1

// 安全调用
#define SAFE_FUN(p, fun) { if ( p ) { p->fun; } }
/* CMD
 * 显示ABS数据	showdebug abilitysystem
 */