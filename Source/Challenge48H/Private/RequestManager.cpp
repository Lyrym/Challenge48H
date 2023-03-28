// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestManager.h"

const std::string BASE_URL = "https://lesratz.fly.dev";
const std::string SCORE_LIST_ENDPOINT = "/scorelist";
const std::string NEW_SCORE_ENDPOINT = "/newscore";

void URequestManager::Scorelist(FOnScoreListSignature callback)
{
    const std::string fullURL = BASE_URL + SCORE_LIST_ENDPOINT;
    FString url = FString(fullURL.c_str()).ToLower();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL(url);
    HttpRequest->OnProcessRequestComplete().BindLambda([callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess)
            {
                FString ResponseString = Response->GetContentAsString();
                UE_LOG(LogTemp, Warning, TEXT("New score response: %s"), *ResponseString);
                callback.ExecuteIfBound(ResponseString);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to update or insert player's score."));
                callback.ExecuteIfBound("");
            }
        });

    HttpRequest->ProcessRequest();

}

void URequestManager::NewScore(FString name, int32 score, FOnNewScore callback)
{
    std::string fullURL = BASE_URL + NEW_SCORE_ENDPOINT;
    FString url = FString(fullURL.c_str()).ToLower();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("PUT");
    HttpRequest->SetURL(url);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    FString Content = FString::Printf(TEXT("{\"pseudo\": \"%s\", \"score\" : \"%d\"}"), *name, score);
    HttpRequest->SetContentAsString(Content);
    HttpRequest->OnProcessRequestComplete().BindLambda([callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess)
            {
                FString ResponseString = Response->GetContentAsString();
                UE_LOG(LogTemp, Warning, TEXT("New score response: %s"), *ResponseString);
                callback.ExecuteIfBound(ResponseString);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to update or insert player's score."));
                callback.ExecuteIfBound("");
            }
        });
    HttpRequest->ProcessRequest();
}
