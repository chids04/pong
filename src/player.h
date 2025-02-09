#pragma once
#include <SDL3/SDL.h>

class Player {

public:
    Player(float x, float y, float width, float height, float vy, int screenWidth, int screenHeight, SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE})
        : rect{x, y, width, height}, vy(vy), color(color), screenWidth(screenWidth), screenHeight(screenHeight) {}

    virtual  ~Player() {}

    virtual void update() = 0;

    virtual void render(SDL_Renderer *renderer) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    virtual SDL_FRect getRect(){
        return rect;
    }

    


protected:
    float vy;
    int screenWidth, screenHeight;
    SDL_FRect rect;
    SDL_Color color;

};