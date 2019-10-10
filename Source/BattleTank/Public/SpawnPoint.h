// Copyright Bradley Olson

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

class AActor;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

private:	
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;

	AActor* NewActor;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor() const;
};
