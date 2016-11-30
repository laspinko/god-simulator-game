#include "game_map.h"
#include "perlin_noise.h"
#include<iostream>

void color_gradient::push_color(double a, color b) {
    p.push_back(a);
    c.push_back(b); //TODO insertion
}
color color_gradient::get_color(double a) {
    for(int i = 0; i < p.size() - 1; i ++) {
        if(p[i] <= a && a < p[i + 1]) {
            color ans;
            double p2 = (a - p[i]) / (p[i + 1] - p[i]);
            double p1 = (p[i + 1] - a) / (p[i + 1] - p[i]);
            ans.r = p1 * c[i].r + p2 * c[i + 1].r;
            ans.g = p1 * c[i].g + p2 * c[i + 1].g;
            ans.b = p1 * c[i].b + p2 * c[i + 1].b;
            return ans;
        }
    }
}

void map_tile::draw(SDL_Renderer* r, int x, int y, color_gradient& gr) {
    color c = gr.get_color(height);
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, 255);
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
    for(int i = 0; i < x; i ++) {
        for(int j = 0; j < y; j ++) {
            m[i][j].height = (m[i][j].height - mn) / (mx - mn);
            m[i][j].water = (m[i][j].water - mn) / (mx - mn) / 2;
        }
    }

    //COLOR GRADIENTS
    gr.push_color(0, color(0, 0, 0)); //black
    gr.push_color(0.2, color(0, 0, 255)); //black
    gr.push_color(0.15, color(255, 255, 0)); //black
    gr.push_color(0.3, color(0, 191, 0)); //green
    gr.push_color(0.7, color(196, 169, 110)); //brownish
    gr.push_color(1, color(255,255,255)); //black
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
            m[x][y].draw(r, x, y, gr);
        }
    }
}
