/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings

#include "SDL_UTILS.h"

#include <chrono>
#include <ratio>
#include <thread>
#include <time.h>
#include <stdlib.h>

//Screen dimension constants

int main(int argc, char *args[])
{

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The window renderer
    SDL_Renderer *gRenderer = NULL;

    //Current displayed texture
    SDL_Texture *gTexture = NULL;


    //Start up SDL and create window
    if (!init(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        while(play(gWindow,gRenderer)){}
    }

    //Free resources and close SDL
    close(gTexture, gRenderer, gWindow);

    return 0;
}
