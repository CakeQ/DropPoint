// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbilityTest.h"
#include "DropPointUnit.h"

UDropPointAbilityTest::UDropPointAbilityTest()
{

}

void UDropPointAbilityTest::Trigger(ADropPointUnit* Owner)
{
	Super::Trigger(Owner);

	Owner->ChangeMaterial(TestMaterial);
}