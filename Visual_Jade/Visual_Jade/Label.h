#define _CRT_SECURE_NO_WARNINGS

#ifndef LABEL_H
#define LABEL_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Label {
	char* name;
	int ip;
}Label;

typedef struct LabelList {
	Label** labels;
	int amount;
}LabelList;

Label* newLabel(char* name, int ip);
void freeLabel(Label* label);
void freeLabelList(LabelList* list);
LabelList* newLabelList();
bool addLabel(LabelList* list, Label* label);

Label* getLabel(LabelList* list, char* label);
bool hasLabel(LabelList* list, char* label);
bool isLabel(char* word);

#endif // !LABEL_H
