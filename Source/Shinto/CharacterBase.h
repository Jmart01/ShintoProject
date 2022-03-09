#pragma once
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterBase.generated.h"
UCLASS()
class SHINTO_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ACharacterBase();

	//virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//TSubclassOf<class UMainInGameUI> InGameUIClass;


	//UFUNCTION()
		//void SpawnInGameUI();

	//Components that will be attached to the character base
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* PlayerEyeSpringArm;
	UCameraComponent* PlayerEye;

	//functions that deal with movement
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float amount);
	void MoveRight(float amount);
	void Turn(float amount);
	void LookUp(float amount);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	

};
