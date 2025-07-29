#pragma once
#include "Engine/DeveloperSettings.h"
#include "LevelEditor.h"
#include "SLevelViewport.h"
#include "LevelViewportTabContent.h"
#include "Editor/LevelEditor/Public/LevelViewportTabContent.h"
#include "Editor/LevelEditor/Private/SActorDetails.h"
//#include "Editor/LevelEditor/Private/SActorDetails.cpp"


#include "MultipleTabsSettings.generated.h"


class SLevelEditor;
class SActorDetails;


UCLASS(Config = Plugins, defaultconfig)
class UMultipleTabsSettings : public UDeveloperSettings
{
	//GENERATED_BODY()
	GENERATED_UCLASS_BODY()
public:
	UMultipleTabsSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual FName GetContainerName() const override { return FName(TEXT("Project")); }
	virtual FName GetCategoryName() const override { return FName(TEXT("Plugins")); }
	virtual FName GetSectionName() const override { return FName(TEXT("MultipleTabs")); }

	virtual ~UMultipleTabsSettings()
	{
		TransientEditorViews.Reset();
		ViewportTabs.Reset();
		AllActorDetailPanels.Reset();
		ActorDetailsObjectFilter.Reset();
		ActorDetailsRootCustomization.Reset();
		ActorDetailsSCSEditorUICustomization.Reset();
	}

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(Config, EditAnywhere, Category = "Content Browser Number", meta = (ClampMin = 0, ClampMax = 100))
	int ContentBrowserNumber=4;

	UPROPERTY(Config, EditAnywhere, Category = "Detail Number", meta = (ClampMin = 0, ClampMax = 100))
	int DetailNumber=4;

	UPROPERTY(Config, EditAnywhere, Category = "Viewport Number", meta = (ClampMin = 0, ClampMax = 100))
	int ViewportNumber=4;


	void ChangedContent();
	void ChangedDetail();
	void ChangedViewport();

	TSharedRef<SDockTab> SummonDetailsPanel(FName TabIdentifier);


	TSharedRef<SDockTab> BuildViewportTab(TSharedPtr<ILevelEditor> InLevelEditor, const FText& Label, const FString LayoutId, const FString& InitializationPayload);

	void OnViewportTabClosed(TSharedRef<SDockTab> ClosedTab);


private:
	TArray< TWeakPtr<FLevelViewportTabContent> > ViewportTabs;

	TMap<FString, FLevelViewportInfo> TransientEditorViews;

	TArray< TWeakPtr<class SActorDetails> > AllActorDetailPanels;

	/** Actor details object filters */
	TSharedPtr<FDetailsViewObjectFilter> ActorDetailsObjectFilter;

	/** Actor details root customization */
	TSharedPtr<IDetailRootObjectCustomization> ActorDetailsRootCustomization;

	TSharedPtr<ISCSEditorUICustomization> ActorDetailsSCSEditorUICustomization;
};
