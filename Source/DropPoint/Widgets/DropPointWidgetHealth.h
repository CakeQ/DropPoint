// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetHealth.generated.h"

/**
 * 
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetHealth : public UUserWidget
{
	GENERATED_BODY()

protected:
	/** The texture to use when active. */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
    class UTexture2D* TextureOn;

	/** The texture to use when inactive. */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
    class UTexture2D* TextureOff;

	/** The current image displayed. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
    class UImage* Image_Status;

public:
    void SetState(bool bOn);
};
