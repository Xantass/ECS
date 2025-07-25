#pragma once

#include "Entity.hpp"

enum class InputType {
    KeyLeft,
    KeyRight,
    KeyUp,
    KeyDown,
    KeySpace,
};

struct InputEvent {
    InputType type;
    Entity player;
};