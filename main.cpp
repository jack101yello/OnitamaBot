#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "Board/board.h"
#include "Button/button.h"
#include "Textbox/textbox.h"

#define WIDTH 1000
#define HEIGHT 750

void player_vs_player(SDL_Window* window, SDL_Renderer* renderer);
void player_vs_computer(SDL_Window* window, SDL_Renderer* renderer);
void computer_training(SDL_Window* window, SDL_Renderer* renderer);
void check_close(SDL_Window* window);
void quit(SDL_Window* window);

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }
    if(TTF_Init() < 0) {
        printf("Error initializing TTF: %s\n", TTF_GetError());
    }

    SDL_Window *win = SDL_CreateWindow("Onitama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("Data/Fonts/Times New Roman.ttf", 24);
    if(!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }

    bool main_menu = true;

    Textbox mainmenu_title(WIDTH/2 - 100, 25, 200, 75, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, "ONITAMA", font);
    Button pvp_button(WIDTH/2 - 200, 125, 400, 50, "Player v. Player", font);
    Button pvc_button(WIDTH/2 - 200, 225, 400, 50, "Play Bot", font);
    Button cvc_button(WIDTH/2 - 200, 325, 400, 50, "Bot Training", font);

    int MouseX;
    int MouseY;

    while(main_menu) {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // Print buttons to screen
        mainmenu_title.draw(renderer);
        pvp_button.draw(win, renderer, font);
        pvc_button.draw(win, renderer, font);
        cvc_button.draw(win, renderer, font);

        // Make choice
        int game_mode = -1;
        SDL_Event mainmenu_event;
        SDL_WaitEvent(&mainmenu_event);
        switch(mainmenu_event.type) {
            case SDL_QUIT:
                quit(win);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(mainmenu_event.button.button == SDL_BUTTON_LEFT) {
                    if(pvp_button.in_click_range(MouseX, MouseY)) {
                        printf("PVP Mode Selected.\n");
                        game_mode = 0;
                    }
                    else if(pvc_button.in_click_range(MouseX, MouseY)) {
                        printf("PVC Mode Selected.\n");
                        game_mode = 1;
                    }
                    else if(cvc_button.in_click_range(MouseX, MouseY)) {
                        printf("CVC Mode Selected.\n");
                        game_mode = 2;
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                MouseX = mainmenu_event.motion.x;
                MouseY = mainmenu_event.motion.y;
                break;
            default:
                break;
        }

        switch(game_mode) { // Run selected game mode
            case 0: player_vs_player(win, renderer); break;
            case 1: player_vs_computer(win, renderer); break;
            case 2: computer_training(win, renderer); break;
            default: break;
        }

        SDL_RenderPresent(renderer); // Render everything to the screen

        check_close(win);
    }

    quit(win);

    return 0;
}

void quit(SDL_Window* window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void check_close(SDL_Window* window) {
    SDL_Event close_event;
    while(SDL_PollEvent(&close_event)) {
        switch(close_event.type) {
            case SDL_QUIT:
                quit(window);
        }
    }
}

void player_vs_player(SDL_Window* window, SDL_Renderer* renderer) {
    bool running = true;
    
    Board b;

    while(running) {
        check_close(window);

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        b.draw(renderer);
        
        SDL_RenderPresent(renderer);
    }
}

void player_vs_computer(SDL_Window* window, SDL_Renderer* renderer) {
    bool running = true;

    while(running) {
        check_close(window);
    }
}

void computer_training(SDL_Window* window, SDL_Renderer* renderer) {
    bool running = true;

    while(running) {
        check_close(window);
    }
}