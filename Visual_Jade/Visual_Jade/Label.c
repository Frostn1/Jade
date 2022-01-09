#include "Label.h"

bool isLabel(char* word) {
	return word[strlen(word) - 1] == ':';
}

Label* newLabel(char* name, int ip) {
	Label* label = (Label*)malloc(sizeof(Label));
	label->name = (char*)malloc(sizeof(char) * strlen(name));
	strcpy(label->name, name);
	label->name[name[strlen(name) - 1] == ':' ? strlen(name) - 1 : strlen(name)] = '\0';
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
bool hasLabel(LabelList* list, char* label, LOOKAHEAD_FLAG flag) {
	for (size_t i = 0; i < list->amount; i++) {
		if (!strcmp(list->labels[i]->name, label))
			return true;
	}
	if(flag)
		addLabel(list, newLabel(label, -1));
	return flag;
}

Label* getLabel(LabelList* list, char* label) {
	for (size_t i = 0; i < list->amount; i++) {
		if (!strcmp(list->labels[i]->name, label))
			return list->labels[i];
	}
	return NULL;
}

bool addLabel(LabelList* list, Label* label) {
	if (hasLabel(list, label->name, LOOKAHEAD_OFF)) {
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

bool validateLabels(LabelList* list) {
	bool returnFlag = true;
	for (size_t i = 0; i < list->amount; i++) {
		if (list->labels[i]->ip == -1) {
			fprintf(stderr, "Uninitialized local label used < %s >\n", list->labels[i]->name);
			returnFlag = false;
		}
	}
	return returnFlag;
}