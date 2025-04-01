#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "Gameplay/Board/board.h"
#include "Graphics/Button/button.h"
#include "Graphics/Textbox/textbox.h"
#include "Gameplay/Game/game.h"
#include "Player/Player/player.h"
#include "Player/HumanPlayer/human_player.h"
#include "Player/Bot/Bot.h"
#include "Player/Bot/ImpatientBot/ImpatientBot.h"
#include "Player/Bot/MatrixBot/MatrixBot.h"
#include "Gameplay/Tournament/tournament.h"

#define WIDTH 1800
#define HEIGHT 1000

void player_vs_player(SDL_Window* window, SDL_Renderer* renderer);
void player_vs_computer(SDL_Window* window, SDL_Renderer* renderer);
void computer_training(SDL_Window* window, SDL_Renderer* renderer);
void check_close(SDL_Window* window);
void quit(SDL_Window* window);

/*
Select various running modes here
This is for debugging and developing purposes
*/
// #define SKIP_MENU_MODE
#define VISUAL_MODE

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }
    if(TTF_Init() < 0) {
        printf("Error initializing TTF: %s\n", TTF_GetError());
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize.\n");
    }

    SDL_Window *win = SDL_CreateWindow("Onitama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("Data/Fonts/Times New Roman.ttf", 24);
    if(!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }

    bool main_menu = true;

    #ifndef SKIP_MENU_MODE
    Textbox mainmenu_title(WIDTH/2 - 100, 25, 200, 75, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, "ONITAMA");
    Button pvp_button(WIDTH/2 - 200, 125, 400, 50, "Player v. Player");
    Button pvc_button(WIDTH/2 - 200, 225, 400, 50, "Play Bot");
    Button cvc_button(WIDTH/2 - 200, 325, 400, 50, "Bot Training");
    #endif

    int MouseX;
    int MouseY;

    #ifdef SKIP_MENU_MODE
    computer_training(win, renderer);
    #else
    while(main_menu) {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // Print buttons to screen
        mainmenu_title.draw(renderer);
        pvp_button.draw(renderer);
        pvc_button.draw(renderer);
        cvc_button.draw(renderer);

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
    #endif

    quit(win);
    SDL_Quit();

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
    Human_Player* p1 = new Human_Player(1);
    Human_Player* p2 = new Human_Player(2);
    Game game(p1, p2, 150, renderer);

    #ifdef VISUAL_MODE
    game.set_visual_mode(true);
    #else
    game.set_visual_mode(false):
    #endif

    Player* winner = game.play_game();
    switch(winner -> get_index()) {
        case 1:
            printf("Player 1 won!\n");
            break;
        case 2:
            printf("Player 2 won!\n");
            break;
    }

    delete p1;
    delete p2;

    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderClear(renderer);
    Textbox GameOver(WIDTH/4, HEIGHT/4, WIDTH/2, HEIGHT/2, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, "GAME OVER");
    
    for(;;) {
        check_close(window);
    }
}

void player_vs_computer(SDL_Window* window, SDL_Renderer* renderer) {
    Human_Player* human = new Human_Player(1);
    MatrixBot* bot = new MatrixBot(2, "BotData/bot_0.dat");

    Game game(human, bot, 150, renderer);

    #ifdef VISUAL_MODE
    game.set_visual_mode(true);
    #else
    game.set_visual_mode(false);
    #endif

    Player* winner = game.play_game();

    switch(winner -> get_index()) {
        case 1:
            printf("The human won!\n");
            break;
        case 2:
            printf("The bot won!\n");
            break;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderClear(renderer);
    Textbox GameOver(WIDTH/4, HEIGHT/4, WIDTH/2, HEIGHT/2, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, "GAME OVER");

    delete human;
    delete bot;

    for(;;) {
        check_close(window);
    }
}

void computer_training(SDL_Window* window, SDL_Renderer* renderer) {
    bool running = true;

    Tournament tournament(10);

    while(running) {
        tournament.play_round(renderer);
        
        check_close(window);
    }
}