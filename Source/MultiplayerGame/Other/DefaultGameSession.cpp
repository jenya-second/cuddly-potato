#include "DefaultGameSession.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"


void ADefaultGameSession::RegisterServer()
{
	Super::RegisterServer();
	
	UE_LOG(LogTemp, Log, TEXT("Creating session----------------------------------------------------------------------------"));
	IOnlineSubsystem* OnlineSubSystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr Session = OnlineSubSystem->GetSessionInterface();

	FOnlineSessionSettings settings;

	settings.bIsDedicated = true;
	settings.bIsLANMatch = true;
	settings.bAllowJoinInProgress = true;
	settings.bShouldAdvertise = true;
	settings.NumPublicConnections = 32;
	settings.bUsesPresence = true;
	
	if (Session->CreateSession(0, FName("aboba game"), settings)) {
		UE_LOG(LogTemp, Log, TEXT("Session created----------------------------------------------------------------------------"));
	}

	
}
