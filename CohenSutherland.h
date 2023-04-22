/*****************************************************************//**
 * \file   CohenSutherland.h
 * \brief  Functions for Cohen-Sutherland algorithm.
 * 
 * Algorithm and functions are based on the implementation of Cohen-Sutherland
 * in the book
 * 'Computer Graphics with OpenGL 4th edition by Donald Hearn and Pauline Baker'
 * 
 * \author aaron
 * \date   April 2023
 *********************************************************************/

#pragma once

#include <Windows.h>
#include <GL/glut.h>


/* World coordinate 2D point */
class wcPt2D
{
public:
    GLfloat x, y;

    wcPt2D() : x(0.0f), y(0.0f) {}

    wcPt2D(const GLfloat x, const GLfloat y)
    {
        this->x = x;
        this->y = y;
    }
};


/* Functions and variables for Cohen-Sutherland algorithm */
namespace CohenSutherland
{
    /* ### Variables ### */

    /* Region bit codes */
    const GLint winLeftBitCode = 0x1;
    const GLint winRightBitCode = 0x2;
    const GLint winBottomBitCode = 0x4;
    const GLint winTopBitCode = 0x8;

    /* ### Functions ### */

    /* Swaps two objects */
    template<typename T>
    inline void swap(T* t1, T* t2) { T temp; temp = *t1; *t1 = *t2; *t2 = temp; }

    /* Rounds a float to nearest integer */
    inline GLint round(const GLfloat a) { return (GLint)(a + 0.5f); }

    /* Checks if code is inside clipping window */
    inline GLboolean inside(const GLubyte code) { return (GLboolean)(!code); }

    /* Checks if line can be rejected */
    inline GLboolean reject(const GLubyte code1, const GLubyte code2) { return (GLboolean)(code1 & code2); }

    /* Checks if line can be accepted */
    inline GLboolean accept(const GLubyte code1, const GLubyte code2) { return (GLboolean)(!(code1 | code2)); }

    GLubyte encode(const wcPt2D& pt, const wcPt2D& winMin, const wcPt2D& winMax)
    {
        GLubyte code = 0x00;

        if (pt.x < winMin.x)
        {
            code = code | winLeftBitCode;
        }
        if (pt.x > winMax.x)
        {
            code = code | winRightBitCode;
        }
        if (pt.y < winMin.y)
        {
            code = code | winBottomBitCode;
        }
        if (pt.y > winMax.y)
        {
            code = code | winTopBitCode;
        }

        return code;
    }
}
