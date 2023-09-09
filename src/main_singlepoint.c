#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <gb/metasprites.h>
#include "ball.h"
#include "common.h"

void main(void)
{
    SetupDemo();

    // Loop forever
    while(1) {

        uint16_t nextPlayerX = playerX, nextPlayerY=playerY;
        int8_t directionY=0,directionX=0;

        GetPlayerInput(&nextPlayerX,&nextPlayerY,&directionX,&directionY);

        uint8_t playerIsMoving = directionX!=0||directionY!=0;

        // If the player is moving at all, We'll handle horizontall and vertical movement separately
        // Handling them separately enables a sliding motion against walls
        if(playerIsMoving){


            // If we are moving horizontally
            if(directionX!=0){

                // Check the tile on the next location
                // If none are solid
                if(!WorldPositionIsSolid(nextPlayerX,playerY)){
                    
                    // Update the player's x position
                    playerX=nextPlayerX;
                }
            }

            // If we are moving vertically
            if(directionY!=0){

                // Check the tile on the next location
                // If none are solid
                if(!WorldPositionIsSolid(playerX,nextPlayerY)){
                    
                    // Update the player's y position
                    playerY=nextPlayerY;
                }
            }

        }

        // Offset by 8 and 16. Taking into consieration the default OAM sprite offset
        move_metasprite(ball_metasprites[0],0,0,playerX+8,playerY+16);

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
