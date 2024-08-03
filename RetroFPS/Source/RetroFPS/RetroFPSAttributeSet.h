#pragma once

#include <CoreMinimal.h>
#include <AttributeSet.h>
#include <AbilitySystemComponent.h>
#include "GameplayEffectExtension.h"
#include "RetroFPSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



UCLASS() 
class RETROFPS_API URetroFPSAttributeSet : public UAttributeSet {
	GENERATED_BODY()
	
public:
	URetroFPSAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URetroFPSAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(URetroFPSAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData PistolAmmo;
	ATTRIBUTE_ACCESSORS(URetroFPSAttributeSet, PistolAmmo);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData RocketAmmo;
	ATTRIBUTE_ACCESSORS(URetroFPSAttributeSet, RocketAmmo);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};