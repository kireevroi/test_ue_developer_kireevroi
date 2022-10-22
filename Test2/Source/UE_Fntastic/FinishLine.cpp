// Copyright kireevroi 2022

#include "FinishLine.h"

AFinishLine::AFinishLine() {
	collisionBox->InitBoxExtent(FVector(100., 100., 100.));
	particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	particles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	particles->SetRelativeLocation(FVector(0.0f, 280.0f, 460.0f));
	particles->bAutoActivate = false;
	textComponent->DestroyComponent();

}

void AFinishLine::BeginPlay() {
	Super::BeginPlay();
}

void AFinishLine::ToggleStartAction() {
	particles->ActivateSystem();
}