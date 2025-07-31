#pragma once
#include <unordered_map>
#include "InputEvent.hpp"

struct CooldownInput {
    std::unordered_map<InputType, float> timers;
};