/*****************************************************************//**
 * \file   CohenSutherland.h
 * \brief  TODO: Add description
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
    void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
    {
        GLubyte code1, code2;
        GLboolean done = false, plotLine = true;
        GLfloat m;

        while (!done)
        {
            code1 = encode(p1, winMin, winMax);
            code2 = encode(p2, winMin, winMax);
            if (accept(code1, code2))
            {
                done = true;
                plotLine = true;
            }
            else
            {
                if (reject(code1, code2))
                {
                    done = true;
                }
                else
                {
                    /* Label the endpoint outside the display window as p1. */
                    if (inside(code1))
                    {
                        swap(&p1, &p2);
                        swap(&code1, &code2);
                    }
                    /* Use slope m to find line-clipEdge intersection. */
                    if (p2.x != p1.x)
                    {
                        m = (p2.y - p1.y) / (p2.x - p1.x);
                    }
                    if (code1 & winLeftBitCode)
                    {
                        p1.y += (winMin.x - p1.x) * m;
                        p1.x = winMin.x;
                    }
                    else if (code1 & winRightBitCode)
                    {
                        p1.y += (winMax.x - p1.x) * m;
                        p1.x = winMax.x;
                    }
                    else if (code1 & winBottomBitCode)
                    {
                        /* Need to update p1.x for nonvertical lines only. */
                        if (p2.x != p1.x)
                        {
                            p1.x += (winMin.y - p1.y) / m;
                        }
                        p1.y = winMin.y;
                    }
                    else if (code1 & winTopBitCode)
                    {
                        if (p2.x != p1.x)
                        {
                            p1.x += (winMax.y - p1.y) / m;
                        }
                        p1.y = winMax.y;
                    }
                }
            }
        }

    }
}

