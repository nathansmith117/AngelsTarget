#include "assets.h"

const char textureAssetsNames[TEXTURE_ASSET_COUNT][ASSETS_NAME_MAX] = {
    "buttonBox.png",
    "mainMenuBackground.png",
    "character.png",
    "world.png"
};

void initAssets(Assets* assets)
{
    TraceLog(LOG_INFO, "Loading assets");

    // Textures.
    for (int i = 0; i < TEXTURE_ASSET_COUNT; ++i)
    {
        char filePath[ASSETS_NAME_MAX];
        snprintf(filePath, ASSETS_NAME_MAX, "assets/%s", textureAssetsNames[i]);
        assets->textures[i] = LoadTexture(filePath);
    }
    
    TraceLog(LOG_INFO, "Assets loaded");
}

void closeAssets(Assets* assets)
{
    TraceLog(LOG_INFO, "Closing assets");

    // Textures.
    for (int i = 0; i < TEXTURE_ASSET_COUNT; ++i)
    {
        UnloadTexture(assets->textures[i]);
    }

    TraceLog(LOG_INFO, "Assets closed");
}

