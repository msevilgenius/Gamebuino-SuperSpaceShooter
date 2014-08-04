/* 
 * File:   Bullet.cpp
 * Author: Michael
 * 
 * Created on 21 July 2014, 20:08
 */

#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "EffectsManager.h"
#include <Gamebuino.h>

extern Gamebuino gb;
extern Player player;
extern EnemyManager enemies;
extern EffectsManager effectsManager;

void Bullet::init(int8_t x, int8_t y, DIRECTION dir, int8_t speed, byte source) {
    this->x = x;
    this->y = y;
    this->direction = dir;
    this->speed = speed;
    this->source = source;
}

Bullet::Bullet() {
    this->x = 0;
    this->y = 0;
    this->direction = D_NONE;
    this->speed = 0;
    this->source = -1;
}

Bullet::~Bullet() {
}

void Bullet::update(){
    // 'destroy' bullets off screen
    if(x < 0 || x > LCDWIDTH ||y < 0 || y > LCDHEIGHT){
        direction = D_NONE;
        return;
    }
    
    /*
     * move and draw
     * combined becuase move direction and the direction of the draw line
     * are the same it makes sense to do them at the same time,
     * rather than have this switch statement run twice
     */

    switch (direction) {
        case DIR_N:
            updateN();
            break;
        case DIR_NE:
            updateNE();
            break;
        case DIR_E:
            updateE();
            break;
        case DIR_SE:
            updateSE();
            break;
        case DIR_S:
            updateS();
            break;
        case DIR_SW:
            updateSW();
            break;
        case DIR_W:
            updateW();
            break;
        case DIR_NW:
            updateNW();
            break;
        case D_NONE:
            return;
    }
}


void Bullet::updateN(){
    y -= speed;
    gb.display.drawFastVLine(x, y, BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x - 1, y + BULLET_SIZE - 1, x+1, y + BULLET_SIZE - 1);
    }
    testCollision(x,y,x,y+1,x,y+2);
}
void Bullet::updateNE(){
    if(gb.frameCount%3){//twice every 3 frames
        y -= speed;
        x += speed;
    }
    gb.display.drawLine(x, y, x-DIAG_BULLET_SIZE, y+DIAG_BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x - BULLET_SIZE, y + 1, x - 1, y + BULLET_SIZE);
    }
    testCollision(x,y,x-1,y+1,x-2,y+2);
}

void Bullet::updateE(){
    x += speed;
    gb.display.drawFastHLine(x - (BULLET_SIZE - 1), y, BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x - (BULLET_SIZE - 1), y - 1, x - (BULLET_SIZE - 1), y + 1);
    }
    testCollision(x,y,x-1,y,x-2,y);
}

void Bullet::updateSE(){
    if(gb.frameCount%3){
        y += speed;
        x += speed;
    }
    gb.display.drawLine(x, y, x-DIAG_BULLET_SIZE, y-DIAG_BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x - BULLET_SIZE, y - 1, x - 1, y - BULLET_SIZE);
    }
    testCollision(x,y,x-1,y-1,x-2,y-2);
}

void Bullet::updateS(){
    y += speed;
    gb.display.drawFastVLine(x, y - (BULLET_SIZE - 1), BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x - 1, y - (BULLET_SIZE - 1), x + 1, y - (BULLET_SIZE - 1));
    }
    testCollision(x,y,x,y-1,x,y-2);
}

void Bullet::updateSW(){
    if(gb.frameCount%3){
        y += speed;
        x -= speed;
    }
    gb.display.drawLine(x, y, x+DIAG_BULLET_SIZE, y-DIAG_BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x + BULLET_SIZE, y - 1, x + 1, y - BULLET_SIZE);
    }
    testCollision(x,y,x+1,y-1,x+2,y-2);
}

void Bullet::updateW(){
    x -= speed;
    gb.display.drawFastHLine(x, y, BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x + BULLET_SIZE - 1, y - 1, x + BULLET_SIZE - 1, y + 1);
    }
    testCollision(x,y,x-1,y,x-2,y);
}

void Bullet::updateNW(){
    if(gb.frameCount%3){
        y -= speed;
        x -= speed;
    }
    gb.display.drawLine(x, y, x+DIAG_BULLET_SIZE, y+DIAG_BULLET_SIZE);
    if(source == SRC_PLAYER){
        gb.display.drawLine(x + BULLET_SIZE, y + 1, x + 1, y + BULLET_SIZE);
    }
    testCollision(x,y,x+1,y+1,x+2,y+2);
}

void Bullet::testCollision(int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t x3, int8_t y3){// co-ords of pixels of bullet
    HitBox hb;
    if (source == SRC_ENEMY){
        hb = player.getCollisionBox();
        if( gb.collidePointRect(x1,y1,hb.x,hb.y,hb.w,hb.h)||
                gb.collidePointRect(x2,y2,hb.x,hb.y,hb.w,hb.h)||
                gb.collidePointRect(x3,y3,hb.x,hb.y,hb.w,hb.h) ){
            player.hit();
            direction = D_NONE; // make me dead
            effectsManager.createEffect(EXPLOSION_SMALL,x,y);
            return;
        }
    }else if (source == SRC_PLAYER){
        if(enemies.TestShot(x1, y1, x2, y2, x3, y3)){
            direction = D_NONE;
            effectsManager.createEffect(EXPLOSION_SMALL,x,y);
        }
    }
}

bool Bullet::isDead(){
    return(direction == D_NONE);
}

