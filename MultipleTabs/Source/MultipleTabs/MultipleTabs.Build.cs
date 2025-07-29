// Some copyright should be here...

using UnrealBuildTool;
using System.Collections.Generic;

public class MultipleTabs : ModuleRules
{
	public MultipleTabs(ReadOnlyTargetRules Target) : base(Target)
	{
		//PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		//PrivateIncludePaths.AddRange(
		//	new string[] {
		//		// ... add other private include paths required here ...
  //              Path.Combine(EngineDirectory, "Source", "Editor"),
  //          }
		//	);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{

                "Core",
                "UnrealEd",
                "ContentBrowser",
                
                ////"ApplicationCore", "Renderer", "RenderCore", "RHI", "ImageWrapper" ,

                //"Engine",
                //"CoreUObject",
                //"Slate",
                //"SlateCore",
                //"EditorStyle",
                //"CommonMenuExtensions",
                //"ToolMenus",
                //"DeveloperSettings",
                //"Projects",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Engine",
                "CoreUObject",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "CommonMenuExtensions",
                "ToolMenus",
                "PropertyPath",
                "DeveloperSettings",
                "Projects",
                "PropertyEditor",
                //"LevelEditor",
                //"WorkspaceMenuStructure",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

//        PublicIncludePaths.AddRange(
//            new string[]
//            {
////#if UE_5_2_OR_LATER
//                // In UHT for UE5.2 and later, when you use PublicIncludePaths, the base path of the module's include will be replaced with the first value, so add the correct base path of the include first.
//                Path.Combine(ModuleDirectory, ".."),
//				//Path.Combine(ModuleDirectory, "Source", "Editor", "LevelEditor", "Private"),
////#endif
//                // To use SDetailsView.
//                Path.Combine(EngineDirectory, "Source", "Editor", "PropertyEditor", "Private"),

//                // To use SActorDetails.
//                Path.Combine(EngineDirectory, "Source", "Editor", "LevelEditor", "Private"),
//            }
//        );
    }
}
