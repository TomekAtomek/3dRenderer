#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* colorBuffer;
extern SDL_Texture* colorBufferTexture;
extern int windowWidth;
extern int windowHeight;

bool initializeWindow(void);
void renderColorBuffer(void);
void displayGrid(uint32_t color);
void drawPixel(int x, int y, uint32_t color);
void drawRect(int x, int y, int width, int height, uint32_t color);
void clearColorBuffer(uint32_t color);
void destroyWindow();


#endif