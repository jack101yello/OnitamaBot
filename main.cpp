#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Board/board.h"

#define WIDTH 1000
#define HEIGHT 750

void setup();
void draw(SDL_Renderer* renderer);

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = SDL_CreateWindow("Onitama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    setup();

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    Board b;

    while(running) {
        SDL_Event close_event;
        while(SDL_PollEvent(&close_event)) {
            switch(close_event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        
        draw(renderer);

        b.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

void setup() {

}

void draw(SDL_Renderer* renderer) {
    
}