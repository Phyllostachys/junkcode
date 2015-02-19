//#pragma comment(lib, "SDL.lib")
//#pragma comment(lib, "SDLmain.lib")

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const unsigned char WIDTH  = 160;
static const unsigned char HEIGHT = 160;
static const unsigned char BLOCK  = 16; // each block pixel is BLOCKxBLOCK ordinary pixels

// Function to draw the src texture to destination renderer at (x,y)
// Input:
//   SDL_Renderer* renderer - pointer to render target where source text will be drawn
//   SDL_Texture* texture  - pointer to texture where source texture is
//   int x                 - x location where texture will be drawn
//   int y                 - y location where texture will be drawn
bool onDraw(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
    SDL_Rect destRect = {x, y, 16, 16};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    return true;
}

int main(int argc, char* argv[])
{
    SDL_Event event;
    int mazeMap[100] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 1, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 1, 1, 1, 1, 0, 1,
        1, 1, 1, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    //int x = 0, y = 0;
    int char_x = 1, char_y = 1;
    bool exitGame = false;

    // exit if there was an error initializing the video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow("MazeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if (window == NULL) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        SDL_Quit();
        return 1;
    }

    // declare surface variables for sprites
    SDL_Surface* wallSprite  = IMG_Load("../res/Wall.png");
    SDL_Surface* floorSprite = IMG_Load("../res/Floor.png");
    SDL_Surface* charSprite  = IMG_Load("../res/NotMeatBoy.png");
    SDL_Surface* exitSprite  = IMG_Load("../res/Exit.png");

    SDL_Texture* wallTex  = SDL_CreateTextureFromSurface(renderer, wallSprite);
    SDL_Texture* floorTex = SDL_CreateTextureFromSurface(renderer, floorSprite);
    SDL_Texture* charTex  = SDL_CreateTextureFromSurface(renderer, charSprite);
    SDL_Texture* exitTex  = SDL_CreateTextureFromSurface(renderer, exitSprite);

    SDL_FreeSurface(wallSprite);
    SDL_FreeSurface(floorSprite);
    SDL_FreeSurface(charSprite);
    SDL_FreeSurface(exitSprite);

    // enter game loop
    while (!exitGame) {
        // loops to draw background
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                switch (mazeMap[(row*10) + col])
                {
                    case 1:
                        onDraw(renderer, wallTex, (col * BLOCK), (row * BLOCK));
                        break;
                    default:
                        onDraw(renderer, floorTex, (col * BLOCK), (row * BLOCK));
                }

                //HACK, FIXME: need to change this so that the value in the maze denotes the exit tile
                if (row == 8 && col == 8) {
                    onDraw(renderer, exitTex, (col * BLOCK), (row * BLOCK));
                }
            }
        }

        // draw character onto their x,y location
        onDraw(renderer, charTex, (char_x * BLOCK), (char_y * BLOCK));

        // flip double buffer
        SDL_RenderPresent(renderer);

        // while waiting for event
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                    // case: user exits the program
                case SDL_QUIT:
                    exitGame = true;
                    break;
                    // case: user presses a key on the keyboard
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                            // left arrow key
                        case SDLK_LEFT:
                            if (mazeMap[ char_y * 10 + char_x - 1 ] == 0) {
                                char_x -= 1;
                                break;
                            } else {
                                break;
                            }
                            // right arrow key
                        case SDLK_RIGHT:
                            if (mazeMap[ char_y * 10 + char_x + 1 ] == 0) {
                                char_x += 1;
                                break;
                            } else {
                                break;
                            }
                            // up arrow key
                        case SDLK_UP:
                            if (mazeMap[ char_y * 10 + char_x - 10 ] == 0) {
                                char_y -= 1;
                                break;
                            } else {
                                break;
                            }
                            // down arrow key
                        case SDLK_DOWN:
                            if (mazeMap[ char_y * 10 + char_x + 10 ] == 0) {
                                char_y += 1;
                                break;
                            } else {
                                break;
                            }
                        default:
                            break;
                    }
            }
        }
    }

    // free up surface resources
    SDL_DestroyTexture(wallTex);
    SDL_DestroyTexture(floorTex);
    SDL_DestroyTexture(charTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
