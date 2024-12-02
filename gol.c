#define VAR_DECLS 1
#include <string.h>
#include <stdio.h>
#include "gol.h"

void init_grid(){
    // glider pattern
    cellArray[1][0] = 1;
    cellArray[2][1] = 1;
    cellArray[0][2] = 1;
    cellArray[1][2] = 1;
    cellArray[2][2] = 1;
}

void draw_grid(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0x3f, 0x3f, 0x3f, 0x3f);

    for (int i = 0; i < NUM_COLUMNS; i++){
        SDL_Rect border = {i * CELL_SIZE, 0, BORDER_WIDTH, WINDOW_HEIGHT};
        SDL_RenderFillRect(renderer, &border);
    }

    for (int i = 0; i < NUM_ROWS; i++){
        SDL_Rect border = {0, i * CELL_SIZE, WINDOW_WIDTH, BORDER_WIDTH};
        SDL_RenderFillRect(renderer, &border);
    }
}

void update_grid(){
    for (int x = 0; x < NUM_COLUMNS; x++){
        for (int y = 0; y < NUM_ROWS; y++){
            uint32_t neighbours = 0;

            for (int adjX = -1; adjX <= 1; adjX++){
                for (int adjY = -1; adjY <= 1; adjY++){ 
                    if ((adjX == 0) && (adjY == 0)) continue;

                    int tX = x + adjX;
                    int tY = y + adjY;

                    if (tX < 0) tX = NUM_COLUMNS - 1;
                    if (tY < 0) tY = NUM_ROWS - 1;
                    if (tX >= NUM_COLUMNS) tX = 0;
                    if (tY >= NUM_ROWS) tY = 0;

                    neighbours += cellArray[tX][tY];
                }
            }

            if (cellArray[x][y]){
                if (neighbours < 2 || neighbours > 3) cellArrayNext[x][y] = 0;
                else cellArrayNext[x][y] = 1;
            }
            else{
                if (neighbours == 3) cellArrayNext[x][y] = 1;
                else cellArrayNext[x][y] = 0;
            }
        }
    }

    memcpy(cellArray, cellArrayNext, NUM_COLUMNS * NUM_ROWS * sizeof(uint8_t));
}

void render_grid(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    for (int x = 0; x < NUM_COLUMNS; x++){
        for (int y = 0; y < NUM_ROWS; y++){
            if (cellArray[x][y]){
                activate_cell(renderer, x, y);
            }
        }
    }

    draw_grid(renderer);
    SDL_RenderPresent(renderer);
}

void inline activate_cell(SDL_Renderer *renderer, int posX, int posY){                      // inline! make the code easier to read 
    SDL_Rect cell = {posX * CELL_SIZE, posY * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_RenderFillRect(renderer, &cell);
}

int main(){

    SDL_Init(SDL_INIT_VIDEO);

    char *window_name = "GOL";
    SDL_Window *window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);   
    draw_grid(renderer);
    
    init_grid();

    printf("Height: %d, Width: %d\nRows: %d, Columns: %d", WINDOW_HEIGHT, WINDOW_WIDTH, NUM_ROWS, NUM_COLUMNS);


    uint8_t running = 1;
    SDL_Event event;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
            }
        }

        update_grid();
        render_grid(renderer);
        SDL_Delay(100);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
