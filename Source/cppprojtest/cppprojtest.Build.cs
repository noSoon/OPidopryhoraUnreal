// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class cppprojtest : ModuleRules
{
	public cppprojtest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
