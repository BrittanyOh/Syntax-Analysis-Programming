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
void getChar(char* x);
void getLine();
void getNonBlank();
void validExpr();
int lex();
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
   do {
     //lex();
   } while (nextToken != EOF);
 }
}

/* getLine - a function to grab entire line before scanning individual chars */
void getLine() {
  while((read = getline(&line, &len, file)) != -1){
      getChar(line);
    }
  fclose(file);
  if(line)
    free(line);
  exit(EXIT_SUCCESS);
}

/*****************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(char* x) {
  for(int i=0; x[i] != '\0'; i++){
   if (isalpha(x[i]))
    charClass = LETTER;
   else if (isdigit(x[i]))
    charClass = DIGIT;
   else charClass = UNKNOWN;
 }
 if(x[i] == EOF){
  charClass = EOF;
}
}
