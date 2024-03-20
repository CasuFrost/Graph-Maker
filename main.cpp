#include "src/drawing.h"


#define WIDTH 800
#define HEIGHT 600

using namespace std;

int main( int argc, char *argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);


    SDL_Window *window = SDL_CreateWindow("Graph Maker", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, WIDTH,HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    
    drawStar(renderer,10,10,10);
    SDL_RenderPresent(renderer);
    //SDL_Delay(2000);
    SDL_Quit();

    //COSE SUL GRAFO
    
    Graph g;



    


    g.showGraphInformation();
    
    

    return 0;
}