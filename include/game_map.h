#include<SDL2/SDL.h>

#ifndef GAME_MAP_H
#define GAME_MAP_H


struct map_tile {
    double height;
    double water;

    void draw(SDL_Renderer* r, int x, int y);
};

class game_map {
    public:
        game_map(int x, int y, int seedh, int seedw);
        virtual ~game_map();
        void draw(SDL_Renderer* r);
        game_map& operator=(const game_map& other);

        map_tile** m;
        int width, height;
    protected:

    private:
};

#endif // GAME_MAP_H
