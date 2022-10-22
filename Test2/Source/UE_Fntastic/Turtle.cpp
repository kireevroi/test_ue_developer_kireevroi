// Copyright kireevroi 2022

#include "Turtle.h"
#include "FinishLine.h"

ATurtle::ATurtle() {
 	PrimaryActorTick.bCanEverTick = true;
	
	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene root"));
	RootComponent = sceneRoot;

	collisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	collisionBox->InitBoxExtent(FVector(40., 40., 40.));
	collisionBox->AttachToComponent(sceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->AttachToComponent(sceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	mesh->SetSimulatePhysics(false);

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Start Queue"));
	audioComponent->AttachToComponent(sceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	audioComponent->bAutoActivate = false;

	deadAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Death Queue"));
	deadAudioComponent->AttachToComponent(sceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	deadAudioComponent->bAutoActivate = false;
	
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATurtle::OnOverlapBegin);
	collisionBox->OnComponentEndOverlap.AddDynamic(this, &ATurtle::OnOverlapEnd);

	actorSpeed = 100;
	actorBackSpeed = 100;
	actorGoTime = 10;
	actorBackTime = 1;
	currentOverlap = nullptr;
	Anim_Walk = nullptr;
	Anim_Die = nullptr;
}


void ATurtle::BeginPlay() {
	Super::BeginPlay();

	direction = -1;
	finished = false;
	speed = actorSpeed;

	audioComponent->Play();
	Move();
}

void ATurtle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!finished) {
		FVector location = GetActorLocation();
		location += GetActorForwardVector() * speed * direction * DeltaTime;
		SetActorLocation(location);
	}
}

void ATurtle::Move() {
	direction *= -1;
	speed = direction > 0 ? actorSpeed : actorBackSpeed;
	if (!finished) {
		if (Anim_Walk && speed > 0)
			mesh->PlayAnimation(Anim_Walk, false);
		if (direction > 0) {
			GetWorldTimerManager().SetTimer(timer, this, &ATurtle::Move, actorGoTime, false);
		}
		else {
			if (actorBackTime > 0) {
				GetWorldTimerManager().SetTimer(timer, this, &ATurtle::Move, actorBackTime, false);
			}
			else {
				direction = -1;
				Move();
			}
		}
	}
}

void ATurtle::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
							 class AActor* OtherActor,
							 class UPrimitiveComponent* OtherComp,
							 int32 OtherBodyIndex,
							 bool bFromSweep,
							 const FHitResult& SweepResult) {

	if (OtherActor && (OtherActor != this) &&
		OtherComp->GetClass()->IsChildOf(UBoxComponent::StaticClass()) &&
		OtherActor->GetClass()->IsChildOf(AFinishLine::StaticClass())) {

		currentOverlap = Cast<AFinishLine>(OtherActor);
		currentOverlap->ToggleStartAction();
		if (Anim_Die)
			mesh->PlayAnimation(Anim_Die, false);
		deadAudioComponent->Play();
		audioComponent->Stop();
		SetLifeSpan(5);
		finished = 1;
	}
}


void ATurtle::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
						   class AActor* OtherActor,
						   class UPrimitiveComponent* OtherComp,
						   int32 OtherBodyIndex) {

	if (OtherActor && (OtherActor != this) && OtherComp) {
		currentOverlap = NULL;
	}
}