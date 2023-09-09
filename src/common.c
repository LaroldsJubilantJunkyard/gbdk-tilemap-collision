#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <gb/metasprites.h>
#include "tileset.h"
#include "tilemap.h"
#include "ball.h"

#define SOLID 1
#define PLAYER_HALF_WIDTH 8
#define PLAYER_HALF_HEIGHT 8
#define GRID_NODE_SIZE 8
#define NUMBER_OF_SOLID_TILES 9

#define TILEMAP_WIDTH_IN_TILES (tilemap_WIDTH>>3)
#define TILEMAP_HEIGHT_IN_TILES (tilemap_HEIGHT>>3)

uint16_t playerX,playerY;

uint8_t WorldPositionIsSolid(uint16_t x, uint16_t y){
    
    // Bit-shifting would be faster here
    uint16_t column = x/GRID_NODE_SIZE; 

    // Make sure the tile is in proper bounds
    if(column>=TILEMAP_WIDTH_IN_TILES)return TRUE;

    uint16_t row = y/GRID_NODE_SIZE;

    // Make sure the tile is in proper bounds
    if(row>=TILEMAP_HEIGHT_IN_TILES)return TRUE;
    
    uint16_t tilemapIndex  = column+row*TILEMAP_WIDTH_IN_TILES;

    uint8_t tileIsSolid = FALSE;

    // Get the tilset tile in our tilemap
    uint8_t tilesetTile = tilemap_map[tilemapIndex];

    // In our tileset, the solid tiles always come first.
    // There are 10 tiles. The first 9 are solid
    // this makes it fast & easy to determine if a tile is solid or not
    tileIsSolid = tilesetTile<NUMBER_OF_SOLID_TILES;

    return  tileIsSolid;

}

void GetPlayerInput(uint16_t* nextPlayerX,uint16_t* nextPlayerY,int8_t* directionX, int8_t* directionY){
    
    // handle joypadInput
    uint8_t joypadCurrent = joypad();

    *nextPlayerX = playerX;
    *nextPlayerY = playerY;
    *directionY=0;
    *directionX=0;

    if(joypadCurrent & J_RIGHT){
        *nextPlayerX+=1;
        *directionX=1;
    }
    if(joypadCurrent & J_LEFT){
        *nextPlayerX-=1;
        *directionX=-1;
    }
    if(joypadCurrent & J_DOWN){
        *nextPlayerY+=1;
        *directionY=1;
    }
    if(joypadCurrent & J_UP){
        *nextPlayerY-=1;
        *directionY=-1;
    }
}

void SetupDemo(){

    SHOW_SPRITES;
    SHOW_BKG;
    SPRITES_8x16;

    set_sprite_data(0,ball_TILE_COUNT,ball_tiles);
    set_bkg_data(0,tileset_TILE_COUNT,tileset_tiles);

    set_bkg_tiles(0,0,TILEMAP_WIDTH_IN_TILES,TILEMAP_HEIGHT_IN_TILES,tilemap_map);

    playerX=80;
    playerY=90;

}