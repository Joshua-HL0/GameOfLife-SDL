#define VAR_DECLS 1
#include <stdint.h>
#include <SDL2/SDL.h>

#include "gol.h"


int draw_grid(SDL_Surface *surface, int numColumns, int numRows){
    for (int i = 0; i < numRows; i++){
        SDL_Rect border = {0, i * CELL_SIZE, WINDOW_WIDTH, BORDER_WIDTH};
        SDL_FillRect(surface, &border, COLOUR_OFFWHITE);
    }

    for (int i = 0; i < numColumns; i++){
        SDL_Rect border = {i * CELL_SIZE, 0, BORDER_WIDTH, WINDOW_HEIGHT};
        SDL_FillRect(surface, &border, COLOUR_OFFWHITE);
    }
}

int activate_cell(SDL_Surface *surface, int posX, int posY){                      // this currently doesn't store the cell anywhere, just drawing. 
                                                                                  // will change before implementing the game logic
    SDL_Rect cell = {posX * CELL_SIZE, posY * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_FillRect(surface, &cell, COLOUR_WHITE);
}

int kill_cell(SDL_Surface *surface, int posX, int posY){
    //
}


int main(){

    SDL_Init(SDL_INIT_VIDEO);

    char *window_name = "GOL";
    SDL_Window *window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);
    
    int numColumns = WINDOW_WIDTH / CELL_SIZE;
    int numRows = WINDOW_HEIGHT / CELL_SIZE;

    draw_grid(surface, NUM_COLUMNS, NUM_ROWS);

    activate_cell(surface, 12, 12);
    activate_cell(surface, 15, 12);
    activate_cell(surface, 11, 13);
    activate_cell(surface, 9, 19);
    activate_cell(surface, 18, 7);

    SDL_UpdateWindowSurface(window);

    uint8_t running = 1;
    uint8_t minimised = 0;
    SDL_Event event;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
            }
        }

        SDL_Delay(20);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
