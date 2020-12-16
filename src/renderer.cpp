#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(std::size_t screen_width,
                   std::size_t screen_height,
                   std::size_t grid_width, std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::shared_ptr<Snake> const snake1, std::shared_ptr<Snake> const snake2, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  //Anjana - Render snake's colourc for snake 1 and 2
  RenderSnakeColour(snake1, block);
  RenderSnakeColour(snake2, block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

// Anjana - separated function for snake colour
void Renderer::RenderSnakeColour(std::shared_ptr<Snake> const snake, SDL_Rect block) {
  // Render snake1's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  
  SDL_RenderFillRect(sdl_renderer, &block);
}

//Anjana - Added score for snake 2
void Renderer::UpdateWindowTitle(int score1, int score2, int fps) {
  std::string title{"Snake1 Score: " + std::to_string(score1) + " " + "Snake2 Score: " + std::to_string(score2) + " FPS: " +      std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

//Anjana - Function Overloading
void Renderer::UpdateWindowTitle(int score1, int score2) {
  std::string title{"Snake Score: " + std::to_string(score1) + " " + "Snake2 Score: " + std::to_string(score2) };
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

