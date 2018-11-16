/**
* \file tinylex.c
* \brief tinylex.c performs lexical analysis
* \author Mantis, Pomponio, Scuderi, Smith
*/
/* ******************************************************************** */
/* tinylex.c performs lexical analysis                                  */
/* ******************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 10000


/* ******************************************************************** */
/* Global declarations variables                                        */
/* ******************************************************************** */
int charClass;
char lexeme[MAX_LEN];
char nextChar;
int  lexLen;
int  token;
int  nextToken;
FILE *in_fp, *fopen();


/* ******************************************************************** */
/* Function declarations                                                */
/* ******************************************************************** */
void addChar();
void getChar();
void getNonBlank();
int lex();


/* ******************************************************************** */
/* Character classes                                                    */
/* ******************************************************************** */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99


/* ******************************************************************** */
/* Token codes                                                          */
/* ******************************************************************** */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LEFT_BRACE 27
#define RIGHT_BRACE 28
#define COMMENT 29

/* ******************************************************************** */
/* main driver                                                          */
/* ******************************************************************** */

/** \brief Main application entry point.
*
* \param args <file>.tiny file to perform lexical analysis   
* \returns nothing
*/

int main(int argc, char **argv) {

   /* open the input data file and process contents */
   if (argc != 2) {
        printf("Usage: front <filename> \n");
        exit(-1);
   }
   if ((in_fp = fopen(argv[1],"r")) == NULL)
       printf("ERROR - cannot open %s in \n", argv[1]);
   else {
      getChar();
      do {
        lex();
      } while (nextToken != EOF);
   }
   return 0;
}


/* ***************************************************************************** */
/* lookup - a function to lookup operators and parentheses  and return the token */
/* ***************************************************************************** */

/** \brief a function to lookup operators and parentheses and return the token.
*
* \param args operator to be looked up
* \returns the token
*/
int lookup(char ch){

   switch(ch){
     case '(':
          addChar();
          nextToken = LEFT_PAREN;
          break;

     case ')':
          addChar();
          nextToken = RIGHT_PAREN;
          break;

     case '{':
          addChar();
          nextToken = LEFT_BRACE;
          break;

     case '}':
          addChar();
          nextToken = RIGHT_BRACE;
          break;

     case '+':
          addChar();
          nextToken = ADD_OP;
          break;

     case '-':
          addChar();
          nextToken = SUB_OP;
          break;

     case '=':
          addChar();
          nextToken = ASSIGN_OP;
          break;

     case '*':
          addChar();
          nextToken = MULT_OP;
          break;

     case '/':
          addChar();
          nextToken = DIV_OP;
          break;

     case '#':
          addChar();
          nextToken = COMMENT;
          break;

     default:
          addChar();
          nextToken = EOF;
          break;
   }

   return nextToken;
}


/* ***************************************************************************** */
/* addChar - a function to add next char to lexeme                               */
/* ***************************************************************************** */
/** \brief a function to add next char to lexeme 
*
* \param args none
* \returns nothing
*/
void addChar(){

   if (lexLen <= MAX_LEN-2){
         lexeme[lexLen++] = nextChar;
         lexeme[lexLen] = 0;
   } else {
        printf("Error - lexeme too long \n");
   }
}


/* ***************************************************************************** */
/* getChar - gets the next char of input and determine its character class       */
/* ***************************************************************************** */
/** \brief gets the next char of input and determine its character class
*
* \param args none
* \returns nothing
*/
void getChar(){

   if ((nextChar = getc(in_fp)) != EOF){
       if (isalpha(nextChar))
          charClass = LETTER;
       else if (isdigit(nextChar))
          charClass = DIGIT;
       else charClass = UNKNOWN;
  } else
    charClass = EOF;
}


/* ***************************************************************************** */
/* getNonBlank - class getChar until it returns a non-whitespace character       */
/* ***************************************************************************** */
/** \brief gets class getChar until it returns a non-whitespace character
*
* \param args none
* \returns nothing
*/
void getNonBlank(){

   while (isspace(nextChar))
      getChar();
}


/* ***************************************************************************** */
/* lex - a simple lexical analyzer for arithmetic expressions                    */
/* ***************************************************************************** */
/** \brief a simple lexical analyzer for arithmetic expressions  
*
* \param args none
* \returns nextToken
*/
int lex(){

   lexLen = 0;
   getNonBlank();

   switch (charClass){
      case LETTER:
           /* parse identifiers */
           addChar();
           getChar();
           while (charClass == LETTER || charClass == DIGIT){
              addChar();
              getChar();
           }
           nextToken = IDENT;
           break;

     case DIGIT:
          /* parse integer literals */
          addChar();
          getChar();
          while (charClass == DIGIT){
             addChar();
             getChar();
          }
          nextToken = INT_LIT;
          break;

    case UNKNOWN:
         /* parenthese and operators */
         lookup(nextChar);
         getChar();
         break;

    case EOF:
         /* EOF */
         nextToken = EOF;
         lexeme[0] = 'E';
         lexeme[1] = 'O';
         lexeme[2] = 'F';
         lexeme[3] = 0;
         break;
} /* end of switch */

  printf("Next token is: %d, next lexeme is %s\n", nextToken, lexeme);
  return nextToken;

} /* end lex */

