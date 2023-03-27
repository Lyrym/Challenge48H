// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HttpModule.h"
#include "Http.h"
#include "CoreMinimal.h"


/**
 * 
 */
class CHALLENGE48H_API RequestManager
{
public:
	RequestManager();
	~RequestManager();
	void Scorelist();
	void NewScore(FString name, int32 score);

private:
	const std::string BASE_URL = "https://lesratz.fly.dev";
	const std::string SCORE_LIST_ENDPOINT = "/scorelist";
	const std::string NEW_SCORE_ENDPOINT = "/newscore";
	void OnScoreListReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
	void OnNewScoreReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

};
