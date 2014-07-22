/* 
 * File:   Enemy.cpp
 * Author: Michael
 * 
 * Created on 22 July 2014, 09:10
 */

#include "Enemy.h"

Enemy::Enemy(int8_t x, int8_t y) {
    this->x = x;
    this->y = y;
}

Enemy::Enemy() {
}

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
}

