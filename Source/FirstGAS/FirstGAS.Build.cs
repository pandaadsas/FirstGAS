// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstGAS : ModuleRules
{
	public FirstGAS(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
		});

		PublicIncludePaths.AddRange(new string[] {
			"FirstGAS",
			"FirstGAS/Variant_Platforming",
			"FirstGAS/Variant_Platforming/Animation",
			"FirstGAS/Variant_Combat",
			"FirstGAS/Variant_Combat/AI",
			"FirstGAS/Variant_Combat/Animation",
			"FirstGAS/Variant_Combat/Gameplay",
			"FirstGAS/Variant_Combat/Interfaces",
			"FirstGAS/Variant_Combat/UI",
			"FirstGAS/Variant_SideScrolling",
			"FirstGAS/Variant_SideScrolling/AI",
			"FirstGAS/Variant_SideScrolling/Gameplay",
			"FirstGAS/Variant_SideScrolling/Interfaces",
			"FirstGAS/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
