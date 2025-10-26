#include "collision.h"
#include <stdbool.h>

static bool solidTiles[] = {
    false, // 0 = Grass
    true, // 1 = Wall
    true, // 2 = Water
    true, // 3 = Stone
    false // 4 = path
};
bool Collision_IsTileSolid(int tileIndex)
{
    if (tileIndex < 0 || tileIndex >= 4)
        return false;
    return solidTiles[tileIndex];
}

bool Collision_Check(float newX, float newY, float spriteW, float spriteH, const Tilemap* tilemap)
{
    // Account for render/world origin offset (margin)
    

    float worldX = newX;
    float worldY = newY;

    int leftTile   = (int)(worldX / tilemap->tileSize);
    int rightTile  = (int)((worldX + spriteW - 1) / tilemap->tileSize);
    int topTile    = (int)(worldY / tilemap->tileSize);
    int bottomTile = (int)((worldY + spriteH - 1) / tilemap->tileSize);

    for (int y = topTile; y <= bottomTile; y++) {
        for (int x = leftTile; x <= rightTile; x++) {
            // Out of bounds = solid
            if (x < 0 || y < 0 || x >= tilemap->width || y >= tilemap->height)
                return true;

            int tileIndex = tilemap->layers[0][y * tilemap->width + x];
            if (Collision_IsTileSolid(tileIndex))
                return true;
        }
    }

    return false;
}