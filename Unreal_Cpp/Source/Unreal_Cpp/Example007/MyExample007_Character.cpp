#include "MyExample007_Character.h"
#include "MyExample007_AnimInstance.h"
#include "MyExample007_Bullet.h"

AMyExample007_Character::AMyExample007_Character() {
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	MyCDO::CreateComponent<USpringArmComponent>(RootComponent, CameraBoom);

	CameraBoom->TargetArmLength = 300.0f;		// The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;								// Camera does not rotate relative to arm

	// Mesh
	MY_CDO_FINDER(GetMesh()->SkeletalMesh, TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin'"));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -97), FRotator(0, 270, 0));

	// AnimBP
	MY_CDO_FINDER(GetMesh()->AnimClass, TEXT("AnimBlueprint'/Game/ThirdPerson/MyExample007/AnimBP_MyExample007'"));

	// Character Movement
	// https://www.youtube.com/watch?v=k5Lcn2Kc3XI
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate			  = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity			  = 600.f;
	GetCharacterMovement()->AirControl				  = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed			  = 225;

	// Montage
	MY_CDO_FINDER(Montage_Equip, TEXT("AnimMontage'/Game/ThirdPerson/MyExample007/Animations/Montage_Equip'"));
	MY_CDO_FINDER(Montage_Fire_Upper, TEXT("AnimMontage'/Game/ThirdPerson/MyExample007/Animations/Montage_Fire_Upper'"));
}

UMyExample007_AnimInstance* AMyExample007_Character::MyAnimInstance()
{
	return Cast<UMyExample007_AnimInstance>(GetMesh()->GetAnimInstance());
}

const USkeletalMeshSocket* AMyExample007_Character::MyFindSocket(FName name)
{
	auto* sock = GetMesh()->GetSocketByName(name);
	if (!sock)
	{
		MY_LOG_ERROR(TEXT("cannot find socket {}"), name);
	}
	return sock;
}

void AMyExample007_Character::BeginPlay()
{
	Super::BeginPlay();

	static FName AimStartSocketName(TEXT("AimStartSocket"));
	AimStartSocket = MyFindSocket(AimStartSocketName);

	static FName SpawnBulletSocketName(TEXT("SpawnBulletSocket"));
	SpawnBulletSocket = MyFindSocket(SpawnBulletSocketName);

	static FName	MyTargetName(TEXT("MyTarget"));
	TArray<AActor*> TargetList;
	MyGameUtil::GetAllActorsWithTag(TargetList, MyTargetName);
	if (TargetList.Num() > 0) {
		Target = TargetList[0];
	}
}

void AMyExample007_Character::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	static const FName BlockMove(TEXT("BlockMove"));
	if (auto* AnimInst = MyAnimInstance())
	{
		BlockMoveCurveValue = AnimInst->GetCurveValue(BlockMove);
		MY_LOG_ON_SCREEN(TEXT("BlockMoveCurveValue={}"), BlockMoveCurveValue);
	}

	if (auto* t = Target.Get())
	{
		if (auto* aimStartSock = AimStartSocket.Get())
		{
			auto start = aimStartSock->GetSocketLocation(GetMesh());
			auto aim = t->GetActorLocation();
			DrawDebugLine(GetWorld(), start, aim, FColor::Red);
		}
	}
}

void AMyExample007_Character::CalcAimOffset(float& AimUp, float& AimRight)
{
	if (auto* t = Target.Get())
	{
		FVector	 targetLoc = t->GetActorLocation();
		FVector	 aim = GetTransform().InverseTransformPosition(targetLoc);
		FRotator rot = aim.Rotation();
		AimUp	 = rot.Pitch;
		AimRight = rot.Yaw;
	}
	else
	{
		AimUp = 0;
		AimRight = 0;
	}
}

void AMyExample007_Character::MyEquip()
{
	MY_LOG_INFO(TEXT("MyEquip"));
	if (!Montage_Equip.IsNull())
	{
		PlayAnimMontage(Montage_Equip);
	}
}

void AMyExample007_Character::MyFire()
{
	MY_LOG_INFO(TEXT("MyFire"));
	if (Montage_Fire_Upper)
	{
		if (auto* AnimInstance = MyAnimInstance())
		{
			AnimInstance->Montage_Play(Montage_Fire_Upper);
			MY_LOG_INFO(TEXT("Montage_Play Montage_Fire_Upper"));
		}
	}
}

void AMyExample007_Character::MyJump()
{
	MY_LOG_INFO(TEXT("MyJump"));
}

void AMyExample007_Character::AnimNotify_Fire()
{
	UClass* Cls = BulletToSpawnClass.Get();
	if (!Cls)
	{
		Cls = AMyExample007_Bullet::StaticClass();
	}
	if (!Cls)
	{
		MY_LOG_ERROR(TEXT("Bullet Class is null"));
	}

	UWorld* World = GetWorld();
	if (!World)
		return;

	FTransform trans = SpawnBulletSocket->GetSocketTransform(GetMesh());
	trans.SetScale3D(FVector::OneVector);

	if (auto* t = Target.Get()) {
		auto targetLoc = t->GetActorLocation();
		auto v = targetLoc - trans.GetLocation();
		trans.SetRotation(v.Rotation().Quaternion());
	}
	World->SpawnActor(Cls, &trans);
}
