#ifndef TESTS_H
#define TESTS_H


#define Num_Tests 10000000


struct TestCase{
    double a, b, c;
    enum QuantOfRoots nRootsref;
    double x1ref = NAN, x2ref = NAN;
};



void Print_TestCase(TestCase);
void Run_One_Test(int*, TestCase, int*);
void Run_All_Tests(void);
void Write_Test_Failed(int, TestCase, double, double, int);
void Write_Test_OK(int);
double Get_Rand(double, double);
int Check_Root(double, double, double, double);
void Run_Random_Tests(int*, int*, enum QuantOfRoots, TestCase);
void Sort_Nums(double*, double*);
QuantOfRoots Squrt_Solve(double a, double b, double c, double* x1, double* x2);
int Is_Zero(double);
int Is_Equal(double, double);
void Printf_With_Delay(const char*);
int Str_To_Int(const char []);


#endif