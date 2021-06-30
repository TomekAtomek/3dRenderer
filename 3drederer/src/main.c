#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"
#include "utils.h"

#define NBR_OF_POINTS 9 * 9 * 9

vec3_t cubePoints[NBR_OF_POINTS];
vec2_t projectedPoints[NBR_OF_POINTS];

vec3_t cameraPosition = {.x = 0, .y = 0, .z = -5};

FILE* logFile;

bool isRunning = false;

void setup(void){

	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);

	colorBufferTexture = SDL_CreateTexture(renderer, 
						 SDL_PIXELFORMAT_ARGB8888, 
						 SDL_TEXTUREACCESS_STREAMING, 
						 windowWidth, 
	                     windowHeight);

	//logFile = fopen("/home/tomek/3drederer/log.txt", "w+");


	int pointCount = 0;

	for(float x = -1; x <= 1; x +=0.25){

		for(float y = -1; y <= 1; y += 0.25){

			for(float z = -1; z <= 1; z += 0.25){

				vec3_t newPoint = {.x = x, .y = y, .z = z};
				cubePoints[pointCount++] = newPoint;

			}

		}

	}

}

vec2_t project2D(vec3_t vec3, vec2_t fovFactor){

  vec2_t vec2 = {.x = vec3.x * fovFactor.x, .y = vec3.y * fovFactor.y};

  return vec2;

}

vec2_t project3D(vec3_t vec3, vec2_t fovFactor){


   vec2_t vec2 = {.x = vec3.x * fovFactor.x, .y = vec3.y * fovFactor.y};

   vec2.x /= vec3.z;
   vec2.y /= vec3.z;

  return vec2;


}


void processInput(void){

	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){

		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
			break;
		default:
			break;
	}

}

void update(void){

	for(int i = 0; i < NBR_OF_POINTS; i++){

		vec2_t fovFactor = {.x = 640.0 , .y = 640.0};

		vec3_t cubePoint = cubePoints[i];

		cubePoint.z -= cameraPosition.z;

		vec2_t newPoint = project3D(cubePoint, fovFactor);

		projectedPoints[i] = newPoint;

	}

}





void render(void){

	clearColorBuffer(0xFF00FF00);
	//drawRect(500,500,100,100, 0xFFFFFFFF);
	//displayGrid(0xFF000000);
	
	//drawRect(150,50,200,200, 0xFF000066);

	for(int i = 0; i < NBR_OF_POINTS; i++){

		vec2_t projectedPoint = projectedPoints[i];

		drawRect(projectedPoint.x + (windowWidth / 2), 
				 projectedPoint.y + (windowHeight / 2), 
				 4,
				 4, 
				 0xFF0000FF);
		LOGINFO("Displaying point :  %f , %f \n", projectedPoint.x + (windowWidth / 2), projectedPoint.y + (windowHeight / 2));

	}

	renderColorBuffer();
	SDL_RenderPresent(renderer);

}




int main(int argc, char* argv[]){

    isRunning = initializeWindow();
	INIT_LOG
	setup();
	while(isRunning){
		LOGINFO("Start of frame...\n");
		LOGINFO("Start of frame...\n");
		LOGINFO("WindowWidth = %d, WindowHeight = %d\n", windowWidth, windowHeight);

		processInput();
		update();
		render();

		LOGINFO("End of frame...\n");
	}

	destroyWindow();
	CLOSE_LOG
	//fclose(logFile);

	return 0;
}
