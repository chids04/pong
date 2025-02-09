#include "gamemanager.h"

#include <iostream>


GameManager::GameManager(SDL_Renderer *renderer, int screenWidth, int screenHeight, TTF_Font *font) : 
    renderer(renderer), screenWidth(screenWidth), screenHeight(screenHeight), font(font)
{
    int paddleSpeed = 4.5;
    player1 = std::make_shared<PongPlayer>(10, 10, 10, 100, paddleSpeed, screenWidth, screenHeight);
    player2 = std::make_shared<PongPlayer>(620, 10, 10, 100, paddleSpeed, screenWidth, screenHeight);

    ball = std::make_unique<Ball>(320, 240, 10, 4, 4, player1, player2);
    
}

void GameManager::handleKeyEvents(SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        switch (event->key.key)
        {
        case SDLK_W:
            //move player 1 up
            player1->handleKey(true, 1);
            break;
        case SDLK_S:
            //move player 1 down
            player1->handleKey(true, -1);
            break;
        case SDLK_UP:
            player2->handleKey(true, 1);
            break;
        case SDLK_DOWN:
            player2->handleKey(true, -1);   
            break;
        default:
            break;
        }
    }
    else if(event->type == SDL_EVENT_KEY_UP){
        switch (event->key.key){
            case SDLK_W:
                //stop player 1 from moving up
                player1->handleKey(false, 0);
                break;
            case SDLK_S:
                //stop player 1 from moving down
                player1->handleKey(false, 0);
                break;
            
            case SDLK_UP:
                player2->handleKey(false, 0);
                break;
            
            case SDLK_DOWN:
                //stop player 2 from moving down
                player2->handleKey(false, 0);
                break;
            default:
                break;
        }
    }

}

void GameManager::update()
{
    player1->update();
    player2->update();
    ball->update(640, 480); 
}

void GameManager::render()
{

    player1->render(renderer);
    player2->render(renderer);
    ball->render(renderer);

    renderText(std::to_string(player1->getScore()), 1);
    renderText(std::to_string(player2->getScore()), 2);
}

void GameManager::renderText(const std::string &msg, int player){
    
    SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};
    std::string message = "1";
    SDL_Surface *surface = TTF_RenderText_Solid(font, msg.c_str(), msg.size(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FRect rect;

    rect.w = surface->w;
    rect.h = surface->h;

    if(player == 1) rect.x = (screenWidth * 1/4) - rect.w / 2;
    if(player == 2) rect.x = (screenWidth * 3/4) - rect.w / 2;

    rect.y = 10;

    SDL_RenderTexture(renderer, texture, NULL, &rect);
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}
