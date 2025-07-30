#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "raylib.h"
#include "Frame.hpp"

namespace fs = std::filesystem;

struct Animation
{
    std::vector<std::string> frameNames;
    float frameDuration;
};

class AssetManager
{
public:
    ~AssetManager()
    {
        unloadAll();
    }

    static void loadAllAssets(const std::string &directory)
    {
        std::unordered_map<std::string, Frame> frames;
        std::unordered_map<std::string, Texture2D> textures;
        for (const auto &entry : fs::directory_iterator(directory))
        {
            if (entry.is_regular_file())
            {
                std::string path = entry.path().string();
                if (entry.path().extension() == ".png")
                {
                    loadTexture(entry.path().stem().string(), path);
                }
                else if (entry.path().extension() == ".json")
                {
                    loadFrames(path);
                }
            }
        }
    }

    static void loadTexture(const std::string &name, const std::string &path)
    {
        if (textures.find(name) != textures.end())
            return;

        Image img = LoadImage(path.c_str());
        if (img.data == nullptr)
        {
            TraceLog(LOG_ERROR, "❌ Failed to load image: %s", path.c_str());
            return;
        }

        int maxWidth = 100;
        int maxHeight = 100;
        if (img.width > maxWidth || img.height > maxHeight)
        {
            ImageResize(&img, maxWidth, maxHeight);
        }

        Texture2D tex = LoadTextureFromImage(img);
        UnloadImage(img);

        if (tex.id == 0)
        {
            TraceLog(LOG_ERROR, "❌ Failed to create texture: %s", path.c_str());
            return;
        }

        textures[name] = tex;
    }

    static void loadFrames(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cerr << "Erreur d'ouverture du fichier JSON: " << path << std::endl;
            return;
        }
        nlohmann::json j;
        file >> j;
        if (!j.contains("frames"))
        {
            std::cerr << "Le JSON ne contient pas de champ 'frames'!" << std::endl;
            return;
        }
        for (auto &[name, data] : j["frames"].items())
        {
            Frame f;
            f.x = data["frame"]["x"];
            f.y = data["frame"]["y"];
            f.width = data["frame"]["w"];
            f.height = data["frame"]["h"];
            f.rotated = data["rotated"];
            frames[name] = f;
        }
    }

    static Texture2D &getTexture(const std::string &name)
    {
        if (textures.find(name) == textures.end())
        {
            TraceLog(LOG_WARNING, "⚠️ Texture not found: %s", name.c_str());
            return textures["missing"];
        }
        return textures[name];
    }

    static Frame &getFrame(const std::string &name)
    {
        if (frames.find(name) == frames.end())
        {
            TraceLog(LOG_WARNING, "⚠️ Frame not found: %s", name.c_str());
            return frames["missing"];
        }
        return frames[name];
    }

    static void unloadAll()
    {
        for (auto &[name, tex] : textures)
        {
            UnloadTexture(tex);
        }
        textures.clear();
    }

private:
    inline static std::unordered_map<std::string, Texture2D> textures{};
    inline static std::unordered_map<std::string, Frame> frames{};
    inline static std::unordered_map<std::string, Animation> animations{};
};
