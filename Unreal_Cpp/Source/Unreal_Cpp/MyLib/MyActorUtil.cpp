#include "MyActorUtil.h"

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Components/MeshComponent.h" 
#include "Components/BillboardComponent.h"

#include "Unreal_Cpp/Example003/MyExample003_CubeMeshComponent.h" // #include "../Example003/MyExample003_CubeMeshComponent.h";

#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
void MyActorUtil::SetOverlayMaterial(AActor* Actor, UMaterialInterface* Material)
{
	if (!Actor)
		return;

	auto* MeshComp = Actor->FindComponentByClass<UMeshComponent>();
	if (!MeshComp)
		return;

	MeshComp->SetOverlayMaterial(Material);
}

UMaterialInterface* MyActorUtil::GetOverlayMaterial(AActor* Actor)
{
	if (!Actor)
		return nullptr;

	auto* MeshComp = Actor->FindComponentByClass<UMeshComponent>();
	if (!MeshComp)
		return nullptr;

	return MeshComp->GetOverlayMaterial();
}
#endif

void MyActorUtil::SetMaterial(AActor* Actor, int ElementIndex, UMaterialInterface* Material)
{
	if (Actor)
		return;

	auto* PrimComp = Actor->FindComponentByClass<UPrimitiveComponent>();
	if (!PrimComp)
		return;

	PrimComp->SetMaterial(ElementIndex, Material);
}

UMaterialInterface* MyActorUtil::GetMaterial(AActor* Actor, int ElementIndex)
{
	if (!Actor)
		return nullptr;

	auto* PrimComp = Actor->FindComponentByClass<UPrimitiveComponent>();
	if (!PrimComp)
		return nullptr;

	return PrimComp->GetMaterial(ElementIndex);
}

UMaterialInstanceDynamic* MyActorUtil::CreateDynamicMaterialInstance(AActor* Actor, int ElementIndex)
{
	if (!Actor)
		return nullptr;

	auto* PrimComp = Actor->FindComponentByClass<UPrimitiveComponent>();
	if (!PrimComp)
		return nullptr;

	return PrimComp->CreateDynamicMaterialInstance(ElementIndex);
}

void MyActorUtil::SetEnableGravity(AActor* Actor, bool bEnable)
{
	if (!Actor)
		return;

	auto* PrimComp = Actor->FindComponentByClass<UPrimitiveComponent>();
	if (!PrimComp)
		return;

	PrimComp->SetEnableGravity(bEnable);
}

bool MyActorUtil::IsGravityEnabled(AActor* Actor)
{
	if (!Actor)
		return false;

	auto* PrimComp = Actor->FindComponentByClass<UPrimitiveComponent>();
	if (!PrimComp)
		return false;

	return PrimComp->IsGravityEnabled();
}

float MyActorUtil::GetBoundingSphereRadius(AActor* Actor, bool bOnlyCollidingComponents)
{
	if (!Actor)
		return 0;

	FVector Origin, BoxExtent;
	Actor->GetActorBounds(bOnlyCollidingComponents, Origin, BoxExtent);

	return BoxExtent.Length();
}

template <class SCENE_COMPONENT_TYPE>
SCENE_COMPONENT_TYPE* MyActorUtil::_SetRootComponentImpl(AActor* Actor, const FName& Name /*= NAME_None*/) {
	if (!Actor)
		return nullptr;

	static_assert(std::is_base_of_v<USceneComponent, SCENE_COMPONENT_TYPE>);
	auto* OutComp = Actor->CreateDefaultSubobject<SCENE_COMPONENT_TYPE>(Name.IsNone() ? SCENE_COMPONENT_TYPE::StaticClass()->GetFName() : Name);
	if (!Actor->SetRootComponent(OutComp))
		return nullptr;
	return OutComp;
}

UStaticMeshComponent* MyActorUtil::SetRootComponent_UStaticMeshComponent(AActor* Actor, const FName& Name/*= NAME_None*/) {
	return MyActorUtil::_SetRootComponentImpl<UStaticMeshComponent>(Actor, Name);
}

UBillboardComponent* MyActorUtil::SetRootComponent_UBillboardComponent(AActor* Actor, const FName& Name/*= NAME_None*/) {
	return MyActorUtil::_SetRootComponentImpl<UBillboardComponent>(Actor, Name);
}

UMyExample003_CubeMeshComponent* MyActorUtil::SetRootComponent_UMyExample003_CubeMeshComponent(AActor* Actor, const FName& Name/*= NAME_None*/) {
	return MyActorUtil::_SetRootComponentImpl<UMyExample003_CubeMeshComponent>(Actor, Name);
}
