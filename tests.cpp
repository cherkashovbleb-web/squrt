#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "colors.h"
#include "squrt.h"
#include "tests.h"



/*печатает всю информацию о структуре test*/
void Print_TestCase(TestCase test){
    printf("a = %lg, b = %lg, c = %lg, Number of roots = %d, x1 = %lg, x2 = %lg", 
            test.a, test.b, test.c, test.nRootsref, test.x1ref, test.x2ref);
}


/*вывод правильного теста*/
void Write_Test_OK(int tests_counter){
    printf("Test " YELLOW "%d" NO_COLOR ": " GREEN "OK" NO_COLOR "\n---\n", tests_counter);
}


/*вывод заваленного теста*/
void Write_Test_Failed(int test_counter, TestCase test, double x1, double x2, QuantOfRoots nRoots){
    printf("Test %d " RED "FAILED" NO_COLOR ": a = %.5lg, b = %.5lg, c = %.5lg\n"
           "EXPECTED: %d roots x1 = %.5lg, x2 = %.5lg"
           "GOT     : %d roots x1 = %.5lg, x2 = %.5lg", test_counter, test.a, test.b, test.c, test.nRootsref,
           test.x1ref, test.x2ref, nRoots, x1, x2);
}


/*запускает один тест*/
void Run_One_Test(int* tests_counter, TestCase test, int* counter_ok_tests){
    ++*tests_counter;
    enum QuantOfRoots nRoots = ZERO_ROOTS;
    double x1 = 0, x2 = 0;
    nRoots = Squrt_Solve(test.a, test.b, test.c, &x1, &x2);
    if (nRoots != test.nRootsref){
        Write_Test_Failed(*tests_counter, test, x1, x2, nRoots);
    }
    else if (nRoots == INF_ROOTS){
        //Write_Test_OK(*tests_counter);
        ++*counter_ok_tests;
    }
    else if (nRoots == ZERO_ROOTS){
        if (Is_Zero(x1) && Is_Zero(x2)){
            //Write_Test_OK(*tests_counter);
            ++*counter_ok_tests;
        }
        else{
            Write_Test_Failed(*tests_counter, test, x1, x2, nRoots);
        }
    }
    else if((Is_Equal(x1, test.x1ref) && isnan(test.x2ref) && Is_Zero(x2)) || (Is_Equal(x1, test.x1ref) && Is_Equal(x2, test.x2ref))){
        //Write_Test_OK(*tests_counter);
        ++*counter_ok_tests;
    }
    else{
        Write_Test_Failed(*tests_counter, test, x1, x2, nRoots);
    }
}


/*серия тестов для программы*/
void Run_All_Tests(){
    int tests_counter = 0, counter_ok_tests = 0;
    double a = 0, b = 0, c = 0;
    TestCase testsStreet[] = {{.a = 0, .b = 0, .c = 0, .nRootsref = INF_ROOTS},
                              {.a = 1., .b = 2.2, .c = 1.21, .nRootsref = ONE_ROOT, .x1ref = -1.1}, 
                              {.a = 2, .b = 0, .c = -8, .nRootsref = TWO_ROOTS, .x1ref = -2, .x2ref = 2}, 
                              {.a = 0.1, .b = 1.6, .c = 6.4, .nRootsref = ONE_ROOT, .x1ref = -8}, 
                              {.a = 0, .b = 0, .c = 35, .nRootsref = ZERO_ROOTS}, 
                              {.a = 1, .b = 2, .c = 2, .nRootsref = ZERO_ROOTS}};

    unsigned int size_testsStreet = sizeof(testsStreet) / sizeof(TestCase);
    for (unsigned int i = 0; i < size_testsStreet; i++){
        Run_One_Test(&tests_counter, testsStreet[i], &counter_ok_tests);
    }
    
    srand(Str_To_Int("meow")); //не больше 4 символов, иначе будет переполнение int
    
    Run_Random_Tests(&tests_counter, &counter_ok_tests, ZERO_ROOTS);
    Run_Random_Tests(&tests_counter, &counter_ok_tests, ONE_ROOT);
    Run_Random_Tests(&tests_counter, &counter_ok_tests, TWO_ROOTS);
    char buffer[100] = {0};
    snprintf(buffer, 100, "from " YELLOW "%d" NO_COLOR " tests completly passed " GREEN "%d" NO_COLOR ", failed " RED "%d" NO_COLOR "\n",
           tests_counter, counter_ok_tests, tests_counter - counter_ok_tests);
    Printf_With_Delay(buffer);
}


/*запускает рандомные тесты с 0, 1, 2 корнями*/
void Run_Random_Tests(int* tests_counter, int* counter_ok_tests, QuantOfRoots nRoots){
    TestCase test = {};
    double min = -100.0, max = 100.0, positive_num = 0, x1 = 0;
    test.nRootsref = nRoots;
    for (int j = 0; j < Num_Tests; ++j){
        test.a = Get_Rand(min, max);
        switch (nRoots){
            case ZERO_ROOTS:
                x1 = Get_Rand(min, max);
                positive_num = Get_Rand(1, 10);
                test.b = -2 * test.a * x1;
                test.c = test.a * x1 * x1 + positive_num * test.a;
                break;
            case ONE_ROOT:
                test.x1ref = Get_Rand(min, max);
                test.b = -2 * test.a * test.x1ref;
                test.c = test.a * test.x1ref * test.x1ref;
                break;
            case TWO_ROOTS:
                test.x1ref = Get_Rand(min, max);
                test.x2ref = Get_Rand(min, max);
                Sort_Nums(&test.x1ref, &test.x2ref);
                if (Is_Zero(test.a * (test.x1ref - test.x2ref))){
                    continue;
                }
                test.b = -test.a * (test.x1ref + test.x2ref);
                test.c = test.a * test.x1ref * test.x2ref;
                break;

        }
        Run_One_Test(tests_counter, test, counter_ok_tests);
    }
}


/*генерирует рандомное double число от min до max*/
double Get_Rand(double min, double max){
    return min + ((double) rand() / RAND_MAX) * (max - min);
}


/*проверяет корень квадратки*/
int Check_Root(double a, double b, double c, double x){
    return Is_Zero(a * x * x + b * x + c);
}


/*хэширует строку в int*/
int Str_To_Int(const char str[]){
    unsigned int size = 0;
    while (str[++size] != '\0');
    int hash = 0, power = 1;
    for (int i = size - 1; i > -1; i--){
        hash += str[i] * power;
        power *= 256;
    }
    return hash;
}