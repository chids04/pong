#pragma once
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include "pongplayer.h"

class Ball {
public:
    Ball(float x, float y, float radius, float vx, float vy, 
        std::shared_ptr<PongPlayer> player1, std::shared_ptr<PongPlayer> player2);

    void update(int screenWidth, int screenHeight); 
    void render(SDL_Renderer* renderer);

private:
    float x, y;
    float radius;
    float vx, vy;
    std::shared_ptr<PongPlayer> p1;
    std::shared_ptr<PongPlayer> p2;
    std::vector<SDL_FPoint> cachedPoints;

    std::vector<SDL_FPoint> PixelizeFilledCircle(float radius);
};