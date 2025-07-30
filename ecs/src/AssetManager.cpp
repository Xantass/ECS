#include "../includes/AssetManager.hpp"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

void AssetManager::loadFramesFromJson(const std::string& jsonPath)
{
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "Erreur d'ouverture du fichier JSON: " << jsonPath << std::endl;
        return;
    }
    json j;
    file >> j;
    if (!j.contains("frames")) {
        std::cerr << "Le JSON ne contient pas de champ 'frames'!" << std::endl;
        return;
    }
    for (auto& [name, data] : j["frames"].items()) {
        Frame f;
        // Supporte le format TexturePacker (frame dans un objet)
        if (data.contains("frame")) {
            f.x = data["frame"]["x"];
            f.y = data["frame"]["y"];
            f.width = data["frame"]["w"];
            f.height = data["frame"]["h"];
        } else {
            // Format simple
            f.x = data["x"];
            f.y = data["y"];
            f.width = data["w"];
            f.height = data["h"];
        }
        frames[name] = f;
    }
}

const Frame& AssetManager::getFrame(const std::string& name)
{
    auto it = frames.find(name);
    if (it == frames.end()) {
        static Frame empty{0,0,0,0};
        std::cerr << "Frame non trouvée: " << name << std::endl;
        return empty;
    }
    return it->second;
} 