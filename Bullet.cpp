/* 
 * File:   Bullet.cpp
 * Author: Michael
 * 
 * Created on 21 July 2014, 20:08
 */

#include "Bullet.h"
#include <Gamebuino.h>

extern Gamebuino gb;

Bullet::Bullet(int8_t x, int8_t y, DIRECTION dir, int8_t speed) {
    this->x = x;
    this->y = y;
    this->age = 1;
    this->direction = dir;
    this->speed = speed;
}

Bullet::Bullet() {
    this->x = 0;
    this->y = 0;
    this->age = 0;
    this->direction = DIR_N;
    this->speed = 0;
}

Bullet::~Bullet() {
}

void Bullet::update(){
    // Note: age = 0 means that the bullet doesn't 'exist' so it can be overwritten, it's a dirty hack
    
    // bullet doesn't exist so skip to the next one
    if(age == 0){
        return;
    }

    // increment age
    age++;
    //'destroy' too old bullets
    if (age > 200){
        age = 0;
        return;
    }
    //'destroy' bullets off screen
    if(x < 0 || x > LCDWIDTH ||y < 0 || y > LCDHEIGHT){
        age = 0;
        return;
    }

    /*
     *  move and draw
     * combined becuase move direction and the direction of the draw line
     * are the same it makes sense to do them at the same time,
     * rather than have this switch statement run twice
     */

    switch (direction) {
        case DIR_N:
            y -= speed;
            gb.display.drawFastVLine(x,y, BULLET_SIZE);
            break;
        case DIR_NE:
            y -= speed;
            x += speed;
            break;
        case DIR_E:
            x += speed;
            gb.display.drawFastHLine(x,y, BULLET_SIZE);
            break;
        case DIR_SE:
            y += speed;
            x += speed;
            break;
        case DIR_S:
            y += speed;
            gb.display.drawFastVLine(x,y, -BULLET_SIZE);
            break;
        case DIR_SW:
            y += speed;
            x -= speed;
            break;
        case DIR_W:
            x -= speed;
            gb.display.drawFastHLine(x,y, -BULLET_SIZE);
            break;
        case DIR_NW:
            y -= speed;
            x -= speed;
            break;
    }
}

bool Bullet::isDead(){
    return(age == 0);
}

