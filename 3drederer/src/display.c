#include "display.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* colorBuffer = NULL;
SDL_Texture* colorBufferTexture = NULL;
int windowWidth = 800;
int windowHeight = 600;

bool initializeWindow(void){

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL\n");
		return false;
	}

	SDL_DisplayMode displayMode;

	SDL_GetCurrentDisplayMode(0, &displayMode);

	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	window = SDL_CreateWindow(
			NULL,
		    SDL_WINDOWPOS_CENTERED,	
		    SDL_WINDOWPOS_CENTERED,
			windowWidth,
			windowHeight,
			SDL_WINDOW_BORDERLESS);

	if(!window){
		fprintf(stderr, "Could not create window");
		return false;
	}	


	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer){

		fprintf(stderr, "Could not create renderer");
		return false;

	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void renderColorBuffer(void){

	SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer, (int)windowWidth * sizeof(uint32_t));
	SDL_RenderCopy(renderer,colorBufferTexture, NULL, NULL);
}

void displayGrid(uint32_t color){

	for (int y = 0; y < windowHeight; ++y){

		for (int x = 0; x < windowWidth; ++x){

			//int currentPos = y * windowWidth + x;

			if(x % 30 == 0 || y % 30 == 0){

				drawPixel(x,y,color);

			}

		}

	}


}

void clearColorBuffer(uint32_t color){

	for(int y = 0; y < windowHeight; ++y){

		for(int x = 0; x < windowWidth; ++x){

			colorBuffer[(windowWidth * y) + x] = color;

		}
}

}

void destroyWindow(){

  	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}


void drawPixel(int x, int y, uint32_t color){

	if(x < windowWidth && x >= 0 && y < windowHeight && y >= 0 ){

	  colorBuffer[(y * windowWidth) + x] = color;

	}

}

void drawRect(int x, int y, int width, int height, uint32_t color){


	for (int i = y; i < y + height; ++i){

		for(int j = x; j < x + width; ++j){

			drawPixel(j,i,color);

		}


	}

}