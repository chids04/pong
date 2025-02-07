#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


namespace {
    struct AppState {
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning;

        int screenWidth = 640;
        int screenHeight = 480;
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

        return SDL_APP_CONTINUE;  
    }

    SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
    {
        if (event->type == SDL_EVENT_QUIT) {
            return SDL_APP_SUCCESS;  
        }
        return SDL_APP_CONTINUE;  
    }

 
    SDL_AppResult SDL_AppIterate(void *appstate)
    {
        AppState *state = static_cast<AppState*>(appstate);

        const double now = ((double)SDL_GetTicks()) / 1000.0;
        const float red = (float) (0.5 + 0.5 * SDL_sin(now));
        const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
        const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(state->renderer);

        SDL_SetRenderDrawColor(state->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

        SDL_FRect rect;
        rect.w = 12;
        rect.h = 50;
        rect.x = 10;
        rect.y = state->screenHeight / 2 - rect.h / 2;

        SDL_RenderFillRect(state->renderer, &rect);
        SDL_RenderPresent(state->renderer);

        return SDL_APP_CONTINUE;  
    }

    void SDL_AppQuit(void *appstate, SDL_AppResult result)
    {
    }

}



