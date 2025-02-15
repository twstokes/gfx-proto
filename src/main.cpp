#include <VirtualDotMatrix.h>
#include <Adafruit_GFX.h>
#include <SDL.h>

#include <stdio.h>
#include <signal.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

struct LedCanvas *offscreen_canvas;

int matrixWidth, matrixHeight;

#define width 64
#define height 32
// scale factor for high resolution screens
#define scale 30

VirtualDotMatrix *matrix = new VirtualDotMatrix(width, height, true);

void delay(uint32_t d) {
    SDL_Delay(d);
}

void setup() {
    matrix->fillScreen(0);
}

void loop() {
    matrix->setCursor(0, 0);
    matrix->setTextColor(31 << 11);
    matrix->print("HELLO");
    delay(10);
}

void catch_int(int sig_num) {
    exit(0);
}

int main(int argc, char **argv) {
  signal(SIGINT, catch_int);

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      printf("Error starting SDL: %s\n", SDL_GetError());
  }

  window = SDL_CreateWindow("GFX Proto",
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          width * scale,
          height * scale,
          SDL_WINDOW_SHOWN);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_TARGET, width, height);

  SDL_Event event;
  setup();

  while(true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      break;
    }
    SDL_UpdateTexture(texture, NULL, matrix->buffer, width*sizeof(uint16_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    loop();
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}

