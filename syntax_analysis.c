/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* Global declarations */
/* Variables */
int charClass;
int i = 0;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *file, *fopen();
char * line = NULL;
size_t len = 0;
size_t read;
string arg;


/* Function declarations */
void addChar();
void getChar();
void getLine();
void getNonBlank();
void validExpr();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define NEG_DIGIT 100
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/******************************************************/
/* main driver */
main(int argc, char *argv[]) {
/* Open the input data file and process its contents */
arg = argv[0];
 if ((file = fopen(arg, "r")) == NULL)
  printf("ERROR - cannot open %s \n", argv[0]);
 else {

   getLine();
 }
}

/* getLine - a function to grab entire line before scanning individual chars */
void getLine() {
  while((read = getline(&line, &len, file)) != -1){
      getChar();
      do {
        lex();
     } while (nextToken != EOF);
   }
  fclose(file);
  if(line)
    free(line);
  exit(EXIT_SUCCESS);
}

/*****************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar() {
  if ((nextChar = line[i]) != '\0') {
    if (isalpha(nextChar))
      charClass = LETTER;
    else if (isdigit(nextChar) > 0 )
      charClass = DIGIT;
    else charClass = UNKNOWN;
    i++;
  }else{
  charClass = EOF;
  i = 0;
  }
}


/*****************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank() {
   while (isspace(nextChar))
    getChar();
  }

  /*****************************************************/
  /* addChar - a function to add nextChar to lexeme */
  void addChar() {
   if (lexLen <= 98) {
     lexeme[lexLen++] = nextChar;
     lexeme[lexLen] = 0;
   }
   else
    printf("Error - lexeme is too long \n");
  }



  /*****************************************************/
  /* lookup - a function to lookup operators and parentheses
   and return the token */
  int lookup(char ch) {
   switch (ch) {
     case '(':
       addChar();
       nextToken = LEFT_PAREN;
       break;

     case ')':
       addChar();
       nextToken = RIGHT_PAREN;
       break;

     case '+':
       addChar();
       nextToken = ADD_OP;
       break;

     case '-':
       addChar();
       nextToken = SUB_OP;
       break;

     case '*':
       addChar();
       nextToken = MULT_OP;
       break;

     case '/':
       addChar();
       nextToken = DIV_OP;
       break;

     default:
       addChar();
       nextToken = EOF;
       break;
    }
   return nextToken;
  }

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex() {
 lexLen = 0;
 getNonBlank();
 switch (charClass) {
  /* Parse identifiers */
   case LETTER:
     addChar();
     getChar();
     while (charClass == LETTER || charClass == DIGIT) {
       addChar();
       getChar();
     }
     nextToken = IDENT;
     break;
  /* Parse integer literals */
   case DIGIT:
     addChar();
     getChar();
     while (charClass == DIGIT) {
       addChar();
       getChar();
     }
     nextToken = INT_LIT;
     break;
  /* Parentheses and operators */
   case UNKNOWN:
     lookup(nextChar);
     getChar();
     break;

  /* EOF */
   case EOF:
     nextToken = EOF;
     lexeme[0] = 'E';
     lexeme[1] = 'O';
     lexeme[2] = 'F';
     lexeme[3] = 0;
     break;
 } /* End of switch */
 printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
 if(nextToken == 100 ){
   perror("Not a valid expression!");
 }else if(nextToken == EOF){
   printf("%s \n************************\nValid Expression\n************************\n\n",line);
 }
 return nextToken;
} /* End of function lex */
