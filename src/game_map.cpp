#include "game_map.h"
#include "perlin_noise.h"
#include<iostream>

void map_tile::draw(SDL_Renderer* r, int x, int y) {
    if(water > height)  SDL_SetRenderDrawColor(r, 0, 0, 255, 255); // blue
    else{
        int n = height * 255.0;
        SDL_SetRenderDrawColor(r, n, n / 2 , 0, 255);
        //SDL_SetRenderDrawColor(r, 102, 51, 0, 255); // brown
    }
    SDL_RenderDrawPoint(r, x, y);
}

game_map::game_map(int x, int y, int seedh, int seedw) {
    width = x;
    height = y;
    m = new map_tile*[x];
    for(int i = 0; i < x; i ++) {
        m[i] = new map_tile[y];
    }
    perlin_noise h(seedh); // height map
    perlin_noise w(seedw); // water map
    double mn = 1 << 16;
    double mx = - (1 << 16);
    for(int i = 0; i < x; i ++) {
        for(int j = 0; j < y; j ++) {
            m[i][j].height = h.octave((double)i / x, (double)j / y, 8);
            m[i][j].water = w.octave((double)i / x, (double)j / x, 8);
            mn = std::min(m[i][j].height, mn);
            mx = std::max(m[i][j].height, mx);
        }
    }
    std::cout << mn << " " << mx << std::endl;
}

game_map& game_map::operator=(const game_map& other) {
    for(int i = 0; i < width; i ++) delete[] m[i];
    delete[] m;
    width = other.width;
    height = other.height;
    m = new map_tile*[width];
    for(int i = 0; i < width; i ++) {
        m[i] = new map_tile[height];
    }
    for(int i = 0; i < width; i ++) {
        for(int j = 0; j < height; j ++) {
            m[i][j] = other.m[i][j];
        }
    }
    return *this;
}

game_map::~game_map() {
    for(int i = 0; i < width; i ++) delete[] m[i];
    delete[] m;
}

void game_map::draw(SDL_Renderer* r) {
    for(int x = 0; x < width; x ++) {
        for(int y = 0; y < height; y ++) {
            m[x][y].draw(r, x, y);
        }
    }
}
