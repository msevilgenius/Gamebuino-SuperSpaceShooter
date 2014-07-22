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