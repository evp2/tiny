/**
* \file stack.c
* \brief stack.c provides struct for a stack and the following functions
* \author Mantis, Pomponio, Scuderi, Smith
*/

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
/** \brief Main application entry point.
*
* \param nothing
* \returns nothing
*/
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
      else if (*nextPtr == '=') { // if token is assignment
         op1=pop();
         op2=pop();
         op1=op2;
         push(op2);
      }
    /*TODO:multi-character character constants  ==, !=, &&, ||
     *#define EQU_OP in tinylex? 
     */
      nextPtr = strtok(NULL," ");
   }

  // display the expression result
   printf("Result: %f\n\n", top());

  // deallocate space
   freeStack();

}
   
/* ********************************** */

/** \brief calloc memory for stack.
*
* \param args nothing
* \returns nothing
*/
void initStack(){
   stk.elements = calloc(MAX_STK_SIZE, sizeof(float));
   stk.ptr = 0;
}

/* ********************************** */
/** \brief pushes an item onto the top of the stack 
*
* \param args item to be pushed
* \returns nothing
*/
void push(float x){
   stk.elements[stk.ptr++] = x;
}

/* ********************************** */
 /** \brief returns the item at the top of the stack and removes it.
*
* \param args nothing
* \returns returns the item at the top of the stack
*/
float pop(){
   return stk.elements[--stk.ptr];
}

/* ********************************** */
 /** \brief shows the item at the top of the stack.
*
* \param args nothing
* \returns returns the item at the top of the stack
*/
float top(){
   return stk.elements[stk.ptr-1];
}

/* ********************************** */
 /** \brief free memory for stack.
*
* \param args nothing
* \returns nothing
*/
void freeStack(){
   free(stk.elements);
}