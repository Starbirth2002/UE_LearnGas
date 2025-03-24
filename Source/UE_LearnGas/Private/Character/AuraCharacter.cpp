// 王乐用于学习Gas的项目，仅供参考

#include "UE_LearnGas/Public/Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraCharacter::AAuraCharacter()
{
  auto Movement = GetCharacterMovement();
  Movement->bOrientRotationToMovement = true;
  Movement->RotationRate = FRotator(0.f, 400.f, 0.f);
  Movement->bConstrainToPlane = true;
  Movement->bSnapToPlaneAtStart = true;

  bUseControllerRotationPitch = false;;
  bUseControllerRotationYaw = false;
  bUseControllerRotationRoll = false;
}

WL_DEBUG_END