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
LabelList* newLabelList();
bool addLabel(LabelList* list, Label* label);

bool hasLabel(LabelList* list, Label* label);
bool isLabel(char* word);

#endif // !LABEL_H
