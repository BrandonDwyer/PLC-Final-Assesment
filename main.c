/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Global declarations */
/* Variables */
int charClass;

const int SIZE = 32;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
void expr(void);
void term(void);
void factor(void);
void error(void);
/* Character classes */
#define LETTER 0 //[a-zA-Z]
#define DIGIT 1 //[0-9]
#define SINGLEQUOTE 2 //[\']
#define DOUBLEQUOTE 3 //[\"]
#define DECIMAL 4 //[\.]
#define KEYWORDS 5 // Reserved words in C
#define UNKNOWN 99 //[^a-zA-Z0-9]

/* Token codes */
#define FLOAT_LIT 9
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define DECIMAL_POINT 27
#define DOLLAR_SIGN 28
#define EXCLAMATION_POINT 29
#define TILDE 30
#define NUMBER_SIGN 31
#define PERCENTAGE_SIGN 32
#define CARET_SIGN 33
#define AMPERSAND_SIGN 34
#define UNDERSCORE_SIGN 35
#define COMMA_SIGN 36
#define VERTICAL_BAR 37
#define FORWARD_SLASH_SIGN 38
#define BACKSLASH_SIGN 39
#define APOSTROPHE_SIGN 40
#define OPENING_ANGLE_BRACKET 41
#define CLOSING_ANGLE_BRACKET 42
#define QUESTION_MARK 43
#define LEFT_BRACE 44
#define RIGHT_BRACE 45
#define LEFT_BRACKET 46
#define RIGHT_BRACKET 47
#define COLON 48
#define QUOTATION_MARK 49
#define SEMICOLON_SIGN 50
#define AT_SYMBOL 51




/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
	 do {
	 	lex();
	 } while (nextToken != EOF);

    expr();
	 }
	 return 0;
}


/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
     case '$':
			 addChar();
			 nextToken = DOLLAR_SIGN;
			 break;
     case '#':
			 addChar();
			 nextToken = NUMBER_SIGN;
			 break;
     case '^':
			 addChar();
			 nextToken = CARET_SIGN;
			 break; 
     case '&':
			 addChar();
			 nextToken = AMPERSAND_SIGN;
			 break;
     case '_':
			 addChar();
			 nextToken = UNDERSCORE_SIGN;
			 break;
     case ',':
			 addChar();
			 nextToken = COMMA_SIGN;
			 break;
     case '|':
			 addChar();
			 nextToken = VERTICAL_BAR;
			 break;
     case '`':
			 addChar();
			 nextToken = APOSTROPHE_SIGN;
			 break;
     case '<':
			 addChar();
			 nextToken = OPENING_ANGLE_BRACKET;
			 break;
     case '>':
			 addChar();
			 nextToken = CLOSING_ANGLE_BRACKET;
			 break;
     case '?':
			 addChar();
			 nextToken = QUESTION_MARK;
			 break;
     case '{':
			 addChar();
			 nextToken = LEFT_BRACE;
			 break;
     case '}':
			 addChar();
			 nextToken = RIGHT_BRACE;
			 break;
     case '[':
			 addChar();
			 nextToken = LEFT_BRACKET;
			 break;
     case ']':
			 addChar();
			 nextToken = RIGHT_BRACKET;
			 break;
     case ':':
			 addChar();
			 nextToken = COLON;
			 break;
     case '"':
			 addChar();
			 nextToken = QUOTATION_MARK;
			 break;
     case ';':
			 addChar();
			 nextToken = SEMICOLON_SIGN;
			 break;
     case '@':
			 addChar();
			 nextToken = AT_SYMBOL;
			 break;
     case '%':
			 addChar();
			 nextToken = PERCENTAGE_SIGN;
			 break;
     case '~':
			 addChar();
			 nextToken = TILDE;
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
		 case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
			 break;
		 case '.':
			 addChar();
			 nextToken = DECIMAL_POINT;
			 break;
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
		 case KEYWORDS:
			 addChar();
			 getChar();
       while (charClass == LETTER && charClass != DIGIT) {
				 addChar();
				 getChar();
			 }
       char keywords[32][10] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
			 
       nextToken = KEYWORDS;
			 break;
		/* Integer & Float literals */
     case LETTER:
			 addChar();
			 getChar();
       while (charClass == LETTER || charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
       nextToken = IDENT;
			 break;
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
       if (charClass == UNKNOWN && nextChar == '.'){
         addChar();
				 getChar();
         while (charClass == DIGIT) {
				  addChar();
				  getChar();
			   }
         nextToken = FLOAT_LIT;
       } else {
			 nextToken = INT_LIT;
       }
		 	break;
    case DECIMAL:
          addChar();
				  getChar();
          if (charClass == DIGIT){
            addChar();
				    getChar();
            while (charClass == DIGIT) {
				      addChar();
				      getChar();
			      }
            nextToken = FLOAT_LIT;
          } else {
              nextToken = DECIMAL_POINT;
          }
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
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */



void expr(void) {
	 term();
	 while (nextToken == ADD_OP || nextToken == SUB_OP) {
		 lex();
		 term();
	 }
}

/* term
 Parses strings in the language generated by the rule:
 <term> -> <factor> {(* | /) <factor>}
 */
void term(void) {
	 factor();
	 while (nextToken == MULT_OP || nextToken == DIV_OP) {
		 lex();
		 factor();
	 }
}

/* factor
 Parses strings in the language generated by the rule:
 <factor> -> id | int_constant | ( <expr> )
 */
void factor(void) {
	 if (nextToken == IDENT || nextToken == INT_LIT || nextToken == FLOAT_LIT)
		 lex();
	 else { if (nextToken == LEFT_PAREN) {
		 lex();
		 expr();
		 if (nextToken == RIGHT_PAREN)
		 	lex();
		 else
		 	error();
		 }
		 else
		 error();
	 }
	 printf("Exit <factor>\n");
}


void error(void){
 exit(1);
}
