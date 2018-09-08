/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=3 images smileyFace.jpg StartScreen.bmp GameOver.bmp bomb.png 
 * Time-stamp: Sunday 11/12/2017, 14:36:58
 * 
 * Image Information
 * -----------------
 * smileyFace.jpg 15@15
 * StartScreen.bmp 240@160
 * GameOver.bmp 240@160
 * bomb.png 28@30
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef IMAGES_H
#define IMAGES_H

extern const unsigned short smileyFace[225];
#define SMILEYFACE_SIZE 450
#define SMILEYFACE_LENGTH 225
#define SMILEYFACE_WIDTH 15
#define SMILEYFACE_HEIGHT 15

extern const unsigned short StartScreen[38400];
#define STARTSCREEN_SIZE 76800
#define STARTSCREEN_LENGTH 38400
#define STARTSCREEN_WIDTH 240
#define STARTSCREEN_HEIGHT 160

extern const unsigned short GameOver[38400];
#define GAMEOVER_SIZE 76800
#define GAMEOVER_LENGTH 38400
#define GAMEOVER_WIDTH 240
#define GAMEOVER_HEIGHT 160

extern const unsigned short bomb[840];
#define BOMB_SIZE 1680
#define BOMB_LENGTH 840
#define BOMB_WIDTH 28
#define BOMB_HEIGHT 30

#endif

