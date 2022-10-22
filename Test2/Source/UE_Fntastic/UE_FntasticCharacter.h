// Copyright kireevroi 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "TurtleButton.h"
#include "UE_FntasticCharacter.generated.h"

UCLASS()
class UE_FNTASTIC_API AUE_FntasticCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AUE_FntasticCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		UCapsuleComponent* TriggerCapsule;

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

	class ATurtleButton* CurrentButton;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void onAction();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
