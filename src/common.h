#define SOLID 1
#define PLAYER_MOVE_SPEED 10
#define PLAYER_HALF_WIDTH 8
#define PLAYER_HALF_HEIGHT 8
#define GRID_NODE_SIZE 8
#define NUMBER_OF_SOLID_TILES 9

extern uint16_t playerX,playerY;


void SetupDemo();
uint8_t WorldPositionIsSolid(uint16_t x, uint16_t y);
void GetPlayerInput(uint16_t* nextPlayerX,uint16_t* nextPlayerY,int8_t* directionX, int8_t* directionY);