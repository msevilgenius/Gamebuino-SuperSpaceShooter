Gamebuino-SuperSpaceShooter
===========================

Side scrolling shoot 'em up for the gamebuino  

To build with the arduino IDE you can make main.cpp an ino file and give it the same name as the folder it's in e.g. 'Gamebuino-SuperSpaceShooter-master.ino' if you downloaded the zip, then you can open it with the Arduino IDE.

###Current State
At the moment the basics of gameplay are implemented, you can move the player around with the arrows and shoot with A. Pressing B will spawn an enemy. There is a basic score and health system, when you die the game just resets for now.
See 'todo.txt' for planned features.

#####Enemy Type System
Hopefully the comments in EnemyTypes.h should explain how to the system is implemented.
Basically, you need three const byte progmem arrays: the first is the sprite, it should be 7x7 as the ones alreaddy there; 
second, an array containing the movement sequence, the first item is the number of steps in the sequence, the rest are pairs of values signed integers the x then y movemnts for that step, for example -1, 0 would move to the left 1 pixel; 
third is the pattern for shooting, again the first byte is the number of steps in the sequence, the rest come in pairs, the first of each pair is a byte representing the directions which bullets are to be fired, each bit represents a direction, leftmost is NorthWest, then moving anticlockwise, the second byte of the pair is the number of frames until the next set of bullets should be fired.

Put these three arrays in that order in *enemy\_types[] in EnemyTypes.h after the ones already there, then in Globals.h add an entry for your enemy to enum ENEMY\_TYPES then ad one to the value in random() in if(gb.buttons.pressed(BTN_B)) in main.cpp.
