#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdarg.h>
#include <string.h>
#include "colors.h"
#include "nRoots.h"


#define eps 1e-6
#define MAXLINE 1000
#define ClearLine "\033[K"


enum WillContinue{
    NO_CONTINUE,
    CONTINUE
};



enum QuantOfRoots Squrt_Solve(double a, double b, double c, double* x1, double* x2);
enum QuantOfRoots Solve_With_Discriminant(double a, double b, double c, double* x1, double* x2);
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


#include "paint_graph.cpp"
#include "tests.cpp"


int main(){
    int continuer = 0, cnt_num_continuer = 1;
    Intro();

    scanf("%d", &continuer);
    while (cnt_num_continuer == 1 && continuer == 1){
        if (Solve_And_Write_Quadratic() == CONTINUE){
            Printf_With_Delay("\nWould you like to solve your equation again? "
                   "If you want, enter 1, else - 0:  ");
            cnt_num_continuer = scanf("%d", &continuer);
        }
    }
    User_Comment();
    return 0;
}


/*ищет корни крвадратного уравнения*/
enum QuantOfRoots Squrt_Solve(double a, double b, double c, double* x1, double* x2){
    //printf("ive started quad\n");
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (Is_Zero(a)){
        if (Is_Zero(b)){
            return (Is_Zero(c))? INF_ROOTS : ZERO_ROOTS;
        }
        else{
            *x1 = -c / b;
            return ONE_ROOT;
        }
    }

    else{
        return Solve_With_Discriminant(a, b, c, x1, x2);
    }
}


/*ищет корни квадратки через дискриминант*/
enum QuantOfRoots Solve_With_Discriminant(double a, double b, double c, double* x1, double* x2){
    //printf("im solving d\n");
    double d = b * b - 4 * a * c;
    if (Is_Zero(d / a)){ // a добавлено для увеличения точности : при небольших a (10^[-2 - -4]) дискриминант может получиться меньше eps, при делении на а он увеличится
                         // и в дальнейшем при извелечении корня он станет больше, и разница между корнями станет значительной, опять же из-за небольшого а;
                         // при больших а даже относительно большой дискриминант (10^[-1 - -3]) может бsть получен очень неточно из-за погрешностей double, умноженных на 
                         // большие числа
        //printf("d = 0, d = %.5lf\n", d);
        *x1 = -b / (2 * a);
        //printf("ive 1 ended quad\n");
        return ONE_ROOT;
    }
    else if (d < 0){
        //printf("d < 0, d = %.5lf\n", d);
        //printf("ive 0 ended quad\n");
        return ZERO_ROOTS;
    }
    else{
        //printf("d > 0, d = %.5lf\n", d);
        *x1 = (-b - sqrt(d)) / (2 * a);
        *x2 = (-b + sqrt(d)) / (2 * a);
        Sort_Nums(x1, x2);
        //printf("ive 2 ended quad\n");
        return TWO_ROOTS;
    }
}


/*вводный текст, чтобы пользователь поинмал, что от него требуется*/
void Intro(){
    int test_mode = 0;
    Printf_With_Delay("#HI! this is quadratic equation solver#\n---\n");
    Printf_With_Delay("Do you want to turn test mode? Enter 1 - yes, 0 - no: ");
    scanf("%d", &test_mode);
    if (test_mode){
        Run_All_Tests();
    }
    Printf_With_Delay("Would you like to solve your equation?\n"
           "If you want, enter 1, else - 0:  ");
}


/*вывод корней*/
void Write_Solutions(enum QuantOfRoots nRoots, double x1, double x2){
    char buffer[80] = {0};
    switch (nRoots){
        case ZERO_ROOTS: snprintf(buffer, 80, RED "No Roots\n" NO_COLOR);
            break;
        case ONE_ROOT: snprintf(buffer, 80, YELLOW "x1 = x2 = %.5lg\n" NO_COLOR, x1);
            break;
        case TWO_ROOTS: snprintf(buffer, 80, YELLOW "x1 = %.5lg, x2 = %.5lg\n" NO_COLOR, x1, x2);
            break;
        case INF_ROOTS: snprintf(buffer, 80, BLUE "Infinite Roots\n" NO_COLOR);
            break;
        default: snprintf(buffer, 80, RED "main(): ERROR nRoots = %d\n" NO_COLOR, nRoots);
            break;
    }
    Printf_With_Delay(buffer);
}


/*оповещение в случае, если пользователь неправильно ввел a, b, c*/
void Print_Input_Error(){
    Printf_With_Delay("Wrong input, " GREEN "Separate integer and fractional parts by period" NO_COLOR", try again\n");
}


/*проверка на равенство 0*/
int Is_Zero(double num){
    return (fabs(num) < eps);
}


/*проверка на равенство двух чисел*/
int Is_Equal(double a, double b){
    return Is_Zero(a - b);
}


/*ввод коэффициентов квадратного уравнения*/
int Enter_Coeffs(double* a, double* b, double* c){
    int buffer_extra_chr_counter = 0;
    Printf_With_Delay("Enter coefficients a, b, c of quadratic equation ax^2+bx+c=0\n");
    Printf_With_Delay("a = ");
    scanf("%lg", a);
    buffer_extra_chr_counter += Clear_Buffer();
    Printf_With_Delay("b = ");
    scanf("%lg", b);
    buffer_extra_chr_counter += Clear_Buffer();
    Printf_With_Delay("c = ");
    scanf("%lg", c);
    buffer_extra_chr_counter += Clear_Buffer();
    return buffer_extra_chr_counter;
}


/*делает вид что думает*/
void AI_Thinking(){
    Printf_With_Delay("Thinking ");
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            Sleep(300);
            printf(".");
        }
        Sleep(600);
        printf("\b\b\b" ClearLine);
        Sleep(600);
    }
    printf("\r" ClearLine);
}


/*объединение функций по поиску и выводу корней*/
enum WillContinue Solve_And_Write_Quadratic(){
    double x1 = NAN, x2 = NAN;
    double a = 0, b = 0, c = 0;

    int buffer_extra_chr_counter = Enter_Coeffs(&a, &b, &c);

    if (buffer_extra_chr_counter > 0){
        Print_Input_Error();
        return NO_CONTINUE;
    }

    //printf("a: %.5lg, b: %.5lg, c: %.5lg\n", a, b, c);
    AI_Thinking();
    enum QuantOfRoots nRoots = Squrt_Solve(a, b, c, &x1, &x2);
    //printf("im out of quad\n");
    Paint_Graph(a, b, c);

    Write_Solutions(nRoots, x1, x2);

    return CONTINUE;
}


/*очищает буффер*/
int Clear_Buffer(){
    char chr = 0, buffer_extra_chr_counter = 0;
    while ((chr = getchar()) != '\n' && chr != EOF){
        buffer_extra_chr_counter++;
    }
    return buffer_extra_chr_counter;
}


/*запись в файл локального времени*/
struct tm* Local_Time(){
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    
    timeinfo = localtime(&rawtime);
    return timeinfo;
}


/*ввод строки*/
void String_Input(char* string){
    unsigned int str_pos = 0;
    char chr = getchar();
    while (str_pos < MAXLINE - 1 && chr != '\n' && chr != EOF){
        string[str_pos] = chr;
        ++str_pos;
        chr = getchar();
    }
    string[str_pos + 1] = '\0';
}


/*комментарий по программе*/
void User_Comment(){
    Clear_Buffer();
    char comment[MAXLINE] = {0};
    char username[MAXLINE] = {0};
    char time_repres[80] = {0};

    Printf_With_Delay("Hope, you like this solver. You may write your comment.\n");

    FILE* fp = 0;
    fp = fopen("output.txt", "a");
    if (fp == NULL){
        Printf_With_Delay(RED "Output File Openning ERROR\n" NO_COLOR);
        return;
    }
    Printf_With_Delay(YELLOW "Your comment:" NO_COLOR " ");
    String_Input(comment);
    Printf_With_Delay(YELLOW "Your username:" NO_COLOR " ");
    String_Input(username);
    if (comment[0] != '\0'){
        strftime(time_repres, sizeof(time_repres), "%d.%m.%Y %H:%M GMT+5", Local_Time());
        fprintf(fp, "[%s]", time_repres);
        if (username[0] == '\0'){
            fprintf(fp, "\t<Anonymous>");
        }
        else{
            fprintf(fp, "\t<%s>", username); 
        }
        fprintf(fp, "  %s\n", comment);
    }
    fclose(fp);
}


/*сортирует два числа*/
void Sort_Nums(double* a, double* b){
    if (*a > *b){
        double swapper = *a;
        *a = *b;
        *b = swapper;
    }
}


/*принтф с задержкой*/
void Printf_With_Delay(const char* line){
    srand(time(NULL));
    for (int i = 0; i < strlen(line); i++){
        printf("%c", line[i]);
        if(((double) rand() / RAND_MAX) > 0.75){
            Sleep(80);
        }
        if (line[i] == '?' || line[i] == '.' || line[i] == '\n' || line[i] == '!'){
            Sleep(60);
        }
        else if(line[i] == ','){
            Sleep(30);
        }
    }
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
