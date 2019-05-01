#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Node {
	char data;
	struct Node *next;
};

void print_node(struct Node* nodes);

int main() {
	//a = 65, g = 71
	int row_index = 0, col_index=0;
	char* strcut;
	struct Node * nodes = (struct Node*)malloc(sizeof(struct Node)*SIZE);
	struct Node * node_p;
	char* str;
	str = (char*)malloc(sizeof(char)*SIZE);

	FILE *fp;
	fp = fopen("hw4.txt", "r");
	if (fp == NULL)
	{
		perror("file open error");
		system("pause");
		exit(0);
	}

	fgets(str, SIZE, fp); //delete first line
	while(fgets(str, SIZE, fp)!=NULL) {
		printf("%s", str);

		//strcut = strtok(str, "\t");//get first column char
		row_index = (*strcut) - 65; //get index
		nodes[row_index].data = (*strcut); //make first node
		nodes[row_index].next = NULL;
		
		col_index = 0;
		node_p = &(nodes[row_index]);

		strcut = strtok(str, "\t");
		strcut = strtok(NULL, "\t");
		while (strcut != NULL) { //add node
			
			int exist = (*strcut) - 48; //change asccii code to integer
			if (exist == 1) {
				printf("%c\n", strcut);
				struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
				new_node->data = col_index + 65;
				new_node->next = NULL;
				node_p->next = new_node;
				//printf("row index : %d, col index : %d, new data:%d\n", row_index, col_index, node_p->next->data);
				node_p = new_node;
			}
			
			printf("%c\n", strcut);
			strcut = strtok(NULL, "\t");
			//col_index++;
		}
		
	}

	//print_node(nodes);

	/*
	printf("\n");
	struct Node * nodep = (struct Node*)malloc(sizeof(struct Node));
	nodep = (&nodes[0]);
	while(nodep!=NULL){	
		printf("%c\n", nodep->data);
		nodep = nodep->next;
	}
	*/

	fclose(fp);
	system("pause");
	return 0;
}

void print_node(struct Node* nodes) {
	printf("****print graph****");
	for (int i = 0; i < SIZE; i++) {
		struct Node* node = (&nodes[i]);
		while (node != NULL) {
			printf("%c -> ", node->data);
			node = node->next;
		}
		printf("NULL\n");
	}
}
