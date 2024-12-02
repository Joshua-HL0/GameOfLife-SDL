#ifndef GOL_H
#define GOL_H

#include <SDL2/SDL.h>
#include <stdint.h>

/*#ifndef VAR_DECLS
#   define _DECL extern
#   define _INIT (x)
#else
#   define _DECL
#   define _INIT(x) = x
#endif

_DECL uint32_t WINDOW_WIDTH _INIT(600);
_DECL uint32_t WINDOW_HEIGHT _INIT(400);
_DECL uint32_t COLOUR_WHITE _INIT(0xffffffff);
_DECL uint32_t COLOUR_OFFWHITE _INIT(0x1f1f1f1f);

_DECL const uint32_t CELL_SIZE _INIT(20);
_DECL const uint32_t NUM_ROWS _INIT(WINDOW_HEIGHT / CELL_SIZE);
_DECL const uint32_t NUM_COLUMNS _INIT(WINDOW_WIDTH / CELL_SIZE);
_DECL uint32_t BORDER_WIDTH _INIT(2);
*/
// my lsp was messing up interpretation of these, causing errors so using just defines for now

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define COLOUR_WHITE 0xffffffff
#define COLOUR_OFFWHITE 0x3f3f3f3f

#define CELL_SIZE 20
#define NUM_ROWS (WINDOW_HEIGHT/ CELL_SIZE)
#define NUM_COLUMNS (WINDOW_WIDTH / CELL_SIZE)
#define BORDER_WIDTH 2

uint8_t cellArray[NUM_COLUMNS][NUM_ROWS];
uint8_t cellArrayNext[NUM_COLUMNS][NUM_ROWS];

void update_grid();
void draw_grid(SDL_Renderer *renderer);
void init_grid();
void render_grid(SDL_Renderer *renderer);
void activate_cell(SDL_Renderer *renderer, int posX, int posY);

#endif
