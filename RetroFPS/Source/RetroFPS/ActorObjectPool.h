// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PooledObject.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorObjectPool.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETROFPS_API UActorObjectPool : public UActorComponent {
	GENERATED_BODY()

public:	
	UActorObjectPool();

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
		APooledObject* SpawnPooledObject();

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		TSubclassOf<class APooledObject> PooledObjectSubClass;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		int PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		float PooledObjectLifeSpan = 0.0f;

	UFUNCTION()
		void OnPooledObjectDespawn(APooledObject* poolActor);
	
protected:
	virtual void BeginPlay() override;

	TArray<APooledObject*> ObjectsPool;
	TArray<int> SpawnedPoolIndexes;
};
