#pragma once

class AActor;
class UMaterialInterface;
class UMaterialInstanceDynamic;

class UStaticMeshComponent;
class UBillboardComponent;

class UMyExample003_CubeMeshComponent;

struct MyActorUtil {
	MyActorUtil() = delete;

#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
	static void					SetOverlayMaterial(AActor* Actor, UMaterialInterface* Material);
	static UMaterialInterface*	GetOverlayMaterial(AActor* Actor);
#endif

	FORCEINLINE static void		SetActorLabel(AActor* Actor, const FString& Label);

	static void					SetMaterial(AActor* Actor, int ElementIndex, UMaterialInterface* Material);
	static UMaterialInterface*	GetMaterial(AActor* Actor, int ElementIndex);

	static UMaterialInstanceDynamic*	CreateDynamicMaterialInstance(AActor* Actor, int ElementIndex);

	static void		SetEnableGravity(AActor* Actor, bool bEnable);
	static bool		IsGravityEnabled(AActor* Actor);

	static float	GetBoundingSphereRadius(AActor* Actor, bool bOnlyCollidingComponents);

	template<class COMP_TYPE, class PARANT>
	static COMP_TYPE*		NewComponent(PARANT* Parent, UClass* Class, const FName& Name = NAME_None);

	template<class COMP_TYPE, class PARANT>
	static COMP_TYPE* NewComponent(PARANT* Parent, const FName& Name = NAME_None) {
		return NewComponent(Parent, nullptr, Name);
	}

	template<class COMP_TYPE, class PARANT>
	static COMP_TYPE*		GetOrNewComponent(PARANT* Parent);

	static UStaticMeshComponent* SetRootComponent_UStaticMeshComponent(AActor* Actor, const FName& Name = NAME_None);
	static UBillboardComponent*	 SetRootComponent_UBillboardComponent(AActor* Actor, const FName& Name = NAME_None);

	static AActor*			GetActor(AActor*         Actor) { return Actor; }
	static AActor*			GetActor(UActorComponent* Comp) { return Comp ? Comp->GetOwner() : nullptr; }

	static USceneComponent*	GetParentComponent(USceneComponent* Comp) { return Comp; }
	static USceneComponent*	GetParentComponent(UActorComponent* Comp) { return GetParentComponent(GetActor(Comp)); }
	static USceneComponent*	GetParentComponent(AActor*         Actor) { return Actor ? Actor->GetRootComponent() : nullptr; }

	static UMyExample003_CubeMeshComponent* SetRootComponent_UMyExample003_CubeMeshComponent(AActor* Actor, const FName& Name = NAME_None);

private:
	template <class SCENE_COMPONENT_TYPE>
	static SCENE_COMPONENT_TYPE* _SetRootComponentImpl(AActor* Actor, const FName& Name = NAME_None);
};

template <class COMP_TYPE, class PARANT> inline
COMP_TYPE* MyActorUtil::GetOrNewComponent(PARANT* Parent)
{
	auto* Actor = GetActor(Parent);
	if (!Actor)
		return nullptr;

	auto* OutComp = Actor->FindComponentByClass<COMP_TYPE>();
	if (OutComp)
		return OutComp;

	return NewComponent<COMP_TYPE>(Parent);
}

FORCEINLINE
void MyActorUtil::SetActorLabel(AActor* Actor, const FString& Label) {
#if WITH_EDITOR
	if (Actor)
		Actor->SetActorLabel(Label);
#endif
}

template <class COMP_TYPE, class PARANT>
inline COMP_TYPE* MyActorUtil::NewComponent(PARANT* Parent, UClass* Class, const FName& Name /*= NAME_None*/)
{
	static_assert(std::is_base_of_v<UActorComponent, COMP_TYPE>);
	if (!Parent)
		return nullptr;

	auto* Actor = GetActor(Parent);
	auto CompName = MakeUniqueObjectName(Actor, COMP_TYPE::StaticClass(), Name);

	auto* OutComp = NewObject<COMP_TYPE>(Actor, Class, CompName);
	Actor->AddInstanceComponent(OutComp);

	if constexpr (std::is_base_of_v<USceneComponent, COMP_TYPE>)
	{
		OutComp->AttachToComponent(GetParentComponent(Parent),
									FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}

	OutComp->RegisterComponent();
	return OutComp;
}