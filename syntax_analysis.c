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
char *read_line;


/* Function declarations */
void addChar();
void getCharArray(char* x);
void getChar();
void getLine();
void getNonBlank(char* z);
void validExpr();
int lex(char* i);

/* Character classes */
#define LETTER 0
#define DIGIT 1
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
main() {
/* Open the input data file and process its contents */
 if ((file = fopen("data.txt", "r")) == NULL)
  printf("ERROR - cannot open data.txt \n");
 else {
   getLine();
 }
}

/* getLine - a function to grab entire line before scanning individual chars */
void getLine() {
  while((read = getline(&line, &len, file)) != -1){
      getCharArray(line);
      // do {
      //   //lex(line);
      // } while (nextToken != EOF);
    }
  fclose(file);
  if(line)
    free(line);
  exit(EXIT_SUCCESS);
}

/*****************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getCharArray(char* x) {
  for(int i=0; x[i] != '\0'; i++){
    nextChar = x[i];
    getChar();
    // do {
    //   lex();
    // } while(nextToken != EOF);
  }
}


void getChar() {
  if(nextChar != EOF){
   if (isalpha(nextChar))
    charClass = LETTER;
   else if (isdigit(nextChar))
    charClass = DIGIT;
   else charClass = UNKNOWN;
 }else{
  charClass = EOF;
  }
  printf("%c\n", nextChar);
}


/*****************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(char* z) {
  for(int i=0; z[i] != '\0'; i++){
   while (isspace(z[i]))
    getChar(z[i]);
  }
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(char* i) {
 lexLen = 0;
 getNonBlank(i);
 switch (charClass) {
  /* Parse identifiers */
   case LETTER:
     //addChar();
     getChar(i);
     while (charClass == LETTER || charClass == DIGIT) {
       //addChar();
       getChar(i);
     }
     nextToken = IDENT;
     break;
  /* Parse integer literals */
   case DIGIT:
     //addChar();
     getChar(i);
     while (charClass == DIGIT) {
       //addChar();
       getChar(i);
     }
     nextToken = INT_LIT;
     break;
  /* Parentheses and operators */
   case UNKNOWN:
     //lookup(y);
     getChar(i);
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
 printf("Next token is: %d, Next lexeme is %s\n",
 nextToken, lexeme);
 return nextToken;
} /* End of function lex */
