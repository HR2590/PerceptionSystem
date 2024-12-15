// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TareaPercepcion : ModuleRules
{
	public TareaPercepcion(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"});
		PublicIncludePaths.Add(ModuleDirectory);
		PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd","ComponentVisualizers"});
	}
}
