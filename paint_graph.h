#ifndef PAINT_GRAPH_H
#define PAINT_GRAPH_H
#include "colors.h"

#define SizeX 153 /*только нечетный*/
#define SizeY 43 /*только нечетный*/
#define xStep 10
#define yStep 5


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
    GRAPH_ZERO_SLANT = '-',
    GRAPH_INF_SLANT = '|',
    GRAPH_POSITIVE_SLANT = '/',
    GRAPH_NEGATIVE_SLANT = '\\',
    GRAPH_POINT = '.',
    GRAPH_STAR = '*',
};


struct GraphPixel{
    enum GraphLines symbol = GRAPH_SPACE;
    char color[8] = {0};
};


void Paint_One_Row_Of_Graph(GraphPixel*);
void Define_Graph_Axes(GraphPixel [][SizeX]);
void Define_Graph_By_Y(GraphPixel [][SizeX], double, double, double);
void Define_Graph_By_X(GraphPixel [][SizeX], double, double, double);
GraphLines Define_Graph_Line_Slant(double, double, int);
void Paint_Graph(double ,double, double);
void Print_GraphPixel(GraphPixel);
enum QuantOfRoots Squrt_Solve(double a, double b, double c, double* x1, double* x2);
void Define_One_X_Line(GraphPixel [][SizeX], int, GraphPixel);
void Define_One_Y_Line(GraphPixel [][SizeX], int, GraphPixel);
void Print_GraphLine(GraphLines);
void Graduate_Y(GraphPixel [][SizeX]);
void Define_One_Y_Value(GraphPixel [][SizeX], int);
void Graduate_X(GraphPixel [][SizeX]);
void Define_One_X_Value(GraphPixel [][SizeX], int);


#endif