#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct MyStack
{
    char contentA[50];
    char contentB[50][3];
    int size;
    int top;
};



bool isEmpty(struct MyStack*);
bool isEmpty(struct MyStack*);
void push(struct MyStack*, char*, bool);
void * pop(struct MyStack *stack, bool isA);
char top(struct MyStack *stack);
struct MyStack* createStack();
char* read();
void solve(char operator, char* a, char* b);
void concat(char*, char);
void subMachine();
int prepareSolve(struct MyStack *stack_a, struct MyStack *stack_b);


char word[50];
int len = 0;
int i = 0;
int t = 0;

int main(){

    gets(word);

    read();
    
    return 0;
}


bool isEmpty(struct MyStack *stack){
    return stack->top == -1;
}


bool isFull(struct MyStack *stack){
    return stack->top == 49;
}

void push(struct MyStack *stack, char * value, bool isA){

    if(isA){
        stack->contentA[stack->size] = value[i];
        stack->size++;
        stack->top++;
        return;
    }

    strcpy(stack->contentB[stack->size], value);
    stack->size++;
    stack->top++;
}

void concat(char* vec, char t){

    vec[1] = t;
    vec[2] = '\0';
    return;
}
void * pop(struct MyStack *stack, bool isA){


    if(isA){
        stack->size--;
        return &(stack->contentA[stack->top--]);
    }

    stack->size--;

    return stack->contentB[stack->top--];
}

struct MyStack* createStack(){

    struct MyStack* stack = (struct MyStack*) malloc(sizeof(struct MyStack));
    stack->size = 0;
    stack->top = -1;
    return stack;
}

char* read(){
    
    struct MyStack *stack_a = createStack();
    struct MyStack *stack_b = createStack();

    while(word[i] != '\0'){
        if(word[i] >= '0' && word[i] <= '9'){

                char temp[2] = {word[i], '\0'};
                push(stack_b, temp, false);
                i++;
            }
            else{
                if(word[i] == '+' || word[i] == '-' || word[i] == '*' || word[i] == '/'){
                    if(stack_a->top == -1){
                            push(stack_a, word, true);
                            i++;
                    }else
                        if((word[i] == '+' || word[i] == '-') && 
                        (stack_a->contentA[stack_a->top] == '+' || 
                        stack_a->contentA[stack_a->top] == '-' || 
                        stack_a->contentA[stack_a->top] == '*' || 
                        stack_a->contentA[stack_a->top] == '/')){

                            //printf("RESOLVE PENDENDICA 1");
                            char vec[3] = "T";
                            prepareSolve(stack_a, stack_b);
                            concat(vec, (t + '0'));
                            push(stack_b, vec, false);

                        }
                        else{
                            if((word[i] == '*' || word[i] == '/') &&
                            (stack_a->contentA[stack_a->top] == '*' || 
                            stack_a->contentA[stack_a->top] == '/')){
                            
                                //printf("RESOLVE PENDENCIA 2");
                                char vec[3] = "T";
                                prepareSolve(stack_a, stack_b);
                                concat(vec, (t + '0'));
                                push(stack_b, vec, false);
                            }
                            else{

                                push(stack_a, word, true);
                                i++;
                            }
                        }       
                }
                else{
                    if(word[i] == '('){
                        i++;
                        char * ret = read(stack_a, stack_b);
                        push(stack_b, ret, false);
                    }else{
                        if(word[i] == ')'){
                            while(stack_a->top != -1){

                                char vec[3] = "T";
                                prepareSolve(stack_a,stack_b);
                                concat(vec, (t + '0'));
                                push(stack_b, vec, false);                    
                            }
                            i++;                    
                            return (char*)pop(stack_b, false);
                        }
                    }
                }
            }
    }
    while(stack_a->top != -1){

        char vec[3] = "T";
        prepareSolve(stack_a,stack_b);
        concat(vec, (t + '0'));
        push(stack_b, vec, false);                  
    }          
}

int prepareSolve(struct MyStack *stack_a, struct MyStack *stack_b){

    char* a = (char*)pop(stack_b, false);
    char* b = (char*)pop(stack_b, false);

    char operator = *((char*) pop(stack_a, true));

    solve(operator, a, b);
}

void solve(char operator, char* a, char* b){

    t++;
    if(operator == '+'){
        printf("\nLDA %s\nADA %s\nSTA T%d\n\n", b, a, t);
    }
    else{
        if(operator == '-'){
            printf("\nLDA %s\nSUB %s\nSTA T%d\n\n", b, a, t);
        }
        else{
            if(operator == '*'){
                printf("\nLDA %s\nMUL %s\nSTA T%d\n\n", b, a, t);
            }
            else{
                if(operator == '/'){
                    printf("\nLDA %s\nDIV %s\nSTA T%d", b, a, t);
                }
            }
        }
    }
}

