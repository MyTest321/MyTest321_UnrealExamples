#pragma once

#include "MyCore/Base/MY_MACRO.h"

//-- Unreal Header --
#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/TriggerBox.h"
#include "Engine/TriggerCapsule.h"
#include "Engine/TriggerSphere.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/MathFwd.h"
#include "Math/Vector.h"
#include "Modules/ModuleManager.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "SceneManagement.h"
#include "UMG.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/NoExportTypes.h"
#include <UObject/ReflectedTypeAccessors.h>
#if IS_UE5
	#include "UObject/ObjectPtr.h" 
#endif
#include "UObject/WeakInterfacePtr.h"
#include "Widgets/SCompoundWidget.h"

#if WITH_EDITOR
	#include "Editor.h"
#endif // WITH_EDITOR