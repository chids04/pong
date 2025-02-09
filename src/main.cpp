#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "gamemanager.h"


namespace {
    struct AppState {
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning;

        const int screenWidth = 640;
        const int screenHeight = 480;

        std::unique_ptr<GameManager> gameManager;
        TTF_Font *font;

    };
}

extern "C" {

    SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
    {
        SDL_SetAppMetadata("pong", "1.0", "com.cix.com");

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        *appstate = new AppState;
        AppState *state = static_cast<AppState*>(*appstate);

        if (!SDL_CreateWindowAndRenderer("pong bitch", state->screenWidth, state->screenHeight, 0, &state->window, &state->renderer)) {
            SDL_Log("window/renderer error: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        if(!TTF_Init()){
            SDL_Log("couldnt initalise sdl text: %s\n", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        state->font = TTF_OpenFont("../../font/8-bit-hud.ttf", 12);

        if(state->font == NULL){
            SDL_Log("could not load font: %s \n", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        TTF_SetFontStyle(state->font, TTF_STYLE_BOLD);
        state->gameManager = std::make_unique<GameManager>(state->renderer, state->screenWidth, state->screenHeight, state->font);

        return SDL_APP_CONTINUE;  
    }

    SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
    {
        if (event->type == SDL_EVENT_QUIT) {
            return SDL_APP_SUCCESS;  
        }
        else if(event->type == SDL_EVENT_KEY_DOWN || SDL_EVENT_KEY_UP){
            AppState *state = static_cast<AppState*>(appstate);

            //handle key events here, in app state function
            state->gameManager->handleKeyEvents(event);
        }
        return SDL_APP_CONTINUE;  
    }

 
    SDL_AppResult SDL_AppIterate(void *appstate)
    {
        AppState *state = static_cast<AppState*>(appstate);

        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(state->renderer);

        state->gameManager->update();
        state->gameManager->render();

        SDL_RenderPresent(state->renderer);
        

        // const double now = ((double)SDL_GetTicks()) / 1000.0;
        // const float red = (float) (0.5 + 0.5 * SDL_sin(now));
        // const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
        // const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

        // SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        // SDL_RenderClear(state->renderer);

        // SDL_SetRenderDrawColor(state->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

        // SDL_FRect rect;
        // rect.w = 12;
        // rect.h = 50;
        // rect.x = 10;
        // rect.y = state->screenHeight / 2 - rect.h / 2;

        // SDL_RenderFillRect(state->renderer, &rect);
        // SDL_RenderPresent(state->renderer);

        return SDL_APP_CONTINUE;  
    }

    void SDL_AppQuit(void *appstate, SDL_AppResult result)
    {
        AppState *state = static_cast<AppState*>(appstate);

        TTF_CloseFont(state->font);
        SDL_DestroyRenderer(state->renderer);
        SDL_DestroyWindow(state->window);
        delete state;

        TTF_Quit();
        SDL_Quit();
    }

}



