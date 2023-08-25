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

uint16_t playerX,playerY;

uint8_t WorldPositionIsSolid(uint16_t x, uint16_t y){
    
    // Bit-shifting would be faster here
    uint16_t column = x/GRID_NODE_SIZE; 
    uint16_t row = y/GRID_NODE_SIZE;
    uint16_t tilemapIndex  = column+row*20;

    uint8_t tileIsSolid = FALSE;

    // Make sure the tile is in proper bounds
    if(column>=20)tileIsSolid=TRUE;
    else if(row>=18)tileIsSolid=TRUE;
    else{

        // Get the tilset tile in our tilemap
        uint8_t tilesetTile = tilemap_map[tilemapIndex];

        // In our tileset, the solid tiles always come first.
        // this makes it fast & easy to determine if a tile is solid or not
        tileIsSolid = tilesetTile<8;

    }

    return  tileIsSolid;

}

void GetPlayerInput(uint16_t* newPlayerX,uint16_t* newPlayerY,int8_t* directionX, int8_t* directionY){
    
    // handle joypadInput
    uint8_t joypadCurrent = joypad();

    *newPlayerX = playerX;
    *newPlayerY = playerY;
    *directionY=0;
    *directionX=0;

    if(joypadCurrent & J_RIGHT){
        *newPlayerX+=1;
        *directionX=1;
    }
    if(joypadCurrent & J_LEFT){
        *newPlayerX-=1;
        *directionX=-1;
    }
    if(joypadCurrent & J_DOWN){
        *newPlayerY+=1;
        *directionY=1;
    }
    if(joypadCurrent & J_UP){
        *newPlayerY-=1;
        *directionY=-1;
    }
}

void SetupDemo(){

    SHOW_SPRITES;
    SHOW_BKG;
    SPRITES_8x16;

    set_sprite_data(0,ball_TILE_COUNT,ball_tiles);
    set_bkg_data(0,tileset_TILE_COUNT,tileset_tiles);

    set_bkg_tiles(0,0,20,18,tilemap_map);

    playerX=80;
    playerY=90;

}