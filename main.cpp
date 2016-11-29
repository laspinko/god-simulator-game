#include<SDL2/SDL.h>
#include<iostream>
#include"perlin_noise.h"

perlin_noise pn(123);

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
    for(int x = 0; x < width; x ++) {
        for(int y = 0; y < height; y ++) {
            double n = pn.interpolate(pn.octave(x / 256.0, y / 256.0, 6));
            int r = (int)(n * 255.0), g = r, b = r;

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);

            SDL_RenderDrawPoint(renderer, x, y);

        }
    }
    SDL_RenderPresent(renderer);
}

int main(int args, char **argv) {

    SDL_Event e;

    bool quit = false;

    init_window();

        draw();
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        draw();
        SDL_Delay(10);
    }

    close_window();

    return 0;
}
