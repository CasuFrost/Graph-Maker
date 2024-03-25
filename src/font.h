#include <iostream>
#include <string>
#include "drawing.h"
#include "other.h"

using namespace std;

const string PATH = "src/PngToTextParser/PngText/";

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

    /*void drawText()
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
    }*/

    /*void drawFromFile(string path, int x, int y)
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
    }*/
    void drawText()
    {
        int relY = 0;
        int relX = 0;

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == '\n')
            {
                relY += stoi(fontSize) * 8 + 2;
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

            relX += stoi(fontSize) * 8 + 2;
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
            for (int j = 0; j < stoi(fontSize); j++)
            {
                if (ch == '1')
                {
                    for (int i = 0; i < stoi(fontSize); i++)
                    {
                        SDL_RenderDrawPoint(renderer, relX + x + i, relY + y + j);
                    }
                }
            }

            relX += stoi(fontSize);
            if (ch == '\n')
            {
                relX = 0;
                relY += stoi(fontSize);
            }
        }
    }
};
