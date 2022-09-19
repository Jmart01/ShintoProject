// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameplayAbilityBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShintoAbilitySystemComp.h"
#include "SetActorAttributes.h"
#include "GameplayAbilityBase.h"
#include <GameplayEffectTypes.h>

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//PlayerEyeSpringArm = CreateDefaultSubobject<USpringArmComponent>("PlayerEyeSpringArm");
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	SkeletalMeshToHide = GetMesh();
	SkeletalMeshToHide->SetActive(false);
	SkeletalMeshToShow = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshToShow");
	SkeletalMeshToShow->SetupAttachment(PlayerEye);
	PlayerEye->SetupAttachment(GetRootComponent());
	PlayerEye->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 600, 0);

	AbilitySystemComp = CreateDefaultSubobject<UShintoAbilitySystemComp>("AbilitySystemComp");
	Attributes = CreateDefaultSubobject<USetActorAttributes>("Attributes");

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	AbilitySystemComp->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
	if (AbilitySystemComp && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EShintoAbilityInputID", 
			static_cast<int32>(EShintoAbilityInputID::Confirm), static_cast<int32>(EShintoAbilityInputID::Cancel));
		AbilitySystemComp->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ensure(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterBase::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterBase::Jump);

	if (AbilitySystemComp && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EShintoAbilityInputID",
			static_cast<int32>(EShintoAbilityInputID::Confirm), static_cast<int32>(EShintoAbilityInputID::Cancel));
		AbilitySystemComp->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}

}

void ACharacterBase::MoveForward(float amount)
{
	if (Controller !=  nullptr && amount != 0)
	{
		FVector ViewLoc;
		FRotator ViewRot;
		GetController()->GetPlayerViewPoint(ViewLoc, ViewRot);
		FVector ForwardDir = ViewRot.Vector();
		AddMovementInput(ForwardDir, amount);
	}
}

void ACharacterBase::MoveRight(float amount)
{
	if (Controller != nullptr && amount != 0)
	{
		FVector RightDir = PlayerEye->GetRightVector();
		AddMovementInput(RightDir, amount);
	}
}

void ACharacterBase::Turn(float amount)
{
	AddControllerYawInput(amount);
}

void ACharacterBase::LookUp(float amount)
{
	AddControllerPitchInput(amount);
}

class UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ACharacterBase::InitializeAttributes()
{
	if (AbilitySystemComp && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ACharacterBase::GiveAbilities()
{
	if (AbilitySystemComp)
	{
		for (TSubclassOf<UGameplayAbilityBase>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComp->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>
					(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}
