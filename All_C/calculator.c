#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "LinkList.h"

/* gcc calculator.c -o calculator -L./ -lLinkList */


int hash(char cal){
    switch (cal){
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '(':
            return 4;
        case ')':
            return 5;
        case '#':
            return 6;
        default:
            return -1;
    }
}

int operate(char operator, int op1, int op2){    // DisplayList(operator);
    // DisplayList(operand);
    switch (operator){
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        default:
            exit(1);
    }
}

int priority(int op_instack, int op_insert){
    /* 1: op_instack > op_insert */
    /* -1: op_instack < op_insert */
    /* 0: op_instack == op_insert */
    const int priority[7][7] = {
        {1, 1, -1, -1, -1, 1, 1},
        {1, 1, -1, -1, -1, 1, 1},
        {1, 1, 1, 1, -1, 1, 1},
        {1, 1, 1, 1, -1, 1, 1},
        {-1, -1, -1, -1, -1, 0, 0},
        {1, 1, 1, 1, 0, 1, 1},
        {-1, -1, -1, -1, -1, 0, 0}
    };
    return priority[hash(op_instack)][hash(op_insert)];
}

int reader(char *cal, int *index, int *is_num){
    int op;

    op = cal[*index];

    /* Process operator */
    if(hash(op) != -1){
        if(*is_num == 0 && !(cal[*index] == '(' || cal[*index-1] == ')')){
            printf("SyntaxError: Two consecutive operators.");
            exit(0);
        }
        
        *is_num = 0;
        *index += 1;
        return op;
    }
    /* Process operand */
    if(*is_num == 1){
        printf("SyntaxError: Two consecutive operands.");
        exit(0);
    }

    *is_num = 1;
    op = 0;
    while(cal[*index] != '\0' && hash(cal[*index]) == -1){
        if(cal[*index] - '0' > 9 || cal[*index] - '0' < 0){
            printf("ValueError: Invalid character!");
            exit(1);
        }
        op = cal[*index] - '0' + op * 10;
        *index += 1;
    }
    return op;
}

int insert(int element, int is_num, LinkNode *operator, LinkNode *operand){
    int last_element, pri, op, op1, op2, result;
    // DisplayList(operator);
    // DisplayList(operand);
    if(is_num){
        Insert(operand, 1, element);
        // printf("num: %d\n", element);
    }
    else{
        // printf("op: %c\n", element);

        last_element = GetElement(operator, 1);
        pri = priority(last_element, element);
        // printf("%d\n", pri);
        while(pri == 1 && !IsEmpty(operator) && !IsEmpty(operand)){
            op = ListPop(operator, 1);
            op2 = ListPop(operand, 1);
            op1 = ListPop(operand, 1);
            result = operate(op, op1, op2);
            Insert(operand, 1, result);
            last_element = GetElement(operator, 1);
            pri = priority(last_element, element);
        }

        if(pri == -1){
            Insert(operator, 1, element);
        }
        else if(pri == 0){
            ListPop(operator, 1);
        }
    }
}

char * delete_blank(char *cal, int *length){
    int * list;
    LinkNode * L;

    list = CharToInt(cal, *length);
    L = CreateList(list, *length, 0);
    DeleteAll(L, ' ');
    list = ToArray(L, length);
    cal = IntToChar(list, *length);
    return cal;
}

int calculator(char *cal, int length){
    LinkNode *operand, *operator;
    int is_num = 0, index = 0, element;

    cal = delete_blank(cal, &length);

    cal[length] = '#';
    cal[length + 1] = '\0';

    operand = (LinkNode *) malloc(sizeof(LinkNode));
    operator = (LinkNode *) malloc(sizeof(LinkNode));
    Insert(operator, 1, '#');
    
    while(cal[index] != '\0'){
        // printf("%d\n", index);
        element = reader(cal, &index, &is_num);
        insert(element, is_num, operator, operand);
    }
    // DisplayList(operator);
    // DisplayList(operand);
    return GetElement(operand, 1);

}


int main(){
    char c[100] = {"12 + 12 9.0 + (20 - 12) * 5 / 2"};
    int result;
    result = calculator(c, strlen(c));
    printf("%d\n", result);
}