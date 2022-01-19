#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdlib.h>

#include "Tool.h"

typedef enum {
	MOV_T,
	PUSH_T,
	POP_T,
}Token_Type;


typedef enum {
	MOV_K,
	PUSH_K,
	POP_K,

	NUM_OF_KEYWORDS
}Keyword_Type;

extern char* SavedKeywords[];


typedef struct Token {
	int line, column;
	Token_Type type;
	char* lexeme;

	bool isFree;
}Token;

typedef struct TokenList {
	Token** tokens;
	int size;
}TokenList;

// TokenList
TokenList* newTokenList();
void freeTokenList(TokenList* list);


// Token
Token* newToken(Token_Type type, char* lexeme, int line, int column, bool isFree);
void freeToken(Token* token);


// General
Token* scanNewToken(char* rawCode, int* currentIndex);
#endif // !LEXER_H
