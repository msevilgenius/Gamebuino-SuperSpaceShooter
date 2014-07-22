/* 
 * File:   Enemy.cpp
 * Author: Michael
 * 
 * Created on 22 July 2014, 09:10
 */

#include "Enemy.h"

extern Gamebuino gb;
extern BulletManager bullets;

const byte ENEMY_SPRITE_1[] PROGMEM = {
    7, 7,
    B00000001, 
    B00111001, 
    B11111111, 
    B10101011, 
    B11111111, 
    B00111001, 
    B00000001, 
};

Enemy::Enemy(int8_t x, int8_t y, ENEMY_TYPE type) {
    this->x = x;
    this->y = y;
    this->type = type;
}

Enemy::Enemy() {
    this->type = DEAD;
    this->x = 0;
    this->y = 0;
}

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
}

void Enemy::draw(){
    gb.display.drawBitmap(x-3, y-3, ENEMY_SPRITE_1);
}

void Enemy::update(){
    x--;
    if(x<-2){
        type = DEAD;
        return;
    }
    if(gb.frameCount%16==0){
        bullets.createBullet(x-4, y, DIR_W, 2);
        bullets.createBullet(x-3, y-3, DIR_NW, 2);
        bullets.createBullet(x-3, y+3, DIR_SW, 2);
    }
}

boolean Enemy::isDead(){
    return type == DEAD;
}
