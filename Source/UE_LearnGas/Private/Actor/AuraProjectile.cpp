// 王乐用于学习Gas的项目，仅供参考

#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic,	ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn,			ECR_Overlap);

	// 绑定组件
	AC_LoopingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopingSoundComponent"));
	AC_LoopingSound->SetupAttachment(RootComponent);
	AC_LoopingSound->bAutoActivate = false;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// 开始运行
void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	
	// 绑定重叠事件
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
	
	// 投掷物播放持续音效
	if ( IsValid(LoopingSound) )
	{
		AC_LoopingSound->SetSound(LoopingSound);
		AC_LoopingSound->Play();
	}
	
}

// 已销毁
void AAuraProjectile::Destroyed()
{
	// 当在客户端上且没发生命中时，如果服务器发生重叠调用了销毁，则说明客户端没有播放特效，这里播放特效
	if ( !bHit && !HasAuthority() )
	{
		// 播放声音 生成特效
		const FVector& Location = GetActorLocation();
		const FRotator& Rotator = GetActorRotation();
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Location, Rotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect,  Location, Rotator);
		AC_LoopingSound->Stop();
	}
	
	Super::Destroyed();
}

// 开始重叠
void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 通常情况是服务器发生重叠，通知销毁，在销毁时播放特效
	// 如果 Destroy()延迟了，客户端可以提前播放特效，不用等待服务器同步

	// 播放声音 生成特效
	const FVector& Location = GetActorLocation();
	const FRotator& Rotator = GetActorRotation();
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Location, Rotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect,  Location, Rotator);
	AC_LoopingSound->Stop();
	
	// 如果是服务器，进行销毁，如果是客户端，标记已命中，等待服务端进行销毁
	if ( HasAuthority() )
	{
		// 造成效果
		if ( UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor) )
		{
			if ( DamageEffectSpecHandle.IsValid() )
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
			}
		}
		
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

WL_DEBUG_END