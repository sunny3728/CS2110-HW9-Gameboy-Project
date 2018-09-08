#include "game.h"

int leftButton = 0;
int oldLeftButton = 0;
int rightButton = 0;
int oldRightButton = 0;

int main() {
	REG_DISPCNT = MODE_3 | BG2_ENABLE;
	showStartScreen();
	resetGame();
	delay(30);
	while(1) {
		 
		if(KEY_DOWN_NOW(BUTTON_LEFT)) {
			leftButton = 1;
		} else {
			leftButton = 0;
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT)) {
			rightButton = 1;
		} else {
			rightButton = 0;
		}

		if(checkWin()) {
			win();
		}

		if(KEY_DOWN_NOW(BUTTON_SELECT)) {
			showStartScreen();
			resetGame();
			delay(50);
		}

		//check buttons for controlling paddle
		//False == left, True == right
		if(leftButton && (leftButton != oldLeftButton)) {
			movePaddle(FALSE);
		} else if(rightButton && (rightButton != oldRightButton)) {
			movePaddle(TRUE);
		}

		moveBall();
		oldLeftButton = leftButton;
		oldRightButton = rightButton;

		waitForVblank();
	}
}