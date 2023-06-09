// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CrazyArcade : ModuleRules
{
	public CrazyArcade(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara", "OnlineSubsystemSteam", "UMG", "OnlineSubsystem" });
	}
}
