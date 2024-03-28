#include "font.h"
class userInfo
{
public:
    bool addNodeMode = false;
    bool deleteNodeMode = false;
    bool selectMode = false;
};
class button : public textBox
{
private:
    Color boxColor = {255, 0, 0};
    Color OgBoxColor = {255, 0, 0};
    int changeColorCounter = 0;
    int boxWidth = 0;
    int boxHeight = 0;

public:
    int padding = 3;

    button(SDL_Renderer *r, string t = "", Color c = {255, 255, 255}) : textBox(r, t, c)
    {
    }

    void updateStr(string a)
    {
        text = a;
        calculateBoxSize(); // recalculate box size
    }

    void drawText()
    {
        drawBox();
        textBox::drawText();
        boxColor = {150, 150, 150};
        if (changeColorCounter == 0)
        {
            boxColor = {255, 0, 0};
        }
        else
        {
            changeColorCounter--;
        }
    }

    void drawBox()
    {
        SDL_Rect rect;
        rect.x = xPos - padding;
        rect.y = yPos - padding;
        rect.w = boxWidth + padding;
        rect.h = boxHeight + padding;
        SDL_SetRenderDrawColor(renderer, boxColor.r, boxColor.g, boxColor.b, 255); // set box color

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }

    void calculateBoxSize()
    {
        int w = 0;
        int h = stoi(fontSize) * 8 + 6;
        int tmpW = 0;
        for (int i = 0; i < text.length(); i++)
        {
            tmpW += stoi(fontSize) * 8 + 2;

            if (text[i] == '\n')
            {
                w = max(w, tmpW);
                h += stoi(fontSize) * 8 + 2;
                tmpW = 0;
            }
        }
        w = max(w, tmpW);
        boxWidth = w;
        boxHeight = h;
    }

    void checkIfPressed(int x, int y, userInfo *user, Graph *g)
    {
        if ((x >= xPos && x <= xPos + boxWidth) &&
            (y >= yPos && y <= yPos + boxHeight))
        {
            pressed(user, g);
        }
    }

    void pressed(userInfo *user, Graph *g)
    {
        changeColorCounter = 15;
        if (text == "DFS")
        {
            drawGraph(renderer, *g);
            if (!g->selected)
                g->selected = g->nodes[0];
            DFSdraw(*g, g->selected, renderer);
            g->selected->selected = false;
            g->selected = NULL;
            return;
        }
        if (text == "BFS")
        {
            drawGraph(renderer, *g);
            if (!g->selected)
                g->selected = g->nodes[0];
            BFSdraw(*g, g->selected, renderer);
            g->selected->selected = false;
            g->selected = NULL;
            return;
        }
        if (text == "create edge")
        {
            user->selectMode = true;
            return;
            // switch to add node mode
        }
        if (text == "add node")
        {
            if (user->addNodeMode)
            {

                user->addNodeMode = false;
                return;
            }
            user->addNodeMode = true;
            return;
            // switch to add node mode
        }
        if (text == "delete node")
        {
            user->deleteNodeMode = true;
            return;
            // switch to add node mode
        }
        if (text == "save graph")
        {
            g->saveGraph("graph.txt");
            return;
        }
        if (text == "example graph")
        {
            g->loadGraphFromFile("example.txt");
            return;
        }
        if (text == "load graph")
        {
            g->loadGraphFromFile("graph.txt");
            return;
        }
    }
};
