// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BackRowStudio : ModuleRules
{
    public BackRowStudio(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        ShadowVariableWarningLevel = WarningLevel.Off;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "HeadMountedDisplay", 
            "EnhancedInput", 
            "Niagara", 
            "GameplayAbilities", 
            "GameplayTags", 
            "GameplayTasks", 
            "UMG", 
            "Slate", 
            "SlateCore",
            "AiModule",
            "NavigationSystem"
        });
    }

}