#pragma once

#include <map>
#include "InputEvent.hpp"
#include "Registry.hpp"

using InputAction = std::function<void()>;
extern std::map<InputType, InputAction> actions;

void setupActions(Registry& registry, Entity playerId);