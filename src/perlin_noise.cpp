#include "perlin_noise.h"
#include<algorithm>
#include<cmath>
#include<random>
#include<iostream>

perlin_noise::perlin_noise(int seed) {
    srand(seed);
    for(int i = 0; i < 256; i ++) p[i] = i;
    std::random_shuffle(p,p + 255);

    for(int i = 0; i < 256; i ++) {
        Gx[i] = double(rand()) / RAND_MAX * 2 - 1.0;
    }
    for(int i = 0; i < 256; i ++) {
        Gy[i] = double(rand()) / RAND_MAX * 2 - 1.0;
    }
}

double perlin_noise::noise(double x, double y) {
    int x0 = (int)(x);
    int x1 = x0 + 1;
    int y0 = (int)(y);
    int y1 = y0 + 1;

    double px = x - x0;
    double py = y - y0;

    int ind;
    ind = p[(p[x0 & 255] + y0) & 255];
    double dp00 = dot_product(px, py, Gx[ind], Gy[ind]);

    ind = p[(p[x0 & 255] + y1) & 255];
    double dp10 = dot_product(px, py - 1, Gx[ind], Gy[ind]);

    ind = p[(p[x1 & 255] + y0) & 255];
    double dp01 = dot_product(px - 1, py, Gx[ind], Gy[ind]);

    ind = p[(p[x1 & 255] + y1) & 255];
    double dp11 = dot_product(px - 1, py - 1, Gx[ind], Gy[ind]);

    double wx = interpolate(px);
    double wy = interpolate(py);

    double xa = lerp(dp00,dp01,wx);
    double xb = lerp(dp10,dp11,wx);

    double value = lerp(xa,xb,wy);

    return  value;
}

double perlin_noise::octave(double x, double y, int o) {
    double ampl = 1, freq = 1;
    double ans = 0;
    for(int i = 0; i < o; i ++) {
        ans += noise( x * freq, y * freq) * ampl;
        freq *= 2.0;
        ampl /= 2.0;
    }
    return (ans + 2) / 4;
}

inline double perlin_noise::interpolate(double a) {
    return a * a * a * ((6 * a - 15) * a + 10);
}

inline double perlin_noise::dot_product(double x0, double y0, double x1, double y1) {
    return x0 * x1 + y0 * y1;
}

inline double perlin_noise::lerp(double a, double b, double n) {
    return a + n * (b - a);
}
