#include <cstdint>
#include <cstdbool>
#include <cstdlib>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <ctime>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

//static const double M_PI = 3.1415;

#define RENDER_X 24
#define RENDER_Y 24

struct Pixel {
    uint8_t alpha;
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct Vec2 {
    float x;
    float y;

    void rot(float radians) {
        float nx, ny;
        nx = x * cos(radians) - y * sin(radians);
        ny = x * sin(radians) + y * cos(radians);
        x = nx;
        y = ny;
    }

    void norm() {
        float mag = sqrt(x * x + y * y);
        x = x / mag;
        y = y / mag;
    }
};

struct Player {
    Vec2 position;
    Vec2 direction;
    float speed;

    void debug_p() {
        printf("Pos(%.02f, %.02f) Dir(%.02f, %.02f) Spd(%.02f)\n", position.x, position.y, direction.x, direction.y, speed);
    }

    void move(SDL_Keycode key) {
        switch (key) {
            case SDLK_w: speed += 0.5; break;
            case SDLK_a: direction.rot(-10.0 * 3.1415 / 180.0); direction.norm(); break;
            case SDLK_s: speed -= 0.5; break;
            case SDLK_d: direction.rot(10.0 * 3.1415 / 180.0); direction.norm(); break;
        }
    }

    void update(double dt) {
        position.x = position.x + (speed * direction.x * dt);
        if (position.x < 0) position.x = 0; if (position.x > 800) position.x = 799;
        position.y = position.y + (speed * direction.y * dt);
        if (position.y < 0) position.y = 0; if (position.y > 600) position.y = 599;
        debug_p();
    }

    void render(SDL_Renderer *renderer) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xAF, 0, 0xFF);
        SDL_RenderDrawPoint(renderer, (int)position.x, (int)position.y);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x3F, 0x6F, 0xFF);
        SDL_RenderDrawLine(renderer,
                           position.x, position.y,
                           position.x + (5 * speed * direction.x),
                           position.y + (5 * speed * direction.y));
        SDL_RenderPresent(renderer);
    }
};

#define MAX_SPEED 5.0f
float inc_vel(float vel, float inc) {
    float temp = vel + inc;
    if (temp > MAX_SPEED) {
        return MAX_SPEED;
    } else if (temp < -MAX_SPEED) {
        return -MAX_SPEED;
    } else {
        return temp;
    }
}

int main(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    srand(time(0));

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        puts("SDL_Init failed?");
    }

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer)) {
        puts("Failed to create window and renderer.");
    }

    uint32_t start = SDL_GetTicks();
    bool quit = false;
    Player player = {{400, 300}, {1.0f, 0.0f}};
    player.debug_p();
    SDL_Keycode last_key;

    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                quit = true;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                } else {
                    last_key = event.key.keysym.sym;
                }
                break;
        }

        SDL_SetRenderDrawColor(renderer, 0x5F, 0x5F, 0x5F, 0xFF);
        SDL_RenderClear(renderer);

        uint32_t now = SDL_GetTicks();
        double dt = (now - start) / 1000.0;

        if (dt > 0.001) {
            player.move(last_key);
            last_key = 0;
            player.update(dt);
        }

        if (dt > 0.016) {
            start = now;
            player.render(renderer);
        }
    }

    //SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
