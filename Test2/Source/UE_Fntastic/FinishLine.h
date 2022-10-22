// Copyright kireevroi 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "TurtleButton.h"
#include "FinishLine.generated.h"

UCLASS()
class UE_FNTASTIC_API AFinishLine : public ATurtleButton
{
	GENERATED_BODY()
	
public:	
	AFinishLine();

	virtual void ToggleStartAction() override;

	UPROPERTY(EditAnywhere, Category = "FinishLine")
		UParticleSystemComponent* particles;

protected:
	virtual void BeginPlay() override;
};
