// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include <MultiplayerGame/MyActors/DefaultTeam.h>
#include "DefaultPlayerState.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "DefaultPlayerController.h"
#include "Blueprint/UserWidget.h"
#include <MultiplayerGame/Widgets/MatchInfo.h>
#include <MultiplayerGame/Widgets/PauseMenuWidget.h>
#include "Blueprint/WidgetBlueprintLibrary.h"


ADefaultCharacter::ADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	WeaponManager = CreateDefaultSubobject<UWeaponManagerComponent>("WeaponManager");
	BulletManager = CreateDefaultSubobject<UBulletManagerComponent>("BulletManager");
	
	Arms = CreateDefaultSubobject<USkeletalMeshComponent>("ArmsMesh");
	Arms->SetupAttachment(RootComponent);
	Arms->SetOnlyOwnerSee(true);
	CurrentHealth = MaxHelth;
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetLocalRole() == ROLE_Authority) {
		MulticastUpdateCameraView(Controller->GetControlRotation());
	}
}

void ADefaultCharacter::MulticastUpdateCameraView_Implementation(FRotator rot)
{
	if (!Controller || GetLocalRole() == ROLE_Authority) {
		FRotator ro = this->Camera->GetComponentRotation();
		this->Camera->SetWorldRotation(FRotator(rot.Pitch, ro.Yaw, ro.Roll));
	}
}

void ADefaultCharacter::MoveForward(float X)
{

	FRotator rot = FRotator(0.0, GetControlRotation().Yaw, 0.0);
	FVector Vector = rot.Vector();
	AddMovementInput(Vector, X);
}

void ADefaultCharacter::MoveSide(float X)
{
	float Yaw = GetControlRotation().Yaw + 90.0;
	if (Yaw > 360.0)
	{
		Yaw = Yaw - 360.0;
	}
	FRotator rot = FRotator(0.0, Yaw, 0.0);
	FVector Vector = rot.Vector();
	AddMovementInput(Vector, X);
}

void ADefaultCharacter::LookRight(float X)
{
	AddControllerYawInput(X);
}

void ADefaultCharacter::LookUp(float X)
{
	AddControllerPitchInput(X);
}

void ADefaultCharacter::PressShoot_Implementation()
{
	if (WeaponManager->FPPWeapons[WeaponManager->IndexWeapon] != nullptr) {
		GetWorldTimerManager().SetTimer(ForShoot, WeaponManager->FPPWeapons[WeaponManager->IndexWeapon], &ADefaultWeapon::PressShoot, WeaponManager->FPPWeapons[WeaponManager->IndexWeapon]->FireSpeed, true, 0);
	}
}

void ADefaultCharacter::UnPressShoot_Implementation()
{
	if (WeaponManager->FPPWeapons[WeaponManager->IndexWeapon] != nullptr) {
		GetWorldTimerManager().ClearTimer(ForShoot);
		WeaponManager->FPPWeapons[WeaponManager->IndexWeapon]->UnPressShoot();
	}	
}

void ADefaultCharacter::PressAlternativeShoot_Implementation()
{
	if (WeaponManager->FPPWeapons[WeaponManager->IndexWeapon] != nullptr) {
		WeaponManager->FPPWeapons[WeaponManager->IndexWeapon]->PressAlternativeShoot();
	}	
}

void ADefaultCharacter::UnPressAlternativeShoot_Implementation()
{
	if (WeaponManager->FPPWeapons[WeaponManager->IndexWeapon] != nullptr) {
		WeaponManager->FPPWeapons[WeaponManager->IndexWeapon]->UnPressAlternativeShoot();
	}	
}

void ADefaultCharacter::StartJump()
{
	Jump();
}

void ADefaultCharacter::StopJump()
{
	StopJumping();
}

void ADefaultCharacter::DestroyWeapons()
{
	if (WeaponManager != nullptr) {
		for (int i = 0; i < WeaponManager->FPPWeapons.Num(); i++) {
			if (WeaponManager->FPPWeapons.Num() > i) {
				WeaponManager->FPPWeapons[i]->Destroy();
				WeaponManager->TPPWeapons[i]->Destroy();
			}
		}
	}
}

void ADefaultCharacter::OnMenu()
{
	ADefaultPlayerController* Contr = Cast<ADefaultPlayerController>(GetOwner());
	if (Contr != nullptr) {
		if (Contr->PauseMenu->IsVisible()) {
			Contr->OnUnFocusMenu();
			InputComponent->AxisBindings = AxBind;
			InputComponent->BindAction("Shoot", IE_Pressed, this, &ADefaultCharacter::PressShoot);
			InputComponent->BindAction("Shoot", IE_Released, this, &ADefaultCharacter::UnPressShoot);
			InputComponent->BindAction("AlternativeShoot", IE_Pressed, this, &ADefaultCharacter::PressAlternativeShoot);
			InputComponent->BindAction("AlternativeShoot", IE_Released, this, &ADefaultCharacter::UnPressAlternativeShoot);
			InputComponent->BindAction("NextWeapon", IE_Pressed, this, &ADefaultCharacter::NextWeapon);
			InputComponent->BindAction("NextBullet", IE_Pressed, this, &ADefaultCharacter::NextBullet);
			InputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultCharacter::StartJump);
			InputComponent->BindAction("Jump", IE_Released, this, &ADefaultCharacter::StopJump);
			InputComponent->BindAction("Stats", IE_Pressed, this, &ADefaultCharacter::OnStatsPressed);
			InputComponent->BindAction("Stats", IE_Released, this, &ADefaultCharacter::OnStatsReleased);
		}
		else {
			Contr->OnFocusMenu();
			InputComponent->AxisBindings.Empty();
			InputComponent->ClearActionBindings();
			InputComponent->BindAction("Menu", IE_Pressed, this, &ADefaultCharacter::OnMenu);
		}
	}
}

void ADefaultCharacter::OnStatsReleased()
{
	ADefaultPlayerController* Contr = Cast<ADefaultPlayerController>(GetOwner());
	if (Contr != nullptr) {
		Contr->MatchStats->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ADefaultCharacter::OnStatsPressed()
{
	ADefaultPlayerController* Contr = Cast<ADefaultPlayerController>(GetOwner());
	if (Contr != nullptr) {
		Contr->MatchStats->SetVisibility(ESlateVisibility::Visible);
	}
}

void ADefaultCharacter::OnDead_Implementation()
{
	DisableInput(Cast<APlayerController>(Controller));
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADefaultCharacter::NextWeapon_Implementation()
{
	int32 a = WeaponManager->IndexWeapon + 1;
	if (a == WeaponManager->WeaponsClasses.Num())
	{
		a = 0;
	}
	WeaponManager->SetCurrentWeapon(a);
}

void ADefaultCharacter::NextBullet_Implementation()
{
	int32 a = BulletManager->IndexBullet + 1;
	if (a == BulletManager->BulletsClasses.Num())
	{
		a = 0;
	}
	BulletManager->SetCurrentBullet(a);
}

void ADefaultCharacter::OnRep_CurrentHealth()
{
	if (GetLocalRole() == ROLE_SimulatedProxy) {
		if (CurrentHealth <= 0)
		{

		}
	}
}

void ADefaultCharacter::OnRep_Color()
{
	SetMat(Color);
}

void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("RunForward", this, &ADefaultCharacter::MoveForward);
	InputComponent->BindAxis("RunSide", this, &ADefaultCharacter::MoveSide);
	InputComponent->BindAxis("LookRight", this, &ADefaultCharacter::LookRight);
	InputComponent->BindAxis("LookUp", this, &ADefaultCharacter::LookUp);
	AxBind = InputComponent->AxisBindings;

	InputComponent->BindAction("Shoot", IE_Pressed, this, &ADefaultCharacter::PressShoot);
	InputComponent->BindAction("Shoot", IE_Released, this, &ADefaultCharacter::UnPressShoot);
	InputComponent->BindAction("AlternativeShoot", IE_Pressed, this, &ADefaultCharacter::PressAlternativeShoot);
	InputComponent->BindAction("AlternativeShoot", IE_Released, this, &ADefaultCharacter::UnPressAlternativeShoot);
	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &ADefaultCharacter::NextWeapon);
	InputComponent->BindAction("NextBullet", IE_Pressed, this, &ADefaultCharacter::NextBullet);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ADefaultCharacter::StopJump);
	InputComponent->BindAction("Menu", IE_Pressed, this, &ADefaultCharacter::OnMenu);
	InputComponent->BindAction("Stats", IE_Pressed, this, &ADefaultCharacter::OnStatsPressed);
	InputComponent->BindAction("Stats", IE_Released, this, &ADefaultCharacter::OnStatsReleased);
}

void ADefaultCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADefaultCharacter, CurrentHealth);
	DOREPLIFETIME(ADefaultCharacter, Shield);
	DOREPLIFETIME(ADefaultCharacter, Color);
}

void ADefaultCharacter::Destroyed()
{
	DestroyWeapons();
	Super::Destroyed();
}

void ADefaultCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void ADefaultCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ADefaultPlayerState* PS = Cast<ADefaultPlayerState>(GetController()->PlayerState);
	PS->isDamageble = true;
	Color = PS->Team->TeamColor;
	ADefaultPlayerController* PC = Cast<ADefaultPlayerController>(NewController);
	if (PC != nullptr) {
		PC->SetModeGameOnly();
	}
	if (GetLocalRole() == ROLE_Authority) {
		WeaponManager->SetCurrentWeapon(0);
	}
}

void ADefaultCharacter::SetMat(FColor Col)
{
	TArray<UMaterialInterface*> Mat = GetMesh()->GetMaterials();
	for (int i = 0; i < Mat.Num(); i++) {
		UMaterialInstanceDynamic* NewMat = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, Mat[i]);
		NewMat->SetVectorParameterValue(FName("Color"), Col);
		GetMesh()->SetMaterialByName(GetMesh()->GetMaterialSlotNames()[i], NewMat);
	}
}
