// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultipleTabsSettings.h"
#include "IContentBrowserSingleton.h"
#include "Framework/Docking/WorkspaceItem.h"
#include "WorkspaceMenuStructureModule.h"
#include "WorkspaceMenuStructure.h"
#include "TutorialMetaData.h"
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#include "ContentBrowserModule.h"
#include "Engine/Selection.h"
//#include "SActorDetails.h"


UMultipleTabsSettings::UMultipleTabsSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ChangedContent();
	ChangedDetail();
	ChangedViewport();
}

void UMultipleTabsSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.MemberProperty)
	{
		if (PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UMultipleTabsSettings, ContentBrowserNumber))
		{
			ChangedContent();
		}
		else if (PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UMultipleTabsSettings, DetailNumber))
		{
			ChangedDetail();
		}
		else if (PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UMultipleTabsSettings, ViewportNumber))
		{
			ChangedViewport();
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}



void UMultipleTabsSettings::ChangedContent()
{
	IContentBrowserSingleton& CurContentBrowserSingleton = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser").Get();
	const FSlateIcon ContentBrowserIcon(FEditorStyle::GetStyleSetName(), "ContentBrowser.TabIcon");
	const IWorkspaceMenuStructure& MenuStructure = WorkspaceMenu::GetMenuStructure();
	FText InDisplayName = FText::FromString(TEXT("Custom Content Browser "));
	FText InTooltipText = FText::FromString(TEXT("Open a Custom Content Browser tab"));
	TSharedRef<FWorkspaceItem> ContentBrowserGroup = MenuStructure.GetToolsCategory()->AddGroup(
		InDisplayName,
		InTooltipText,
		ContentBrowserIcon,
		true);
	for (int32 BrowserIdx = 0; BrowserIdx < 101; BrowserIdx++)
	{
		const FName TabID = FName(*FString::Printf(TEXT("ContentBrowserTab%d"), BrowserIdx + 5));
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabID);
	}
	for (int32 BrowserIdx = 0; BrowserIdx < ContentBrowserNumber; BrowserIdx++)
	{
		const FName TabID = FName(*FString::Printf(TEXT("ContentBrowserTab%d"), BrowserIdx + 5));

		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabID, FOnSpawnTab::CreateLambda([&, BrowserIdx](const FSpawnTabArgs& SpawnTabArgs)
			{
				TSharedRef<SDockTab> NewTab = SNew(SDockTab)
					.TabRole(ETabRole::NomadTab)
					.Label(FText::FromString(FString::Printf(TEXT("ContentBrowser%d"), BrowserIdx + 5)));

				TSharedRef<SWidget> NewBrowser = CurContentBrowserSingleton.CreateContentBrowser(SpawnTabArgs.GetTabId().TabType, NewTab, nullptr);
				TSharedRef<SBox> Wrapper =
					SNew(SBox)
					.AddMetaData<FTutorialMetaData>(FTutorialMetaData(TEXT("ContentBrowser"), TEXT("ContentBrowserTab1")))
					[
						NewBrowser
					];

				NewTab->SetContent(Wrapper);

				return NewTab;
			}))
			.SetDisplayName(FText::FromString(FString::Printf(TEXT("ContentBrowser %d"), BrowserIdx + 5)))
				.SetTooltipText(FText::FromString("Open a Content Browser tab."))
				.SetGroup(ContentBrowserGroup)
				.SetIcon(ContentBrowserIcon);
	}
}

void UMultipleTabsSettings::ChangedDetail()
{
	const FName LevelEditorModuleName("LevelEditor");
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(LevelEditorModuleName);
	TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();

	const FSlateIcon DetailsIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details");
	const IWorkspaceMenuStructure& MenuStructure = WorkspaceMenu::GetMenuStructure();
	FText InDisplayName = FText::FromString(TEXT("Custom Details "));
	FText InTooltipText = FText::FromString(TEXT("Open a Custom Details tab"));
	TSharedRef<FWorkspaceItem> WorkspaceItem = MenuStructure.GetToolsCategory()->AddGroup(
		InDisplayName,
		InTooltipText,
		DetailsIcon,
		true);
	for (int32 BrowserIdx = 0; BrowserIdx < 101; BrowserIdx++)
	{
		const FName TabID = FName(*FString::Printf(TEXT("CustomnDetails%d"), BrowserIdx + 5));
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabID);
	}

	for (int32 BrowserIdx = 0; BrowserIdx < DetailNumber; BrowserIdx++)
	{
		const FName TabID = FName(*FString::Printf(TEXT("CustomnDetails%d"), BrowserIdx + 5));
		LevelEditorTabManager->RegisterTabSpawner(TabID, FOnSpawnTab::CreateLambda([&, TabID](const FSpawnTabArgs& SpawnTabArgs)
			{
				TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveLevelViewport();
				if (!ActiveLevelViewport.IsValid())
				{
					return SNew(SDockTab);
				}
				TSharedRef<SDockTab> DetailsPanel = SummonDetailsPanel(TabID);
				GUnrealEd->UpdateFloatingPropertyWindows();
				return DetailsPanel;
			}))
			.SetDisplayName(FText::FromString(FString::Printf(TEXT("Details %d"), BrowserIdx + 5)))
				.SetTooltipText(FText::FromString("Open a Custom Details tab."))
				.SetGroup(MenuStructure.GetLevelEditorDetailsCategory())
				.SetIcon(DetailsIcon);
	}
}

void UMultipleTabsSettings::ChangedViewport()
{
	const FName LevelEditorModuleName("LevelEditor");
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(LevelEditorModuleName);
	TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();

	const FSlateIcon ViewportIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports");
	const IWorkspaceMenuStructure& MenuStructure = WorkspaceMenu::GetMenuStructure();
	FText InDisplayName = FText::FromString(TEXT("Custom Viewports "));
	FText InTooltipText = FText::FromString(TEXT("Open a Custom Viewports tab"));
	TSharedRef<FWorkspaceItem> WorkspaceItem = MenuStructure.GetToolsCategory()->AddGroup(
		InDisplayName,
		InTooltipText,
		ViewportIcon,
		true);

	for (int32 BrowserIdx = 0; BrowserIdx < 101; BrowserIdx++)
	{
		const FName TabID = FName(*FString::Printf(TEXT("Viewport %d"), BrowserIdx + 5));
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabID);
	}

	for (int32 BrowserIdx = 0; BrowserIdx < ViewportNumber; BrowserIdx++)
	{
		const FName TabID = FName(*FString::Printf(TEXT("Viewport %d"), BrowserIdx + 5));
		LevelEditorTabManager->RegisterTabSpawner(TabID, FOnSpawnTab::CreateLambda([&, TabID](const FSpawnTabArgs& SpawnTabArgs)
			{
				TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveLevelViewport();
				if (!ActiveLevelViewport.IsValid())
				{
					return SNew(SDockTab);
				}
				TSharedPtr<ILevelEditor> ParentLevelEditorShared = ActiveLevelViewport->GetParentLevelEditor().Pin();
				if (!ParentLevelEditorShared.IsValid())
				{
					return SNew(SDockTab);
				}

				FText LevelViewportTypes = FText::FromString(TabID.ToString());
				return BuildViewportTab(ParentLevelEditorShared, LevelViewportTypes, TabID.ToString(), FString());
			}))
			.SetDisplayName(FText::FromString(FString::Printf(TEXT("Viewports %d"), BrowserIdx + 5)))
				.SetTooltipText(FText::FromString("Open a Viewports tab."))
				.SetGroup(MenuStructure.GetLevelEditorViewportsCategory())
				.SetIcon(ViewportIcon);
	}
}


TSharedRef<SDockTab> UMultipleTabsSettings::SummonDetailsPanel(FName TabIdentifier)
{
	const FName LevelEditorModuleName("LevelEditor");
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(LevelEditorModuleName);

	TSharedRef<SActorDetails> ActorDetails = SNew(SActorDetails, TabIdentifier, LevelEditorModule.GetGlobalLevelEditorActions(), LevelEditorModule.GetLevelEditorTabManager());
	//TSharedRef<SActorDetails> ActorDetails = ;
	// Immediately update it (otherwise it will appear empty)
	{
		TArray<UObject*> SelectedActors;
		for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
		{
			AActor* Actor = static_cast<AActor*>(*It);
			checkSlow(Actor->IsA(AActor::StaticClass()));

			if (!Actor->IsPendingKill())
			{
				SelectedActors.Add(Actor);
			}
		}

		const bool bForceRefresh = true;
		ActorDetails->SetObjects(SelectedActors, bForceRefresh);
	}

	ActorDetails->SetActorDetailsRootCustomization(ActorDetailsObjectFilter, ActorDetailsRootCustomization);
	ActorDetails->SetSCSEditorUICustomization(ActorDetailsSCSEditorUICustomization);

	//static TArray< TWeakPtr<class SActorDetails> > AllActorDetailPanels;
	AllActorDetailPanels.Add(ActorDetails);

	const FText Label = NSLOCTEXT("LevelEditor", "DetailsTabTitle", "Details");

	TSharedRef<SDockTab> DocTab = SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
		.Label(Label)
		[
			SNew(SBox)
			.AddMetaData<FTutorialMetaData>(FTutorialMetaData(TEXT("ActorDetails"), TEXT("LevelEditorSelectionDetails")))
		[
			ActorDetails
		]
		];

	//TSharedRef<SDockTab> DocTab=SNew(SDockTab);
	return DocTab;
}

TSharedRef<SDockTab> UMultipleTabsSettings::BuildViewportTab(TSharedPtr<ILevelEditor> InLevelEditor, const FText& Label, const FString LayoutId, const FString& InitializationPayload)
{
	// The tab must be created before the viewport layout because the layout needs them
	TSharedRef< SDockTab > DockableTab =
		SNew(SDockTab)
		.Label(Label)
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Viewports"))
		.OnTabClosed_Lambda([&](TSharedRef<SDockTab> ClosedTab)
			{
				OnViewportTabClosed(ClosedTab);
			});

	// Create a new tab
	TSharedRef<FLevelViewportTabContent> ViewportTabContent = MakeShareable(new FLevelViewportTabContent());

	// Track the viewport
	CleanupPointerArray(ViewportTabs);
	ViewportTabs.Add(ViewportTabContent);
	const FName LevelEditorModuleName("LevelEditor");
	FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>(LevelEditorModuleName);

	ViewportTabContent->Initialize(InLevelEditor, DockableTab, LayoutId);

	// Restore transient camera position
	if (InLevelEditor.IsValid())
	{
		const TMap<FName, TSharedPtr<IEditorViewportLayoutEntity>>* const Viewports = ViewportTabContent->GetViewports();
		if (Viewports)
		{
			const FString& CurLayoutId = ViewportTabContent->GetLayoutString();
			for (auto& Pair : *Viewports)
			{
				TSharedPtr<SLevelViewport> Viewport = StaticCastSharedPtr<ILevelViewportLayoutEntity>(Pair.Value)->AsLevelViewport();
				if (!Viewport.IsValid())
				{
					continue;
				}

				FLevelEditorViewportClient& LevelViewportClient = Viewport->GetLevelViewportClient();
				bool bInitializedOrthoViewport = false;
				for (int32 ViewportType = 0; ViewportType < LVT_MAX; ViewportType++)
				{
					if (ViewportType == LVT_Perspective || !bInitializedOrthoViewport)
					{
						const FString Key = FString::Printf(TEXT("%s[%d]"), *CurLayoutId, ViewportType);
						const FLevelViewportInfo* const TransientEditorView = TransientEditorViews.Find(Key);
						if (TransientEditorView)
						{
							LevelViewportClient.SetInitialViewTransform(
								static_cast<ELevelViewportType>(ViewportType),
								TransientEditorView->CamPosition,
								TransientEditorView->CamRotation,
								TransientEditorView->CamOrthoZoom
							);
						}
					}
				}
			}
		}
	}

	return DockableTab;
}

void UMultipleTabsSettings::OnViewportTabClosed(TSharedRef<SDockTab> ClosedTab)
{
	TWeakPtr<FLevelViewportTabContent>* const ClosedTabContent = ViewportTabs.FindByPredicate([&ClosedTab](TWeakPtr<FLevelViewportTabContent>& InPotentialElement) -> bool
		{
			TSharedPtr<FLevelViewportTabContent> ViewportTabContent = InPotentialElement.Pin();
			return ViewportTabContent.IsValid() && ViewportTabContent->BelongsToTab(ClosedTab);
		});

	if (ClosedTabContent)
	{
		TSharedPtr<FLevelViewportTabContent> ClosedTabContentPin = ClosedTabContent->Pin();
		if (ClosedTabContentPin.IsValid())
		{
			const TMap<FName, TSharedPtr<IEditorViewportLayoutEntity>>* const Viewports = ClosedTabContentPin->GetViewports();
			if (Viewports)
			{
				const FString& LayoutId = ClosedTabContentPin->GetLayoutString();
				for (auto& Pair : *Viewports)
				{
					TSharedPtr<SLevelViewport> Viewport = StaticCastSharedPtr<ILevelViewportLayoutEntity>(Pair.Value)->AsLevelViewport();

					if (!Viewport.IsValid())
					{
						continue;
					}
					const FLevelEditorViewportClient& LevelViewportClient = Viewport->GetLevelViewportClient();
					const FString Key = FString::Printf(TEXT("%s[%d]"), *LayoutId, static_cast<int32>(LevelViewportClient.ViewportType));
					TransientEditorViews.Add(
						Key, FLevelViewportInfo(
							LevelViewportClient.GetViewLocation(),
							LevelViewportClient.GetViewRotation(),
							LevelViewportClient.GetOrthoZoom()
						)
					);
				}
			}

			// Untrack the viewport
			ViewportTabs.Remove(ClosedTabContentPin);
			CleanupPointerArray(ViewportTabs);
		}
	}
}
