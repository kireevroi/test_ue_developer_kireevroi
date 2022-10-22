// Copyright kireevroi 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimSequence.h"
#include "Turtle.generated.h"

UCLASS()
class UE_FNTASTIC_API ATurtle : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurtle();

	UPROPERTY(EditAnywhere, Category = "Turtle")
		UAudioComponent* audioComponent;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		UAudioComponent* deadAudioComponent;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		USceneComponent* sceneRoot;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		USkeletalMeshComponent* mesh;
	UPROPERTY(EditAnywhere, Category = "Button")
		UBoxComponent* collisionBox;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		UAnimSequence* Anim_Walk;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		UAnimSequence* Anim_Die;

	UPROPERTY(EditAnywhere, Category = "Turtle")
		float actorSpeed;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		float actorBackSpeed;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		float actorGoTime;
	UPROPERTY(EditAnywhere, Category = "Turtle")
		float actorBackTime;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
							class AActor* OtherActor,
							class UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex,
							bool bFromSweep,
							const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
						  class AActor* OtherActor,
						  class UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex);
	
	class AFinishLine *currentOverlap;

protected:
	virtual void BeginPlay() override;

	void Move();

	FTimerHandle timer;
	float speed;
	int direction;
	bool finished;
	
public:	
	virtual void Tick(float DeltaTime) override;
};
