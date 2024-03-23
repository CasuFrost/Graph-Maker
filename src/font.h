#include <iostream>
#include <string>
#include "drawing.h"
#include <fstream>
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

    textBox(SDL_Renderer *r, string t = "", Color c = {255, 255, 255})
    {
        color = c;
        renderer = r;
        text = t;
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
                relY += 10;
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

            string path = PATH + tmp.append(".txt");

            drawFromFile(path, xPos + relX, yPos + relY);
            relX += 10;
        }

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
