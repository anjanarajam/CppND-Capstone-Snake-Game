#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int head_pos_x, int head_pos_y, int id)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(head_pos_x),
        head_y(head_pos_y),
  		id_(id) {}

  void Update();

  void GrowBody();
  
  //Anjana - Added template for Snake Cell
  template <typename T>
  T SnakeCell(T x, T y)
  {
      if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
        return true;
      }
      for (auto const &item : body) {
        if (x == item.x && y == item.y) {
            return true;
         }
       }
    return false;
  }
    
  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x{};
  float head_y{};
  std::vector<SDL_Point> body{};
  // Anjana - creating snake id
  int id_{};

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width{};
  int grid_height{};  
};

#endif