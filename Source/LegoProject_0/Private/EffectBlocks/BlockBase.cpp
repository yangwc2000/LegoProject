// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBlocks/BlockBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root Component(Scene Component)
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComp);

	// Box Component
	BoxColliderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxColliderComp->SetupAttachment(SceneComp);
	BoxColliderComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BoxColliderComp->OnComponentBeginOverlap.AddDynamic(this, &ABlockBase::OnCharacterOverlap);
	BoxColliderComp->OnComponentEndOverlap.AddDynamic(this, &ABlockBase::OnCharacterEndOverlap);
	
	// Static Mesh Component
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComp->SetupAttachment(SceneComp);
}

// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockBase::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABlockBase::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABlockBase::ApplyEffect(ACharacter* Target)
{

}

