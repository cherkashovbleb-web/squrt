#include <stdio.h>
#include <math.h>
#include "colors.h"
#include "nRoots.h"


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
enum GraphLines Define_Graph_Line_Slant(double, double, int);
void Paint_Graph(double ,double, double);
void Print_GraphPixel(GraphPixel);
enum QuantOfRoots Squrt_Solve(double a, double b, double c, double* x1, double* x2);
void Define_One_X_Line(GraphPixel [][SizeX], int, GraphPixel);
void Define_One_Y_Line(GraphPixel [][SizeX], int, GraphPixel);
GraphLines Turn_Digit_To_GraphLines(int);
void Print_GraphLine(GraphLines);
void Graduate_Y(GraphPixel [][SizeX]);
void Define_One_Y_Value(GraphPixel [][SizeX], int);
void Graduate_X(GraphPixel [][SizeX]);
void Define_One_X_Value(GraphPixel [][SizeX], int);



/*печатает один пиксель графика*/
void Print_GraphPixel(GraphPixel pixel){
    printf("%s%c" NO_COLOR, pixel.color, pixel.symbol);
}


/*печатает заданный символ из GraphLines*/
void Print_GraphLine(GraphLines a){
    printf("%c", a);
}


/*рисует в терминале параболу*/
void Paint_Graph(double a, double b, double c){
    GraphPixel matr[SizeY][SizeX] = {};
    Define_Graph_Axes(matr);

    Define_Graph_By_Y(matr, a, b, c);
    
    Define_Graph_By_X(matr, a, b, c);

    Graduate_Y(matr);
    Graduate_X(matr);
    matr[SizeY / 2][SizeX / 2] = {.symbol = GRAPH_NULL, .color = YELLOW};

    for (unsigned int row = 0; row < SizeY; row++){
        Paint_One_Row_Of_Graph(matr[row]);
    }
}


/*определяет оси координат графика параболы*/
void Define_Graph_Axes(GraphPixel matr[][SizeX]){
    for (unsigned int row = SizeY / 2 % yStep; row < SizeY; row += yStep){
        Define_One_X_Line(matr, row, {.symbol = GRAPH_POINT, .color = BLUE});
    }
    for (unsigned int col = SizeX / 2 % xStep; col < SizeX; col += xStep){
        Define_One_Y_Line(matr, col, {.symbol = GRAPH_POINT, .color = BLUE});
    }
    Define_One_X_Line(matr, SizeY / 2, {.symbol = GRAPH_ABSC, .color = GRAY});
    Define_One_Y_Line(matr, SizeX / 2, {.symbol = GRAPH_ORDIN, .color = GRAY});

    matr[0][SizeX / 2] = {.symbol = GRAPH_ORDIN_VECTOR, .color = GRAY};
    matr[SizeY / 2][SizeX - 1] = {.symbol = GRAPH_ABSC_VECTOR, .color = GRAY};
    matr[0][SizeX / 2 - 1] = {.symbol = GRAPH_NAME_Y, .color = BLUE};
    matr[SizeY / 2 + 1][SizeX - 1] = {.symbol = GRAPH_NAME_X, .color = BLUE};
}


/*рисует одну строку параболы*/
void Paint_One_Row_Of_Graph(GraphPixel line[]){
    for (unsigned int col = 0; col < SizeX; ++col){
        Print_GraphPixel(line[col]);
    }
    printf("\n");
}


/*заполняет параболу по оси y*/
void Define_Graph_By_Y(GraphPixel matr[][SizeX], double a, double b, double c){
    enum QuantOfRoots nRoots = ZERO_ROOTS;
    int x1_int = 0, x2_int = 0;
    double x1 = NAN, x2 = NAN;
    for (int row = 0; row < SizeY; row++){
        //printf("im in y %d before quad\n", i);
        nRoots = Squrt_Solve(a, b, c - (SizeY / 2 - row), &x1, &x2);
        //printf("im in y %d after quad\n", i);
        //printf("nRoots = %d, x1 = %d, x2 = %d, |x1 - x2| = %d\n", nRoots, x1_int, x2_int, abs(x1_int - x2_int));
        x1_int = round(x1);
        x2_int = round(x2);
        if (fabs(x1_int) < (SizeX / 2)){
            matr[row][x1_int + SizeX / 2] = {.symbol = Define_Graph_Line_Slant(a, b, x1_int), .color = GREEN};
        }
        if (fabs(x2_int) < (SizeX / 2)){
            matr[row][x2_int + SizeX / 2] = {.symbol = Define_Graph_Line_Slant(a, b, x2_int), .color = GREEN};
        }
        x1 = NAN;
        x2 = NAN;
    }
}


/*заполняет параболу по оси x*/
void Define_Graph_By_X(GraphPixel matr[][SizeX], double a, double b, double c){
    int y = 0, x = 0;
    for (int col = 0; col < SizeX; col++){
        //printf("im in x %d\n", col);
        x = col - SizeX / 2;
        y = round(a * x * x + b * x + c);
        if (abs(y) <= SizeY / 2){
            matr[SizeY / 2 - y][col] = {.symbol = Define_Graph_Line_Slant(a, b, x), .color = GREEN};
        }
    }
}


/*определяет угол наклона линии графика*/
enum GraphLines Define_Graph_Line_Slant(double a, double b, int x){
    const double pi = M_PI;
    double angle = atan(2 * a * x + b) * 180.0 / pi;
    double inf_edge = 65;
    double flat_edge = 30;
    if ((angle > -90 && angle < -inf_edge) || (angle >= inf_edge && angle < 90)){
        return GRAPH_INF_SLANT;
    }
    else if (angle >= -inf_edge && angle < -flat_edge){
        return GRAPH_NEGATIVE_SLANT;
    }
    else if (angle >= -flat_edge && angle < flat_edge){
        return GRAPH_ZERO_SLANT;
    }
    else {
        return GRAPH_POSITIVE_SLANT;
    }
}


/*заполняет один столбец графика заданными символами*/
void Define_One_Y_Line(GraphPixel matr[][SizeX], int col, GraphPixel symbol){
    for (unsigned int row = 0; row < SizeY; row++){
        matr[row][col] = symbol;
    }
}


/*заполняет одну строку графика заданными символами*/
void Define_One_X_Line(GraphPixel matr[][SizeX], int row, GraphPixel symbol){
    for (unsigned int col = 0; col < SizeX; col++){
        matr[row][col] = symbol;
    }
}


/*градуирует ось ординат*/
void Graduate_Y(GraphPixel matr[][SizeX]){
    for (unsigned int row = SizeY / 2 % yStep; row < SizeY; row += yStep){
        Define_One_Y_Value(matr, row);
    }
}


/*заполняет одно значение на оси ординат*/
void Define_One_Y_Value(GraphPixel matr[][SizeX], int row){
    int y = SizeY / 2 - row;
    int is_negative = (y < 0);
    y = abs(y);
    int pos = 1;
    if (y != 0){
        while (y){
            matr[row][SizeX / 2 - pos] = {.symbol = Turn_Digit_To_GraphLines(y % 10), .color = YELLOW};
            y /= 10;
            pos++;
        }
    }
    if (is_negative){
        matr[row][SizeX / 2 - pos] = {.symbol = GRAPH_MINUS, .color = YELLOW};
    }
}


/*градуирует ось абсцисс*/
void Graduate_X(GraphPixel matr[][SizeX]){
    for (unsigned int col = SizeX / 2 % xStep; col < SizeX; col += xStep){
        Define_One_X_Value(matr, col);
    }
}


/*заполняет одно значение на оси ординат*/
void Define_One_X_Value(GraphPixel matr[][SizeX], int col){
    int x = col - SizeX / 2;
    int is_negative = (x < 0);
    x = abs(x);
    int x_copy = x, ndigits = 0;
    while (x_copy){
        ndigits++;
        x_copy /= 10;
    }
    if (is_negative){
        ndigits++;
    }
    int pos = ndigits / 2;
    while (x){
        if (col + pos < SizeX && col + pos >= 0){
            matr[SizeY / 2 + 1][col + pos] = {.symbol = Turn_Digit_To_GraphLines(x % 10), .color = YELLOW};
        }
        pos--;
        x /= 10;
    }
    if (is_negative){
        matr[SizeY / 2 + 1][col + pos] = {.symbol = GRAPH_MINUS, .color = YELLOW};
    }
}


/*переводит цифру в GraphLines*/
GraphLines Turn_Digit_To_GraphLines(int a){
    switch(a){
        case 0: return GRAPH_NULL;
        case 1: return GRAPH_ONE;
        case 2: return GRAPH_TWO;
        case 3: return GRAPH_THREE;
        case 4: return GRAPH_FOUR;
        case 5: return GRAPH_FIVE;
        case 6: return GRAPH_SIX;
        case 7: return GRAPH_SEVEN;
        case 8: return GRAPH_EIGHT;
        case 9: return GRAPH_NINE;
        default: printf("%d is not a digit ^(0_0)^\n", a);
            break;
    }
    return GRAPH_STAR;
}