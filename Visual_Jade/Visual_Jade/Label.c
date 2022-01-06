#include "Label.h"

bool isLabel(char* word) {
	return word[strlen(word) - 1] == ':';
}

Label* newLabel(char* name, int ip) {
	Label* label = (Label*)malloc(sizeof(Label));
	label->name = (char*)malloc(sizeof(char) * strlen(name));
	strcpy(label->name, name);
	label->name[strlen(name) - 1] = '\0';
	label->ip = ip;
	return label;
}

LabelList* newLabelList() {
	LabelList* list = (LabelList*)malloc(sizeof(LabelList));
	list->amount = 0;
	list->labels = NULL;
	return list;
}

void freeLabel(Label* label) {
	// free(label->name);
	free(label);
	return;
}

void freeLabelList(LabelList* list) {
	for (size_t i = 0; i < list->amount; i++) {
		freeLabel(list->labels[i]);
	}
	free(list->labels);
	free(list);
	return;
}
bool hasLabel(LabelList* list, char* label) {
	for (size_t i = 0; i < list->amount; i++) {
		if (!strcmp(list->labels[i]->name, label))
			return true;
	}
	return false;
}

Label* getLabel(LabelList* list, char* label) {
	for (size_t i = 0; i < list->amount; i++) {
		if (!strcmp(list->labels[i]->name, label))
			return list->labels[i];
	}
	return NULL;
}

bool addLabel(LabelList* list, Label* label) {
	if (hasLabel(list, label->name)) {
		getLabel(list, label->name)->ip = label->ip;
	}
	else {
		// Drive over the old one
		list->labels = (Label**)realloc(list->labels, sizeof(Label*) * (list->amount + 1));
		list->labels[list->amount] = label;
		list->amount++;
	}
	
	return true;
}