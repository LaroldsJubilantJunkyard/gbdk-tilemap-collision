#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <gb/metasprites.h>
#include "tileset.h"
#include "tilemap.h"
#include "ball.h"

#define SOLID 1
#define PLAYER_MOVE_SPEED 10
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

void main(void)
{
    SHOW_SPRITES;
    SHOW_BKG;
    SPRITES_8x16;

    set_sprite_data(0,ball_TILE_COUNT,ball_tiles);
    set_bkg_data(0,tileset_TILE_COUNT,tileset_tiles);

    set_bkg_tiles(0,0,20,18,tilemap_map);


    uint8_t startingSprite = 0;

    playerX=80<<4;
    playerY=90<<4;


    // Loop forever
    while(1) {

        // handle joypadInput
        uint8_t joypadCurrent = joypad();

        uint16_t newPlayerX = playerX, newPlayerY=playerY;
        int8_t directionY=0,directionX=0;

        if(joypadCurrent & J_RIGHT){
            newPlayerX+=PLAYER_MOVE_SPEED;
            directionX=1;
        }
        if(joypadCurrent & J_LEFT){
            newPlayerX-=PLAYER_MOVE_SPEED;
            directionX=-1;
        }
        if(joypadCurrent & J_DOWN){
            newPlayerY+=PLAYER_MOVE_SPEED;
            directionY=1;
        }
        if(joypadCurrent & J_UP){
            newPlayerY-=PLAYER_MOVE_SPEED;
            directionY=-1;
        }

        int16_t realPlayerX = newPlayerX>>4;
        int16_t realPlayerY = newPlayerY>>4;

        if(directionX!=0||directionY!=0){

            int16_t realPreviousPlayerX = playerX>>4;
            int16_t realPreviousPlayerY = playerY>>4;

            // If we are moving horizontally
            if(directionX!=0){

                // Check the tiles on our side
                uint8_t solid =
                    WorldPositionIsSolid(realPlayerX+directionX*PLAYER_HALF_WIDTH,realPreviousPlayerY-PLAYER_HALF_HEIGHT)||
                    WorldPositionIsSolid(realPlayerX+directionX*PLAYER_HALF_WIDTH,realPreviousPlayerY)||
                    WorldPositionIsSolid(realPlayerX+directionX*PLAYER_HALF_WIDTH,realPreviousPlayerY+PLAYER_HALF_HEIGHT);

                // If none are solid
                if(!solid){
                    
                    // Update the player's x position
                    playerX=newPlayerX;
                    realPreviousPlayerX=realPlayerX;
                }else{
                        
                    // we'll use the existing x position
                    realPlayerX = playerX>>4;
                }
            }

            // If we are moving vertically
            if(directionY!=0){

                // Check the tiles above or below us
                uint8_t solid =
                    WorldPositionIsSolid(realPreviousPlayerX+PLAYER_HALF_WIDTH,realPlayerY+directionY*PLAYER_HALF_HEIGHT)||
                    WorldPositionIsSolid(realPreviousPlayerX,realPlayerY+directionY*PLAYER_HALF_HEIGHT)||
                    WorldPositionIsSolid(realPreviousPlayerX-PLAYER_HALF_WIDTH,realPlayerY+directionY*PLAYER_HALF_HEIGHT);

                // If none are solid
                if(!solid){
                    
                    // Update the player's y position
                    playerY=newPlayerY;
                }else{
                        
                    realPlayerY = playerY>>4;
                }
            }

        }

        move_metasprite(ball_metasprites[0],0,0,realPlayerX+8,realPlayerY+16);

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
