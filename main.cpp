/*****************************************************************//**
 * \file   main.cpp
 * \brief  
 * 
 * \author aaron
 * \date   April 2023
 *********************************************************************/

#include <Windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>

#define REQUIRED_ARGC 5


int main(int argc, char** argv)
{
    double x1, y1, x2, y2;

    /* Parse arguments */
    try
    {
        if (argc != REQUIRED_ARGC)
        {
            throw "Incorrect argc";
        }

        x1 = std::stod(argv[1]);
        y1 = std::stod(argv[2]);
        x2 = std::stod(argv[3]);
        y2 = std::stod(argv[4]);
    }
    catch (...)
    {
        std::cout << "Usage: CG-Maman13.exe <x1> <y1> <x2> <y2>\n"
                     "Where <x1> <y1> <x2> <y2> are real numbers.\n"
                     "Example: CG-Maman13.exe -4.1 2 3.141 -8" << std::endl;
    }

    return 0;
}
