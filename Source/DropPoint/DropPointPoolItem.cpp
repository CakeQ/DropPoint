// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointPoolItem.h"

float FDropPointPoolItem::GetWeight(const int32& CurrentDistance)
{
    float ReturnWeight = BaseWeight;
    for (FDropPointPoolBonus& Bonus : BonusWeights)
    {
        ReturnWeight += Bonus.GetLocationBonus(CurrentDistance);
    }
    return FMath::Max(0.0f, ReturnWeight);
}