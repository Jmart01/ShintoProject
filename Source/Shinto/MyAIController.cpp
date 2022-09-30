// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"


AMyAIController::AMyAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig && PerceptionComp)
	{
		SightConfig->SightRadius = AISightRadius;
		SightConfig->LoseSightRadius = AILoseSightRadius;
		SightConfig->PeripheralVisionAngleDegrees = AISightAngle;

		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		//GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		//GetPerceptionComponent()->ConfigureSense(*SightConfig);
		PerceptionComp->SetDominantSense(*SightConfig->GetSenseImplementation());
		PerceptionComp->ConfigureSense(*SightConfig);
	}
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::PerceptionUpdated);
	}
	if(BehaviorTreeToUse)
	{
		RunBehaviorTree(BehaviorTreeToUse);
	}

}

void AMyAIController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);
}


void AMyAIController::PerceptionUpdated(AActor* Target, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		auto ExistingTarget = GetBlackboardComponent()->GetValueAsObject(FName("Target"));
		UAISenseConfig* StimulusConfig = PerceptionComp->GetSenseConfig(Stimulus.Type);
		if (!ExistingTarget || StimulusConfig->GetClass() == UAISenseConfig_Sight::StaticClass())
		{
			UE_LOG(LogTemp, Warning, TEXT("Detected Something"));
			if (Target == Cast<ACharacterBase, AActor>(Target))
			{
				UE_LOG(LogTemp, Warning, TEXT("Tareget is the player"));
				GetBlackboardComponent()->SetValueAsObject(FName("Target"), Target);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Not detecting player"));
			}
			
		}
		else
		{
			TArray<AActor*> ActorInSight;
			PerceptionComp->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), ActorInSight);
			if (ActorInSight.Num() == 0)
			{
				GetBlackboardComponent()->ClearValue(FName("Target"));
			}
		}
	}
}
