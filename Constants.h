/*****************************************************************//**
 * \file   Constants.h
 * \brief  TODO: Add description
 * 
 * \author aaron
 * \date   April 2023
 *********************************************************************/

#pragma once

/* General constants */
#define REQUIRED_ARGC 5                 // Number of required command line arguments

/* Window constants */
#define WINDOW_INIT_POS  100, 100       // Initial window position
#define WINDOW_INIT_SIZE 640, 480       // Initial window size (width, height)
#define WINDOW_TITLE     "CG Maman 13"  // Window title

/* Display constants */
#define WORLD_COORD       0.0, 100.0, 0.0, 100.0  // World coordinates values

/* Animation constants */
#define SLEEP_DURATION_MS 750

/* Clipping window and region constants */
#define CLIP_WIN_MIN_COORD   30.0, 30.0
#define CLIP_WIN_MAX_COORD   70.0, 70.0
#define L_BORDER_LINE_COORD1 30.0, 0.0
#define L_BORDER_LINE_COORD2 30.0, 100.0
#define R_BORDER_LINE_COORD1 70.0, 0.0
#define R_BORDER_LINE_COORD2 70.0, 100.0
#define T_BORDER_LINE_COORD1 0.0, 70.0
#define T_BORDER_LINE_COORD2 100.0, 70.0
#define B_BORDER_LINE_COORD1 0.0, 30.0
#define B_BORDER_LINE_COORD2 100.0, 30.0

/* Line constants */
#define LINE_WIDTH_THICK  7.0f
#define LINE_WIDTH_THIN   2.0f
#define LINE_DASH_PATTERN 0x0F0F

/* Colors */
#define BLACK 0.0, 0.0, 0.0
#define RED   1.0, 0.0, 0.0
#define GREEN 0.0, 1.0, 0.0
#define BLUE  0.0, 0.0, 1.0