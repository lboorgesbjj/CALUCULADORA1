#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX 512

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isFunction(const char *str) {
    return strcmp(str, "log") == 0 || strcmp(str, "sen") == 0 || strcmp(str, "cos") == 0;
}

float performOperation(char op, float a, float b) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Erro: Divisão por zero.\n");
                return -1; 
            }
            return a / b;
        case '^': return pow(a, b);
        default: return -1; 
    }
}

char *getFormaInFixa(char *Str) {
    static char infixa[MAX];
    char stack[MAX][MAX];
    int top = -1;

    for (int i = 0; i < strlen(Str); i++) {
        if (Str[i] == ' ') continue; 

        if (!isOperator(Str[i]) && !isalpha(Str[i])) {
            char operand[16];
            int k = 0;
            while (Str[i] != ' ' && Str[i] != '\0') {
                operand[k++] = Str[i++];
            }
            operand[k] = '\0';
            strcpy(stack[++top], operand);
            i--; 
        } else if (isalpha(Str[i])) {
            char func[4];
            int j = 0;
            while (Str[i] != ' ' && Str[i] != '\0') {
                func[j++] = Str[i++];
            }
            func[j] = '\0';

            if (isFunction(func)) {
                char op1[MAX];
                strcpy(op1, stack[top--]);
                sprintf(stack[++top], "%s(%s)", func, op1);
            }
            i--; 
        } else {
            char op2[MAX], op1[MAX];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            sprintf(stack[++top], "(%s %c %s)", op1, Str[i], op2);
        }
    }

    strcpy(infixa, stack[top]);
    return infixa;
}

float getValor(char *Str) {
    float stack[MAX];
    int top = -1;
    char temp[MAX];
    int j = 0;

    for (int i = 0; i < strlen(Str); i++) {
        if (Str[i] == ' ') continue; 

        if (!isOperator(Str[i]) && !isalpha(Str[i])) {
            char number[16];
            int k = 0;
            while (Str[i] != ' ' && Str[i] != '\0') {
                number[k++] = Str[i++];
            }
            number[k] = '\0';
            stack[++top] = atof(number);
            i--; 
        } else if (isalpha(Str[i])) {
            char func[4];
            int j = 0;
            while (Str[i] != ' ' && Str[i] != '\0') {
                func[j++] = Str[i++];
            }
            func[j] = '\0';

            float a = stack[top--];
            if (strcmp(func, "log") == 0)
                stack[++top] = log10(a);  
            else if (strcmp(func, "sen") == 0)
                stack[++top] = sin(a * M_PI / 180.0);  
            else if (strcmp(func, "cos") == 0)
                stack[++top] = cos(a * M_PI / 180.0);  
            i--; 
        } else {
            float b = stack[top--];
            float a = stack[top--];
            float result = performOperation(Str[i], a, b);

            if (result == -1) {
                return -1; 
            }

            stack[++top] = result;
        }
    }

    return stack[top];
}
