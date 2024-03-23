#include "src/font.h"

// #define WIDTH 1280
// #define HEIGHT 720

using namespace std;

int main(int argc, char *argv[])
{
    bool defaultSize = false;

    int WIDTH = 0;
    int HEIGHT = 0;
    GetDesktopResolution(WIDTH, HEIGHT);

    WIDTH -= 200;
    HEIGHT -= 200;
    if (defaultSize)
    {
        WIDTH = 1280;
        HEIGHT = 720;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Graph Maker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    textBox title(renderer);
    title.setFontSize("16");
    title.updateStr("Graph Editor");
    title.updatePos(10, 10);

    textBox nodeText(renderer);
    nodeText.setFontSize("8");
    nodeText.updateStr("press the left mouse\nbutton to add a node");
    nodeText.updatePos(10, 50);

    textBox edgeText(renderer);
    edgeText.setFontSize("8");
    edgeText.updateStr("press the right mouse\nbutton on two nodes\nto create an edge");
    edgeText.updatePos(10, 80);

    textBox removeText(renderer);
    removeText.setFontSize("8");
    removeText.updateStr("press the r keyboard\nbutton on a node\nto delete it");
    removeText.updatePos(10, 130);

    textBox DFSText(renderer);
    DFSText.setFontSize("8");
    DFSText.updateStr("press the space keyboard\nbutton to start the DFS");
    DFSText.updatePos(10, 170);

    vector<textBox> texts;
    texts.push_back(title);
    texts.push_back(nodeText);
    texts.push_back(removeText);
    texts.push_back(edgeText);
    texts.push_back(DFSText);

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
                if (event.key.keysym.sym == SDLK_r)
                {
                    g.deleteNode(xMouse, yMouse);
                }
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    drawGraph(renderer, g);
                    if (!g.selected)
                        g.selected = g.nodes[0];
                    DFSdraw(g, g.selected, renderer);
                    g.selected->selected = false;
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

        for (int i = 0; i < texts.size(); i++)
        {
            texts[i].drawText();
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