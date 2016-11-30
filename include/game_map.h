#include<SDL2/SDL.h>
#include<vector>

#ifndef GAME_MAP_H
#define GAME_MAP_H

struct color{
    int r, g, b;
    color(int red = 0, int green = 0, int blue = 0):r(red), g(green), b(blue){};
};

struct color_gradient {
    std::vector<double> p;
    std::vector<color> c;
    void push_color(double a, color b);
    color get_color(double a);

};

struct map_tile {
    double height;
    double water;

    void draw(SDL_Renderer* r, int x, int y, color_gradient& cr);
};

class game_map {
    public:
        game_map(int x, int y, int seedh, int seedw);
        virtual ~game_map();
        void draw(SDL_Renderer* r);
        game_map& operator=(const game_map& other);

        int width, height;
    protected:
        map_tile** m;
        color_gradient gr;

    private:
};

#endif // GAME_MAP_H
