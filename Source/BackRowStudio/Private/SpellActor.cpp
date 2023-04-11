// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellActor.h"

void ISpellActor::InternalDebugSpell(const ESpellType type, const FVector range, const float radius, const FVector origin, const FRotator rotation, const UWorld *world) const
{
    const auto location = origin + rotation.RotateVector(range);
    const auto left = rotation + FRotator(0, -radius / 2, 0);
    const auto right = left + FRotator(0, radius, 0);
    const auto coneSectionSize = 500 / range.X * 2.5;
    const FRotator section = FRotator(0, coneSectionSize, 0);
    const auto leftVector = left.RotateVector(range);
    const auto rightVector = right.RotateVector(range);
    const auto widthOffset = (rotation + FRotator(0, 90, 0)).RotateVector(FVector(radius, 0, 0));
    const auto widthOffsetIncrement = widthOffset / (radius / 10);
    const auto sectionSize = 500 / radius * 2.5;
    const FRotator circleSection = FRotator(0, sectionSize, 0);
    auto leftOuter = origin + leftVector;
    switch (type)
    {
    case ESpellType::Circle:
        for (int i = 0; i < 360 / circleSection.Yaw; ++i)
        {
            DrawDebugLine(world, location, location + (circleSection * i).RotateVector(FVector(radius, 0, 0)), FColor::Red, false, 60, 0, 1);
        }
        break;
    case ESpellType::Cone:
        DrawDebugLine(world, origin, origin + leftVector, FColor::Red, false, 60, 0, 1.f);
        DrawDebugLine(world, origin, origin + rightVector, FColor::Red, false, 60, 0, 1.f);
        for (int i = 0; i < (right - left).Yaw / coneSectionSize - 1; ++i)
        {
            auto rightPos = origin + (left + section * (i + 1)).RotateVector(range);
            DrawDebugLine(world, origin, rightPos, FColor::Red, false, 60, 0, 1.f);
            DrawDebugLine(world, leftOuter, rightPos, FColor::Red, false, 60, 0, 1.f);
            leftOuter = rightPos;
        }
        break;
    case ESpellType::Line:
        for (int i = 0; i < widthOffset.Size() / widthOffsetIncrement.Size(); ++i)
        {
            DrawDebugLine(world, origin + widthOffsetIncrement * (i + 1), location + widthOffsetIncrement * (i + 1), FColor::Red, false, 60);
            DrawDebugLine(world, origin - widthOffsetIncrement * (i + 1), location - widthOffsetIncrement * (i + 1), FColor::Red, false, 60);
        }
        DrawDebugLine(world, origin, location, FColor::Red, false, 60);
        DrawDebugLine(world, origin + widthOffset, origin - widthOffset, FColor::Red, false, 60);
        DrawDebugLine(world, origin + widthOffset, location + widthOffset, FColor::Red, false, 60);
        DrawDebugLine(world, origin - widthOffset, location - widthOffset, FColor::Red, false, 60);
        DrawDebugLine(world, location + widthOffset, location - widthOffset, FColor::Red, false, 60);
    }
}

TArray<AActor *> ISpellActor::GetActors(ESpellType type, const FVector range, const float radius, const FVector origin, const FRotator rotation, UWorld *world) const
{
    TArray<FHitResult> OutHits;
    TArray<FHitResult> OutHits2;
    TArray<AActor *> OutActors;
    const auto location = origin + rotation.RotateVector(range);
    const auto left = rotation + FRotator(0, -radius / 2, 0);
    const auto right = left + FRotator(0, radius, 0);
    const auto coneSectionSize = 500 / range.X * 2.5;
    const FRotator section = FRotator(0, coneSectionSize, 0);
    const auto leftVector = left.RotateVector(range);
    const auto rightVector = right.RotateVector(range);
    const auto widthOffset = (rotation + FRotator(0, 90, 0)).RotateVector(FVector(radius, 0, 0));
    const auto widthOffsetIncrement = widthOffset / (radius / 10);
    const auto boxHit = FCollisionShape::MakeBox(FVector(5, 5, 5));
    const auto sectionSize = 500 / radius * 2.5;
    const FRotator circleSection = FRotator(0, sectionSize, 0);
    bool isHit;
    switch (type)
    {
    case ESpellType::Circle:
        for(int i = 0; i < 360 / circleSection.Yaw; ++i)
        {
            isHit = world->SweepMultiByChannel(OutHits, location, location + (circleSection * i).RotateVector(FVector(radius, 0, 0)), FQuat::Identity, ECC_Visibility, boxHit) || isHit;
            OutHits2.Append(OutHits);
        }
        break;
    case ESpellType::Cone:
        isHit = world->SweepMultiByChannel(OutHits, origin, origin + leftVector, FQuat::Identity, ECC_Visibility, boxHit);
        OutHits2 = OutHits;
        isHit = world->SweepMultiByChannel(OutHits, origin, origin + rightVector, FQuat::Identity, ECC_Visibility, boxHit) || isHit;
        OutHits2.Append(OutHits);
        for (int i = 0; i < (right - left).Yaw / coneSectionSize - 1; ++i)
        {
            auto rightPos = origin + (left + section * (i + 1)).RotateVector(range);
            isHit = world->SweepMultiByChannel(OutHits, origin, rightPos, FQuat::Identity, ECC_Visibility, boxHit) || isHit;
            OutHits2.Append(OutHits);
        }
        break;
    case ESpellType::Line:
        for (int i = 0; i < widthOffset.Size() / widthOffsetIncrement.Size(); ++i)
        {
            isHit = world->SweepMultiByChannel(OutHits, origin + widthOffsetIncrement * (i + 1), location + widthOffsetIncrement * (i + 1), FQuat::Identity, ECC_Visibility, boxHit);
            OutHits2.Append(OutHits);
            isHit = world->SweepMultiByChannel(OutHits, origin - widthOffsetIncrement * (i + 1), location - widthOffsetIncrement * (i + 1), FQuat::Identity, ECC_Visibility, boxHit) || isHit;
            OutHits2.Append(OutHits);
        }
        isHit = world->SweepMultiByChannel(OutHits, origin, location, FQuat::Identity, ECC_Visibility, boxHit) || isHit;
        OutHits2.Append(OutHits);
        isHit = world->SweepMultiByChannel(OutHits, origin + widthOffset, origin - widthOffset, FQuat::Identity, ECC_Visibility, boxHit) || isHit;
        OutHits2.Append(OutHits);
        isHit = world->SweepMultiByChannel(OutHits, origin + widthOffset, location + widthOffset, FQuat::Identity, ECC_Visibility, boxHit) || isHit;
        OutHits2.Append(OutHits);
    }

    for (FHitResult hitResult : OutHits2)
    {
        OutActors.AddUnique(hitResult.GetActor());
    }

    if (isHit)
    {
        
    }
}

void ISpellActor::CastSpell(const FVector origin, const FRotator rotation, UWorld *world, const bool is_heavy)
{
    TArray<AActor *> actors;

    if (is_heavy)
    {
        HeavyAttack(origin, rotation, world, actors);
    }
    else
    {
        LightAttack(origin, rotation, world, actors);
    }
}

void ISpellActor::DebugSpell(const FVector origin, const FRotator rotation, const UWorld *world) const
{
    if (Spell.DebugHeavy)
        InternalDebugSpell(Spell.Heavy.Type, Spell.Heavy.Range, Spell.Heavy.Radius, origin, rotation, world);
    if (Spell.DebugLight)
        InternalDebugSpell(Spell.Light.Type, Spell.Light.Range, Spell.Light.Radius, origin, rotation, world);
}

void ISpellActor::LightAttack(FVector origin, FRotator rotation, UWorld *world, TArray<AActor *> &actors) { actors = GetActors(Spell.Light.Type, Spell.Light.Range, Spell.Light.Radius, origin, rotation, world); }

void ISpellActor::HeavyAttack(FVector origin, FRotator rotation, UWorld *world, TArray<AActor *> &actors) { actors = GetActors(Spell.Heavy.Type, Spell.Heavy.Range, Spell.Heavy.Radius, origin, rotation, world); }
