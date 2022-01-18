#include "Lexer.h"

char* SavedKeywords[NUM_OF_KEYWORDS] = {
	"mov",
	"push",
	"pop",
};



Token* newToken(Token_Type type, char* lexeme, int line, int column, bool isFree) {
	Token* token = (Token*)malloc(sizeof(Token));
	token->type = type;
	token->lexeme = lexeme;
	token->line = line;
	token->column = column;
	token->isFree = isFree;
	return token;
}

void freeToken(Token* token) {
	if (token->isFree) free(token->lexeme);
	free(token);
	return;
}


TokenList* newTokenList() {
	TokenList* list = (TokenList*)malloc(sizeof(TokenList*));
	list->tokens = (Token**)malloc(sizeof(Token*));
	list->size = 0;
	return;
}

void freeTokenList(TokenList* list) {
	for (size_t i = 0; i < list->size; i++) {
		freeToken(list->tokens[i]);
	}
}


Token* scanNewToken(char* rawCode, int currentIndex) {

	while (isSpace(rawCode[currentIndex])) currentIndex++;


	return NULL;
}