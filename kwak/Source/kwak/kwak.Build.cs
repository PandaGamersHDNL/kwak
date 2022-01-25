// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class kwak : ModuleRules
{
	public kwak(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
