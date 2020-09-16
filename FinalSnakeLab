/******************************************************************************
*    File: snakemain.cpp
*   Class: COP 2001 202005
*  Author: B.Stafford
* Purpose: Main application file for the snake game (Lab 4)
*******************************************************************************/
#include <iostream>       // console i/o
#include <stdlib.h>       // random numbers
#include <time.h>         // seed random numbers

#include "opengl.h"       // graphics library
#include "snakedefs.h"    // game definitions
#include "block.h"        // game block objects
#include "snake.h"        // the snake object

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------

void InitGameObjects(Block borders[], Snake& snake, Block& food);
Direction processInput(OpenGL& window);
bool update(Snake& snake, Block borders[], Block& food, float deltaTime);
void render(OpenGL& window, Block borders[], Snake snake, Block food);
bool CollisionChecks(Snake snake, Block borders[]);
Block NextFood(Snake snake);

int main()
{
	// initiate random number sequences
	srand(time(NULL));

	// create our graphics window for drawing 
	OpenGL window = OpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str());

	// game objects
	Block borders[4];
	Snake snake = Snake();   // initialize with default constructor
	Block food;

	InitGameObjects(borders, snake, food);

	// fps timing
	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };

	// main game loop
	bool gameover = false;
	while (!gameover && !window.isClosing())
	{

		// calculate elapsed time
		float currentFrame = window.getTime();
		deltaTime += (currentFrame - lastFrame) * 1000;
		lastFrame = currentFrame;

		// get user input if not still waiting to process input
		if (snake.getNext() == None)
			snake.setNext(processInput(window));

		// set gameover if user chose to exit
		if (snake.getNext() == Exit)
			gameover = true;

		// update game state per frame
		while (!gameover && deltaTime >= FPS_RATE)
		{
			gameover = update(snake, borders, food, deltaTime);
			deltaTime -= FPS_RATE;
		}

		// draw objects
		render(window, borders, snake, food);

		window.pollEvents();
	} //  end game loop

	std::cout << "Game Over!!\nPress any key and enter to close..." << std::endl;
	char pause;
	std::cin >> pause;

	return 0; // echo %errorlevel%

} // end main


/******************************************************************************
initilalize game objects for game startup
parameters:
	borders     - border walls
	snake       - snake class object
	food        - set starting food
returns:
	void
*******************************************************************************/
void InitGameObjects(Block borders[], Snake& snake, Block& food)
{

	// initialize border walls
	borders[TopWall] = Block(MARGIN,
		                     MARGIN,
		                     WINDOW_WIDTH - 2 * MARGIN,
		                     BORDER_SIZE,
		                     BORDER_COLOR);

	borders[BottomWall] = Block(MARGIN,
							    WINDOW_HEIGHT - MARGIN - BORDER_SIZE,
							    WINDOW_WIDTH - 2 * MARGIN,
							    BORDER_SIZE,
							    BORDER_COLOR);
	//fix
	borders[LeftWall] = Block(MARGIN,
							  MARGIN,
							  BORDER_SIZE,
							  WINDOW_HEIGHT - 2 * MARGIN,
							  BORDER_COLOR);

	borders[RightWall] = Block(WINDOW_WIDTH - MARGIN - BORDER_SIZE,
							   MARGIN,
							   BORDER_SIZE,
							   WINDOW_HEIGHT - 2 * MARGIN,
							   BORDER_COLOR);
	// set starting food location
	food = NextFood(snake);

} // end InitGameObjects


/******************************************************************************
get user input to drive the snake
parameters:
	window      - graphics and I/O object
returns:
	Direction   - direction to turn snake, or None/Exit
*******************************************************************************/
Direction processInput(OpenGL& window)
{
	Direction dir = None;

	GL_KEY key = window.GetKey();

	switch (key) {
	case GL_KEY::KEY_ESC:
	case GL_KEY::KEY_X:
		dir = Direction::Exit;
		break;
		// (22)
	case GL_KEY::KEY_W:
	case GL_KEY::KEY_UP_ARROW:
		dir = Direction::Up;
		break;
		// (23)
	case GL_KEY::KEY_A:
	case GL_KEY::KEY_LEFT_ARROW:
		dir = Direction::Left;
		break;
	case GL_KEY::KEY_S:
	case GL_KEY::KEY_DOWN_ARROW:
		dir = Direction::Down;
		break;
	case GL_KEY::KEY_D:
	case GL_KEY::KEY_RIGHT_ARROW:
		dir = Direction::Right;
	}

	return dir;

} // end processInput


/******************************************************************************
update state of game objectsw
parameters:
	snake       - snake class object
	borders     - walls array
	food        - food block
	deltaTime   - accumulated frame time
returns:
	bool        - true if snake had a collision
*******************************************************************************/
bool update(Snake& snake, Block borders[], Block& food, float deltaTime)
{
	bool collision = false;     // state check for collisions

	// skip updates until snake begins to move
	if (!snake.isMoving())
	{ 
		if (snake.getNext() == None)
			return false;
		else
			// make first turn
			snake.turn();
	}

	// calculate distance this frame
	float distance = SNAKE_VELOCITY / deltaTime;
	snake.move(distance);

	// snaked has moved full block size
	if (snake.hasMoved())
	{
		snake.turn();

		snake.reset();

		// see if the snake ate food
		if (snake.hitBlock(&food))
		{

			snake.grow();

			// get a new food block
			food = NextFood(snake);

		}
		else
			collision = CollisionChecks(snake, borders);

	} // end full block transversal

	return collision;     // return collision/false
} // end update


/******************************************************************************
draws game objects to the graphics window
parameters:
	window      - handle to the graphics window
	border      - border walls for game window
	snake       - the snake structure
	food        -
returns:
	void
*******************************************************************************/
void render(OpenGL& window, Block borders[], Snake snake, Block food)
{

	// clear window memory buffer
	window.clearWindow();

	// draw the snake's head
	snake.draw(window);

	// draw the food
	food.draw(window);


	// draw the border
	borders[TopWall].draw(window);
	borders[BottomWall].draw(window);;
	borders[RightWall].draw(window);
	borders[LeftWall].draw(window);

	// repaint screen
	window.paintWindow();

} // end render



/******************************************************************************
check if snake hits walls or itself
parameters:
	snake        - snake structure
	borders      - array of walls
returns:
	bool         - true if snake hits something
*******************************************************************************/
bool CollisionChecks(Snake snake, Block borders[])
{
	bool collide = false;

	// see if snake hit top wall
	if (snake.getCurrent() == Up && snake.hitBlock(&borders[TopWall]))
		collide = true;

	// see if snake hit bottom wall
	else if (snake.getCurrent() == Down && snake.hitBlock(&borders[BottomWall]))
		collide = true;

	// see if snake hit left wall
	else if (snake.getCurrent() == Left && snake.hitBlock(&borders[LeftWall]))
		collide = true;

	// see if snake hit right wall
	else if (snake.getCurrent() == Right && snake.hitBlock(&borders[RightWall]))
		collide = true;

	// see if snake hit itself
	else
	{
		collide = snake.hitSelf();
	}


	return collide;
}




/******************************************************************************
set location of food
parameters:
	snake       - snake- make sure we dont place on top of the snake
returns:
	block       - new location of food
*******************************************************************************/
Block NextFood(Snake snake) {
	Block food = Block( 0, 0, BLOCK_SIZE, BLOCK_SIZE, FOOD_COLOR );

	bool placed = false;
	while (!placed)
	{
		// get random location for food
		int xCoord = rand() % (GAME_WIDTH - BLOCK_SIZE); // random columns
		int yCoord = rand() % (GAME_HEIGHT - BLOCK_SIZE); // random rows

		// move coordinates into visible screen
		xCoord += MARGIN + BORDER_SIZE;
		yCoord += MARGIN + BORDER_SIZE;

		food.setX(xCoord);
		food.setY(yCoord);

		placed = !snake.hitBlock(&food, true);

	}  // while not placed



	return food;
}
