#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CharacterBase.h"
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
	virtual void BeginPlay() override;
	UFUNCTION()
		void PerceptionUpdated(AActor* Target, FAIStimulus Stimulus);

	
};
