/* 
 * File:   Player.cpp
 * Author: Michael
 * 
 * Created on 21 July 2014, 19:21
 */

#include "Player.h"

extern Gamebuino gb;
extern BulletManager bullets;

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

Player::Player() {
    x = 10;
    y = LCDHEIGHT /2;
    bullet_speed = 2;
    abilities = 0;
    last_bullet_time = 5;
}

Player::~Player() {
}

void Player::draw(){
    gb.display.drawBitmap(x-5, y-3, SHIP_SPRITE);
}

void Player::shoot(){
    if(last_bullet_time > 5){
            if(abilities == 0){
                bullets.createBullet(x + 1, y, DIR_E, bullet_speed);
                last_bullet_time = 0;
            }
        }else{
            last_bullet_time++;
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

