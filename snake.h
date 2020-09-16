/******************************************************************************
*    File: snake.h
*   Class: COP 2001 202005
*  Author: B.Stafford
* Purpose: Header file for a Snake class for a snake game where the snake
* moves around the screen and grows when it eats food.
*******************************************************************************/
#ifndef SNAKE_H
#define SNAKE_H

#include "block.h"

class Snake
{
public:
    // ------------------------------------------------------------------------
    // constructors
    // ------------------------------------------------------------------------
    
    Snake(); // default constructor
    
    
    // ------------------------------------------------------------------------
    // accessors (getters and setters)
    // ------------------------------------------------------------------------
    Block* getHead();
    Block* getTail();
    int    getSize();
    float  getDistance();

    Direction getCurrent();
    Direction getNext();
    void      setNext(Direction value);

    
    // ------------------------------------------------------------------------
    // member methods
    // ------------------------------------------------------------------------
    bool isMoving();
    void turn();
    void move(float distance);
    bool hasMoved();
    void reset();
    bool hitSelf();
    bool hitBlock(Block* block, bool all = false);
    void grow();
    void draw(OpenGL& window);


private:
	Block head;           // root of snake
    Block* tail;          // tail of the snake
    int size;             // how large is the snake
    float distance;       // distance snake has traveled in this full frame
    Direction current;    // direction snake is moving in now
    Direction next;       // direction user wants to turn

};


#endif  // SNAKE_H