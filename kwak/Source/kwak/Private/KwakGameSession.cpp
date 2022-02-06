// Fill out your copyright notice in the Description page of Project Settings.


#include "KwakGameSession.h"

bool AKwakGameSession::HandleStartMatchRequest() { 
	Restart();
	return true; }
