/**
 * include files
 * @brief the stdlib.h library is added for exit function and the ctype.h is added for the toupper function
 **/
/**
 * @file projectm.c
 * @file in.txt
 * @file regs.txt
 * @brief this code is a cpu simulator
 * @version: v1.09
 * @date: 27 january 2023
 * @author: niloofar asoubar
 * @warning
 * warning test
 * @note fundamentals of programming 4011
 * \mainpage
 * CPU REGISTERS
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int j;
int array[32] = {0};
int sobat[8] = {2, 2, 2, 2, 2, 2, 2, 2};
int stack[50];
/**
 *\fn void red()
 *\brief font color is adjusted to red
 *\param void
 *\return void
 **/
void red()
{
    printf("\033[0;31m");
}
/**
 *\fn void yellow()
 *\brief font color is adjusted to yellow
 *\param void
 *\return void
 **/
void yellow()
{
    printf("\033[0;33m");
}
/**
 *\fn void whitebold()
 *\brief font color is adjusted to a bold white version
 *\param void
 *\return void
 **/
void whitebold()
{
    printf("\033[1;37m");
}
/**
 *\fn void reset()
 *\brief resets the color output
 *\param void
 *\return void
 **/
void reset()
{
    printf("\033[0m");
}
/**
 *\fn void parityflag(int result)
 *\brief it checks wether the binary form of the input has even number of "1" bits or not
 *\param int result
 *\return void
 **/
void parity_flag(int result)
{
    int count = 0;
    while (result > 0)
    {
        if (result % 2 == 1)
        {
            count++;
        }
        result /= 2;
    }
    if (count % 2 == 1)
    {
        sobat[0] = 1;
    }
    else
    {
        sobat[0] = 0;
    }
}
/**
 *\fn void zeroflag(int result)
 *\brief checks wether or not the result is equal to zero
 *\param int result
 *\return void
 **/
void zero_flag(int result)
{
    if (result == 0)
    {
        sobat[1] = 1;
    }
    else
    {
        sobat[1] = 0;
    }
}
/**
 *\fn void signflag(int result)
 *\brief checks wether or not the input is a negative number
 *\param int result
 *\return void
 **/
void sign_flag(int result)
{
    if (result < 0)
    {
        sobat[2] = 1;
    }
    else
    {
        sobat[2] = 0;
    }
}
/**
 *\fn void overflow_flag_sum(int result)
 *\brief checks wether or not an overflow has occured in the addition of two numbers
 *\param int result
 *\return void
 **/
void overflow_flag_sum(int result, int a, int b)
{
    if (a > 0 && b > 0 && result < 0 || a < 0 && b < 0 && result > 0)
    {
        sobat[5] = 1;
    }
    else
    {
        sobat[5] = 0;
    }
}
/**
 *\fn void overflow_flag_sub(int result)
 *\brief checks wether or not an overflow has occured in the subtraction of two numbers
 *\param int result
 *\return void
 **/
void overflow_flag_sub(int result, int a, int b)
{
    if (a > 0 && b < 0 && result < 0 || a < 0 && b > 0 && result > 0)
    {
        sobat[5] = 1;
    }
    else
    {
        sobat[5] = 0;
    }
}
/**
 *\fn void overflow_flag_product(int result)
 *\brief checks wether or not an overflow has occured in the product of two numbers
 *\param int result
 *\return void
 **/
void overflow_flag_product(int result, int a, int b)
{
    if (a != 0 && (result / a) != b)
    {
        sobat[5] = 1;
    }
    else
    {
        sobat[5] = 0;
    }
}
/**
 *\fn void PUSH(int n)
 *\brief puts sobat[n] on top of a predefined stack
 *\param int n
 *\return void
 **/
void PUSH(int n)
{
    for (int i = 0; i < 50; i++)
    {
        stack[i + 1] = stack[i];
    }
    stack[0] = sobat[n];
}
/**
 *\fn void POP(int n)
 *\brief gets a number from the top of a predefined stack and puts it in sobat[n]
 *\param int n
 *\return void
 **/
void POP(int n)
{
    sobat[n] = stack[0];
    for (int i = 0; i < 50; i++)
    {
        stack[i] = stack[i + 1];
    }
}
/**
 *\fn void ADD(int add, int srt, int srs)
 *\brief adds two of the inputs together and puts it in the predefined array
 *\param int add, int srt, int srs
 *\return void
 **/
void ADD(int add, int srt, int srs)
{
    array[add] = array[srt] + array[srs];
    parity_flag(array[add]);
    zero_flag(array[add]);
    sign_flag(array[add]);
    overflow_flag_sum(array[add], array[srt], array[srs]);
}
/**
 *\fn void SUB(int sub, int srt, int srs)
 *\brief subtracts two of the inputs from eachother and puts it in the predefined array
 *\param int sub, int srt, int srs
 *\return void
 **/
void SUB(int sub, int srt, int srs)
{
    array[sub] = array[srt] - array[srs];
    parity_flag(array[sub]);
    zero_flag(array[sub]);
    sign_flag(array[sub]);
    overflow_flag_sub(array[sub], array[srt], array[srs]);
}
/**
 *\fn void AND(int and, int srt, int srs)
 *\brief ands two of the inputs together and puts it in the predefined array
 *\param int and, int srt, int srs
 *\return void
 **/
void AND(int and, int srt, int srs)
{
    array[and] = array[srt] & array[srs];
    parity_flag(array[and]);
    zero_flag(array[and]);
    sign_flag(array[and]);
}
/**
 *\fn void XOR(int xor, int srt, int srs)
 *\brief xors two of the inputs together and puts it in the predefined array
 *\param int xor, int srt, int srs
 *\return void
 **/
void XOR(int xor, int srt, int srs)
{
    array[xor] = array[srt] ^ array[srs];
    parity_flag(array[xor]);
    zero_flag(array[xor]);
    sign_flag(array[xor]);
}
/**
 *\fn void OR(int or, int srt, int srs)
 *\brief ors two of the inputs together and puts it in the predefined array
 *\param int or, int srt, int srs
 *\return void
 **/
void OR(int or, int srt, int srs)
{
    array[or] = array[srt] | array[srs];
    parity_flag(array[or]);
    zero_flag(array[or]);
    sign_flag(array[or]);
}
/**
 *\fn void ADDI(int addi, int srs, int imm)
 *\brief adds two of the inputs together and puts it in the predefined array
 *\param int addi, int srs, int imm
 *\return void
 **/
void ADDI(int addi, int srs, int imm)
{
    array[addi] = array[srs] + imm;
    parity_flag(array[addi]);
    zero_flag(array[addi]);
    sign_flag(array[addi]);
    overflow_flag_sum(array[addi], array[srs], imm);
}
/**
 *\fn void SUBI(int subi, int srs, int imm)
 *\brief subs two of the inputs together and puts it in the predefined array
 *\param int subi, int srs, int imm
 *\return void
 **/
void SUBI(int subi, int srs, int imm)
{
    array[subi] = array[srs] - imm;
    parity_flag(array[subi]);
    zero_flag(array[subi]);
    sign_flag(array[subi]);
    overflow_flag_sub(array[subi], array[srs], imm);
}
/**
 *\fn void ANDI(int andi, int srs, int imm)
 *\brief ands two of the inputs together and puts it in the predefined array
 *\param int andi, int srs, int imm
 *\return void
 **/
void ANDI(int andi, int srs, int imm)
{
    array[andi] = array[srs] & imm;
    parity_flag(array[andi]);
    zero_flag(array[andi]);
    sign_flag(array[andi]);
}
/**
 *\fn void XORI(int xori, int srs, int imm)
 *\brief xors two of the inputs together and puts it in the predefined array
 *\param int xori, int srs, int imm
 *\return void
 **/
void XORI(int xori, int srs, int imm)
{
    array[xori] = array[srs] ^ imm;
    parity_flag(array[xori]);
    zero_flag(array[xori]);
    sign_flag(array[xori]);
}
/**
 *\fn void ORI(int ori, int srs, int imm)
 *\brief ors two of the inputs together and puts it in the predefined array
 *\param int ori, int srs, int imm
 *\return void
 **/
void ORI(int ori, int srs, int imm)
{
    array[ori] = array[srs] | imm;
    parity_flag(array[ori]);
    zero_flag(array[ori]);
    sign_flag(array[ori]);
}
/**
 *\fn void MOV(int srt,int imm)
 *\brief moves a number tinto the predefined array
 *\param int srt, int imm
 *\return void
 **/
void MOV(int srt, int imm)
{
    array[srt] = imm;
}
/**
 *\fn void SWP(int srs,int imm)
 *\brief swaps two of the elements in the predefined array
 *\param int srs, int srt
 *\return void
 **/
void SWP(int srs, int srt)
{
    int t = array[srs];
    array[srs] = array[srt];
    array[srt] = t;
}
/**
 *\fn void DUMP_REGS()
 *\brief prints the elements of the array as well as sobat
 *\param void
 *\return void
 **/
void DUMP_REGS()
{
    whitebold();
    printf("\nARRAY:");
    reset();
    for (int i = 0; i < 32; i++)
    {
        printf("%d ", array[i]);
    }
    whitebold();
    printf("\nSOBAT VAZIAT HA:");
    reset();
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", sobat[i]);
    }
}
/**
 *\fn void DUMP_REGS_F()
 *\brief prints the elements of the array as well as sobat in a file called regs.txt
 *\param void
 *\return void
 **/
void DUMP_REGS_F()
{
    FILE *file;
    file = fopen("regs.text", "w");
        fprintf(file, "\nsobat vaziat ha:");
        for (int i = 0; i < 8; i++)
        {
            fprintf(file, "%d ", sobat[i]);
        }
        fprintf(file, "\narray:");
        for (int i = 0; i < 32; i++)
        {
            fprintf(file, "%d", array[i]);
        }
    fclose(file);
}
/**
 *\fn void INPUT()
 *\brief takes an input from the user
 *\param void
 *\return void
 **/
void INPUT()
{
    printf("\nplease enter the value of array[0]:");
    scanf("%d", &array[0]);
}
/**
 *\fn void OUTPUT()
 *\brief prints the value of the first element in the predefined array
 *\param void
 *\return void
 **/
void OUTPUT()
{
    printf("\narray[0]: %d", array[0]);
}
/**
 *\fn void DIV(int srs, int srt)
 *\brief divides the inputs and saves the quotient and the remainder of the division
 *\param int srs, int srt
 *\return void
 **/
void DIV(int srs, int srt)
{
    int quotient = array[srt] / array[srs];
    int remainder = array[srt] % array[srs];
    array[srt] = quotient;
    array[srs] = remainder;
    parity_flag(array[srt]);
    zero_flag(array[srt]);
    sign_flag(array[srt]);
}
/**
 *\fn void MULL(int srt, int srs)
 *\brief multiplies two registers and saves the four higher bits in one input the four lower bits in the other
 *\param int srt, int srs
 *\return void
 **/
void MULL(int srt, int srs)
{
    int product = array[srt] * array[srs];
    int temp1 = 15;
    int temp2 = 240;
    array[srt] = product & temp2;
    array[srs] = product & temp1;
    array[srt] = array[srt] >> 4;
    parity_flag(product);
    zero_flag(product);
    sign_flag(product);
    overflow_flag_product(product, array[srt], array[srs]);
}
/**
 *\fn void errorandis(int a, int b, int c, char command[])
 *\brief checks for errors in the argument
 *\param int a, int b, int c, char command[]
 *\return int
 **/
int errorandis(int a, int b, int c, char command[], int line)
{
    int checkandis = 1;
    if (a < 0 || b < 0 || c < 0)
    {
        red();
        printf("\nerror:you have a negative argument in %s in line %d", command, line);
        reset();
        checkandis = 0;
    }
    if (a > 31 || b > 31 || c > 31)
    {
        red();
        printf("\nerror:your array in %s in line %d only has 32 elements", command, line);
        reset();
        checkandis = 0;
    }
    return checkandis;
}
/**
 * main
 * \section main
 * \brief is the main part of my project
 * \param int argc, char *argv[]
 * \return 0
 **/
int main(int argc, char *argv[])
{
    int countjmp = 0;  // is used in the jump section of int main
    char buffer[1000]; // saves each line of the file in each round of the while loop
    int checktotallines = 0;
    int error=0;
    FILE *enter;
    if (argc < 2)
    {
        printf("\nthe file name is: in.txt");
        enter = fopen("in.txt", "r");
    }
    else
    {
        printf("the file name is: %s\n", argv[1]);
        enter = fopen(argv[1], "r");
    }
    while (fscanf(enter, "%[^\n]\n", buffer) != EOF)
    {
        checktotallines++;
    }
    rewind(enter);
    while (fscanf(enter, "%[^\n]\n", buffer) != EOF)
    {
        error++;
        int result, one, two; /*is used as the inputs for simplicity
        and similarity of all functions in the main part*/
        for (int i = 0; i < sizeof(buffer); i++)
        {
            buffer[i] = toupper(buffer[i]);
        }
        char command[15] = {'\0'};
        for (j = 0; buffer[j] != ' ' && buffer[j] != '\n' && buffer[j] != '/' && buffer[j] != '\0'; j++)
        {
            command[j] = buffer[j];
        }
        if (command[0] != '\0')
        {
            if (strcmp(command, "EXIT") == 0)
            {
                exit(0);
            }
            else if (strcmp(command, "ADD") == 0)
            {
                sscanf(buffer, "ADD S%d, S%d, S%d", &result, &one, &two);
                if (errorandis(result, one, two, command, error) == 1)
                    ADD(result, one, two);
            }
            else if (strcmp(command, "SUB") == 0)
            {
                sscanf(buffer, "SUB S%d, S%d, S%d", &result, &one, &two);
                if (errorandis(result, one, two, command, error) == 1)
                    SUB(result, one, two);
            }
            else if (strcmp(command, "AND") == 0)
            {
                sscanf(buffer, "AND S%d, S%d, S%d", &result, &one, &two);
                if (errorandis(result, one, two, command, error) == 1)
                    AND(result, one, two);
            }
            else if (strcmp(command, "XOR") == 0)
            {
                sscanf(buffer, "XOR S%d, S%d, S%d", &result, &one, &two);
                if (errorandis(result, one, two, command, error) == 1)
                    XOR(result, one, two);
            }
            else if (strcmp(command, "OR") == 0)
            {
                sscanf(buffer, "OR S%d, S%d, S%d", &result, &one, &two);
                if (errorandis(result, one, two, command, error) == 1)
                    OR(result, one, two);
            }
            else if (strcmp(command, "ADDI") == 0)
            {
                sscanf(buffer, "ADDI S%d, S%d, %d", &result, &one, &two);
                if (errorandis(result, one, 0, command, error) == 1)
                    ADDI(result, one, two);
            }
            else if (strcmp(command, "SUBI") == 0)
            {
                sscanf(buffer, "SUBI S%d, S%d, %d", &result, &one, &two);
                if (errorandis(result, one, 0, command, error) == 1)
                    SUBI(result, one, two);
            }
            else if (strcmp(command, "ANDI") == 0)
            {
                sscanf(buffer, "ANDI S%d, S%d, %d", &result, &one, &two);
                if (errorandis(result, one, 0, command, error) == 1)
                    ANDI(result, one, two);
            }
            else if (strcmp(command, "XORI") == 0)
            {
                sscanf(buffer, "XORI S%d, S%d, %d", &result, &one, &two);
                if (errorandis(result, one, 0, command, error) == 1)
                    XORI(result, one, two);
            }
            else if (strcmp(command, "ORI") == 0)
            {
                sscanf(buffer, "ORI S%d, S%d, %d", &result, &one, &two);
                if (errorandis(result, one, 0, command, error) == 1)
                    ORI(result, one, two);
            }
            else if (strcmp(command, "MOV") == 0)
            {
                if (buffer[8] == 'S' || buffer[9] == 'S')
                {
                    sscanf(buffer, "MOV S%d, S%d", &result, &one);
                    if (errorandis(0, result, one, command, error) == 1)
                        MOV(result, array[one]);
                }
                else
                {
                    sscanf(buffer, "MOV S%d, %d", &result, &one);
                    if (errorandis(0, result, 0, command, error) == 1)
                        MOV(result, one);
                }
            }
            else if (strcmp(command, "SWP") == 0)
            {
                sscanf(buffer, "SWP S%d, S%d", &result, &one);
                if (errorandis(0, result, one, command, error) == 1)
                    SWP(result, one);
            }
            else if (strcmp(command, "DUMP_REGS") == 0)
            {
                DUMP_REGS();
            }
            else if (strcmp(command, "DUMP_REGS_F") == 0)
            {
                DUMP_REGS_F(error);
            }
            else if (strcmp(command, "INPUT") == 0)
            {
                INPUT();
            }
            else if (strcmp(command, "OUTPUT") == 0)
            {
                OUTPUT();
            }
            else if (strcmp(command, "JMP") == 0)
            {
                countjmp++;
                if (countjmp > 10)
                {
                    yellow();
                    printf("\nbackwards loop has ended in line %d.", error);
                    reset();
                    countjmp = 0;
                }
                else
                {
                    int countlines=1;
                    sscanf(buffer, "JMP %d", &result);
                    if (result <= 0)
                    {
                        red();
                        printf("\nerror in line %d,you can't jump to a zero or a negative line.", error);
                        reset();
                    }
                    else if (result > checktotallines)
                    {
                        red();
                        printf("\nerror in line %d,you only have %d lines.", error, checktotallines);
                        reset();
                    }
                    else
                    {
                        rewind(enter);
                        error = result -1;
                        while (countlines != result)
                        {
                            if (fgetc(enter) == '\n')
                            {
                                countlines++;
                            }
                        }
                    }
                }
            }
            else if (strcmp(command, "SKIE") == 0)
            {
                sscanf(buffer, "SKIE S%d, S%d", &result, &one);
                if (errorandis(0, result, one, command, error) == 1)
                {
                    if (array[result] == array[one])
                    {
                        fscanf(enter, "%[^\n]\n", buffer);
                    }
                    error++;
                }
            }
            else if (strcmp(command, "DIV") == 0)
            {
                sscanf(buffer, "DIV S%d, S%d", &result, &one);
                if (errorandis(0, result, one, command, error) == 1)
                    DIV(result, one);
            }
            else if (strcmp(command, "MULL") == 0)
            {
                sscanf(buffer, "MULL S%d, S%d", &result, &one);
                if (errorandis(0, result, one, command, error) == 1)
                    MULL(result, one);
            }
            else if (strcmp(command, "PUSH") == 0)
            {
                sscanf(buffer, "PUSH S%d", &result);
                if (errorandis(0, result, 0, command, error) == 1)
                    PUSH(result);
            }
            else if (strcmp(command, "POP") == 0)
            {
                sscanf(buffer, "POP S%d", &result);
                if (errorandis(0, result, 0, command, error) == 1)
                    POP(result);
            }
            else
            {
                red();
                printf("\nwrong input in line %d,error in command.", error);
                reset();
            }
        }
    }
    fclose(enter);
    return 0;
}