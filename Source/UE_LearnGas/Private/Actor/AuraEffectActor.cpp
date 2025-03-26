// 王乐用于学习Gas的项目，仅供参考

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UE_LearnGas/UE_LearnGas.h"

WL_DEBUG_BEGIN

// 构造函数
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

// 开始运行
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// 添加动态绑定
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}

// 当重叠时
void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 转换为 ASCInterface
	if ( auto ASCInterface = Cast<IAbilitySystemInterface>(OtherActor) )
	{
		const auto AuraASC = ASCInterface->GetAbilitySystemComponent();
		const auto AuraAS = Cast<UAuraAttributeSet>(AuraASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		const_cast<UAuraAttributeSet*>(AuraAS)->SetHealth(AuraAS->GetHealth() + 25.f);
		Destroy();
	}
	
}

// 结束重叠
void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

WL_DEBUG_END
