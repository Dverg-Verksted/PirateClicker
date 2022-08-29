#pragma once

#include "CoreMinimal.h"
#include "LibraryDataTypes.generated.h"

// Custom log verbosity
UENUM(BlueprintType)
enum class ELogRSVerb : uint8
{
    Display,
    Warning,
    Error
};
