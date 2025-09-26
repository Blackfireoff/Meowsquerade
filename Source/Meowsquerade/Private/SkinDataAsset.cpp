// Fill out your copyright notice in the Description page of Project Settings.


#include "SkinDataAsset.h"

USkeletalMesh* USkinDataAsset::GetSkinMeshByIndex(int32 Index) const
{
	if (Index < 0 || Index >= SkinList.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("GetSkinMeshByIndex: Index %d is out of bounds (0 - %d)"), Index, SkinList.Num() - 1);
		return nullptr;
	}
	return SkinList[Index].SkinMesh;
}
