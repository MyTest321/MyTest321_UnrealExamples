#include "MyExample004_PlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "MyExample004_Pawn.h"

AMyExample004_PlayerController::AMyExample004_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	InputDirection = FVector::ZeroVector;
}

AMyExample004_Pawn* AMyExample004_PlayerController::GetMyPwan() const
{
	return CastChecked<AMyExample004_Pawn>(Super::GetPawn());
}

void AMyExample004_PlayerController::BeginPlay() {
	Super::BeginPlay();

	MY_LOG_WARNING(TEXT("AMyExample004_PlayerController::BeginPlay"));

#if WITH_EDITOR
	static FName s_FolderPath = TEXT("MyGame");

	MyActorUtil::SetActorLabel(this, TEXT("MyController Test"));

	MyActorUtil::SetFolderPath(this, s_FolderPath);

	if (auto* GameMode = MyActorUtil::GetGameMode(this))
	{
		MyActorUtil::SetFolderPath(GameMode, s_FolderPath);
	}
#endif

	UpdateCameraTarget();
}

void AMyExample004_PlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	MY_LOG_ON_SCREEN(TEXT("InputDirection {}"), InputDirection);

	if (auto* p = GetMyPwan())
	{
		auto NewLoc = p->GetActorLocation();
		NewLoc += InputDirection * 100 * DeltaSeconds;
		p->SetActorLocation(NewLoc);
	}
}

void AMyExample004_PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	SetShowMouseCursor(true);

	// Axis
	InputComponent->BindAxis("Move Forward / Backward", this, &ThisClass::OnInputAxis_MoveForward);
	InputComponent->BindAxis("Move Right / Left",		this, &ThisClass::OnInputAxis_MoveRight);

	// Action
	InputComponent->BindAction("Jump", IE_Pressed,		this, &ThisClass::OnInputAction_Jump_Pressed);
	InputComponent->BindAction("Jump", IE_Released,		this, &ThisClass::OnInputAction_Jump_Released);
	InputComponent->BindAction("Jump", IE_Axis,			this, &ThisClass::OnInputAction_Jump_Axis);
	InputComponent->BindAction("Jump", IE_Repeat,		this, &ThisClass::OnInputAction_Jump_Repeat);
	InputComponent->BindAction("Jump", IE_DoubleClick,	this, &ThisClass::OnInputAction_Jump_DoubleClick);

	InputComponent->BindAction("MyChangeCamera", IE_Pressed, this, &ThisClass::OnInputAction_MyChangeCamera);
}

void AMyExample004_PlayerController::OnInputAxis_MoveForward(float Value) { InputDirection.X = Value; }
void AMyExample004_PlayerController::OnInputAxis_MoveRight  (float Value) { InputDirection.Y = Value; }

void AMyExample004_PlayerController::OnInputAction_Jump_Pressed()		{ MY_LOG_INFO(TEXT("Jump_Pressed")); }
void AMyExample004_PlayerController::OnInputAction_Jump_Released()		{ MY_LOG_INFO(TEXT("Jump_Released")); }
void AMyExample004_PlayerController::OnInputAction_Jump_Axis()			{ MY_LOG_INFO(TEXT("Jump_Axis")); }
void AMyExample004_PlayerController::OnInputAction_Jump_Repeat()		{ MY_LOG_INFO(TEXT("Jump_Repeat")); }
void AMyExample004_PlayerController::OnInputAction_Jump_DoubleClick()	{ MY_LOG_INFO(TEXT("Jump_DoubleClick")); }

void AMyExample004_PlayerController::OnInputAction_MyChangeCamera()
{
	MY_LOG_INFO(TEXT("OnInputAction_MyChangeCamera"));

	CurrentCameraIndex++;
	UpdateCameraTarget();
}

void AMyExample004_PlayerController::UpdateCameraTarget() {
	static FName MyCameraTag(TEXT("MyCamera"));

	TArray<AActor*> CameraList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MyCameraTag, CameraList);

	int N = CameraList.Num();
	if (N <= 0) return;

	auto* Cam = CameraList[CurrentCameraIndex % N];
	SetViewTargetWithBlend(Cam);
}
