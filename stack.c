#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STK_SIZE 100

struct Stack{
   int   ptr;
   float *elements;
} stk;

void  initStack(void);
void  freeStack(void);
void  push(float);
float pop(void);
float top(void);

/* ********************************** */
main(){
   float op1, op2;
   char  expr[256];
   char* nextPtr;

  // allocate space for stack
   initStack();

   printf("Enter postfix expression to be evaluated: ");
   gets(expr);

   nextPtr = strtok(expr," ");  
   while (nextPtr != NULL) {
      printf("Token: %s\n", nextPtr);
      printf("atof: %f\n\n", atof(nextPtr));
      if (atof(nextPtr) != 0) {
         push(atof(nextPtr));
      } 
      else if (*nextPtr == '+') { // if token is addition
         op1=pop();
         op2=pop();
         push(op1+op2);
      }
      else if (*nextPtr == '-') { // if token is subtraction
         op1=pop();
         op2=pop();
         push(op2-op1);
      }
      else if (*nextPtr == '*') { // if token is multiplication
         op1=pop();
         op2=pop();
         push(op1*op2);
      }
      else if (*nextPtr == '/') { // if token is division
         op1=pop();
         op2=pop();
         push(op2/op1);
      }
      
      nextPtr = strtok(NULL," ");
   }

  // display the expression result
   printf("Result: %f\n\n", top());

  // deallocate space
   freeStack();

}
   
/* ********************************** */
void initStack(){
   stk.elements = calloc(MAX_STK_SIZE, sizeof(float));
   stk.ptr = 0;
}

/* ********************************** */
void push(float x){
   stk.elements[stk.ptr++] = x;
}

/* ********************************** */
float pop(){
   return stk.elements[--stk.ptr];
}

/* ********************************** */
float top(){
   return stk.elements[stk.ptr-1];
}

/* ********************************** */
void freeStack(){
   free(stk.elements);
}