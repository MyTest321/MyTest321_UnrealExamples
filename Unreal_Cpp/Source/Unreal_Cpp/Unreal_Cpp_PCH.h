#pragma once

//-- Unreal Header --
#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SceneManagement.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "UObject/WeakInterfacePtr.h"
#include "UObject/ConstructorHelpers.h"

#include "GameFramework/Actor.h"

// UI
#include "Widgets/SCompoundWidget.h"
#include "UMG.h"

#if WITH_EDITOR
	#include "Editor.h"
#endif // WITH_EDITOR

//-- My Header --
#include "MyLib/MyActorUtil.h"
#include "MyLib/MyCDO.h"
#include "MyLib/MyLog.h"

