#ifndef SQURT_H
#define SQURT_H

/**The area where the comarison of double and float numbers with null takes place */
#define EPS 1e-6

/**The maximum string length */
#define MAXLINE 1000

/**ANSI code to delete all characters in the line to the right of the carriage return */
#define ClearLine "\033[K"


/**
 * \enum WillContinue
 * 
 * \brief The parameter that determines whether the quadratic equation will be solved again
 */
enum WillContinue{
    NO_CONTINUE,
    CONTINUE
};


/**
 * \enum QuantOfRoots
 * 
 * \brief Number of the roots of the quadratic equation
 */
enum QuantOfRoots{
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};


/**
 * \brief Solve the quadratic equation
 * 
 * Writes the values of the roots to the variables x1, x2\n
 * if the equation has 2 roots: run Solve_With_Discriminant(...)\n
 * 1 root: the value will be written to x1, x2 won't be changed\n
 * 0 or infinitive roots: x1, x2 will remain unchanged.
 * 
 * \param[in] a the coefficient of quadratic equation for x^2
 * \param[in] b the coefficient of quadratic equation for x
 * \param[in] c the free coefficient of quadratic equation
 * \param[in, out] x1 the first root
 * \param[in, out] x1 the second root
 * 
 * \return number of roots of the quadratic equation as a QuantOfRoots
 */
QuantOfRoots Squrt_Solve(double a, double b, double c, double* x1, double* x2);


/** 
 * \brief Solve the quadratic equation with discriminant (a != 0)
 * 
 * Writes the values of the roots to the variables x1, x2\n
 * d - discriminant of quadratic equation\n
 * if the equation has a number of roots other than 2 (d <= 0):\n
 * 1 root (d == 0): the value will be written to x1, x2 won't be changed\n
 * 0 (d < 0): x1, x2 will remain unchanged.
 * 
 * \note if equation has 2 roots, x1, x2 MUST BE sorted in accending order
 * 
 * \param[in] a the coefficient of quadratic equation for x^2
 * \param[in] b the coefficient of quadratic equation for x
 * \param[in] c the free coefficient of quadratic equation
 * \param[in, out] x1 the first (minimal) root
 * \param[in, out] x1 the second (maximal) root
 * 
 * \return Number of roots of the quadratic equation as a QuantOfRoots
*/
QuantOfRoots Solve_With_Discriminant(double a, double b, double c, double* x1, double* x2);


/**
 * \brief An introductory text for users to know what is requiredof them
 */
void Intro(void);


/**
 * \brief Write roots
 * 
 * if number of roots equals 1: print x1 = x2 = <root>\n
 * if number of roots equals 2: print x1 = <root1>, x2 = <root2>\n
 * if number of roots eqials 0: print No Root\n
 * if equation has infinitive roots: print Infinite Roots\n
 * 
 * \param[in] nRoots number of roots
 * \param[in] x1 the first root
 * \param[in] x2 the second root 
 */
void Write_Solutions(QuantOfRoots nRoots, double x1, double x2);


/**
 * \brief Print notification if user entered coefficients a, b, c incorrectly
 */
void Print_Input_Error(void);


/**
 * \brief Ask user to enter coefficients a, b, c
 * 
 * \param[in] a the coefficient of quadratic equation for x^2
 * \param[in] b the coefficient of quadratic equation for x
 * \param[in] c the free coefficient of quadratic equation
 * 
 * \return Quantity of wrong-inputed symbols (letters, punktuation marks, excluding the period)
 */
int Enter_Coeffs(double*, double*, double*);


/**
 * \brief Checking double and float number for equality to zero
 * 
 * checks if absolute value of number is less then EPS
 * 
 * \param[in] num
 * 
 * \return 1 if number is equal to zero within a certain approximation else - 0
 */
int Is_Zero(double num);


/**
 * \brief Checking double and float numbers for their equality
 * 
 * use function Is_Zero(...)
 * 
 * \param[in] a the first number
 * \param[in] b the second number
 * 
 * \return 1 if numbers are equal within a certain approximation else - 0
 */
int Is_Equal(double a, double b);


/**
 * \brief Delete all symbols from buffer
 * 
 * \return The quantity of deleted symbols 
 */
int Clear_Buffer(void);


/**
 * \brief A string input
 * 
 * if user inputed more than (MAXLINE - 1) symbols, the inputed string will be truncated to appropriate size\n
 * the last character of the string is the NULL symbol in ASCII characters table
 * 
 * \param[in, out] str an char array of fixed length - MAXLINE
 */
void String_Input(char* str);


/**
 * \brief A user's comment for programm
 * 
 * ask user to write his comment and username\n
 * then write a string in format [Day.Month.Year Hour:Minute] <username> comment to the file output.txt\n
 * if programm couldn't open the file, an error will be displayed
 * if user hasn't written the comment, nothing will be written to the file\n
 * if default value of username is "Anonymous"\n
 */
void User_Comment(void);


/**
 * \brief Determines the local time
 * 
 * \return Local time in format struct tm
 */
struct tm* Local_Time(void);


/**
 * \brief Pretends to think
 * 
 * Print "Think", then print three dots with a delay and then delete them three times
 */
void AI_Thinking(void);


/**
 * \brief Print text like AI
 * 
 * use Sleep and rand to output text, based on tokens
 */
void Printf_With_Delay(const char*);


#endif