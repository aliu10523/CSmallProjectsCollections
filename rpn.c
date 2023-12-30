#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int data;
	struct node *next;
} Node;

typedef struct {
	Node *top;
} Stack;

void initialize(Stack *ptr);
void pstack(Node *top, int first);
void push(Stack *ptr, int data);
int isEmpty(Stack *ptr);
int pop(Stack *stack);

int main() {
	Stack stack;
	initialize(&stack);
	//char buffer[10000000];
	char *buffer = malloc(sizeof(char) * 10000000);
	char *token;
	char *temp;

	while (fgets(buffer, 10000000, stdin) != NULL ) {
		temp = buffer;
		while ((token = strsep(&temp, " \n")) != NULL) {
			if (token[0] != '\0') {
				if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '%' || token[0] == '*')) {
					int postValue = pop(&stack);

					if (isEmpty(&stack)) {
						push(&stack, postValue);
						pstack(stack.top, 1);
						//printf("Not enough operands");
						free(buffer);
						return 0;
					}
					int preValue = pop(&stack);
					int newVal;

					switch (token[0]) {
						case '+':
							newVal = preValue + postValue;
							break;
						case '-':
							newVal = preValue - postValue;
							break;
						case '%':
							newVal = preValue % postValue;
							break;
						case '*':
							newVal = preValue * postValue;
					}
					push(&stack, newVal);
					//pstack(stack.top, 1);
				} else if ((token[0] == '-' && (token[1] >= '0' && token[1] <= '9')) || (token[0] >= '0' && token[0] <= '9')) {
					int val = atoi(token);
					push(&stack, val);
					//pstack(stack.top, 1);
				} else {
					pstack(stack.top, 1);
					free(buffer);
					//printf("Invalid Token");
					return 0;
				}
			}
		}
	}
	pstack(stack.top, 1);
	free(buffer);
	return 0;
}

void initialize(Stack *ptr) {
	ptr->top = NULL;
}

int isEmpty(Stack *ptr) {
	return ptr->top == NULL;
}

void push(Stack *ptr, int data) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	if (newNode == NULL) {
		return;
	}
	newNode->data = data;
	newNode->next = ptr->top;
	ptr->top = newNode;
}

int pop(Stack *stack) {
	if (isEmpty(stack)) {
		return 0;
	}
	int data = stack->top->data;
	Node *temp = stack->top;
	stack->top = stack->top->next;
	free(temp);
	return data;

}

void pstack(Node *top, int first) {
	if (!top) {
		if (first)
			puts ("[ ]");
		return;
	}
	pstack(top->next, 0);
	printf("%c %d", (top->next ? ',' : '['), top->data);
	if (first)
		puts(" ]");
}




