#include <iostream>
#include <string>
#include "drawing.h"
#include "other.h"

using namespace std;

const string PATH = "src/PngToTextParser/PngText/";

struct Color
{
    int r;
    int g;
    int b;
};

class textBox
{
public:
    Color color;
    string text;
    SDL_Renderer *renderer;
    int xPos = 0;
    int yPos = 0;
    string fontSize = "8";

    int width;
    int height;

    textBox(SDL_Renderer *r, string t = "", Color c = {255, 255, 255})
    {
        color = c;
        renderer = r;
        text = t;
    }

    void setFontSize(string size)
    {
        fontSize = size;
    }

    void updatePos(int x, int y)
    {
        xPos = x;
        yPos = y;
    }

    void updateStr(string a)
    {
        text = a;
    }

    void drawText()
    {
        int relY = 0;
        int relX = 0;

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == '\n')
            {
                relY += stoi(fontSize) + 2;
                relX = 0;
                continue;
            }

            string tmp;
            tmp = text[i];

            if (text[i] == '?')
            {
                tmp = "questionMark";
            }

            if (text[i] == ' ')
            {
                tmp = "spaz";
            }

            string size;
            size = fontSize;
            size.append(tmp);
            tmp = size;

            string path = PATH + fontSize + "/" + tmp.append(".txt");

            drawFromFile(path, xPos + relX, yPos + relY);

            relX += stoi(fontSize) + 2;
        }
        height = relY;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    }

    void drawFromFile(string path, int x, int y)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255); // set color text
        char ch;
        fstream fin(path, fstream::in);

        int relX = 0;
        int relY = 0;

        while (fin >> noskipws >> ch)
        {
            if (ch == '1')
            {
                SDL_RenderDrawPoint(renderer, relX + x, relY + y);
            }
            relX++;
            if (ch == '\n')
            {
                relX = 0;
                relY++;
            }
        }
    }
};

class button : public textBox
{
private:
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
    }

    void drawBox()
    {
        SDL_Rect rect;
        rect.x = xPos - padding;
        rect.y = yPos - padding;
        rect.w = boxWidth + padding;
        rect.h = boxHeight + padding;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // set box color

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }

    void calculateBoxSize()
    {
        int w = 0;
        int h = stoi(fontSize) + 6;
        int tmpW = 0;
        for (int i = 0; i < text.length(); i++)
        {
            tmpW += stoi(fontSize) + 2;

            if (text[i] == '\n')
            {
                w = max(w, tmpW);
                h += stoi(fontSize) + 2;
                tmpW = 0;
            }
        }
        w = max(w, tmpW);
        boxWidth = w;
        boxHeight = h;
    }
};