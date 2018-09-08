#include "game.h"
#include "text.h"
#include "images.h"
#include <stdio.h>

const int numBricks = 15;
BRICK bricks[15];
PADDLE paddle;
BALL ball;
int score = 0;

void showStartScreen() {
	int startNotPressed = TRUE;
	drawImage3(0,0,STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, StartScreen);
	//wait and don't draw anything else until the start key is pressed
	while(startNotPressed) {
		if(KEY_DOWN_NOW(BUTTON_START)) {
			startNotPressed = FALSE;
		}
	}
	drawRectangle(0,0,STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, BLACK);
}

void showEndScreen() {
	int selectNotPressed = TRUE;
	drawImage3(0,0,GAMEOVER_WIDTH, GAMEOVER_HEIGHT, GameOver);
	//wait and don't draw anything else until the select key is pressed
	while(selectNotPressed) {
		if(KEY_DOWN_NOW(BUTTON_SELECT)) {
			selectNotPressed = FALSE;
		}
	}
	showStartScreen();
	resetGame();
	delay(30);
}

void initializeBricks() {
	//randomly generate brick colors and draw them on the game screen
	u16 colors[] = {RED, GREEN, BLUE, MAGENTA, YELLOW, CYAN};
	int numColors = sizeof(colors)/sizeof(colors[0]);

	int initrow = 5;
	int initcol = 5;
	int rowdel = 15;
	int coldel = 47;
	//5 bricks per row, 3 rows, 15 bricks
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			bricks[count].color = colors[rand()%numColors];
			bricks[count].row = initrow + (rowdel*i);
			bricks[count].col = initcol + (coldel*j);
			bricks[count].exists = TRUE;
			bricks[count].width = 42;
			bricks[count].height = 10;
			count++;
		}
	}

	//draw bricks
	for (int i = 0; i < 15; i++) {
		drawRectangle(bricks[i].row, bricks[i].col, bricks[i].width, bricks[i].height, bricks[i].color);
	}
}

void resetGame() {
	//draws game screen and sets up structs for game logic
	drawRectangle(0,0,240,160,BLACK);
	initializeBricks();
	updateScore(0);

	paddle.col = 100;
	paddle.row = 135;
	paddle.width = 60;
	paddle.height = 8;
	paddle.coldel = 50;
	drawRectangle(paddle.row, paddle.col, paddle.width, paddle.height, GRAY);

	ball.col = 100;
	ball.row = 80;
	ball.oldcol = 100;
	ball.oldrow = 80;
	ball.coldel = 10;
	ball.rowdel = 20;
	drawImage3(ball.row, ball.col, SMILEYFACE_WIDTH, SMILEYFACE_HEIGHT, smileyFace);
}

void updateScore(int newScore) {
	drawRectangle(145,0,80,15, BLACK);
	score = newScore;
	char scoreStr[12];
	sprintf(scoreStr, "Score: %d", score);
	drawString(150, 0, scoreStr, WHITE);
}

void movePaddle(int dir) {

	if(dir) { //right
		drawRectangle(paddle.row, paddle.col, paddle.width, paddle.height, BLACK);
		if ((paddle.col + paddle.coldel + paddle.width) > 239) {
			paddle.col = (239 - paddle.width);
		} else {
			paddle.col += paddle.coldel;
		}
		drawRectangle(paddle.row, paddle.col, paddle.width, paddle.height, GRAY);

	} else {  //left
		drawRectangle(paddle.row, paddle.col, paddle.width, paddle.height, BLACK);
		if ((paddle.col - paddle.coldel) < 0) {
			paddle.col = 0;
		} else {
			paddle.col -= paddle.coldel;
		}
		drawRectangle(paddle.row, paddle.col, paddle.width, paddle.height, GRAY);
	}
}

int brickCollide() {
	//bricks will never be lower than 45 pixels, so if ball is that low, then ball won't collide
	if (ball.row > 45) {
		return 0;
	}
	//iterate backwards to go from right to left, bottom to top
	for(int i = numBricks - 1; i >= 0; i--) {
		//only check bricks that aren't broken
		if(bricks[i].exists) {
			//since we start with the bottom most brick, if the ball is below this brick in height we don't have to check the rest
			if(ball.row > bricks[i].row + bricks[i].height) {
				return 0;
			}
			if(ball.row <= (bricks[i].row + bricks[i].height) && (ball.col + (int)(SMILEYFACE_WIDTH / 2)) > bricks[i].col && (ball.col + (int)(SMILEYFACE_WIDTH / 2)) < (bricks[i].col + bricks[i].width)) {
				bricks[i].exists = FALSE;
				if (bricks[i].color == MAGENTA) {
					updateScore(score + 3);
				} else {
					updateScore(score + 1);
				}
				bricks[i].color = BLACK;
				drawRectangle(bricks[i].row, bricks[i].col, bricks[i].width, bricks[i].height, bricks[i].color);
				return bricks[i].row + bricks[i].height;
			}
		}
	}
	//not touching any bricks
	return 0;
}

 void moveBall() {
	delay(8);
	ball.oldrow = ball.row;
	ball.oldcol = ball.col;
	ball.row += ball.rowdel;
	ball.col += ball.coldel;

	int brickCollision = brickCollide();
	if(ball.row > 159) {
		showEndScreen();
	} else if(brickCollision != 0) {
		ball.row = brickCollision;
		ball.rowdel = -ball.rowdel;
	} else if (ball.row <= 0) {
		ball.row = 0;
		ball.rowdel = -ball.rowdel;
	} else if((ball.row >= (paddle.row - SMILEYFACE_HEIGHT)) && ((ball.col + (int)(SMILEYFACE_WIDTH / 2) - 1) > paddle.col) && ((ball.col  + (int)(SMILEYFACE_WIDTH / 2)) <= (paddle.col + paddle.width))) {
		ball.row = paddle.row - SMILEYFACE_HEIGHT;
		ball.rowdel = -ball.rowdel;
	}
	if(ball.col < 0) {
		ball.col = 0;
		ball.coldel = -ball.coldel;
	}
	if(ball.col > 239 - SMILEYFACE_WIDTH + 1) {
		ball.col = 239 - SMILEYFACE_WIDTH + 1;
		ball.coldel = -ball.coldel;
	}

	drawRectangle(ball.oldrow, ball.oldcol, SMILEYFACE_WIDTH, SMILEYFACE_HEIGHT, BLACK);
	drawImage3(ball.row, ball.col, SMILEYFACE_WIDTH, SMILEYFACE_HEIGHT, smileyFace);
}

int checkWin() {
	for (int i = 0; i < numBricks; i++) {
		if(bricks[i].exists) {
			return 0;
		}
	}
	return 1;
}

void win() {
	drawRectangle(0,0,240,160,YELLOW);
	char winStr[12];
	sprintf(winStr, "You Win! -- Score: %d", score);
	drawString(50, 50, winStr, BLACK);
	delay(100);
	showEndScreen();
}
