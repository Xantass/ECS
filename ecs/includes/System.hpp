#pragma once

#include "Entity.hpp"
#include <tuple>
#include <functional>
#include <vector>
#include <type_traits>

class Registry;

// Nouvelle base système template
// Permet la détection automatique des composants et l'API ForEach

template<typename... Components>
class SystemBase {
public:
    virtual ~SystemBase() = default;
    // Méthode à surcharger dans les systèmes
    virtual void OnUpdate() = 0;

    void setRegistry(Registry* reg) { registry = reg; }
protected:
    Registry* registry = nullptr;
    // API ergonomique pour itérer sur les entités ayant les bons composants
    void ForEach(std::function<void(Entity, Components&...)> func);
};