// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorUtilExtention.h"
#include "Modules/ModuleManager.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "UnrealEdGlobals.h"
#include "AssetRegistryModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "IMeshMergeUtilities.h"

bool UEditorUtilExtention::MergeStaticMeshComponents(const AActor* Actor, const FString& PackageName, const FMeshMergingSettings& MergeOptions)
{
	const IMeshMergeUtilities& MeshUtilities = FModuleManager::Get().LoadModuleChecked<IMeshMergeModule>("MeshMergeUtilities").GetUtilities();

	TInlineComponentArray<UStaticMeshComponent*> ComponentArray;
	Actor->GetComponents<UStaticMeshComponent>(ComponentArray);

	TArray<UPrimitiveComponent*> allComponents;

	bool bActorIsValid = false;
	for (UStaticMeshComponent* MeshCmp : ComponentArray)
	{
		if (MeshCmp->GetStaticMesh() && MeshCmp->GetStaticMesh()->RenderData.IsValid())
		{
			allComponents.Add(MeshCmp);
		}
	}

	FVector MergedActorLocation;
	TArray<UObject*> CreatedAssets;
	const float ScreenAreaSize = TNumericLimits<float>::Max();
	MeshUtilities.MergeComponentsToStaticMesh(allComponents, allComponents[0]->GetOwner()->GetWorld(), MergeOptions, nullptr, nullptr, PackageName, CreatedAssets, MergedActorLocation, ScreenAreaSize, true);

	UStaticMesh* MergedMesh = nullptr;
	if (!CreatedAssets.FindItemByClass(&MergedMesh))
	{
		UE_LOG(LogTemp, Error, TEXT("MergeStaticMeshComponents failed. No mesh was created."));
		return false;
	}

	FAssetRegistryModule& AssetRegistry = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	for (UObject* Obj : CreatedAssets)
	{
		AssetRegistry.AssetCreated(Obj);
	}

	//Also notify the content browser that the new assets exists
	if (!IsRunningCommandlet())
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(CreatedAssets, true);
	}

	return true;
}
