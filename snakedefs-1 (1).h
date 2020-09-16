/******************************************************************************
*    File: snakedefs.h
*   Class: COP 2001 202005
*  Author: B.Stafford
* Purpose: Definitions header file for the Snake Game (Lab 4)
*******************************************************************************/

#ifndef SNAKE_DEF_H
#define SNAKE_DEF_H

#include <string>

//-----------------------------------------------------------------------------
// Global space- constants, functions, data structures, etc.
//-----------------------------------------------------------------------------

// games frames-per-second rate (FPS) in milliseconds
const float FPS_RATE = 1000 / 60.0f; // 16.66667


// game area boundary
const int GAME_WIDTH{ 400 };
const int GAME_HEIGHT{ 200 };

// game object sizes
const int MARGIN{ 10 };
const int BORDER_SIZE{ 2 };
const int BLOCK_SIZE{ 10 };

// block array index for head of the snake in the body array
const int SNAKE_HEAD{ 0 };

// snakes speed across the screen
const float SNAKE_VELOCITY{ BLOCK_SIZE * 5 };


const int WINDOW_WIDTH{ GAME_WIDTH + 2 * MARGIN + 2 * BORDER_SIZE };
const int WINDOW_HEIGHT{ GAME_HEIGHT + 2 * MARGIN + 2 * BORDER_SIZE };
const std::string WINDOW_TITLE = "Snake Game";



enum Color
{
    White = 0xFFFFFF00,
    Silver = 0xC0C0C000,
    Gray = 0x80808000,
    Black = 0x00000000,
    Red = 0xFF000000,
    Maroon = 0x80000000,
    Yellow = 0xFFFF0000,
    Olive = 0x80800000,
    Lime = 0x00FF0000,
    Green = 0x00800000,
    Aqua = 0x00FFFF00,
    Teal = 0x00808000,
    Blue = 0x0000FF00,
    Navy = 0x00008000,
    Fuchsia = 0xFF00FF00,
    Purple = 0x80008000
};

const Color BORDER_COLOR{ Fuchsia };
const Color SNAKE_COLOR{ Purple };
const Color FOOD_COLOR{ Aqua };




// array indexes for the border walls
enum Border
{
    TopWall,
    BottomWall,
    LeftWall,
    RightWall,
};

enum Direction
{
    Exit = -1,
    None,
    Up,
    Down,
    Left,
    Right,
};



#endif // SNAKE_DEF_H