#include <stdlib.h>
#include "myLib.h"

typedef struct {
	u16 color;
	int row;
	int col;
	int width;
	int height;
	int exists;
} BRICK;

typedef struct {
	int row;
	int col;
	int width;
	int height;
	int coldel;
} PADDLE;

typedef struct {
	int col;
	int row;
	int coldel;
	int rowdel;
	int oldcol;
	int oldrow;
} BALL;

void showStartScreen();
void showEndScreen();
void initializeBricks();
void resetGame();
void updateScore(int newScore);
void movePaddle(int dir);
void moveBall();
int brickCollide();
int checkWin();
void win();