#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>
#include "raylib.h"

namespace fs = std::filesystem;

class AssetManager
{
public:
    ~AssetManager()
    {
        unloadAll();
    }

    static void loadAllAssets(const std::string &directory)
    {
        for (const auto &entry : fs::directory_iterator(directory))
        {
            if (entry.is_regular_file())
            {
                std::string path = entry.path().string();
                if (entry.path().extension() == ".png")
                {
                    loadTexture(entry.path().stem().string(), path);
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

    static Texture2D &getTexture(const std::string &name)
    {
        if (textures.find(name) == textures.end())
        {
            TraceLog(LOG_WARNING, "⚠️ Texture not found: %s", name.c_str());
            return textures["missing"];
        }
        return textures[name];
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
};
