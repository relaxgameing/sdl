#include <stdio.h>
#include <math.h>
#include <SDL.h>

#define UNIT_RADIAN (M_PI / 180)
#define NO_OF_RAYS 500

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 800

#define OBJECT_X 500
#define OBJECT_Y 200
#define OBJECT_R 100

void drawCircle(SDL_Renderer* render, double x, double y, double r) {
    // for (double theta = 0; theta <= 180; theta += 0.1)
    // {
    //     double angle = theta * UNIT_RADIAN;
    //     double dx = r * cos(angle);
    //     double dy = r * sin(angle);
    //     SDL_RenderDrawLineF(render, x - dx, y - dy, x + dx, y + dy);
    // }
    double rr = r * r;
    for (int dy = -r; dy <= r; dy++) {
        for (int dx = -r; dx <= r; dx++) {
            if (dx * dx + dy * dy <= rr) {
                SDL_RenderDrawPoint(render, x + dx, y + dy);
            }
        }
    }
}

void drawLine(SDL_Renderer* render, double x, double y, double angle) {
    // y - y1 = m ( x - x1 )
    int l = 0;
    int touched = 0;
    double rx = x;
    double ry = y;
    while (1)
    {
        l += 1;
        rx = l * cos(angle);
        ry = l * sin(angle);
        if (x + rx < 0 || x + rx > WINDOW_WIDTH)
        {
            break;
        }

        if (y + ry < 0 || y + ry > WINDOW_HEIGHT)
        {
            break;
        }

        if (pow(OBJECT_X - (x + rx), 2) + pow(OBJECT_Y - (y + ry), 2) <= pow(OBJECT_R, 2))
        {
            break;
        }
        SDL_RenderDrawPoint(render, x + rx, y + ry);
    }
}

void drawRays(SDL_Renderer* render, double x, double y) {
    double delta = (2 * M_PI) / NO_OF_RAYS;
    for (int i = 0; i <= NO_OF_RAYS; i++)
    {
        double angle = i * delta;
        drawLine(render, x, y, angle);
    }
}

int main(void) {
    // Attempt to initialize graphics and timer system.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("raytracing",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* render = SDL_CreateRenderer(window, 0, 0);

    if (!window)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    double ballX = 100;
    double ballY = 100;

    // Keep the window open, in this case SDL_Delay(5000); statement won't work.
    int running = 1;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_MOUSEMOTION:

                if (e.motion.state)
                {
                    ballX = e.motion.x;
                    ballY = e.motion.y;
                    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
                    SDL_RenderClear(render);
                }
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        drawCircle(render, ballX, ballY, 50);


        drawCircle(render, 500, 200, 100);

        drawRays(render, ballX, ballY);

        SDL_RenderPresent(render);
        SDL_Delay(20);
    }

    // clean up resources before exiting.
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}