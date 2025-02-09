#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "pongplayer.h"
#include "ball.h"

class GameManager{

public:
    GameManager(SDL_Renderer *renderer, int screenWidth, int screenHeight, TTF_Font *font);
    void handleKeyEvents(SDL_Event *event);
    void update();
    void render();
    void renderText(const std::string &msg, int xpos);
        

    static int getScreenWidth();
    static int getScreenHeight();

private:
    int score1 = 0;
    int score2 = 0;
    SDL_Renderer *renderer;
    int screenWidth;
    int screenHeight;

    TTF_Font *font = nullptr;

    std::shared_ptr<PongPlayer> player1;
    std::shared_ptr<PongPlayer> player2;
    std::unique_ptr<Ball> ball;



    
};