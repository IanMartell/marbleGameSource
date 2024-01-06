
#include "TestGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "TestPlayerController.h"
#include "TestHud.h"


ATestGameModeBase::ATestGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/myAdditionsArcade/testing/testCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ATestPlayerController::StaticClass();
	HUDClass = ATestHud::StaticClass();
}
