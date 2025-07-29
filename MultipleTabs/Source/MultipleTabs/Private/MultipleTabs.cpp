// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultipleTabs.h"
#define LOCTEXT_NAMESPACE "FMultipleTabsModule"

void FMultipleTabsModule::StartupModule()
{
	/*if (const UMultipleTabsSettings& CurSettings = GetDefault<UMultipleTabsSettings>())
	{
		CurSettings.ChangedContent();
		CurSettings.ChangedDetail();
		CurSettings.ChangedViewport();
	}*/
	
}

void FMultipleTabsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMultipleTabsModule, MultipleTabs)