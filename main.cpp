#include "src/drawing.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Graph Maker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // drawStar(renderer, 100, 100, 50);
    // SDL_RenderPresent(renderer);

    // COSE SUL GRAFO

    Graph g(0, 0.02);
    g.selected = NULL;
    int xMouse = 0;
    int yMouse = 0;
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            SDL_GetMouseState(&xMouse, &yMouse);
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == 1)
                {
                    g.addNode(xMouse, yMouse);
                    if (g.selected)
                    {
                        g.addNearest(xMouse, yMouse);
                    }
                }

                if (event.button.button == 3)
                {
                    g.addNearest(xMouse, yMouse);
                }
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    drawGraph(renderer, g);
                    if (!g.selected)
                        g.selected = g.nodes[0];
                    DFSdraw(g, g.selected, renderer);
                    g.selected = NULL;
                }
            }
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        if (g.selected)
        {
            SDL_SetRenderDrawColor(renderer, 255, 191, 41, 255);
            SDL_RenderDrawLine(renderer, g.selected->pos.x, g.selected->pos.y, xMouse, yMouse);
        }

        drawGraph(renderer, g);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    // g.showGraphInformation();

    // drawGraph(renderer, g);

    // SDL_Delay(600);
    SDL_Quit();

    return 0;
}