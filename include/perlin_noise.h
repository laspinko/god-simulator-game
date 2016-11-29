#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H


class perlin_noise
{
    public:
        perlin_noise(int seed);
        double noise(double x, double y);
        double octave(double x, double y, int o);

        inline double interpolate(double a);
        inline double dot_product(double x0, double y0, double x1, double y1);
        inline double lerp(double a, double b, double n);
    protected:

    private:

        int p[256];

        double Gx[256], Gy[256];
};

#endif // PERLIN_NOISE_H
