// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestManager.h"

const std::string BASE_URL = "http://192.168.0.23:8080";
const std::string SCORE_LIST_ENDPOINT = "/scoreboard/The_Probably_Enchanted_Cavern";
const std::string NEW_SCORE_ENDPOINT = "/newscore";
const std::string LOGIN_ENDPOINT = "/login";
const std::string SIGNIN_ENDPOINT = "/signin";





void URequestManager::SignIn(FString username, FString email, FString password, FOnTokenReceived callback)
{
    const std::string fullURL = BASE_URL + SIGNIN_ENDPOINT;
    FString url = FString(fullURL.c_str()).ToLower();

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetURL(url);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    FString Content = FString::Printf(TEXT("{\"username\": \"%s\",\"email\": \"%s\", \"password\": \"%s\"}"), *username, *email, *password);
    HttpRequest->SetContentAsString(Content);

    HttpRequest->OnProcessRequestComplete().BindLambda([callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess)
            {
                FString RequestBody = Response->GetContentAsString();
                UE_LOG(LogTemp, Warning, TEXT("SignIn success."), *RequestBody);
                callback.ExecuteIfBound(RequestBody);
            }
            else
            {
                FString RequestBody = Response->GetContentAsString();
                UE_LOG(LogTemp, Warning, TEXT("SignIn failed."));
                callback.ExecuteIfBound(RequestBody);
            }
        });

    HttpRequest->ProcessRequest();
}


void URequestManager::Login(FString username, FString email, FString password, FOnTokenReceived callback)
{
    const std::string fullURL = BASE_URL + LOGIN_ENDPOINT;
    FString url = FString(fullURL.c_str()).ToLower();

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetURL(url);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    FString Content = FString::Printf(TEXT("{\"username\": \"%s\",\"email\": \"%s\", \"password\": \"%s\"}"), *username, *email, *password);
    if (username == "") {
        Content = FString::Printf(TEXT("{\"email\": \"%s\", \"password\": \"%s\"}"), *email, *password);
    }
    else if(email == "") {
        Content = FString::Printf(TEXT("{\"username\": \"%s\", \"password\": \"%s\"}"), *username, *password);
    }
    HttpRequest->SetContentAsString(Content);

    HttpRequest->OnProcessRequestComplete().BindLambda([callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess && Response.IsValid())
            {
                FString AuthorizationHeader = Response->GetHeader(TEXT("Authorization"));
                FString RequestError = Response->GetContentAsString();
                if (!AuthorizationHeader.IsEmpty())
                {
                    UE_LOG(LogTemp, Warning, TEXT("Login success. Token received: %s"), *AuthorizationHeader);
                    callback.ExecuteIfBound(AuthorizationHeader);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to get token."));
                    callback.ExecuteIfBound(RequestError);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Login failed."));
                callback.ExecuteIfBound("");
            }
        });

    HttpRequest->ProcessRequest();
}

void URequestManager::Scorelist(FOnScoreListSignature callback)
{
    const std::string fullURL = BASE_URL + SCORE_LIST_ENDPOINT;
    FString url = FString(fullURL.c_str());
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL(url);
    HttpRequest->OnProcessRequestComplete().BindLambda([callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess)
            {
                FString ResponseString = Response->GetContentAsString();
                UE_LOG(LogTemp, Warning, TEXT("New scorelist response: %s"), *ResponseString);
                callback.ExecuteIfBound(ResponseString);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to get scorelist"));
                callback.ExecuteIfBound("");
            }
        });

    HttpRequest->ProcessRequest();

}

void URequestManager::NewScore(FString token, int32 score, FOnNewScore callback)
{
    std::string fullURL = BASE_URL + NEW_SCORE_ENDPOINT;
    FString url = FString(fullURL.c_str());
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("PUT");
    HttpRequest->SetURL(url);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    HttpRequest->SetHeader(TEXT("Authorization"), token);
    FString Content = FString::Printf(TEXT("{\"game\": \"The_Probably_Enchanted_Cavern\", \"score\" : \"%d\"}"), score);
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
                FString ResponseString = Response->GetContentAsString();
                UE_LOG(LogTemp, Warning, TEXT("Failed to update or insert player's score."));
                callback.ExecuteIfBound(ResponseString);
            }
        });
    HttpRequest->ProcessRequest();
}

FString URequestManager::ParseScores(FString toparse) {

    FString formatedString = TEXT("{values:"+toparse+"}");
    TSharedPtr<FJsonObject> resJsonObject;
    
    FString ScoresTab;

    // Array of json objects at top level of json
    TArray<TSharedPtr<FJsonValue>> JsonArray;

    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(toparse);
    // Deserialize the json data given Reader and the actual object to deserialize
    if (FJsonSerializer::Deserialize(Reader, JsonArray)) {
        //Get the value of the json object by field name
        UE_LOG(LogTemp, Warning, TEXT("===== GET VALUES1 ====="));
        

        for (TSharedPtr<FJsonValue> entry : JsonArray) {
            int32 score = entry->AsObject()->GetIntegerField("score");
            FString name = entry->AsObject()->GetStringField("user");
            ScoresTab += (name+" : "+FString::FromInt(score)+"\n");
        }
        return ScoresTab;
    }


    UE_LOG(LogTemp, Warning, TEXT("===== NO VALUES ====="));
    return formatedString;


    

}
