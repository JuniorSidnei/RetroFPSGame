// Fill out your copyright notice in the Description page of Project Settings.


#include "RetroFPSAttributeSet.h"

#include "RetroFPSCharacter.h"

URetroFPSAttributeSet::URetroFPSAttributeSet()
{
}

void URetroFPSAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	ARetroFPSCharacter* retroChar = Cast<ARetroFPSCharacter>(GetOwningActor());

	if(Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0, retroChar->maxHealth);
	} else if(Attribute == GetArmorAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0, retroChar->maxArmor);
	} else if (Attribute == GetPistolAmmoAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0, retroChar->maxPistolAmmo);
	} else if(Attribute == GetRocketAmmoAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0, retroChar->maxRocketsAmmo);
	}
}

bool URetroFPSAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) {
	float dataMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	ARetroFPSCharacter* retroChar = Cast<ARetroFPSCharacter>(GetOwningActor());
	
	if(Data.EvaluatedData.Magnitude > 0) {
		if(Data.EvaluatedData.Attribute == GetArmorAttribute()) {
			if(GetArmor() + dataMagnitude >= retroChar->maxArmor) {
				SetArmor(retroChar->maxArmor);
				return false;
			}
			
			SetArmor(dataMagnitude);
			return true;
		}

		if(Data.EvaluatedData.Attribute == GetHealthAttribute()) {
			if(GetHealth() + dataMagnitude >= retroChar->maxHealth) {
				SetHealth(retroChar->maxHealth);
				return false;
			}

			SetHealth(dataMagnitude);
			return true;
		}

		if(Data.EvaluatedData.Attribute == GetPistolAmmoAttribute()) {
			if(GetPistolAmmo() + dataMagnitude >= retroChar->maxPistolAmmo) {
				SetPistolAmmo(retroChar->maxPistolAmmo);
				return false;
			}
			
			SetHealth(dataMagnitude);
			return true;
		}

		if(Data.EvaluatedData.Attribute == GetRocketAmmoAttribute()) {
			if(GetRocketAmmo() + dataMagnitude >= retroChar->maxRocketsAmmo) {
				SetRocketAmmo(retroChar->maxRocketsAmmo);
				return false;
			}
			
			SetRocketAmmo(dataMagnitude);
			return true;
		}
	}
	else if(Data.EvaluatedData.Attribute == GetArmorAttribute() && dataMagnitude > GetArmor()) {
		Health.SetCurrentValue(Health.GetCurrentValue() - (dataMagnitude - GetArmor()));
	}
	
	return true;
}

void URetroFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	
	if(Attribute == GetHealthAttribute() && GetHealth() < 0) {
		SetHealth(0);
	} else if(Attribute == GetArmorAttribute() && GetArmor() < 0) {
		SetArmor(0);
	} else if (Attribute == GetPistolAmmoAttribute() && GetPistolAmmo() < 0) {
		SetPistolAmmo(0);
	} else if(Attribute == GetRocketAmmoAttribute() && GetRocketAmmo() < 0) {
		SetRocketAmmo(0);
	}
}
