/* 
 * File:   Enemy.cpp
 * Author: Michael
 * 
 * Created on 22 July 2014, 09:10
 */

#include "Enemy.h"

extern Gamebuino gb;
extern BulletManager bullets;
extern int16_t score;

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

void Enemy::init(int8_t x, int8_t y, ENEMY_TYPE type) {
    this->x = x;
    this->y = y;
    this->type = type;
}

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::draw(){
    gb.display.drawBitmap(x-3, y-3, ENEMY_SPRITE_1);
}

void Enemy::update(){
    x--;
    if(type == DEAD)return;
    if(x<-2){
        type = DEAD;
        return;
    }
    if(gb.frameCount%16==0){
        bullets.createBullet(x, y, DIR_W, 2, SRC_ENEMY);
        bullets.createBullet(x, y, DIR_NW, 2, SRC_ENEMY);
        bullets.createBullet(x, y, DIR_SW, 2, SRC_ENEMY);
    }
}

boolean Enemy::isDead(){
    return type == DEAD;
}


HitBox Enemy::getCollisionBox(){
    HitBox hb;
    hb.x = this->x-3;
    hb.y = this->y-2;
    hb.w = 7;
    hb.h = 5;
    return hb;
}

void Enemy::hit(){
    type = DEAD;
    score += 10;
}