#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 7
#define STRSIZE 100

struct Node {
	char data;
	struct Node *next;
};

void print_node(struct Node* nodes);

int main() {
	//a = 65, g = 71
	int row_index = 0, col_index = 0;
	char* strcut;
	struct Node * nodes = (struct Node*)malloc(sizeof(struct Node)*BUFSIZE);
	struct Node * node_p;
	char* str;
	str = (char*)malloc(sizeof(char)*BUFSIZE);

	FILE *fp;
	fp = fopen("hw4.data", "r");

	//make Adj array and adjacency list in alphabetical order.
	fgets(str, STRSIZE, fp); //delete first line
	while (fgets(str, STRSIZE, fp) != NULL) {
		printf("%s", str);

		strcut = strtok(str, "\t");
		row_index = (*strcut) - 65; //get index
		nodes[row_index].data = (*strcut); //make first node
		nodes[row_index].next = NULL;

		col_index = 0; //initalize for column
		node_p = &(nodes[row_index]);

		strcut = strtok(NULL, "\t");
		while (strcut != NULL) {
			int exist = (*strcut) - 48; //change asccii code to integer
			//printf("%d\n", exist);
			if (exist == 1) {
				struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
				new_node->data = col_index + 65;
				new_node->next = NULL;
				node_p->next = new_node;
				node_p = new_node;
			}
			col_index++;
			strcut = strtok(NULL, "\t");
		}
	}
	print_node(nodes);


	fclose(fp);
	system("pause");
	return 0;
}

void print_node(struct Node* nodes) {
	printf("\n\n****print graph****\n");
	for (int i = 0; i < BUFSIZE; i++) {
		struct Node* node = (&nodes[i]);
		while (node != NULL) {
			printf("%c -> ", node->data);
			node = node->next;
		}
		printf("NULL\n");
	}
}
