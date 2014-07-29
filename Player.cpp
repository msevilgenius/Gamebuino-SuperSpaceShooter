/* 
 * File:   Player.cpp
 * Author: Michael
 * 
 * Created on 21 July 2014, 19:21
 */

#include "Player.h"

extern Gamebuino gb;
extern BulletManager bullets;
extern void reset();

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

const byte heart2[] PROGMEM = {
    5, 5, 
    B01010111, 
    B11111111, 
    B11111111, 
    B01110111, 
    B00100111
};

const byte heart1[] PROGMEM = {
    5, 5, 
    B01010111, 
    B11101111, 
    B11001111, 
    B01110111, 
    B00100111
};

const byte heart0[] PROGMEM = {
    5, 5, 
    B01010111, 
    B10101111, 
    B10001111, 
    B01010111, 
    B00100111
};

const byte *hearts[] = {
    heart0,
    heart1,
    heart2
};

Player::Player() {
}

Player::~Player(){
}

void Player::begin(){
    x = 10;
    y = LCDHEIGHT /2;
    bullet_speed = 2;
    abilities = 0;
    last_bullet_time = 5;
    health = 6;
}

void Player::draw(){
    if (last_bullet_time < 200)last_bullet_time++; //piggy backing on a function executed every frame
    gb.display.drawBitmap(x-5, y-3, SHIP_SPRITE);
    //draw health
    gb.display.drawBitmap(11, LCDHEIGHT - 6, hearts[max(0,health-4)]);
    gb.display.drawBitmap(6, LCDHEIGHT - 6, hearts[max(0,min(health-2,2))]);
    gb.display.drawBitmap(1, LCDHEIGHT - 6, hearts[max(0,min(health,2))]);
}

void Player::shoot(){
    if(last_bullet_time > 5){// don't let the player shoot too often
        if(abilities == 0){
            bullets.createBullet(x + 1, y, DIR_E, bullet_speed, SRC_PLAYER);
            last_bullet_time = 0;
        }
    }
}

void Player::moveUp(){
    if(y > 2){
        y--;
    }
}

void Player::moveDown(){
    if(y < LCDHEIGHT - 3){
        y++;
    }
}

void Player::moveLeft(){
    if(x >= 5){
        x--;
    }
}

void Player::moveRight(){
    if(x < LCDWIDTH - 10){
        x++;
    }
}

HitBox Player::getCollisionBox(){
    HitBox hb;
    hb.x = x-2;
    hb.y = y-1;
    hb.w = 3;
    hb.h = 3;
    return hb;
}

// called when player is hit by bullet
void Player::hit(){
    gb.sound.playCancel();
    health--;
    //temporary
    if(health<0)
    reset();
}