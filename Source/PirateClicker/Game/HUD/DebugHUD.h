// This section is the property of the Dverg Verksted team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DebugHUD.generated.h"

/**
 * @class Debug HUD
 */
UCLASS()
class PIRATECLICKER_API ADebugHUD : public AHUD
{
    GENERATED_BODY()

public:
    // Construct the debugging HUD, mainly establishing a font to use for display.
    ADebugHUD();

protected:
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;

    // Draw the HUD.
    virtual void DrawHUD() override;

    // Add a FText to the HUD for rendering.
    void AddText(const TCHAR* title, const FText& value);

    // Add a float to the HUD for rendering.
    void AddFloat(const TCHAR* title, float value);

    // Add an int32 to the HUD for rendering.
    void AddInt(const TCHAR* title, int32 value);

    // Add a bool to the HUD for rendering.
    void AddBool(const TCHAR* title, bool value);

private:
    // Font used to render the debug information.
    UPROPERTY(EditDefaultsOnly, Category = "Debug")
    UFont* MainFont{nullptr};

    // Size text for Main font.
    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (ClampMin = "1"))
    int32 SizeFont{16};

    // Color display of the title parameter text
    UPROPERTY(EditDefaultsOnly, Category = "Debug")
    FLinearColor TitleColor{FLinearColor::White};

    // The current X coordinate.
    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (ForceUnits = "cm"))
    float DefaultX{50.0f};

    // The current Y coordinate.
    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (ForceUnits = "cm"))
    float DefaultY{50.0f};

    // The line height to separate each HUD entry.
    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (ForceUnits = "cm"))
    float LineHeight{26.0f};

    // The horizontal offset to render the statistic values.
    UPROPERTY(EditDefaultsOnly, Category = "Debug", meta = (ForceUnits = "cm"))
    float HorizontalOffset{250.0f};

    // Current X and Y
    float X;
    float Y;

    // Settings Font
    FSlateFontInfo ParamFont;

    // Render a statistic onto the HUD canvas.
    void RenderStatistic(const TCHAR* title, const FText& value, const FLinearColor& valueColor = FLinearColor::White);

    // Convert a TCHAR pointer to FText.
    FText CStringToText(const TCHAR* text);

    // Convert a bool to FText.
    FText BoolToText(bool value);
};
