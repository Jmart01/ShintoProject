// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


AMyAIController::AMyAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig && PerceptionComp)
	{
		SightConfig->SightRadius = 2500.f;
		SightConfig->LoseSightRadius = 50000.f;
		SightConfig->PeripheralVisionAngleDegrees = 60.f;

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		
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

void AMyAIController::PerceptionUpdated(AActor* Target, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		auto ExistingTarget = GetBlackboardComponent()->GetValueAsObject(FName("Target"));
		UAISenseConfig* StimulusConfig = PerceptionComp->GetSenseConfig(Stimulus.Type);
		if (!ExistingTarget || StimulusConfig->GetClass() == UAISenseConfig_Sight::StaticClass())
		{
			//working on the team affiliation, resume the video at 1:35
			GetBlackboardComponent()->SetValueAsObject(FName("Target"), Target);
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
