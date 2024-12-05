#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#define VAR_DECLS 1
#include <string.h>
#include <stdio.h>
#include "gol.h"

void init_grid(){
    // glider pattern
    /*cellArray[1][0] = 1;
    cellArray[2][1] = 1;
    cellArray[0][2] = 1;
    cellArray[1][2] = 1;
    cellArray[2][2] = 1;*/

    // random pattern
    for (int i = 0; i < NUM_COLUMNS; i++){
        for (int j = 0; j < NUM_ROWS; j++){
            cellArray[i][j] = rand() % 2;
        }
    }


}

void draw_grid(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, COLOUR_OFFWHITE);

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

    SDL_SetRenderDrawColor(renderer, COLOUR_WHITE);

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

void inline cell_click(SDL_MouseButtonEvent *e){
    if (e->button == SDL_BUTTON_LEFT){
        int x, y;
        SDL_GetMouseState(&x, &y);
        printf("Click %d, %d\n", x, y);
        cellArray[x / CELL_SIZE][y / CELL_SIZE] = !cellArray[x / CELL_SIZE][y / CELL_SIZE];
    }
}

int main(){

    SDL_Init(SDL_INIT_VIDEO);

    char *window_name = "GOL";
    SDL_Window *window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);   
    draw_grid(renderer);
    
    init_grid();

    printf("Height: %d, Width: %d\nRows: %d, Columns: %d\n", WINDOW_HEIGHT, WINDOW_WIDTH, NUM_ROWS, NUM_COLUMNS);


    uint8_t running = 1;
    SDL_Event event;
    while (running){

        update_grid(); // grid update has to be before click check, otherwise normal update will override click changes

        while (SDL_PollEvent(&event)){
            switch (event.type){
                case (SDL_QUIT):            running = 0;
                case (SDL_MOUSEBUTTONDOWN): cell_click(&event.button);
            }
        }
        render_grid(renderer);
        SDL_Delay(100);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
