// Copyright kireevroi 2022

#include "TurtleButton.h"

ATurtleButton::ATurtleButton() {
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = sceneRoot;

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	collisionBox->InitBoxExtent(FVector(40., 40., 40.));
	collisionBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	objectComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	objectComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Button Press"));
	audioComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	audioComponent->bAutoActivate = false;

	textComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	textComponent->AttachToComponent(objectComponent, FAttachmentTransformRules::KeepRelativeTransform);
	textComponent->SetTextRenderColor(FColor::Red);
	textComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	textComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));
	textComponent->SetXScale(3.f);
	textComponent->SetYScale(5.f);
	textComponent->SetHorizontalAlignment(EHTA_Center);
	textComponent->SetVerticalAlignment(EVRTA_TextCenter);
	
	actorSpeed = 100;
	actorBackSpeed = 100;
	actorGoTime = 10;
	actorBackTime = 1;
	actorToSpawn = nullptr;

}

void ATurtleButton::BeginPlay() {
	Super::BeginPlay();
	initLocation = GetActorLocation();
	maxSpawn = 3;
	btnPressed = false;
	speed = 30;
	distance = 10;
	direction = 1;
}

void ATurtleButton::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector location = GetActorLocation();
	if (btnPressed && direction == 1) {
		location -= GetActorUpVector() * speed * DeltaTime;
		SetActorLocation(location);
	}
	else if (btnPressed && direction == -1) {
		location += GetActorUpVector() * speed * DeltaTime;
		SetActorLocation(location);
	}
	if (initLocation.Z - location.Z >= 10)
		direction = -1;
	if (initLocation.Z - location.Z <= 0 && direction == -1) {
		btnPressed = false;
		direction = 1;
	}
}

void ATurtleButton::ToggleStartAction() {
	FVector location = GetActorLocation();
	location.Set(location.X + 100., location.Y, location.Z);
	FQuat rotation = GetActorRotation().Quaternion();
	btnPressed = true;
	audioComponent->Play();
	Spawn(location, rotation);
	maxSpawn--;
}

void ATurtleButton::Spawn(FVector location, FQuat rotation) {
	FTransform transform;
	transform.SetLocation(location);
	transform.SetRotation(rotation);
	if (actorToSpawn && maxSpawn > 0) {
		ATurtle* spawn = GetWorld()->SpawnActorDeferred<ATurtle>(actorToSpawn, transform);
		spawn->actorSpeed = actorSpeed;
		spawn->actorBackSpeed = actorBackSpeed;
		spawn->actorGoTime = actorGoTime;
		spawn->actorBackTime = actorBackTime;
		UGameplayStatics::FinishSpawningActor(spawn, transform);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ACTOR NOT SELECTED\nOR SPAWN LIMIT REACHED"));
	}
}

