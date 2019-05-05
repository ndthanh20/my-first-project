#include "SDL_UTILS.h"

void initializeObstacle(obstacle &Obstacle1, obstacle &Obstacle2, obstacle &Obstacle3, circle &Circle1, circle &Circle2, circle &Circle3,star &Star1, star &Star2, star &Star3)
{
    int chooseRandom, chooseRandom1, chooseRandom2;

    srand(time(NULL));

    chooseRandom = rand() % 3 + 1;

    switch (chooseRandom)
    {
    case 1:
    {
        Obstacle1.mTexture = Circle1.mTexture;
        Obstacle1.setObject(Circle1.x, Circle1.y, Circle1.W, Circle1.H);
        break;
    }
    case 2:
    {

        Obstacle1.mTexture = Circle2.mTexture;
        Obstacle1.setObject(Circle2.x, Circle2.y, Circle2.W, Circle2.H);
        break;
    }
    case 3:
    {
        Obstacle1.mTexture = Circle3.mTexture;
        Obstacle1.setObject(Circle3.x, Circle3.y, Circle3.W, Circle3.H);
        break;
    }

    default:
        break;
    }

    Obstacle1.y -= (Obstacle1.W) / 2;

    Star1.updatePosition((SCREEN_WIDTH - Star1.W) / 2, (Obstacle1.y + (Obstacle1.H - Star1.H) / 2));

    chooseRandom1 = rand() % 3 + 1;

    switch (chooseRandom1)
    {
    case 1:
    {
        Obstacle2.mTexture = Circle1.mTexture;
        Obstacle2.setObject(Circle1.x, Circle1.y, Circle1.W, Circle1.H);
        break;
    }
    case 2:
    {
        Obstacle2.mTexture = Circle2.mTexture;
        Obstacle2.setObject(Circle2.x, Circle2.y, Circle2.W, Circle2.H);
        break;
    }
    case 3:
    {
        Obstacle2.mTexture = Circle3.mTexture;
        Obstacle2.setObject(Circle3.x, Circle3.y, Circle3.W, Circle3.H);
        break;
    }

    default:
        break;
    }

    Obstacle2.y = Obstacle1.y - 150 - Obstacle2.H;

    Star2.updatePosition((SCREEN_WIDTH - Star2.W) / 2, (Obstacle2.y + (Obstacle2.H - Star2.H) / 2));



    chooseRandom2 = rand() % 3 + 1;
    switch (chooseRandom2)
    {
    case 1:
    {
        Obstacle3.mTexture = Circle1.mTexture;
        Obstacle3.setObject(Circle1.x, Circle1.y, Circle1.W, Circle1.H);
        break;
    }
    case 2:
    {
        Obstacle3.mTexture = Circle2.mTexture;
        Obstacle3.setObject(Circle2.x, Circle2.y, Circle2.W, Circle2.H);
        break;
    }
    case 3:
    {
        Obstacle3.mTexture = Circle3.mTexture;
        Obstacle3.setObject(Circle3.x, Circle3.y, Circle3.W, Circle3.H);
        break;
    }

    default:
        break;
    }
    Obstacle3.y = Obstacle2.y - 150 - Obstacle3.H;

    Star3.updatePosition((SCREEN_WIDTH - Star3.W) / 2, (Obstacle3.y + (Obstacle3.H - Star3.H) / 2));

    return;
}

int changeBall(ball &Ball, ball &ball1, ball &ball2, ball &ball3, ball &ball4)
{
    int a;
    srand(time(NULL));
    a = rand() % 4 + 1;
    switch (a)
    {
    case 1:
    {
        Ball.mTexture = ball1.mTexture;
        Ball.W = ball1.W;
        Ball.H = ball1.H;
        return 1;
    }
    case 2:
    {
        Ball.mTexture = ball2.mTexture;
        Ball.W = ball2.W;
        Ball.H = ball2.H;
        return 2;
    }
    case 3:
    {
        Ball.mTexture = ball3.mTexture;
        Ball.W = ball3.W;
        Ball.H = ball3.H;
        return 3;
    }
    case 4:
    {
        Ball.mTexture = ball4.mTexture;
        Ball.W = ball4.W;
        Ball.H = ball4.H;
        return 4;
    }

    default:
    {
        return 0;
    }
    }
}

void passObstacle(ball &Ball, obstacle &Obstacle, bool &quit, int numberBall)
{
    switch (numberBall)
    {
    case 1:
    {
        if (Ball.y <= Obstacle.y + Obstacle.H && Ball.y+Ball.H >= Obstacle.y + Obstacle.H - 25)
        {
            if (Obstacle.getDegrees() > 90 && Obstacle.getDegrees() < 180)
            {
                return;
            }
            else
            {
                quit = 1;
                return;
            }
        }

        if ((Ball.y+Ball.H >= Obstacle.y && Ball.y <= Obstacle.y + 25))
            if (Obstacle.getDegrees() > 270&& Obstacle.getDegrees()<360)
            {
                return;
            }
            else
            {
                quit=1;
                return ;
            }
        
    }
    case 2:
    {
        if (Ball.y <= Obstacle.y + Obstacle.H && Ball.y+Ball.H >= Obstacle.y + Obstacle.H - 25)
        {
            if (Obstacle.getDegrees() > 0 && Obstacle.getDegrees() < 90)
            {
                return;
            }
            else
            {
                quit = 1;
                return;
            }
        }

        if ((Ball.y+Ball.H >= Obstacle.y && Ball.y <= Obstacle.y + 25))
            if (Obstacle.getDegrees() > 180 && Obstacle.getDegrees() < 270)
            {
                return;
            }
            else
            {
                quit = 1;
                return;
            }
        
    }
    case 3:
    {
        if (Ball.y <= Obstacle.y + Obstacle.H && Ball.y+Ball.H >= Obstacle.y + Obstacle.H - 25)
        {
            if (Obstacle.getDegrees() > 270 && Obstacle.getDegrees() < 360)
            {
                return;
            }
            else
            {
                quit = 1;
                return;
            }
        }

        if ((Ball.y+Ball.H >= Obstacle.y && Ball.y <= Obstacle.y + 25))
            if (Obstacle.getDegrees() > 90 && Obstacle.getDegrees() < 180)
            {
                return;
            }
            else
            {
                quit = 1;
                return;
            }
    }
    case 4:
    {
        if (Ball.y <= Obstacle.y + Obstacle.H && Ball.y+Ball.H >= Obstacle.y + Obstacle.H - 25)
        {
            if (Obstacle.getDegrees() > 180 && Obstacle.getDegrees() < 270)
            {
                return;
            }
            else
            {
                quit = 1;
                return;
            }
        }

        if ((Ball.y+Ball.H >= Obstacle.y && Ball.y <= Obstacle.y + 25))
            if (Obstacle.getDegrees() > 0 && Obstacle.getDegrees() < 90)
            {
                return;
            }
            else
            {
                quit = 1;
                return;
            }
    }
    default:
        return;
    }
}

bool checkobstacle(obstacle &Obstacle, circle &Circle1, circle &Circle2, circle &Circle3)
{
    int a;
    if (Obstacle.y > SCREEN_HEIGHT)
    {
        
        a = rand() % 3 + 1;
        switch (a)
        {
        case 1:
        {
            Obstacle.mTexture = Circle1.mTexture;
            Obstacle.setObject(Circle1.x, Circle1.y, Circle1.W, Circle1.H);
            break;
        }
        case 2:
        {
            Obstacle.mTexture = Circle2.mTexture;
            Obstacle.setObject(Circle2.x, Circle2.y, Circle2.W, Circle2.H);
            break;
        }
        case 3:
        {
            Obstacle.mTexture = Circle3.mTexture;
            Obstacle.setObject(Circle3.x, Circle3.y, Circle3.W, Circle3.H);
            break;
        }

        default:
            break;
        }

        return 1;
    }
    return 0;
}

void renderOb(SDL_Renderer *gRenderer, obstacle &Obstacle, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{

    SDL_Rect renderQuad = Obstacle.sprite;

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, Obstacle.mTexture, clip, &renderQuad, angle, center, flip);
}
void renderCL(SDL_Renderer *gRenderer, changeColor &ChangeColor, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = ChangeColor.sprite;

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, ChangeColor.mTexture, clip, &renderQuad, angle, center, flip);
}
void close(SDL_Texture *&gTexture, SDL_Renderer *&gRenderer, SDL_Window *&gWindow)
{
    //Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
