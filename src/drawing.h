#include <iostream>
#include <SDL2/SDL.h>
#include<math.h>
#include "graphStructure.h"

//#include "struct.h"

using namespace std;

void drawStar(SDL_Renderer *renderer,int x=100, int y=100, int r=15){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawLine(renderer, x-r,y,x+r,y);
    SDL_RenderDrawLine(renderer, x,y-r,x,y+r);
    for(int i = 0;i<r;i++){

        
        SDL_RenderDrawLine(renderer, x+i-r,y-i,x+i-r,y+i);
        SDL_RenderDrawLine(renderer, x+i, y-(r-i) ,x+i, y+(r-i));


        

        

    }
    SDL_Rect rect;
    int i = sqrt(2*r*r);
    rect.x = x-i/2;
    rect.y = y-i/2;
    rect.w =i;
    rect.h =i;
    SDL_RenderFillRect(renderer, &rect);
    
}
/*
void drawGraph(SDL_Renderer *renderer,Graph &g){

    int y=100;
    int x=100;
    for(int i=0;i<g.nodes.size();i++){ 
        drawStar(renderer,x,y,15);
        
        g.updateNodePos(i,x,y);
        
        x+=100;
        if((i+1)%2==0){
            y+=100;
            x=100;
        }
    }
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    
    for(int i=0;i<g.nodes.size();i++){ 
        for(int j=0;j<g.nodes[i].adjacent.size();j++){ 
            cout<<g.nodes[i].adjacent[j].x<<"-"<< g.nodes[i].adjacent[j].y <<"-"<< g.nodes[i].x<<"-"<< g.nodes[i].y;
            SDL_RenderDrawLine(renderer, g.nodes[i].adjacent[j].x, g.nodes[i].adjacent[j].y ,g.nodes[i].x,g.nodes[i].y);
           
        }
    }
    SDL_RenderPresent(renderer);
    
}
*/
