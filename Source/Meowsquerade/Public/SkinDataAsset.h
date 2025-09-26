// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkinDataAsset.generated.h"

/**
 * 
 */
USTRUCT()
struct FSkinAssetInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString SkinName;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* SkinIcon;
	
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkinMesh;
};

UCLASS()
class MEOWSQUERADE_API USkinDataAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TArray<FSkinAssetInfo> SkinList;

public:
	USkeletalMesh* GetSkinMeshByIndex(int32 Index) const;
};
