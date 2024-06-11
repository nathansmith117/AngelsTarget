#include "gameCommon.h"

// Used for loading and freeing assets.

#define ASSETS_NAME_MAX 100
#define TEXTURE_ASSET_COUNT 5

#ifndef ASSETS_H
#define ASSETS_H

extern const char textureAssetsNames[TEXTURE_ASSET_COUNT][ASSETS_NAME_MAX];

enum
{
    BUTTON_BOX_TEXTURE,
    MAIN_MENU_BACKGROUND_TEXTURE,
    CHARACTER_TEXTURE,
    GRASS_TEXTURE,
    HOUSE_TEXTURE
};

typedef struct Assets {
    Texture textures[TEXTURE_ASSET_COUNT];
} Assets;

void initAssets(Assets* assets);
void closeAssets(Assets* assets);

#endif

