// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

APooledObject::APooledObject() {

}

void APooledObject::Deactivate() {
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}

void APooledObject::SetActive(bool isActive) {
	m_isActive = isActive;
	SetActorHiddenInGame(!m_isActive);
	GetWorldTimerManager().SetTimer(m_lifeSpanTimer, this, &APooledObject::Deactivate, m_lifeSpan, false);
}

void APooledObject::SetLifeSpan(float lifeTime) {
	m_lifeSpan = lifeTime;
}

void APooledObject::SetPoolIndex(int index) {
	m_poolIndex = index;
}

bool APooledObject::IsActive() const {
	return m_isActive;
}

int APooledObject::GetPoolIndex() const {
	return m_poolIndex;
}

