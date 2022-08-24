#pragma once

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "Tests/AutomationCommon.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Misc/OutputDeviceNull.h"

namespace TestUtils
{
template <typename Type1, typename Type2>
struct TestPayload
{
    Type1 TestValue;
    Type2 ExpectedValue;
    float Tolerance = KINDA_SMALL_NUMBER;
};

#define ENUM_LOOP_START(TYPE, EnumElem)                                        \
    for (int32 Index = 0; Index < StaticEnum<TYPE>()->NumEnums() - 1; ++Index) \
    {                                                                          \
        const auto EnumElem = static_cast<TYPE>(StaticEnum<TYPE>()->GetValueByIndex(Index));
#define ENUM_LOOP_END }

template <typename EnumType, typename FunctionType>
void ForEach(FunctionType&& Function)
{
    const UEnum* Enum = StaticEnum<EnumType>();
    for (int32 i = 0; i < Enum->NumEnums(); ++i)
    {
        Function(static_cast<EnumType>(Enum->GetValueByIndex(i)));
    }
}

template <typename T>
T* CreateBlueprint(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
{
    const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
    return (World && Blueprint) ? World->SpawnActor<T>(Blueprint->GeneratedClass, Transform) : nullptr;
}

template <typename T>
T* CreateBlueprintDeferred(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
{
    const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
    return (World && Blueprint) ? World->SpawnActorDeferred<T>(Blueprint->GeneratedClass, Transform) : nullptr;
}

class LevelScope
{
public:
    LevelScope(const FString& MapName) { AutomationOpenMap(MapName); }
    ~LevelScope() { ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand); }
};

UWorld* GetTestGameWorld()
{
    const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
    for (const FWorldContext& Context : WorldContexts)
    {
        if ((Context.WorldType == EWorldType::PIE || Context.WorldType == EWorldType::Game) && Context.World())
        {
            return Context.World();
        }
    }

    return nullptr;
}

void CallFuncByNameWithParams(UObject* Object, const FString& FuncName, const TArray<FString>& Params)
{
    if (!Object) return;

    // Command pattern: "FunctionName Param1 Param2 Param3"
    FString Command = FuncName;
    for (const auto Param : Params)
    {
        Command.Append(" ").Append(Param);
    }
    FOutputDeviceNull OutputDeviceNull;
    Object->CallFunctionByNameWithArguments(*Command, OutputDeviceNull, nullptr, true);
}

int32 GetActionBindingIndexByName(UInputComponent* InputComp, const FString& ActionName, EInputEvent InputEvent)
{
    if (!InputComp) return INDEX_NONE;

    for (int32 i = 0; i < InputComp->GetNumActionBindings(); ++i)
    {
        const FInputActionBinding Action = InputComp->GetActionBinding(i);
        if (Action.GetActionName().ToString().Equals(ActionName) && Action.KeyEvent == InputEvent)
        {
            return i;
        }
    }

    return INDEX_NONE;
}

int32 GetAxisBindingIndexByName(UInputComponent* InputComp, const FString& AxisName)
{
    if (!InputComp) return INDEX_NONE;

    const int32 AxisIndex = InputComp->AxisBindings.IndexOfByPredicate(
        [=](const FInputAxisBinding& AxisBind) { return AxisBind.AxisName.ToString().Equals(AxisName); });

    return AxisIndex;
}

template <class T>
T* FindWidgetByClass()
{
    TArray<UUserWidget*> Widgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetTestGameWorld(), Widgets, T::StaticClass(), false);
    return Widgets.Num() != 0 ? Cast<T>(Widgets[0]) : nullptr;
}

UWidget* FindWidgetByName(const UUserWidget* Widget, const FName& WidgetName)
{
    if (!Widget || !Widget->WidgetTree) return nullptr;

    UWidget* FoundWidget = nullptr;
    UWidgetTree::ForWidgetAndChildren(Widget->WidgetTree->RootWidget,
        [&](UWidget* Child)
        {
            if (Child && Child->GetFName().IsEqual(WidgetName))
            {
                FoundWidget = Child;
            }
        });
    return FoundWidget;
}

void DoInputAction(UInputComponent* InputComponent, const FString& ActionName, const FKey& Key)
{
    if (!InputComponent) return;

    const int32 ActionIndex = GetActionBindingIndexByName(InputComponent, ActionName, EInputEvent::IE_Pressed);
    if (ActionIndex != INDEX_NONE)
    {
        const auto ActionBind = InputComponent->GetActionBinding(ActionIndex);
        ActionBind.ActionDelegate.Execute(Key);
    }
}

void PausePressed(UInputComponent* InputComponent)
{
    DoInputAction(InputComponent, "ToggleGamePause", EKeys::P);
}

}  // namespace Test

#endif