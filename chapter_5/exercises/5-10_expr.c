/* Evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPERAND_STACK_SIZE 1024
#define MAX_OPERATOR_STACK_SIZE 1024

double operand_stack[MAX_OPERAND_STACK_SIZE];
unsigned int operand_stack_size = 0;

int main(int argc, char *argv[])
{
    /* if argc is odd (that is argc - 1 is even) the inputs are invalid: operators are all binary operators so need n+1 operators for n operands.
     * a minimum of 4 arguments are required: program name, 2 operands and the operator. */
    if(argc % 2 || argc < 4) {
        printf("Invalid number of arguments supplied: expected n+1 operands followed by n operators");
        exit(EXIT_FAILURE);
    }    


    while(--argc > 0 && operand_stack_size <= MAX_OPERAND_STACK_SIZE && isdigit(**(++argv))) {
        operand_stack[operand_stack_size++] = atof(*argv);
    }

    printf("operand_stack_size: %d\n", operand_stack_size);
    for(int i = 0; i < operand_stack_size; ++i) {
        printf("%f\n", operand_stack[i]);
    }

    int c;
    double result = 0;
    double operator_count = 0;
    double operand_count = operand_stack_size;
    /* loop until a non operator is encountered or sufficient operators for the given operands is encountered */
    while(operand_count - operator_count > 0 && ((c = **argv) == '+' || c == '-' || c == '*' || c == '/')) {
        printf("%c\n", c);
        if(operator_count == 0) {
            double operand_a = operand_stack[--operand_stack_size];
            double operand_b = operand_stack[--operand_stack_size];
            switch (c) {
                case '+':
                    result = operand_a + operand_b;
                    break;
                case '-':
                    result = operand_a - operand_b;
                    break;
                case '*':
                    result = operand_a * operand_b;
                    break;
                case '/':
                    result = operand_a / operand_b;
                    break;
                default:
                    break;
            }
        }
        else {
            double operand = operand_stack[--operand_stack_size];
            switch (c) {
                case '+':
                    result += operand;
                    break;
                case '-':
                    result -= operand;
                    break;
                case '*':
                    result *= operand;
                    break;
                case '/':
                    result /= operand;
                    break;
                default:
                    break;
            }

        }
        ++argv;
        ++operator_count;
    }
    printf("Result: %10.2f\n", result);
    return EXIT_SUCCESS;
}
