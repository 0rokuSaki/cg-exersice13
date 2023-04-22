/*****************************************************************//**
 * \file   main.cpp
 * \brief  My solution for Q4 in exersice ('Maman') 13 in Computer Graphics (20562) course.
 *
 * TODO: Add description
 *
 * Repo link: https://github.com/0rokuSaki/cg-exersice13
 *
 * *** BUILD INSTRUCTIONS (VS2019/VS2022 Windows 10/11) ***
 * 1. Setup OpenGL: https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/.
 * 2. Select x86 Debug configuration.
 * 3. Build the solution (ctrl + shift + B).
 * 
 * \author aaron
 * \date   April 2023
 *********************************************************************/

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

#include "CohenSutherland.h"
#include "Constants.h"


/* Line edges */
wcPt2D p1, p2;


 /* Creates and initializes GLUT display-window. */
void createWindow(int argc, char** argv)
{
    /* Create the window */
    glutInit(&argc, argv);                        // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowPosition(WINDOW_INIT_POS);      // Set top-left window position
    glutInitWindowSize(WINDOW_INIT_SIZE);         // Set window width and height
    glutCreateWindow(WINDOW_TITLE);               // Create window

    /* Initialize the window */
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // Set window color to white
}


/* Create a black clipping window with clipping region borders */
void displayClippingWindow(void)
{
    glColor3d(BLACK);

    /* Create rectangle frame */
    glLineWidth(LINE_WIDTH_THICK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectd(CLIP_WIN_MIN_COORD, CLIP_WIN_MAX_COORD);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* Create dotted region lines */
    glLineWidth(LINE_WIDTH_THIN);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, LINE_DASH_PATTERN);
    glBegin(GL_LINES);  // Left border
        glVertex2d(L_BORDER_LINE_COORD1);
        glVertex2d(L_BORDER_LINE_COORD2);
    glEnd();
    glBegin(GL_LINES);  // Right border
        glVertex2d(R_BORDER_LINE_COORD1);
        glVertex2d(R_BORDER_LINE_COORD2);
    glEnd();
    glBegin(GL_LINES);  // Top border
        glVertex2d(T_BORDER_LINE_COORD1);
        glVertex2d(T_BORDER_LINE_COORD2);
    glEnd();
    glBegin(GL_LINES);  // Bottom border
        glVertex2d(B_BORDER_LINE_COORD1);
        glVertex2d(B_BORDER_LINE_COORD2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glFlush();
}


/* Display a line with specified width and color */
void displayLine(const wcPt2D& p1, const wcPt2D& p2, float lineWidth, double r, double g, double b)
{
    glLineWidth(lineWidth);
    glColor3d(r, g, b);
    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}


/**
 * Callback for 'glutDisplayFunc'.
 * Sets display properties once.
 */
void displayCallback(void)
{
    static bool setDisplay = true;
    if (setDisplay)
    {
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(WORLD_COORD);

        setDisplay = false;
    }
}


/**
 * Callback for 'glutIdleFunc'.
 * Animates Cohen-Sutherland algorithem.
 */
void idleCallback(void)
{
    using namespace CohenSutherland;
    static std::chrono::milliseconds duration(SLEEP_DURATION_MS);
    static GLubyte code1, code2;
    static GLboolean done = false, plotLine = true;
    static wcPt2D winMin(CLIP_WIN_MIN_COORD);
    static wcPt2D winMax(CLIP_WIN_MAX_COORD);
    static GLfloat m;

    displayCallback(); // Set display properties once

    if (!done)
    {
        /* Display clipped line segment */
        glClear(GL_COLOR_BUFFER_BIT);
        displayLine(p1, p2, LINE_WIDTH_THICK, BLUE);
        displayClippingWindow();

        std::this_thread::sleep_for(duration);

        /* Perform one algorithm iteration */
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
                glClear(GL_COLOR_BUFFER_BIT);
                displayClippingWindow();
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

                /* Save p1 to display clipped section later */
                wcPt2D prev = p1;

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

                /* Display the clipped section */
                displayLine(prev, p1, LINE_WIDTH_THICK, RED);

                std::this_thread::sleep_for(duration);
            }
        }
    }
}


/* Assigns callback functions for events */
void registerCallbacks(void)
{
    glutIdleFunc(idleCallback);
    glutDisplayFunc(displayCallback);
}


int main(int argc, char** argv)
{
    /* Parse arguments */
    try
    {
        if (argc != REQUIRED_ARGC)
        {
            throw std::exception();
        }

        p1.x = std::stod(argv[1]);
        p1.y = std::stod(argv[2]);
        p2.x = std::stod(argv[3]);
        p2.y = std::stod(argv[4]);

        /* Initialize OpenGL */
        createWindow(argc, argv);  // Create the display-window
        registerCallbacks();       // Assign callback functions for events
        glutMainLoop();            // Display everything and wait
    }
    catch (...)
    {
        std::cout << "Usage: CG-Maman13.exe <x1> <y1> <x2> <y2>\n"
                     "Where <x1> <y1> <x2> <y2> are real numbers.\n"
                     "Example: CG-Maman13.exe -4.1 2 3.141 -8" << std::endl;
    }

    return 0;
}
