/* 
 * File:   Enemy.cpp
 * Author: Michael
 * 
 * Created on 22 July 2014, 09:10
 */

#include "Enemy.h"
#include <avr/pgmspace.h>
#include "enemyTypes.h"
#include "EffectsManager.h"

extern Gamebuino gb;
extern BulletManager bullets;
extern EffectsManager effectsManager;
extern int16_t score;
extern const byte *enemy_types[];

void Enemy::init(int8_t x, int8_t y, ENEMY_TYPE type) {
    this->x = x;
    this->y = y;
    this->type = type;
    last_bullet_time = 0;
    shoot_frame = 0;
}

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::draw(){
    gb.display.drawBitmap(x-3, y-3, (const byte*)pgm_read_word(&(enemy_types[type*3])));
}

void Enemy::update(){
    if(type == DEAD)return;
    if(x<-2){
        type = DEAD;
        return;
    }
    last_bullet_time++;
    move();
    shoot();
}

boolean Enemy::isDead(){
    return type == DEAD;
}


HitBox Enemy::getCollisionBox(){
    HitBox hb;
    hb.x = this->x - 3;
    hb.y = this->y - (type == SPINNER ? 2 : 3);
    hb.w = 7;
    hb.h = (type == SPINNER ? 5 : 7);
    return hb;
}

void Enemy::hit(){
    type = DEAD;
    score += 10;
    effectsManager.createEffect(EXPLOSION_LARGE, x, y);
}

void Enemy::move(){
    const byte *ref = (const byte*)pgm_read_word(&(enemy_types[type*3+1]));
    uint8_t frame = gb.frameCount % (uint8_t )pgm_read_byte(&(ref[0]));
    x += (int8_t) pgm_read_byte(&(ref[frame*2+1]));
    y += (int8_t) pgm_read_byte(&(ref[frame*2+2]));
}

void Enemy::shoot(){
    uint8_t num_frames;
    const byte *ref = (const byte*)pgm_read_word(&(enemy_types[type*3+2]));
    num_frames = (uint8_t)pgm_read_byte(&(ref[0]));
    // the calculation in the index of ref is a horrible way of finding the data for the previous frame, which has to wrap around negatively
    if (last_bullet_time < (uint8_t)pgm_read_byte(&(ref[((shoot_frame+(num_frames-1))%num_frames +1)*2]))){
        return;
    }
    
    byte directions = (byte)pgm_read_byte(&(ref[(shoot_frame*2+1)])) ;
    if(directions & 0b10000000){
        bullets.createBullet(x, y, DIR_NW, 2, SRC_ENEMY);
    }
    if(directions & 0b01000000){
        bullets.createBullet(x, y, DIR_W, 2, SRC_ENEMY);
    }
    if(directions & 0b00100000){
        bullets.createBullet(x, y, DIR_SW, 2, SRC_ENEMY);
    }
    if(directions & 0b00010000){
        bullets.createBullet(x, y, DIR_S, 2, SRC_ENEMY);
    }
    if(directions & 0b00001000){
        bullets.createBullet(x, y, DIR_SE, 2, SRC_ENEMY);
    }
    if(directions & 0b00000100){
        bullets.createBullet(x, y, DIR_E, 2, SRC_ENEMY);
    }
    if(directions & 0b00000010){
        bullets.createBullet(x, y, DIR_NE, 2, SRC_ENEMY);
    }
    if(directions & 0b00000001){
        bullets.createBullet(x, y, DIR_N, 2, SRC_ENEMY);
    }
    
    shoot_frame = (shoot_frame+1) % num_frames;
    last_bullet_time = 0;
}