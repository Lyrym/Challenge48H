// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RequestManager.h"
#include "BP_Requests.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGE48H_API UBP_Requests: public UBlueprintFunctionLibrary
{


	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "RequestsBPLibrary") static void NewScore();


};
