// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorObjectPool.h"


UActorObjectPool::UActorObjectPool() {
	
}

APooledObject* UActorObjectPool::SpawnPooledObject() { 
	for (APooledObject* poolableObj : ObjectsPool) {
		if(poolableObj != nullptr && !poolableObj->IsActive()) {
			poolableObj->TeleportTo(FVector(0,0,0), FRotator(0,0,0));
			poolableObj->SetLifeSpan(PooledObjectLifeSpan);
			poolableObj->SetActive(true);
			SpawnedPoolIndexes.Add(poolableObj->GetPoolIndex());
		
			return poolableObj;	
		}
	}

	if(SpawnedPoolIndexes.Num() > 0) {
		int pooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(pooledObjectIndex);
		APooledObject* poolableActor = ObjectsPool[pooledObjectIndex];

		if(poolableActor == nullptr) return nullptr;
	
		poolableActor->TeleportTo(FVector(0,0,0), FRotator(0,0,0));
		poolableActor->SetLifeSpan(PooledObjectLifeSpan);
		poolableActor->SetActive(true);
		SpawnedPoolIndexes.Add(poolableActor->GetPoolIndex());
		
		return poolableActor;	
	}
		
	return nullptr;
}

void UActorObjectPool::OnPooledObjectDespawn(APooledObject* poolActor) {
	SpawnedPoolIndexes.Remove(poolActor->GetPoolIndex());
}


void UActorObjectPool::BeginPlay() {
	Super::BeginPlay();

	if(PooledObjectSubClass == nullptr) return;

	UWorld* const world = GetWorld();

	if(world == nullptr) return;

	for (int i = 0; i < PoolSize; i++) {
		APooledObject* poolableActor = world->SpawnActor<APooledObject>(PooledObjectSubClass, FVector().ZeroVector, FRotator().ZeroRotator);

		if(poolableActor == nullptr) continue;

		poolableActor->SetActive(false);
		poolableActor->SetPoolIndex(i);
		poolableActor->OnPooledObjectDespawn.AddDynamic(this, &UActorObjectPool::OnPooledObjectDespawn);
		ObjectsPool.Add(poolableActor);
	}
}
