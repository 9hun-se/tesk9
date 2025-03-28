// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tesk9 : ModuleRules
{
	public Tesk9(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","UMG", "Slate", "SlateCore", });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { "Tesk9" });

    }
}
