#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Controller const &mouse_controller, Renderer &renderer,
               std::size_t target_frame_duration);
  
  //Anjana- Adding extra score and sizes for the snake 1 and 2
  int GetSnake1Score() const;
  int GetSnake2Score() const;
  int GetSnake1Size() const;
  int GetSnake2Size() const;
  
 private:
  // Anjana - Turned the snake objects as shared pointer objects
  std::shared_ptr<Snake> snake1, snake2;
  SDL_Point food{};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  //Anjana- Adding two scores for the snakes
  int score_snake1{0}, score_snake2{0};

  void PlaceFood();
  void Update(std::shared_ptr<Snake> snake);
};

#endif