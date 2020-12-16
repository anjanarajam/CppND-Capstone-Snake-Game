#include "game.h"
#include <iostream>
#include "SDL.h"
#include <functional>
#include <thread>
#include <future>
#include <mutex>

//Anjana - mutex
std::mutex mtx;

Game::Game(std::size_t grid_width, std::size_t grid_height) :
  engine(dev()),
  random_w(0, static_cast<int>(grid_width)),
  random_h(0, static_cast<int>(grid_height)) {
          
    // Anjana - creating two snake objects
    snake1 = std::make_shared<Snake> (grid_width, grid_height, grid_width / 2, grid_height / 2, 1);
    snake2 = std::make_shared<Snake> (grid_width, grid_height, grid_width / 4, grid_height / 4, 2);

    PlaceFood();
}

void Game::Run(Controller const &controller, Controller const &mouse_controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake1);
    mouse_controller.HandleInput(running, snake2);
    
	//Anjana- creating two threads of update function for snake1 and snake2
    std::future<void> ftr1 = std::async(std::launch::async, std::bind(&Game::Update, this, snake1));
    std::future<void> ftr2 = std::async(std::launch::async, std::bind(&Game::Update, this, snake2));
    
    // Anjana 
    renderer.Render(snake1, snake2, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score_snake1, score_snake2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    
    ftr1.wait();
    ftr2.wait();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake1->SnakeCell(x, y) || !snake2->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}



void Game::Update(std::shared_ptr<Snake> snake) {  
  
  if (!snake->alive) return;

  snake->Update();

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Anjana - adding mutex to avoid both snakes eating food at the same time
  std::lock_guard<std::mutex> lock(mtx);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    if (snake->id_ == 1) {
    	score_snake1++;
    } else if (snake->id_ == 2) {
      	score_snake2++;
    }
    
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02;
  }
}
 //Anjana- separate scores and size for snake 1 and snake 2
int Game::GetSnake1Score() const { return score_snake1; }
int Game::GetSnake2Score() const { return score_snake2; }
int Game::GetSnake1Size() const { return snake1->size; }
int Game::GetSnake2Size() const { return snake2->size; }