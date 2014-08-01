/* 
 * File:   EffectsManager.cpp
 * Author: Michael
 * 
 * Created on 01 August 2014, 12:01
 */

#include "EffectsManager.h"
#include <Gamebuino.h>
extern Gamebuino gb;

const byte smallExplosion0[] PROGMEM = {
    5, 3,
    B00000000,
    B00000000,
    B00100000
};

const byte smallExplosion1[] PROGMEM = {
    5, 4,
    B00000000,
    B00010000,
    B01000000,
    B00100000
};

const byte smallExplosion2[] PROGMEM = {
    5, 5,
    B01000000,
    B00001000,
    B10000000,
    B10000000,
    B00100000
};

const byte smallExplosion3[] PROGMEM = {
    5, 4,
    B00100000,
    B00000000,
    B00001000,
    B10000000
};

const byte *smallExplosion[] = {
    smallExplosion0,
    smallExplosion1,
    smallExplosion2,
    smallExplosion3
};

const byte largeExplosion0[] PROGMEM = {
    8, 5,
    B00000000,
    B00000000,
    B00000000,
    B0001000,
    B0001100
};

const byte largeExplosion1[] PROGMEM = {
    8, 7,
    B00000000,
    B00010000,
    B00100100,
    B00010010,
    B01001000,
    B00101100,
    B00010000
};

const byte largeExplosion2[] PROGMEM = {
    8, 8,
    B00010000,
    B00110010,
    B00000000,
    B00100010,
    B10000000,
    B00000000,
    B11000101,
    B00100010
};

const byte largeExplosion3[] PROGMEM = {
    8, 4,
    B01000000,
    B00000001,
    B10000000,
    B00000000,
    B00001000,
    B00000000,
    B00000000,
    B01000001
};

const byte *largeExplosion[] = {
    largeExplosion0,
    largeExplosion1,
    largeExplosion2,
    largeExplosion3
};

EffectsManager::EffectsManager() {
}

EffectsManager::~EffectsManager() {
}

void EffectsManager::init(){
    for(int8_t i = 0; i < MAX_EFFECTS; i++){
        effects[i].type = E_NONE;
    }
    starTimer = 0;
}

void EffectsManager::createEffect(EFFECT_TYPE type, int8_t x, int8_t y){
    int8_t i = 0;
    while(effects[i].type != E_NONE && i < MAX_EFFECTS-1){
        i++;
    }
    initEffect(i, type, x, y);
}

void EffectsManager::initEffect(int8_t id, EFFECT_TYPE type, int8_t x, int8_t y){
    effects[id].type = type;
    effects[id].x = x;
    effects[id].y = y;
    effects[id].age = 0;
}

void EffectsManager::update(){
    for(int8_t i = 0; i < MAX_EFFECTS; i++){
        switch(effects[i].type){
            case EXPLOSION_SMALL:
                if(effects[i].age > 3){
                    effects[i].type = E_NONE;
                    break;
                }
                // draw the frame with random flip and rotaion - we don't want every one to look exactly the same!
                gb.display.drawBitmap(
                    effects[i].x - 2, effects[i].y - 2, smallExplosion[effects[i].age], random(4), random(4));
                break;
            case EXPLOSION_LARGE:
                if(effects[i].age > 3){
                    effects[i].type = E_NONE;
                    break;
                }
                gb.display.drawBitmap(
                    effects[i].x - 3, effects[i].y - 3, largeExplosion[effects[i].age], random(4), random(4));
                break;
            
            // fallthrough
            case E_NONE:
            default:
                continue;
        }
        effects[i].age++;
    }
    drawStarField();
}

void EffectsManager::drawStarField(){
    for(int8_t i = 0; i < MAX_STARS; i++){
        starField[i].x -= (gb.frameCount % 2);
        if(starField[i].x >= 0){
            gb.display.drawPixel(starField[i].x, starField[i].y);
        }else if(starTimer < 1){
            starField[i].x = LCDWIDTH;
            starField[i].y = random(LCDHEIGHT);
            starTimer = random(16,64);
        }
    }
    starTimer--;
}

