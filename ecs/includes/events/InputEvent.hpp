#pragma once

#include "Entity.hpp"

enum class InputType {
    KeyLeft,
    KeyRight,
    KeyUp,
    KeyDown,
    KeySpace,
    KeyNone,
};

struct InputEvent {
    InputType type;
    Entity player;
};