#ifndef PAINT_GRAPH_H
#define PAINT_GRAPH_H
#include "colors.h"

/**
 * The width of the graph
 * \note only odd
*/
#define SizeX 153

/**
 * The height of the graph
 * \note only odd
*/
#define SizeY 43

/**
 * The step at which numbers are placed on the y-axis
 * \note only positive integer
 */
#define xStep 10

/**
 * The step at which numbers are placed on the x-axis
 * \note only positive integer
 */
#define yStep 5


/**
 * \enum GraphLines
 * 
 * \brief Symbols that make up graph
 */
enum GraphLines{
    GRAPH_SPACE = ' ',
    GRAPH_ORDIN = '|',
    GRAPH_ABSC = '-',
    GRAPH_ORDIN_VECTOR = '^',
    GRAPH_ABSC_VECTOR = '>',
    GRAPH_NULL = '0',
    GRAPH_ONE = '1',
    GRAPH_TWO = '2',
    GRAPH_THREE = '3', 
    GRAPH_FOUR = '4',
    GRAPH_FIVE = '5',
    GRAPH_SIX = '6',
    GRAPH_SEVEN = '7',
    GRAPH_EIGHT = '8', 
    GRAPH_NINE = '9',
    GRAPH_MINUS = '-',
    GRAPH_NAME_Y = 'y',
    GRAPH_NAME_X = 'x',
    GRAPH_ZERO_SLANT = '=',
    GRAPH_INF_SLANT = '|',
    GRAPH_POSITIVE_SLANT = '/',
    GRAPH_NEGATIVE_SLANT = '\\',
    GRAPH_POINT = '.',
    GRAPH_STAR = '*',
};


/**
 * \struct GraphPixel
 * 
 * \brief Information about one cell of the graph matrix
 */
struct GraphPixel{
    enum GraphLines symbol = GRAPH_SPACE;
    char color[8] = {0};
};


/**
 * \brief Print symbols from one graph line
 * 
 * \param[in, out] line one line of graph matrix
 */
void Paint_One_Row_Of_Graph(GraphPixel* line);


/**
 * \brief Fill the graph matrix with symbols of axes and scale lines
 * 
 * (GRAPH_ORDIN, GRAPH_ABSC, GRAPH_ORDIN_VECTOR, GRAPH_ABSC_VECTOR, GRAPH_NAME_Y, GRAPH_NAME_X, GRAPH_POINT)
 * Scale lines are marked with a step of yStep (on y-axis) and xStep (on x-axis)
 * 
 * \param[in, out] matr graph matrix
 */
void Define_Graph_Axes(GraphPixel matr[][SizeX]);


/**
 * \brief Fill in the graph, movig along the y-axis
 * 
 * For every value of y solve the quadratic equation a*x^2 + b*x + c = y,\n
 * rounds the roots of the equation and write to the cells with the corresponding coordinates
 * 
 * \param[in, out] matr graph matrix
 * \param[in] a the coefficient of quadratic equation for x^2
 * \param[in] b the coefficient of quadratic equation for x
 * \param[in] c the free coefficient of quadratic equation
 */
void Define_Graph_By_Y(GraphPixel matr[][SizeX], double a, double b, double c);


/**
 * \brief Fill in the graph, movig along the x-axis
 * 
 * For every value of x substitute it into the quadratic equation and get y,\n
 * rounds the roots of the equation and write to the cells with the corresponding coordinates
 * 
 * \param[in, out] matr graph matrix
 * \param[in] a the coefficient of quadratic equation for x^2
 * \param[in] b the coefficient of quadratic equation for x
 * \param[in] c the free coefficient of quadratic equation
 */
void Define_Graph_By_X(GraphPixel matr[][SizeX], double a, double b, double c);


/**
 * \brief Define slant of graph in specific point
 * 
 * Count the derivative in specific x
 * 
 * \param[in] a the coefficient of quadratic equation for x^2
 * \param[in] b the coefficient of quadratic equation for x
 * \param[in] x the coordinate on x-axis
 * 
 * \return GRAPH_INF_SLANT or GRAPH_POSITIVE_SLANT or GRAPH_ZERO_SLANT or GRAPH_NEGATIVE_SLANT based on the value of the derivative
 */
GraphLines Define_Graph_Line_Slant(double, double, int);


/**
 * \brief Paint graph of the quadratic equation
 * 
 * at first it fill axes\n
 * then define graph with x and y\n
 * finally it graduate axes and point null
 * 
 */
void Paint_Graph(double ,double, double);


/**
 * \brief Print one symbol of certain color defined in the struct GraphPixel
 * 
 * \param[in] pixel on cell in graph matrix
 */
void Print_GraphPixel(GraphPixel pixel);


/**
 * \brief Fill one column of graph matrix with specified symbols
 * 
 * \param[in, out] matr graph matrix
 * \param[in] col the coordinate in graph matrix
 * \param[in] pixel the symbol to fil the column
 */
void Define_One_X_Line(GraphPixel matr[][SizeX], int col, GraphPixel pixel);


/**
 * \brief Fill one row of graph matrix with specified symbols
 * 
 * \param[in, out] matr graph matrix
 * \param[in] row the coordinate in graph matrix
 * \param[in] pixel the symbol to fil the row
 */
void Define_One_Y_Line(GraphPixel matr[][SizeX], int row, GraphPixel pixel);


/**
 * \brief Graduate the y-axis with numbers with a step yStep
 * 
 * \param[in, out] matr graph matrix
 */
void Graduate_Y(GraphPixel matr[][SizeX]);


/**
 * \brief Print one number on y-axis
 * 
 * The number is located to the left of the x-axis and cetered
 * 
 * \param[in, out] matr graph matrix
 * \param[in] y the coordinate to print
 */
void Define_One_Y_Value(GraphPixel matr[][SizeX], int y);


/**
 * \brief Graduate the x-axis with numbers with a step xStep
 * 
 * \param[in, out] matr graph matrix
 */
void Graduate_X(GraphPixel matr[][SizeX]);


/**
 * \brief Print one number on x-axis
 * 
 * The number is located ander the x-axis and cetered to its coordinate
 * 
 * \param[in, out] matr graph matrix
 * \param[in] x the coordinate to print
 */
void Define_One_X_Value(GraphPixel matr[][SizeX], int x);


#endif