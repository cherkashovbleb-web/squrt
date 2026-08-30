#ifndef SQURT_H
#define SQURT_H



#define eps 1e-6
#define MAXLINE 1000
#define ClearLine "\033[K"


enum WillContinue{
    NO_CONTINUE,
    CONTINUE
};


enum QuantOfRoots{
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};



QuantOfRoots Squrt_Solve(double a, double b, double c, double* x1, double* x2);
QuantOfRoots Solve_With_Discriminant(double a, double b, double c, double* x1, double* x2);
void Intro(void);
void Write_Solutions(int, double, double);
void Print_Input_Error(void);
int Enter_Coeffs(double*, double*, double*);
int Is_Zero(double);
int Is_Equal(double, double);
int Clear_Buffer(void);
void String_Input(char*);
void User_Comment(void);
struct tm* Local_Time(void);
enum WillContinue Solve_And_Write_Quadratic();
void AI_Thinking(void);
void Printf_With_Delay(const char*);
int Str_To_Int(const char []);


#endif