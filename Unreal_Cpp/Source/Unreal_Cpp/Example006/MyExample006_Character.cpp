#include "MyExample006_Character.h"
#include "MyExample006_AnimInstance.h"

AMyExample006_Character::AMyExample006_Character() {
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
	MY_CDO_FINDER(GetMesh()->AnimClass, TEXT("AnimBlueprint'/Game/ThirdPerson/MyExample006/MyExample006_AnimBP'"));

	// Character Movement
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate			  = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity			  = 600.f;
	GetCharacterMovement()->AirControl				  = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed			  = 225;
}

void AMyExample006_Character::BeginPlay()
{
	Super::BeginPlay();

	static FName MyTargetName(TEXT("MyTarget"));
	TArray<AActor*> TargetList;
	MyGameUtil::GetAllActorsWithTag(TargetList, MyTargetName);
	if (TargetList.Num() > 0)
	{
		Target = TargetList[0];
	}
}

void AMyExample006_Character::MyEquip()
{
	MY_LOG_INFO(TEXT("MyEquip"));
}

void AMyExample006_Character::MyFire()
{
	MY_LOG_INFO(TEXT("MyFire"));
}

void AMyExample006_Character::MyJump()
{
	MY_LOG_INFO(TEXT("MyJump"));
}