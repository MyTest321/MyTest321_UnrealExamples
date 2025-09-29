#pragma once

//-- Unreal Header --
#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/OverlapResult.h"
#include "Engine/TriggerBox.h"
#include "Engine/TriggerCapsule.h"
#include "Engine/TriggerSphere.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Math/MathFwd.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "SceneManagement.h"
#include "UMG.h"
#include "UObject/WeakInterfacePtr.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/SCompoundWidget.h"

#if WITH_EDITOR
	#include "Editor.h"
#endif // WITH_EDITOR

//-- My Header --
#include "MyLib/MyActorUtil.h"
#include "MyLib/MyCDO.h"
#include "MyLib/MyConsole.h"
#include "MyLib/MyGameUtil.h"
#include "MyLib/MyLog.h"
#include "MyLib/MyUI.h"
#include "MyLib/MyPhysics.h"
