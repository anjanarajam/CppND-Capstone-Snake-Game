#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
  //Anjana - File system
#include <fstream>
#include <sstream>
#include <string>

int main() {
  //Anjana - File system
  // Removed constant expressions and inputted from file 
  std::size_t MsPerFrame{};
  std::string line{}, word{};
  int frames_per_second{}, grid_height{}, grid_width{}, value{}, screen_width{}, screen_height{}; 
  std::ifstream input_file;
  std::ofstream file_output;  
  
  input_file.open("../input.txt");  
  file_output.open("../output.txt");
  
  // Loop until EOF and get lines 
  while(getline(input_file, line)) {
    std::stringstream ss{line};
    
    //Get the string and int value from a line
    ss >> word >> value;
    
    if (word == "FramesPerSecond") {
     	frames_per_second = value;
    } else if (word == "GridWidth") {
     	grid_width = value;
    } else if (word == "GridHeight") {
     	grid_height = value;
    } else if (word == "ScreenWidth") {
		screen_width = value;
    } else if (word == "ScreenHeight") {
		screen_height = value;
    }      
  }  

  Renderer renderer(screen_width, screen_height, grid_width, grid_height);
  Controller controller;
  MouseWheelController mouse_controller;  
  
  Game game(grid_width, grid_height);
  MsPerFrame = 1000 / frames_per_second;

  //Anjana - adding another controller for running another snake
  game.Run(controller, mouse_controller, renderer, MsPerFrame);
  
  //Anjana - File system
  //Output the results to the file
  file_output << "The result of the game is" << std::endl;
  file_output << "Score_Snake1: " << game.GetSnake1Score() << "\n";
  file_output << "Score_Snake2: " << game.GetSnake2Score() << "\n";
  file_output << "Size_Snake1: " << game.GetSnake1Size() << "\n";
  file_output << "Size_Snake2: " << game.GetSnake2Size() << "\n";    

  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score_Snake1: " << game.GetSnake1Score() << "\n";
  std::cout << "Score_Snake2: " << game.GetSnake2Score() << "\n";
  std::cout << "Size_Snake1: " << game.GetSnake1Size() << "\n";
  std::cout << "Size_Snake2: " << game.GetSnake2Size() << "\n";
  
  input_file.close();
  file_output.close();
  
  return 0;
}