// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class MyProject : ModuleRules
{
	public MyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        string ThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty/");
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "TinyXML2"));

        //PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "TinyXML2", "tinyxml2.cpp"));

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "XmlParser" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
