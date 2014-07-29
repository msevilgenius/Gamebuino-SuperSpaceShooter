#include <SPI.h>
#include <Gamebuino.h>
#include "Player.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "globals.h"

Gamebuino gb;

extern byte font3x5[];

const byte logo[] PROGMEM = {
    64, 28,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
    B01111000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01000100, 
    B01001000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00101000, 
    B01000001, B00010011, B11100111, B11011100, B00000000, B00000000, B00000000, B00000000, 
    B01111001, B00010010, B00100100, B01010100, B00000000, B00010000, B00000000, B00101000, 
    B00001001, B00010010, B00100111, B11010000, B00000000, B00101000, B00000000, B01000100, 
    B00001001, B00010010, B00100100, B00010000, B00000000, B00010000, B00000000, B00000000, 
    B01001001, B00010010, B00100100, B01010000, B00000000, B00000000, B00000000, B00000000, 
    B01111001, B11110011, B11100111, B11010000, B00000000, B00000000, B00000001, B11110000, 
    B00000000, B00000010, B00111100, B00000000, B00000000, B00000000, B00000010, B01000000, 
    B00000000, B00000010, B00100100, B00000000, B00000000, B00000000, B00000000, B11110000, 
    B00000000, B00000010, B00100000, B11111001, B11100011, B11001111, B10000001, B11100000, 
    B00111110, B00000000, B00111100, B10001000, B00100010, B01001000, B10000000, B11110000, 
    B00011000, B00000000, B00000100, B10001001, B11100010, B00001111, B10000010, B01000000, 
    B00011100, B00000000, B00000100, B10001001, B00100010, B00001000, B00000001, B11110000, 
    B00011111, B10011100, B00100100, B10001001, B00100010, B01001000, B10000000, B00000000, 
    B00011100, B00000000, B00111100, B11111001, B11100011, B11001111, B10000000, B00000000, 
    B00011000, B00000000, B00000000, B10000000, B00000000, B00000000, B00000000, B00000000, 
    B00111110, B00000000, B00000000, B10000000, B00000000, B00000000, B00000000, B00000000, 
    B00000000, B00000000, B00111100, B10000000, B00000000, B00000100, B00000000, B00000000, 
    B00000000, B00000000, B00100100, B10000000, B00000000, B00000100, B00000000, B00000000, 
    B00000000, B00000000, B00100000, B11111001, B11110011, B11101111, B01111101, B11000000, 
    B00000000, B00000000, B00111100, B10001001, B00010010, B00100100, B01000101, B01000000, 
    B00000000, B00100000, B00000100, B10001001, B00010010, B00100100, B01111101, B00000000, 
    B00000000, B00000000, B00000100, B10001001, B00010010, B00100100, B01000001, B00000000, 
    B00000000, B00000000, B00100100, B10001001, B00010010, B00100100, B01000101, B00000000, 
    B00100000, B00000000, B00111100, B10001001, B11110011, B11100111, B01111101, B00000000, 
    B01010000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, 
};

Player player;
BulletManager bullets;
EnemyManager enemies;

uint16_t score;

// button states (whether they are pressed or not)
bool upbtn = false,
        dnbtn = false,
        lfbtn = false,
        rtbtn = false,
        abtn  = false;


void reset(){
    score = 0;
    player.begin();
    bullets.reset();
    enemies.reset();
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

void drawScore(){
    gb.display.setFont(font3x5);
    gb.display.cursorX = 1;
    gb.display.cursorY = 1;
    gb.display.print(score);
}

void setup() {
    gb.begin();
    gb.titleScreen(F(" SSS by msevilgenius"), logo);
    gb.pickRandomSeed();
    gb.battery.show = false;
    reset();
}

void loop() {
    if (gb.update()) {
        updateButtons();
        //player movement
        if(upbtn){
            player.moveUp();
        }
        if(dnbtn){
            player.moveDown();
        }
        if(lfbtn){
            player.moveLeft();
        }
        if(rtbtn){
            player.moveRight();
        }
        
        //player shooting
        if(abtn||gb.buttons.pressed(BTN_A)){
            player.shoot();
        }
        
        //temporary way to create enemies for testing
        if(gb.buttons.pressed(BTN_B)){
            enemies.createEnemy(LCDWIDTH+3, random(3, LCDHEIGHT-3), BASIC);
        }
        
        if(gb.buttons.pressed(BTN_C)){
            gb.titleScreen(F(" SSS by msevilgenius"), logo);
            reset();
        }
        
        
        // updating and rendering
        enemies.update();
        bullets.updateAndDraw();
        player.draw();
        drawScore();
    }
}
