// Fill out your copyright notice in the Description page of Project Settings.
#include "BP_Requests.h"




void UBP_Requests::NewScore() {
	RequestManager manager; 
	manager.NewScore(TEXT("AAAAA"),399);
}

