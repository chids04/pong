#pragma once

#include "player.h"

class PongPlayer : public Player {
public:
    PongPlayer(float x, float y, float width, float height, float vy, int screenWidth, int screenHeight)
        : Player(x, y, width, height, vy, screenWidth, screenHeight) {}

    void update() override {
        if (moving) {
            if (direction == 1) {
                if (rect.y -vy >= 0) {
                    rect.y -= vy;
                }
            } else if (direction == -1) {
                if (rect.y +vy <= screenHeight - rect.h) {
                    rect.y += vy;
                }
            }
        }
    }

    void handleKey(bool isMoving, int dir){
        moving = isMoving;
        direction = dir;
    }

    void addScore(){
        score++;
    }

    int getScore(){
        return score;
    }  

private:
    bool moving = false;
    int direction = 0;
    int score = 0;
};
