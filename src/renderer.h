#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>

class Renderer {
 public:
  Renderer(std::size_t screen_width, std::size_t screen_height,
           std::size_t grid_width, std::size_t grid_height);
  ~Renderer();

  void Render(std::shared_ptr<Snake> const snake1, std::shared_ptr<Snake> const snake2, SDL_Point const &food);
  void UpdateWindowTitle(int score1, int score2, int fps);
  //Anjana - Function Overloading
  void UpdateWindowTitle(int score1, int score2);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
  
  void RenderSnakeColour(std::shared_ptr<Snake> const snake, SDL_Rect block);
};

#endif