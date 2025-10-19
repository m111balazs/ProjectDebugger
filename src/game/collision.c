#include "collision.h"
#include <stdbool.h>

static bool solidTiles[] = {
    false, // 0 = Grass
    true, // 1 = Wall
    true, // 2 = Water
    true // 3 = Stone
};
bool Collision_IsTileSolid(int tileIndex)
{
    if (tileIndex < 0 || tileIndex >= 4)
        return false;
    return solidTiles[tileIndex];
}

bool Collision_Check(float newX, float newY, float spriteW, float spriteH, const Tilemap* tilemap)
{
    int leftTile   = (int)(newX / tilemap->tileSize);
    int rightTile  = (int)((newX + spriteW - 1) / tilemap->tileSize);
    int topTile    = (int)(newY / tilemap->tileSize);
    int bottomTile = (int)((newY + spriteH - 1) / tilemap->tileSize);

    for (int y = topTile; y <= bottomTile; y++) {
        for (int x = leftTile; x <= rightTile; x++) {
            // Out of bounds = solid
            if (x < 0 || y < 0 || x >= tilemap->width || y >= tilemap->height)
                return true;

            int tileIndex = tilemap->data[y * tilemap->width + x];
            if (Collision_IsTileSolid(tileIndex))
                return true;
        }
    }

    return false;
}