#include "SDL_UTILS.h"

bool init(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, int screenWidth, int screenHeight)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(ball &Ball, obstacle &Obstacle1,obstacle &Obstacle2, star &Star, changeColor &ChangeColor, SDL_Renderer *gRenderer)
{
    //Loading success flag
    bool success = true;

    //Load PNG texture

    if (!Obstacle1.loadFromFile("Image.png", gRenderer))
    {
        printf("Failed to load obstacle image!\n");
        success = false;
    }
    if(!Obstacle2.loadFromFile("Image.png",gRenderer));
    {
        printf("Failed to load obstacle image!\n");
    }

    if (!Ball.loadFromFile("ball1.png", gRenderer))
    {
        printf("Failed to load ball image!\n");
        success = false;
    }
    if (!Star.loadFromFile("Star.png", gRenderer))
    {
        printf("Failed to load star image\n");
        success = false;
    }
    if (!ChangeColor.loadFromFile("CL.png", gRenderer))
    {
        printf("Failed to load Change Color image\n");
        success = false;
    }

    return success;
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

Texture::Texture()
{
    //Initialize

    mTexture = NULL;
    x = 0;
    y = 0;
    W = 0;
    H = 0;
}
Texture::~Texture()
{
    //Deallocate
    free();
}

void Texture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        W = 0;
        H = 0;
    }
}

bool Texture::loadFromFile(const string &path, SDL_Renderer *&gRenderer)
{
    int mWidth, mHeight;
    //The final texture
    free();

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {

        //Create texture from surface pixels

        mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            W = (loadedSurface->w);
            H = (loadedSurface->h);
            updateTexture();
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return mTexture != NULL;
}
void Texture::updateTexture()
{
    sprite.x = x;
    sprite.y = y;
    sprite.h = H;
    sprite.w = W;
}

ball::ball()
{
    //Initialize ball
    mTexture = NULL;
    x = 284;
    y = 620;
    vec = -10;
    a = 0;
}
void ball::move()
{
    vec = 10;
    a = 0;
}
void ball::updatePosition()
{
    y -= vec;
    vec = 10 - a;
    a++;
    if (y > BALL_START)
        y = BALL_START;
}
int ball::getX()
{
    return x;
}
int ball::getY()
{
    return y;
}

int ball::getvec()
{
    return vec;
}

obstacle::obstacle()
{
    mTexture = NULL;
    x = 188;
    y = -125;
    degrees = 0;
    flipType = SDL_FLIP_NONE;
}
void obstacle::Rotation()
{
    degrees += 3;
    if (degrees >= 360)
        degrees -= 360;
}
int obstacle::getDegrees()
{
    return degrees;
}
int obstacle::getX()
{
    return x;
}
int obstacle::getY()
{
    return y;
}
void obstacle::updatePosition(int a)
{
    y += 2;
}

//Set up star class
star::star()
{
    //Initialize star
    x = 284;
    y = 0;
}
void star::updatePosition(int a, int b)
{
    x = a;
    y = b;
}
int star::getX()
{
    return x;
}
int star::getY()
{
    return y;
}

changeColor::changeColor()
{
    x = 284;
    y = 0;
}
void changeColor::Rotation()
{
    degrees += 3;
    if (degrees >= 360)
        degrees -= 360;
}
int changeColor::getX()
{
    return x;
}
int changeColor::getY()
{
    return y;
}
int changeColor::getDegrees()
{
    return degrees;
}
