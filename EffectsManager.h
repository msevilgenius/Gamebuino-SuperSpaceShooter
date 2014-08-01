/* 
 * File:   EffectsManager.h
 * Author: Michael
 *
 * Created on 01 August 2014, 12:01
 */

#ifndef EFFECTSMANAGER_H
#define	EFFECTSMANAGER_H

#include "globals.h"

#define MAX_EFFECTS 8
#define MAX_STARS 8

class EffectsManager {
public:
    EffectsManager();
    virtual ~EffectsManager();
    void init();
    void update();
    void createEffect(EFFECT_TYPE type, int8_t x, int8_t y);
private:
    typedef struct{
        EFFECT_TYPE type;
        int8_t x;
        int8_t y;
        uint8_t age;
    }effect;
    typedef struct{
        int8_t x;
        int8_t y;
    }point;
    effect effects[MAX_EFFECTS];
    point starField[MAX_STARS];
    int8_t starTimer;
    void initEffect(int8_t id, EFFECT_TYPE type, int8_t x, int8_t y);
    void drawStarField();
};

#endif	/* EFFECTSMANAGER_H */

