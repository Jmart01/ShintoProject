#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CharacterBase.h"
#include "AIModule/Classes/Navigation/CrowdFollowingComponent.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHINTO_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyAIController();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTree* BehaviorTreeToUse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UAIPerceptionComponent* PerceptionComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Perception")
		UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPathFollowingComponent* PathFollowingComp;
		
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* PawnToPossess) override;
	
	UFUNCTION()
		void PerceptionUpdated(AActor* Target, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
	float AISightRadius = 2500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
		float AILoseSightRadius = 50000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
		float AISightAngle = 90.f;

	//float DistanceToPlayer;

};
