// Copyright kireevroi 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Turtle.h"
#include "TurtleButton.generated.h"

UCLASS()
class UE_FNTASTIC_API ATurtleButton : public AActor
{
	GENERATED_BODY()

public:

	ATurtleButton();

	UFUNCTION(BlueprintCallable, Category = "Button")
		virtual void ToggleStartAction();

	UPROPERTY(EditAnywhere, Category = "Button")
		UAudioComponent* audioComponent;
	UPROPERTY(EditAnywhere, Category = "Button")
		UBoxComponent* collisionBox;
	UPROPERTY(EditAnywhere, Category = "Button")
		USceneComponent* sceneRoot;
	UPROPERTY(EditAnywhere, Category = "Button")
		UStaticMeshComponent* objectComponent;
	UPROPERTY(EditAnywhere, Category = "Button")
		UTextRenderComponent* textComponent;
	UPROPERTY(EditAnywhere, Category = "Button")
		TSubclassOf<ATurtle> actorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Button")
		float actorSpeed;
	UPROPERTY(EditAnywhere, Category = "Button")
		float actorBackSpeed;
	UPROPERTY(EditAnywhere, Category = "Button")
		float actorGoTime;
	UPROPERTY(EditAnywhere, Category = "Button")
		float actorBackTime;

protected:
	virtual void BeginPlay() override;

	void Spawn(FVector location, FQuat rotation);

	int maxSpawn;
	FVector initLocation;
	float speed;
	float distance;
	bool btnPressed;
	int direction;

public:
	virtual void Tick(float DeltaTime) override;

};
