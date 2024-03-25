#include <iostream>
#include <SDL2/SDL.h>
#include "graphStructure.h"
// #include "struct.h"

using namespace std;

struct Color
{
    int r;
    int g;
    int b;
};

void drawStar(SDL_Renderer *renderer, int x = 100, int y = 100, int r = 15)
{

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, x - r, y, x + r, y);
    SDL_RenderDrawLine(renderer, x, y - r, x, y + r);
    for (int i = 0; i < r; i++)
    {

        SDL_RenderDrawLine(renderer, x + i - r, y - i, x + i - r, y + i);
        SDL_RenderDrawLine(renderer, x + i, y - (r - i), x + i, y + (r - i));
    }
    SDL_Rect rect;
    int i = sqrt(2 * r * r);
    rect.x = x - i / 2;
    rect.y = y - i / 2;
    rect.w = i;
    rect.h = i;
    SDL_RenderFillRect(renderer, &rect);
}

void drawGraph(SDL_Renderer *renderer, Graph &g)
{

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < g.nodes.size(); i++)
    {

        for (int j = 0; j < g.nodes[i]->adj.size(); j++)
        {

            SDL_RenderDrawLine(renderer, g.nodes[i]->pos.x, g.nodes[i]->pos.y, g.nodes[i]->adj[j]->pos.x, g.nodes[i]->adj[j]->pos.y);
        }
    }
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    for (int i = 0; i < g.nodes.size(); i++)
    {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        if (g.nodes[i]->selected == true)
        {
            SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
        }

        drawStar(renderer, g.nodes[i]->pos.x, g.nodes[i]->pos.y, 15); // draw node
    }
}

void DFSrecDraw(Graph g, Node *x, SDL_Renderer *renderer)
{

    x->visited = true;

    if (renderer)
    {

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        drawStar(renderer, x->pos.x, x->pos.y, 15);
        SDL_RenderPresent(renderer);
        SDL_Delay(300);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawStar(renderer, x->pos.x, x->pos.y, 15);
    }

    for (int i = 0; i < x->adj.size(); i++)
    {
        if ((x->adj[i])->visited == false)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, x->adj[i]->pos.x, x->adj[i]->pos.y, x->pos.x, x->pos.y);
            SDL_RenderPresent(renderer);

            SDL_Delay(200);
            DFSrecDraw(g, x->adj[i], renderer);
        }
    }
}
void DFSdraw(Graph g, Node *x, SDL_Renderer *renderer)
{

    DFSrecDraw(g, x, renderer);

    for (int i = 0; i < g.nodes.size(); i++)
    {
        g.nodes[i]->visited = false;
    }
}

void drawAddPivot(SDL_Renderer *renderer, int x, int y, Color c)
{
    int size = 8;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    SDL_RenderDrawLine(renderer, x, y, x + size, y);

    SDL_RenderDrawLine(renderer, x, y, x, y + size);

    SDL_RenderDrawLine(renderer, x, y, x, y - size);

    SDL_RenderDrawLine(renderer, x, y, x - size, y);
}
