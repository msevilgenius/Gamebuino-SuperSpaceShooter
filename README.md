Gamebuino-SuperSpaceShooter
===========================

Side scrolling shoot 'em up for the gamebuino  

To build it's probably easiest to use Netbeans and the [Arduino Netbeans plugin](https://code.google.com/p/arduino-netbeans/) you may need to update the Makefile (in netbeans under 'Important Files') specifically setting the 'ARDUINO\_BASE_DIR' to the location you installed the Arduino IDE  

Or you cna make main.cpp an ino file and give it the same name as the folder it's in 'Gamebuino-SuperSpaceShooter-master' if you downloaded the zip, then you can open it with the Arduino IDE.

###Current State
At the moment the basics of gameplay are implemented, you can move the player around with the arrows and shoot with A. Pressing B will spawn an enemy. Enemies will dissapear when hit by the players bullets, enemy bullets hitting the player are detected and the bullet is destroyed but nothing happens to the player yet.
See 'todo.txt' for planned features.
