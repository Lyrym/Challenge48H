// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestManager.h"

RequestManager::RequestManager()
{
}

RequestManager::~RequestManager()
{
}



void RequestManager::Scorelist()
{
    std::string fullURL = BASE_URL + SCORE_LIST_ENDPOINT;
    FString url = FString(fullURL.c_str()).ToLower();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL(url);
    HttpRequest->OnProcessRequestComplete().BindRaw(this, &RequestManager::OnScoreListReceived);
    HttpRequest->ProcessRequest();

}

void RequestManager::OnScoreListReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    if (bSuccess)
    {
        FString ResponseString = Response->GetContentAsString();
        UE_LOG(LogTemp, Warning, TEXT("Player score list response: %s"), *ResponseString);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to fetch player score list."));
    }
}

void RequestManager::NewScore(FString name, int32 score)
{
    std::string fullURL = BASE_URL + NEW_SCORE_ENDPOINT;
    FString url = FString(fullURL.c_str()).ToLower();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("PUT");
    HttpRequest->SetURL(url);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    FString Content = FString::Printf(TEXT("{\"pseudo\": \"%s\", \"score\" : \"%d\"}"), *name, score);
    HttpRequest->SetContentAsString(Content);
    HttpRequest->OnProcessRequestComplete().BindRaw(this, &RequestManager::OnNewScoreReceived);
    HttpRequest->ProcessRequest();
}
void RequestManager::OnNewScoreReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    if (bSuccess)
    {
        FString ResponseString = Response->GetContentAsString();
        UE_LOG(LogTemp, Warning, TEXT("New score response: %s"), *ResponseString);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to update or insert player's score."));
    }
}