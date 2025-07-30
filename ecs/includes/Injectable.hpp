#pragma once

// Mixin pour l'injection automatique de dépendances dans les systèmes

template<typename... Resources>
class Injectable {
public:
    void inject(Resources&... resources) {
        injectImpl(resources...);
    }
protected:
    void injectImpl(Resources&... resources) {
        int dummy[] = { (setResource(resources), 0)... };
        (void)dummy;
    }
    template<typename T>
    void setResource(T& resource) {
        getMember<T>() = &resource;
    }
    template<typename T>
    T*& getMember() {
        static_assert(sizeof(T) == 0, "Spécialise getMember<T>() dans ton système ou utilise la macro INJECTABLE_MEMBERS !");
        return nullptr;
    }
};

// Macro pour générer automatiquement les membres et la spécialisation de getMember<T>()
#define INJECTABLE_MEMBERS(...) \
    template<typename U> U*& getMember(); \
    __INJECTABLE_MEMBERS_IMPL(__VA_ARGS__)

#define __INJECTABLE_MEMBERS_IMPL(...) \
    __INJECTABLE_MEMBERS_IMPL_(__VA_ARGS__)
#define __INJECTABLE_MEMBERS_IMPL_(...) \
        __VA_ARGS__

// Utilisation :
// INJECTABLE_MEMBERS( \
//     InputManager* inputManager = nullptr; \
//     template<> InputManager*& getMember<InputManager>() { return inputManager; } \
//     AudioService* audioService = nullptr; \
//     template<> AudioService*& getMember<AudioService>() { return audioService; } \
// ) 