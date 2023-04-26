// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HttpModule.h"
#include "Http.h"
#include "Serialization/JsonSerializer.h"
#include "CoreMinimal.h"
#include "RequestManager.generated.h"



/**
 *
 */
UCLASS()
class CHALLENGE48H_API URequestManager : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnScoreListSignature, FString, ScoreList);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnNewScore, FString, Res);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTokenReceived, FString, Res);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSignInTokenReceived, FString, Res);


	UFUNCTION(BlueprintCallable, Category = "APIRequestsBPLibrary")
		static void SignIn(FString username, FString email, FString password, FOnTokenReceived callback);
	UFUNCTION(BlueprintCallable, Category = "APIRequestsBPLibrary")
		static void Login(FString username, FString email, FString password, FOnTokenReceived callback);
	UFUNCTION(BlueprintCallable, Category = "APIRequestsBPLibrary")
		static void Scorelist(FOnScoreListSignature callback);
	UFUNCTION(BlueprintCallable, Category = "APIRequestsBPLibrary")
		static void NewScore(FString token, int32 score, FOnNewScore callback);

	UFUNCTION(BlueprintCallable, Category = "APIRequestsBPLibrary")
		static FString ParseScores(FString toparse);

	// Delegate signature


};



