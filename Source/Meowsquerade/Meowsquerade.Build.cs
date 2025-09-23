// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Meowsquerade : ModuleRules
{
	public Meowsquerade(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Meowsquerade",
			"Meowsquerade/Variant_Horror",
			"Meowsquerade/Variant_Horror/UI",
			"Meowsquerade/Variant_Shooter",
			"Meowsquerade/Variant_Shooter/AI",
			"Meowsquerade/Variant_Shooter/UI",
			"Meowsquerade/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
