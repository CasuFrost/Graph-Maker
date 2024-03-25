#include "src/buttonsFunctionalities.h"

// #define WIDTH 1280
// #define HEIGHT 720

using namespace std;

int main(int argc, char *argv[])
{

    userInfo *user = new userInfo();

    bool defaultSize = true;

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
    title.setFontSize("2");
    title.updateStr("Graph Editor");
    title.updatePos(10, 10);

    textBox edgeText(renderer);
    edgeText.setFontSize("1");
    edgeText.updateStr("press the right mouse\nbutton on two nodes\nto create an edge");
    edgeText.updatePos(10, 80);

    button DFS(renderer);
    DFS.setFontSize("1");
    DFS.updateStr("DFS");
    DFS.updatePos(10, 170);

    button saveText(renderer);
    saveText.setFontSize("1");
    saveText.updateStr("save graph");
    saveText.updatePos(10, 200);

    button loadText(renderer);
    loadText.setFontSize("1");
    loadText.updateStr("load graph");
    loadText.updatePos(10, 230);

    vector<button> buttons;
    vector<textBox> texts;

    texts.push_back(title);

    texts.push_back(edgeText);
    buttons.push_back(DFS);
    buttons.push_back(loadText);
    buttons.push_back(saveText);

    button test(renderer);
    test.setFontSize("1");
    test.updateStr("add node");
    test.updatePos(10, 50);
    buttons.push_back(test);

    button remove(renderer);
    remove.setFontSize("1");
    remove.updateStr("delete node");
    remove.updatePos(10, 130);
    buttons.push_back(remove);

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
                    if (user->addNodeMode)
                    {
                        g.addNode(xMouse, yMouse);

                        user->addNodeMode = false;
                    }
                    if (user->deleteNodeMode)
                    {
                        g.deleteNode(xMouse, yMouse);

                        user->deleteNodeMode = false;
                    }

                    for (int i = 0; i < buttons.size(); i++)
                    {
                        buttons[i].checkIfPressed(xMouse, yMouse, user, &g);
                    }
                }

                if (event.button.button == 3)
                {
                    g.addNearest(xMouse, yMouse);
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
        for (int i = 0; i < buttons.size(); i++)
        {
            buttons[i].drawText();
        }

        drawGraph(renderer, g);

        if (user->addNodeMode)
        {
            user->deleteNodeMode = false;
            Color c = {0, 255, 0};
            drawAddPivot(renderer, xMouse, yMouse, c);
        }
        if (user->deleteNodeMode)
        {
            Color c = {255, 0, 0};
            drawAddPivot(renderer, xMouse, yMouse, c);
        }
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