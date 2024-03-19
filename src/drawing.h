#include <iostream>
#include <SDL2/SDL.h>
#include<math.h>
using namespace std;

void drawStar(SDL_Renderer *renderer,int x=100, int y=100, int r=15){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawLine(renderer, x-r,y,x+r,y);
    SDL_RenderDrawLine(renderer, x,y-r,x,y+r);
    for(int i = 0;i<r;i++){

        
        SDL_RenderDrawLine(renderer, x+i-r,y-i,x+i-r,y+i);
        SDL_RenderDrawLine(renderer, x+i, y-(r-i) ,x+i, y+(r-i));


        

        SDL_RenderPresent(renderer);

    }
    SDL_Rect rect;
    int i = sqrt(2*r*r);
    rect.x = x-i/2;
    rect.y = y-i/2;
    rect.w =i;
    rect.h =i;
    SDL_RenderFillRect(renderer, &rect);

}