// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);

UCLASS()
class RETROFPS_API APooledObject : public AActor {
	GENERATED_BODY()
	
public:	

	APooledObject();

	FOnPooledObjectDespawn OnPooledObjectDespawn;
	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
		void Deactivate();
	
	void SetActive(bool isActive);
	void SetLifeSpan(float lifeTime);
	void SetPoolIndex(int index);

	bool IsActive() const;
	int GetPoolIndex() const;
	
protected:
	float m_lifeSpan = 0.0f;
	int m_poolIndex;
	bool m_isActive;

	FTimerHandle m_lifeSpanTimer;
};
