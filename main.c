/*COP 3502C Midterm Assignment One
This program is written by: Esteban Brugal*/

/*This program takes an expression in infix, converts it to postfix with a stack,
and then evaluates the expression. Also checks for balance in parenthesis.
Doesn't account for random symbols and letters*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define size 100

struct stack{
    char items[size];
    int top;
}typedef stack;

struct stackInt{
    int items[size];
    int top;
}typedef stackInt;

void push(stack* , char);
void pushInt(stackInt*, int);
int popInt(stackInt*);
char peek(stack*);
char pop(stack*);
void isFull(stack*);
void isEmpty(stack*);
void init(stack*);
void display(stack*);
int isBalancedParenthesis(char*);
char* convertToPostfix(char  *);
int getOperatorPriority(char );
int  isOperator(char );
int convertToInt(char );
int calculate(int a, int b, char op);
void  evaluate(char*);
char* menu();


int main()
{
    char* str;
    while(strcmp(str=menu(), "exit")!=0){
        if(isBalancedParenthesis(str)){
            char* postfix = convertToPostfix(str);
            printf("infix: %s", str);
            printf("\nparenthesis: balanced");
            printf("\npostfix: %s", postfix);
            evaluate(postfix);
            free(postfix);
        }else{
            printf("infix: %s", str);
            printf("\nparenthesis: unbalanced\npostfix: n/a\nvalue: n/a\n");
        }
        free(str);
    }
    free(str);
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void push(stack* stack , char x){
    if(stack->top==size-1){
        printf("Stack is full");
    }else{
        (stack->top)++;
        stack->items[stack->top] = x;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void pushInt(stackInt* stack , int x){
    if(stack->top==size-1){
        printf("Stack is full");
    }else{
        (stack->top)++;
        stack->items[stack->top] = x;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char pop(stack* stack){
    if(stack->top<0){
        printf("Stack is empty.");
        return 'X';
    }
    return stack->items[stack->top--];
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int popInt(stackInt* stack){
    if(stack->top<0){
        printf("Stack is empty.");
        return 'X';
    }
    return stack->items[stack->top--];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
char peek(stack* stack){
    if(stack->top<0){
        printf("Stack is empty.");
        return 'X';
    }
    return stack->items[stack->top];
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void isFull(stack* stack){
    if(stack->top==size-1)
        printf("\nStack is full.");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void isEmpty(stack* stack){
    if(stack->top<0)
        printf("\nStack is empty.");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void init(stack* stack){
    stack->top=-1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void display(stack* stack){
    if(stack->top<0){
        printf("Stack is empty");
    }else{
        for(int i=0; i<=stack->top; i++){
            printf("%c ", stack->items[i]);
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int isBalancedParenthesis(char* word){
    stack balance;
    init(&balance);
    for(int i=0; i<strlen(word);i++){
        if(word[i]=='('||word[i]=='['||word[i]=='{'){
            push(&balance, word[i]);
        }else if(word[i]==')'||word[i]=='}'||word[i]==']'){
            if(balance.top<0){
                return 0;
            }else{
                char check = pop(&balance);
                switch (check){
                    case '{':   if('}'!=word[i]){
                                    return 0;
                                }
                                break;
                    case '(':   if(')'!=word[i]){
                                    return 0;
                                }
                                break;
                    case '[':   if(']'!=word[i]){
                                    return 0;
                                }
                }
            }
        }
    }
    if(balance.top==-1){
        return 1;
    }else{
        return 0;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char* convertToPostfix(char* math){
    char* postfix = calloc(size, sizeof(char));
    stack operator;
    init(&operator);
    int postCount=0;
    for(int i=0; i<strlen(math); i++){
        if(math[i]-0==32){

        }else if(isOperator(math[i])==0){
            int count=0;
            int j=i+1;
            while(1){
                if(isdigit(math[j])!=0){
                    count++;
                    j++;
                }else break;
            }
            postfix[postCount] = math[i];
            postCount++;
            int k=i+1;
            while(count!=0){
                postfix[postCount] = math[k];
                postCount++;
                k++;
                count--;
                i++;
            }
            strcat(postfix, " ");
            postCount++;
        }else{
            if(operator.top<0)
                push(&operator, math[i]);
            else if(math[i]=='(')
                push(&operator, math[i]);
            else if(math[i]==')'){
                while(1){
                    char last = pop(&operator);
                    if(last=='('){
                        break;
                    }
                    postfix[postCount] = last;
                    postCount++;
                    strcat(postfix, " ");
                    postCount++;
                }
            }else{
                int priority = getOperatorPriority(math[i]);
                while(1){
                    if(operator.top<0){
                        push(&operator, math[i]);
                        break;
                    }
                    char last = peek(&operator);
                    if(priority<=getOperatorPriority(last)){
                        char popped = pop(&operator);
                        postfix[postCount] = popped;
                        postCount++;
                        strcat(postfix, " ");
                        postCount++;
                    }else{
                        push(&operator, math[i]);
                        break;
                    }
                }
            }
        }
    }
    while(operator.top!=-1){
        postfix[postCount] = pop(&operator);
        postCount++;
        strcat(postfix, " ");
        postCount++;
    }
    return postfix;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int getOperatorPriority(char c){
    if(c=='+'||c=='-')
        return 0;
    if(c=='*'||c=='/'||c=='%')
        return 1;
    if(c=='^')
        return 2;
    if(c=='(')
        return -1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int isOperator(char  c){
    if(c=='+'||c=='-'||c=='%'||c=='/'||c=='*'||c=='^'||c=='('||c==')')
        return 1;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int convertToInt(char c){
    int x = c - '0';
    return x;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int calculate(int a, int b, char op){
    switch (op){
        case '+':   return a+b; break;
        case '-':   return a-b; break;
        case '^':   return pow(a,b); break;
        case '*':   return a*b; break;
        case '/':   return a/b; break;
        case '%':   return a%b; break;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void  evaluate(char* post){
    stackInt ans;
    ans.top=-1;
    for(int i=0; i<strlen(post); i++){
        if(post[i]==32){

        }else if(isOperator(post[i])==0){
            float count=1;
            if(isdigit(post[i]+1)!=0){
                int j=i+1;
                while(1){
                    if(isdigit(post[j])!=0){
                        count++;
                        j++;
                    }else break;
                }
            }
            int x = convertToInt(post[i]);
            while(count!=1){
                x = x*10+convertToInt(post[i+1]);
                i++;
                count--;
            }
            pushInt(&ans, x);
        }else{
            int B = popInt(&ans);
            int A = popInt(&ans);
            int c = calculate(A, B, post[i]);
            pushInt(&ans, c);
        }
    }
    printf("\nvalue: %d\n",  popInt(&ans));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char*  menu(){
    char c;
    char ans;
    while(1){
        printf("Enter e to enter an infix, enter x to exit the program.\n");
        scanf("%c", &ans);
        while ((c = getchar()) != '\n' && c != EOF);
        if(ans=='e'){
            char* string = malloc(size*sizeof(char));
            scanf("%[^\n]s", string);
            while ((c = getchar()) != '\n' && c != EOF);
            return string;
        }
        if(ans=='x'){
            char* string = malloc(5*sizeof(char));
            strcpy(string, "exit");
            return string;
        }
    }

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

