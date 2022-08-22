// Fill out your copyright notice in the Description page of Project Settings.


#include "ShintoGameModeBase.h"

AShintoGameModeBase::AShintoGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SHINTO_Content/Player/M_CharacterBase"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		//try to find the blueprint of the player
		//PlayerPawnBPClass = 
	}
}