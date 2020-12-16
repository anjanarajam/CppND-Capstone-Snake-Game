#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(std::shared_ptr<Snake> snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->size == 1) snake->direction = input;
  return;
}

void Controller::HandleInput(bool &running, std::shared_ptr<Snake> snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
      std::cout << "not running" << std::endl;
    } else if (e.type == SDL_KEYDOWN) {
      
      std::cout << "running......" << std::endl;
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}

// Anjana.. Handling virtual function by adding child class 
void MouseWheelController::HandleInput(bool &running, std::shared_ptr<Snake> snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEWHEEL) {
        // scroll up
        if(e.wheel.y > 0) 
        {
           ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
        }
        // scroll down
        else if(e.wheel.y < 0) 
        {
           ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
        }
		// scroll right
        if(e.wheel.x > 0) 
        {
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
        }
      	// scroll left
        else if(e.wheel.x < 0) 
        {
            ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
        }      
     }
  }
}