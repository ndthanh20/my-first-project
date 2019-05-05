#include "SDL_UTILS.h"

void initializeStar(star &Star, star &Star1, star &Star2, star &Star3)
{
    Star1.mTexture = Star.mTexture;

    Star1.setWidthHeight(Star.W, Star.H);

    Star2.mTexture = Star.mTexture;

    Star2.setWidthHeight(Star.W, Star.H);

    Star3.mTexture = Star.mTexture;

    Star3.setWidthHeight(Star.W, Star.H);
}

void checkStar(ball &Ball, star &Star,int &score)
{
    if(Ball.y<=Star.y+20)
    {
        score++;
        Star.updatePosition(Star.x,-1000);
    }
}

void closeObject(ball &Ball,ball  &ball1,ball &ball2, ball &ball3, ball &ball4, obstacle &Obstacle1,obstacle &Obstacle2,obstacle &Obstacle3,star &Star,star &Star1,star &Star2,star &Star3,changeColor &ChangeColor,circle &Circle1,circle &Circle2,circle &Circle3,rectangle &Rectangle,Text &text,Text &textScore)
{
    Ball.free();
    ball1.free();
    ball2.free();
    ball3.free();
    ball4.free();
    Obstacle1.free();
    Obstacle2.free();
    Obstacle3.free();
    Star.free();
    Star1.free();
    Star2.free();
    Star3.free();
    ChangeColor.free();
    Circle1.free();
    Circle2.free();
    Circle3.free(); 
    Rectangle.free();
    text.free();
    textScore.free();


}

bool play(SDL_Window *&gWindow, SDL_Renderer *&gRenderer)
{

    //Object Declaration
    ball Ball, ball1, ball2, ball3, ball4;
    obstacle Obstacle1, Obstacle2, Obstacle3;
    star Star, Star1, Star2, Star3;
    changeColor ChangeColor;
    circle Circle1, Circle2, Circle3;
    rectangle Rectangle;
    Text text, textScore;

    int numberBall, count = 0, score = 0;

    if (!loadMedia(ball1, ball2, ball3, ball4, Circle1, Circle2, Circle3, Rectangle, Star, ChangeColor, gRenderer))
    {
        printf("Failed to load media!\n");
    }
    else
    {

        //Main loop flag

        bool quit = false;

        //Event handler
        SDL_Event e, ee;

        //Initialize Object

        initializeStar(Star, Star1, Star2, Star3);

        initializeObstacle(Obstacle1, Obstacle2, Obstacle3, Circle1, Circle2, Circle3, Star1, Star2, Star3);

        text.load("Press Y to play again, N to close game", 24, gRenderer);

        numberBall = changeBall(Ball, ball1, ball2, ball3, ball4);

        ChangeColor.updatePosition(Obstacle1.y - 75);

        //While application is running
        while (!quit)
        {
            SDL_Delay(20);

            while (SDL_PollEvent(&e) != 0)
            {

                if (e.type == SDL_QUIT)
                {
                    return false;
                }
                if (e.type == SDL_KEYDOWN)
                    if (e.key.keysym.sym == SDLK_UP)
                    {
                        Ball.move();
                    }
            }

            SDL_RenderClear(gRenderer);

            if (checkobstacle(Obstacle1, Circle1, Circle2, Circle3))
            {
                Obstacle1.y = Obstacle3.y - 150 - Obstacle1.H;
                Star1.updatePosition((SCREEN_WIDTH - Star1.W) / 2, (Obstacle1.y + (Obstacle1.H - Star1.H) / 2));
            }

            if (checkobstacle(Obstacle2, Circle1, Circle2, Circle3))
            {
                Obstacle2.y = Obstacle1.y - 150 - Obstacle2.H;
                Star2.updatePosition((SCREEN_WIDTH - Star2.W) / 2, (Obstacle2.y + (Obstacle2.H - Star2.H) / 2));
            }

            if (checkobstacle(Obstacle3, Circle1, Circle2, Circle3))
            {
                Obstacle3.y = Obstacle2.y - 150 - Obstacle3.H;
                Star3.updatePosition((SCREEN_WIDTH - Star3.W) / 2, (Obstacle3.y + (Obstacle3.H - Star3.H) / 2));
            }

            //Update Object

            Ball.updatePosition();

            Obstacle1.Rotation();

            Obstacle2.Rotation();

            Obstacle3.Rotation();

            ChangeColor.Rotation();

            if (Ball.y < SCREEN_HEIGHT - 360)
            {
                Obstacle1.updatePosition(2);
                Obstacle2.updatePosition(2);
                Obstacle3.updatePosition(2);
                Star1.updatePosition(Star1.x,Star1.y+2);
                Star2.updatePosition(Star2.x,Star2.y+2);
                Star3.updatePosition(Star3.x,Star3.y+2);
                ChangeColor.updatePosition(2);
            }

            if (Ball.y <= ChangeColor.y)
            {
                numberBall = changeBall(Ball, ball1, ball2, ball3, ball4);
                if (count == 0)
                {
                    ChangeColor.updatePosition(-150 - Obstacle2.H);
                }
                if (count == 1)
                {
                    ChangeColor.updatePosition(-150 - Obstacle3.H);
                }
                if (count == 2)
                {
                    ChangeColor.updatePosition(-150 - Obstacle1.H);
                }
                count++;
                count = count % 3;
            }

            //Check Ball pass Obstacle

            passObstacle(Ball, Obstacle1, quit, numberBall);

            passObstacle(Ball, Obstacle2, quit, numberBall);

            passObstacle(Ball, Obstacle3, quit, numberBall);

            //Check pass star

            checkStar(Ball,Star1,score);

            checkStar(Ball,Star2,score);

            checkStar(Ball,Star3,score);

            //Update Texture

            Obstacle1.updateTexture();

            Obstacle2.updateTexture();

            Obstacle3.updateTexture();

            Ball.updateTexture();

            Star1.updateTexture();
            Star2.updateTexture();
            Star3.updateTexture();

            ChangeColor.updateTexture();

            //Render to screen

            renderOb(gRenderer, Obstacle1, Obstacle1.x, Obstacle1.y, NULL, Obstacle1.getDegrees(), NULL, Obstacle1.flipType);

            renderOb(gRenderer, Obstacle2, Obstacle2.x, Obstacle2.y, NULL, Obstacle2.getDegrees(), NULL, Obstacle2.flipType);

            renderOb(gRenderer, Obstacle3, Obstacle3.x, Obstacle3.y, NULL, Obstacle3.getDegrees(), NULL, Obstacle3.flipType);

            renderCL(gRenderer, ChangeColor, ChangeColor.x, ChangeColor.y, NULL, ChangeColor.getDegrees(), NULL, ChangeColor.flipType);

            SDL_RenderCopy(gRenderer, Ball.mTexture, NULL, &Ball.sprite);

            SDL_RenderCopy(gRenderer, Star1.mTexture, NULL, &Star1.sprite);

            SDL_RenderCopy(gRenderer, Star2.mTexture, NULL, &Star2.sprite);

            SDL_RenderCopy(gRenderer, Star3.mTexture, NULL, &Star3.sprite);


            textScore.load(to_string(score), 14, gRenderer);

            SDL_RenderCopy(gRenderer, textScore.mTexture, NULL, &textScore.sprite);

            //Update screeng
            SDL_RenderPresent(gRenderer);
        }

        //Request player to play again
        if (quit == 1)
        {
            while (1)
            {
                while (SDL_PollEvent(&ee) != 0)
                {
                    if (ee.type == SDL_QUIT)
                    {
                        return false;
                    }
                    if (ee.type == SDL_KEYDOWN)
                    {
                        if (ee.key.keysym.sym == SDLK_y)
                            return true;
                        if (ee.key.keysym.sym == SDLK_n)
                            return false;
                    }
                }
                SDL_RenderCopy(gRenderer, text.mTexture, NULL, &text.sprite);

                SDL_RenderPresent(gRenderer);
            }
        }
    }

    closeObject(Ball, ball1, ball2, ball3, ball4,  Obstacle1, Obstacle2, Obstacle3, Star, Star1, Star2, Star3, ChangeColor, Circle1, Circle2, Circle3, Rectangle,text, textScore);
    return true;
}