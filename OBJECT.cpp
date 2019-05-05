#include "SDL_UTILS.h"

bool init(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, int screenWidth, int screenHeight)
{
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {

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

                //Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(ball &ball1, ball &ball2, ball &ball3, ball &ball4, circle &Circle1, circle &Circle2, circle &Circle3, rectangle &Rectangle, star &Star, changeColor &ChangeColor, SDL_Renderer *gRenderer)
{
    bool success = true;

    if (!Rectangle.loadFromFile("Rectangle.png", gRenderer))
    {
        printf("Failed to load obstacle image!\n");
        success = false;
    }
    if (!Circle1.loadFromFile("Image.png", gRenderer))
    {
        printf("Failed to load circle1 image!\n");
        success = false;
    }
    Circle1.x = 188;

    if (!Circle2.loadFromFile("Circle2.png", gRenderer))
    {
        printf("Failed to load Circle2 image!\n");
        success = false;
    }
    Circle2.x = 210;

    if (!Circle3.loadFromFile("Circle3.png", gRenderer))
    {
        printf("Failed to load Circle3 image!\n");
        success = false;
    }

    Circle3.x = 225;

    if (!ball1.loadFromFile("ball1.png", gRenderer))
    {
        printf("Failed to load ball image!\n");
        success = false;
    }

    if (!ball2.loadFromFile("ball2.png", gRenderer))
    {
        printf("Failed to load ball image!\n");
        success = false;
    }

    if (!ball3.loadFromFile("ball3.png", gRenderer))
    {
        printf("Failed to load ball image!\n");
        success = false;
    }

    if (!ball4.loadFromFile("ball4.png", gRenderer))
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

//Set up text
Text::Text()
{
    mTexture = NULL;
    x = 0;
    y = 0;
    sprite.x = 0;
    sprite.y = 0;
}
void Text::load(const string &text, const int size, SDL_Renderer *&gRenderer)
{
    free();

    //Load font
    TTF_Font *font = TTF_OpenFont("font.ttf", size);

    SDL_Color textColor = {255, 255, 255, 0};

    //Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface == NULL)
        cout << "Unable to render text surface! SDL_TTF Error: " << TTF_GetError() << endl;
    else
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL)
            cout << "Unable to create texture from Surface! SDL Error: " << SDL_GetError() << endl;
        else
        {
            sprite.w = textSurface->w;
            sprite.h = textSurface->h;
            sprite.y = 0;
            sprite.x = 0;
        }
        SDL_FreeSurface(textSurface);
    }
    TTF_CloseFont(font);
}
void Text::free()
{
    if (mTexture != NULL)
        SDL_DestroyTexture(mTexture);
}
SDL_Texture *Text::getTexture()
{
    return mTexture;
}

// Set up ball
ball::ball()
{
    //Initialize ball
    mTexture = NULL;
    x = 284;
    y = 620;
    vec = 0;
    a = 0;
}
void ball::move()
{
    vec = 10;
    a = 1;
}
void ball::updatePosition()
{
    y -= vec;
    vec = 10 - a;
    a++;
    if (y > BALL_START)
        y = BALL_START;
}

//Set up obstacle
obstacle::obstacle()
{
    mTexture = NULL;
    x = 0;
    y = 0;
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

void obstacle::setObject(int a, int b, int c, int d)
{
    x = a;
    y = b;
    W = c;
    H = d;
}

void obstacle::updatePosition(int a)
{
    y += a;
    //if(y>SCREEN_HEIGHT) y-=(SCREEN_HEIGHT+H);
}

//Set up star class
star::star()
{
    //Initialize star
    x = 0;
    y = 0;
}
void star::updatePosition(int a, int b)
{
    x = a;
    y = b;
}
void star::setWidthHeight(int a, int b)
{
    W = a;
    H = b;
}

//Set up change color
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
int changeColor::getDegrees()
{
    return degrees;
}
void changeColor::updatePosition(int a)
{
    y += a;
}

//Set up circle
circle::circle()
{
    mTexture = NULL;
    x = 0;
    y = 0;
}

//Set up rectangle
rectangle::rectangle()
{
    mTexture = NULL;
    x = 150;
    y = 0;
}