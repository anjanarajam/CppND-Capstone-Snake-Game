#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>

class Controller {
 public:
  //Anjana..
  //Making this function virtual
  virtual void HandleInput(bool &running, std::shared_ptr<Snake> snake) const;

 //private:
 protected:
   void ChangeDirection(std::shared_ptr<Snake> snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};


//Anjana.. Adding child class to controller
class MouseWheelController : public Controller {
public:
  void HandleInput(bool &running, std::shared_ptr<Snake> snake) const override;  
};
#endif