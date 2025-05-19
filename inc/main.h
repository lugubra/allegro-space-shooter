#ifndef _MAIN_H
#define _MAIN_H

#ifdef ALLEGRO_WINDOWS // MSVC, MinGW, Cygwin
    #define SRAND48() srand((long)time(NULL))
    #define DRAND48() ((double)rand() / RAND_MAX)
#else // OSX, Linux
    #define SRAND48() srand48(time(NULL))
    #define DRAND48() drand48()
#endif // ALLEGRO_WINDOWS

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#endif // _MAIN_H
