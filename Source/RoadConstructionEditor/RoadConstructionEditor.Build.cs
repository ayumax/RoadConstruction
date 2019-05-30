// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class RoadConstructionEditor : ModuleRules
{
	public RoadConstructionEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            });

        PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "AssetTools",
                    "EditorStyle",
                    "MainFrame",
                    "MeshDescription",
                    "MeshDescriptionOperations",
                    "RawMesh",
                    "Slate",
                    "SlateCore",
                    "UnrealEd",
                    "MeshMergeUtilities",
                    "EditorScriptingUtilities",
                    "AssetRegistry",
                    "ContentBrowser"
                }
            );
    }
}
