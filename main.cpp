#include <SPI.h>
#include <Gamebuino.h>


#define MAX_ENEMIES 10
#define MAX_BULLETS 50
#define BULLET_SIZE 3

Gamebuino gb;

//spites
const byte SHIP_SPRITE[] PROGMEM = {
    7, 7,
    B11111001, 
    B01100001, 
    B01110001, 
    B11111111, 
    B01110001, 
    B01100001, 
    B11111001
};

enum ENEMY_TYPE {};
enum DIRECTION {DIR_N, DIR_NE,DIR_E, DIR_SE, DIR_S, DIR_SW, DIR_W, DIR_NW};

typedef struct{
    int8_t x;
    int8_t y;
    ENEMY_TYPE type;
}Enemy;

typedef struct{
    int8_t x;
    int8_t y;
    int8_t bullet_speed;
    int8_t last_bullet_time;
    byte abilities;
}Player;

typedef struct{
    int8_t x;
    int8_t y;
    int8_t speed;
    DIRECTION direction;
    uint8_t age;
}Bullet;

Bullet bullets[MAX_BULLETS];
Enemy enemies[MAX_ENEMIES];
Player player;

// button states (whether they are pressed or not)
boolean upbtn = false,
        dnbtn = false,
        lfbtn = false,
        rtbtn = false,
        abtn  = false;

void initPlayer(){
    player.x = 10;
    player.y = LCDHEIGHT /2;
    player.bullet_speed = 2;
    player.abilities = 0;
    player.last_bullet_time = 5;
}

/**
 * creates a new bullets and adds it to the bullet array
 * @param x horizontal coordinate
 * @param y vertival coordinate
 * @param dir direction the bullet is travelling (8 posibilities)
 * @param speed number of pixels to move per step;
 */
void createBullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed){
    
    // not terribly efficient way to find an inactive bullet
    int8_t i = 0;
    while(bullets[i].age != 0 && i < MAX_BULLETS-1){
        i++;
    }
    
    // initialise
    bullets[i].x = x;
    bullets[i].y = y;
    bullets[i].age = 1;
    bullets[i].direction = dir;
    bullets[i].speed = speed;
}


/**
 * updates the position of and also draws all of the bullets
 */
void updateBullets(){
    for(int8_t i = 0;i < MAX_BULLETS;i++){
        
        // Note: age = 0 means that the bullet doesn't 'exist' so it can be overwritten, it's a dirty hack
        
        // bullet doesn't exist so skip to the next one
        if(bullets[i].age == 0){
            continue;
        }
        
        // increment age
        bullets[i].age++;
        //'destroy' too old bullets
        if (bullets[i].age > 200){
            bullets[i].age = 0;
            continue;
        }
        //'destroy' bullets off screen
        if(bullets[i].x < 0 || bullets[i].x > LCDWIDTH ||bullets[i].y < 0 || bullets[i].y > LCDHEIGHT){
            bullets[i].age = 0;
            continue;
        }
        
        /*
         *  move and draw
         * combined becuase move direction and the direction of the draw line
         * are the same it makes sense to do them at the same time,
         * rather than have this switch statement run twice
         */
        
        switch (bullets[i].direction) {
            case DIR_N:
                bullets[i].y -= bullets[i].speed;
                gb.display.drawFastVLine(bullets[i].x,bullets[i].y, BULLET_SIZE);
                break;
            case DIR_NE:
                bullets[i].y -= bullets[i].speed;
                bullets[i].x += bullets[i].speed;
                break;
            case DIR_E:
                bullets[i].x += bullets[i].speed;
                gb.display.drawFastHLine(bullets[i].x,bullets[i].y, BULLET_SIZE);
                break;
            case DIR_SE:
                bullets[i].y += bullets[i].speed;
                bullets[i].x += bullets[i].speed;
                break;
            case DIR_S:
                bullets[i].y += bullets[i].speed;
                gb.display.drawFastVLine(bullets[i].x,bullets[i].y, -BULLET_SIZE);
                break;
            case DIR_SW:
                bullets[i].y += bullets[i].speed;
                bullets[i].x -= bullets[i].speed;
                break;
            case DIR_W:
                bullets[i].x -= bullets[i].speed;
                gb.display.drawFastHLine(bullets[i].x,bullets[i].y, -BULLET_SIZE);
                break;
            case DIR_NW:
                bullets[i].y -= bullets[i].speed;
                bullets[i].x -= bullets[i].speed;
                break;
        }
    }
}

/**
 * draw the players ship
 */
void drawPlayer(){
    gb.display.drawBitmap(player.x-5, player.y-3, SHIP_SPRITE);
}

/**
 * updates the status of the buttons
 * 
 * we don't want to have to constantly be pressing movement/shooting buttons
 * we want to be able to just hold them down
 */
void updateButtons(){
    if(!upbtn && gb.buttons.pressed(BTN_UP)){
        upbtn = true;
    }else if(upbtn && gb.buttons.released(BTN_UP)){
        upbtn = false;
    }
    if(!dnbtn && gb.buttons.pressed(BTN_DOWN)){
        dnbtn = true;
    }else if(dnbtn && gb.buttons.released(BTN_DOWN)){
        dnbtn = false;
    }
    if(!lfbtn && gb.buttons.pressed(BTN_LEFT)){
        lfbtn = true;
    }else if(lfbtn && gb.buttons.released(BTN_LEFT)){
        lfbtn = false;
    }
    if(!rtbtn && gb.buttons.pressed(BTN_RIGHT)){
        rtbtn = true;
    }else if(rtbtn && gb.buttons.released(BTN_RIGHT)){
        rtbtn = false;
    }
    if(!abtn && gb.buttons.pressed(BTN_A)){
        abtn = true;
    }else if(abtn && gb.buttons.released(BTN_A)){
        abtn = false;
    }
}

void setup() {
    gb.begin();
    gb.titleScreen(F("side scroller"));
    initPlayer();
}

void loop() {
    if (gb.update()) {
        updateButtons();
        //player movement
        if(upbtn && player.y > 2){
            player.y--;
        }
        if(dnbtn && player.y < LCDHEIGHT - 3){
            player.y++;
        }
        if(lfbtn && player.x >= 5){
            player.x--;
        }
        if(rtbtn && player.x < LCDWIDTH - 10){
            player.x++;
        }
        
        //player shooting
        if(player.last_bullet_time > 5){
            if(abtn){
                if(player.abilities == 0){
                    createBullet(player.x + 1, player.y, DIR_E, player.bullet_speed);
                    player.last_bullet_time = 0;
                }
            }
        }else{
            player.last_bullet_time++;
        }
        
        
        //rendering
        updateBullets();
        drawPlayer();
    }
}
