// Accuracy
// K. M. Kroski
// 14 Dec 2016

#include <Arduboy.h>

Arduboy arduboy;

bool abuffer = false;
byte state = 0;
float accuracy = 0.0;
unsigned int score = 0;
byte level = 1;
byte xpos = 63;
bool left = false;

void resetGame() {
  score = 0;
  level = 1;
  xpos = 63;
  left = false;
  state = 0;
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  resetGame();
}

void loop() {
  if (!arduboy.nextFrame()) { return; }
  
  arduboy.clear();

  if (arduboy.notPressed(A_BUTTON)) {
    abuffer = false;
  }

  switch (state) {
    case 0: {
      arduboy.setTextSize(2);
      arduboy.setCursor(4, 16);
      arduboy.print("ACCURACY");

      arduboy.setTextSize(1);
      arduboy.setCursor(4, 55);
      arduboy.print("Press A to start");

      arduboy.drawRect(4, 34, 102, 2, WHITE);
      arduboy.drawCircle(114, 26, 12, WHITE);
      arduboy.drawCircle(114, 26, 8, WHITE);
      arduboy.drawCircle(114, 26, 4, WHITE);

      if (arduboy.pressed(A_BUTTON) && !abuffer) {
        abuffer = true;
        state = 1;
      }
      break;
    }

    case 1: {
      if (left) {
        xpos -= level;
      } else {
        xpos += level;
      }
    
      arduboy.drawCircle(63, 31, 20, WHITE);
      arduboy.drawCircle(63, 31, 15, WHITE);
      arduboy.drawCircle(63, 31, 10, WHITE);
      arduboy.drawCircle(63, 31, 5, WHITE);
      
      arduboy.fillCircle(xpos, 31, 19, WHITE);\
      arduboy.drawChar(xpos - 7, 19, 'A', BLACK, WHITE, 3);
    
      if (xpos <= 20) {
        left = false;
      } else if (xpos >= 107) {
        left = true;
      }

      if (arduboy.pressed(A_BUTTON) && !abuffer) {
        abuffer = true;

        accuracy = 100 * (1.0 - (abs(63 - xpos) / 63.0));
        score += accuracy * 10;
        
        state = 2;
      }
      break;
    }

    case 2: {
      arduboy.setTextSize(2);
      arduboy.setCursor(4, 16);
      arduboy.print(accuracy);
      arduboy.print("%");

      arduboy.setTextSize(1);
      arduboy.setCursor(4, 4);
      arduboy.print("Level ");
      arduboy.print(level);

      arduboy.setCursor(4, 35);
      arduboy.print(score);
      arduboy.print(" points");
      
      arduboy.setCursor(4, 55);
      arduboy.print("Press A to continue");

      if (arduboy.pressed(A_BUTTON) && !abuffer) {
        abuffer = true;
        
        level++;
        if (level > 10) {
          state = 3;
        } else {
          xpos = 63;
          left = false;
          state = 1;
        }
      }  
      break;
    }

    case 3: {
      arduboy.setTextSize(2);
      arduboy.setCursor(4, 16);
      arduboy.print("GAME OVER");

      arduboy.setTextSize(1);
      arduboy.setCursor(4, 35);
      arduboy.print(score);
      arduboy.print(" points");
      
      arduboy.setCursor(4, 55);
      arduboy.print("Press A to restart");

      if (arduboy.pressed(A_BUTTON) && !abuffer) {
        abuffer = true;
        resetGame();
      }
      break;
    }
  }

  arduboy.display();
}
