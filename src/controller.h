#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
public:
    //Anjana..
    //Making this function virtual
    virtual void HandleInput(bool& running, Snake& snake) const;

    //private:
protected:
    void ChangeDirection(Snake& snake, Snake::Direction input,
        Snake::Direction opposite) const;
};


//Anjana.. Adding child class to controller
class MouseWheelController : public Controller {
    void HandleInput(bool& running, Snake& snake) const override;
};
#endif