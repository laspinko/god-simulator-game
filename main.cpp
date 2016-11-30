#include<SDL2/SDL.h>
#include<iostream>
#include"perlin_noise.h"
#include"game_map.h"

// GLOBAL

int sh = 1, sw = 2;
game_map m(512,512, sh, sw);

// WINDOW RELATED

SDL_Window *window;
SDL_Renderer *renderer;

int width = 512;
int height = 512;

void init_window() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("God simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

void close_window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void draw() {
    m.draw(renderer);
    SDL_RenderPresent(renderer);
}

int main(int args, char **argv) {

    SDL_Event e;

    bool quit = false;

    init_window();
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        m = game_map(512,512, sw,sh);
        sw ++;
        sh ++;
        draw();
        SDL_Delay(10);
    }

    close_window();

    return 0;
}
