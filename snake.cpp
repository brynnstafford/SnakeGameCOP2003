/******************************************************************************
*    File: snake.cpp
*   Class: COP 2001 202005
*  Author: B.Stafford
* Purpose: Implementation file for a Snake class for a snake game where the 
* snake moves around the screen and grows when it eats food.
*******************************************************************************/
#include "snake.h"

// ------------------------------------------------------------------------
// constructors
// ------------------------------------------------------------------------
/******************************************************************************
defalut constructor
*******************************************************************************/
Snake::Snake()
{
	// initialize the snake with 1 body block for the head
	head = Block( WINDOW_WIDTH / 2 - BLOCK_SIZE / 2,
				  WINDOW_HEIGHT / 2 - BLOCK_SIZE / 2,
				  BLOCK_SIZE,
				  BLOCK_SIZE,
				  SNAKE_COLOR);
	tail = &head;

	size = 1;
	current = None;
	next = None;
	distance = 0;
} 


// ------------------------------------------------------------------------
// accessors (getters and setters)
// ------------------------------------------------------------------------
Block* Snake::getHead() { return &head; }
Block* Snake::getTail() { return tail; }
int    Snake::getSize() { return size; }
float  Snake::getDistance() { return distance; }

Direction Snake::getCurrent() { return current; }
Direction Snake::getNext() { return next; }
void      Snake::setNext(Direction value) { next = value; }


// ------------------------------------------------------------------------
// member methods
// ------------------------------------------------------------------------

/******************************************************************************
determine if the snake is moving
parameters:
returns:
	bool        - true if block is moving
*******************************************************************************/
bool Snake::isMoving()
{
	// truncate floats to integer for comparison
	return head.isMoving();
}

/******************************************************************************
turn the snake based on user input direction
parameters:
returns:
	void
*******************************************************************************/
void Snake::turn()
{
	// adjust thead of the snake's velocities
	switch (next)
	{
	case Up:
		if (current != Down)
		{
			head.setVelocityX(0);
			head.setVelocityY(-1);
			current = next;
		}
		break;
	case Left:
		if (current != Right)
		{
			head.setVelocityX(-1);
			head.setVelocityY(0);
			current = next;
		}
		break;
	case Down:
		if (current != Up)
		{
			head.setVelocityX(0);
			head.setVelocityY(1);
			current = next;
		}
		break;
	case Right:
		if (current != Left)
		{
			head.setVelocityX(1);
			head.setVelocityY(0);
			current = next;
		}
	} // end direction switch

	// wait for next user input
	next = None;

}  // end turn


/******************************************************************************
move the snake a set distance
parameters:
    distance     - disntance in pixels to move the snake
returns:
	void
*******************************************************************************/
void Snake::move(float distance)
{
	// limit the distance to full blocks only
	if (this->distance + distance > BLOCK_SIZE)
		distance = BLOCK_SIZE - this->distance;

	// set snakes total distance moved
	this->distance += distance;

	Block* part = &head;
	while(part)
	{ 
		// move the block
		part->move(distance);

		// move pointer to block after this one
		part = part->getAfter();
	}

} // end move



/******************************************************************************
the snake has traveled a full block size
parameters:
returns:
	bool        - true if moved full block size
*******************************************************************************/
bool Snake::hasMoved()
{
	return distance >= BLOCK_SIZE;
}



/******************************************************************************
reset snakes distance and align snake directions and alignment
parameters:
returns:
	bool        - true if moved full block size
*******************************************************************************/
void Snake::reset()
{
	distance = 0;    // reset full travel property

	Block* part = tail;

	// loop from tail to head to adjest velocities
	while ( part->getBefore() )
	{
		// copy x-velocity of block in front of this one
		part->setVelocityX( part->getBefore()->getVelocityX() );

		// align the vertical tops for this block
		if ( part->getVelocityX() )    // true=!0 or false=0
			part->setY( part->getBefore()->getY() );

		// copy y-velocty of block in front of this one
		part->setVelocityY( part->getBefore()->getVelocityY() );

		// align the horizontal left sides for this block
		if ( part->getVelocityY() )
			part->setX( part->getBefore()->getX() );

		part = part->getBefore();

	} // adjust velocities

}  // end reset



/******************************************************************************
check to see if head of the snake hit the body
parameters:
returns:
	bool        - true if collision
*******************************************************************************/
bool Snake::hitSelf()
{
	bool collide = false;

	Block* part = head.getAfter();
	int skip = 3;
	while (part && !collide)
	{
		// skip the first 3 blocks after the head
		if (skip)
			skip--;
		else
			// check the head with the current part
			collide = head.intersects(part);

		// move to the next part
		part = part->getAfter();
	}


	return collide;
} // end hitSelf



/******************************************************************************
check to see if a block overlaps the head of the snake or the whole snake
parameters:
    block       - pointer to block to check
	all         - false = just the head, true = whole snake (default to false)
returns:
	bool        - true if collision
*******************************************************************************/
bool Snake::hitBlock(Block* block, bool all)
{
	bool collide = head.intersects(block);

	// do we need to check rest of body
	if (all && !collide)
	{
		Block* part = head.getAfter();;
		while (part && !collide)
		{
			// check the block with the current part
			collide = block->intersects(part);

			// move to the next part
			part = part->getAfter();
		}

	}
	return collide;
} // end hitBlock



/******************************************************************************
add a new tail onto the end of the snake
parameters:
returns:
	void       
*******************************************************************************/
void Snake::grow()
{
	// save off the current tail location
	tail->append(tail);

	tail = tail->getAfter();

	// move the new tail one block in opposite direction the tail is moving
	tail->setX(tail->getX() + tail->getVelocityX() * -1 * BLOCK_SIZE);
	tail->setY(tail->getY() + tail->getVelocityY() * -1 * BLOCK_SIZE);

	// add the new tail onto the snake and increase the snake's size
	size++;

} // end grow



/******************************************************************************
render the snake's body on the graphics window
parameters:
	window      - handle to graphics window
returns:
	void
*******************************************************************************/
void Snake::draw(OpenGL& window)
{
	Block* part = &head;
	while (part)
	{
		// move the block
		part->draw(window);

		// move pointer to block after this one
		part = part->getAfter();
	}
} // end draw