#include <SPI.h>
#include <Gamebuino.h>
#include "Player.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "globals.h"

Gamebuino gb;

Player player;
BulletManager bullets;
EnemyManager enemies;

// button states (whether they are pressed or not)
bool upbtn = false,
        dnbtn = false,
        lfbtn = false,
        rtbtn = false,
        abtn  = false;

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
    gb.pickRandomSeed();
    gb.battery.show = false;
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
        
        //rendering
        enemies.update();
        bullets.updateAndDraw();
        player.draw();
    }
}
