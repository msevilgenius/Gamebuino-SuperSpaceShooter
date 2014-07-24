/* 
 * File:   EnemyManager.cpp
 * Author: Michael
 * 
 * Created on 22 July 2014, 12:05
 */

#include "EnemyManager.h"

extern Gamebuino gb;

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::update(){
    for(int8_t i = 0; i < MAX_ENEMIES; i++){
        if(!enemies[i].isDead()){
            enemies[i].update();
            enemies[i].draw();
        }
    }
}

void EnemyManager::createEnemy(int8_t x, int8_t y, ENEMY_TYPE type){
    // not terribly efficient way to find an dead enemy
    int8_t i = 0;
    while(!enemies[i].isDead() && i < MAX_ENEMIES-1){
        i++;
    }
    Enemy newEnemy(x, y, type);
    enemies[i] = newEnemy;
    
}

// this method is here becuase there seems to be something fundamentally wrong with accessing extern arrays using a variable as the index
bool EnemyManager::TestShot(int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t x3, int8_t y3){
    HitBox hb;
    for(uint8_t i = 0; i< MAX_ENEMIES; i++){
        if(!enemies[i].isDead()){
            hb = enemies[i].getCollisionBox();
            if( gb.collidePointRect(x3,y3,hb.x,hb.y,hb.w,hb.h)||
                    gb.collidePointRect(x2,y2,hb.x,hb.y,hb.w,hb.h)||
                    gb.collidePointRect(x1,y1,hb.x,hb.y,hb.w,hb.h) ){
                enemies[i].hit();
                return true;
            }

        }
    }
    return false;
}