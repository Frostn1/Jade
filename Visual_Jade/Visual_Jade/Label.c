#include "Label.h"

bool isLabel(char* word) {
	return word[strlen(word) - 1] == ':';
}

Label* newLabel(char* name, int ip) {
	Label* label = (Label*)malloc(sizeof(Label));
	label->name = name;
	label->ip = ip;
	return label;
}

LabelList* newLabelList() {
	LabelList* list = (LabelList*)malloc(sizeof(LabelList));
	list->amount = 0;
	return list;
}

bool hasLabel(LabelList* list, Label* label) {
	for (size_t i = 0; i < list->amount; i++) {
		if (!strcmp(list->labels[i]->name, label->name))
			return true;
	}
	return false;
}

bool addLabel(LabelList* list, Label* label) {
	if (hasLabel(list, label)) return false;
	list->labels = (Label**)realloc(list->labels, sizeof(Label*) * (list->amount + 1));
	list->labels[list->amount] = label;
	return true;
}