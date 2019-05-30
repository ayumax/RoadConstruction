// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MeshMergeModule.h"
#include "EditorUtilExtention.generated.h"

class AActor;

UCLASS()
class ROADCONSTRUCTIONEDITOR_API UEditorUtilExtention : public UObject
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Extention")
	static bool MergeStaticMeshComponents(const AActor* Actor, const FString& PackageName, const FMeshMergingSettings& MergeOptions);

};
