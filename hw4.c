#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADJSIZE 7
#define STRSIZE 100

struct Node {
	char data;
	struct Node *next;
};

void print_node(struct Node* nodes, FILE* fp_o);

int main() {
	//a = 65, g = 71
	int row_index = 0, col_index = 0;
	char* strcut;
	struct Node * nodes_origin = (struct Node*)malloc(sizeof(struct Node)*ADJSIZE);
	struct Node * nodes_trans = (struct Node*)malloc(sizeof(struct Node)*ADJSIZE);
	struct Node * node_p;
	char* str;
	str = (char*)malloc(sizeof(char)*STRSIZE);

	//file open
	FILE *fp;
	FILE *fp_o;
	fp = fopen("hw4.data", "r");
	fp_o = fopen("output.txt", "w");

	//make Adj array and adjacency list in alphabetical order.
	for (int i = 0; i < ADJSIZE; i++) {
		nodes_origin[i].data = i + 65;
		nodes_origin[i].next = NULL;
	}
	fgets(str, STRSIZE, fp); //delete first line
	while (fgets(str, STRSIZE, fp) != NULL) {
		printf("%s", str);

		strcut = strtok(str, "\t");
		row_index = (*strcut) - 65; //get index

		col_index = 0; //initalize for column
		node_p = &(nodes_origin[row_index]);

		strcut = strtok(NULL, "\t");
		while (strcut != NULL) {
			int exist = (*strcut) - 48; //change asccii code to integer
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
	printf("\n****print original graph****\n");
	fprintf(fp_o, "\n****print original graph****\n");
	print_node(nodes_origin, fp_o); //print Adj array and adjacency list

	//make transpose graph
	for (int i = 0; i < ADJSIZE; i++) {
		nodes_trans[i].data = i + 65;
		nodes_trans[i].next = NULL;
	}
	for (int i = 0; i < ADJSIZE; i++) {
		struct Node* node = (&nodes_origin[i]);
		while ((node = node->next)!=NULL) {
			struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
			new_node->data = nodes_origin[i].data;
			new_node->next = NULL;
	
			struct Node* node_end = (&nodes_trans[(node->data) - 65]);
			while(node_end->next!=NULL){ //add new node in the end node
				node_end = node_end->next;
			}
			node_end->next = new_node;
		}

	}
	printf("\n****print transpose graph****\n");
	fprintf(fp_o, "\n****print transpose graph****\n");
	print_node(nodes_trans, fp_o); //print Adj array and adjacency list transposed

	fclose(fp);
	fclose(fp_o);
	system("pause");
	return 0;
}

void print_node(struct Node* nodes, FILE* fp_o) {
	for (int i = 0; i < ADJSIZE; i++) {
		struct Node* node = (&nodes[i]);
		while (node != NULL) {
			printf("%c --> ", node->data);
			fprintf(fp_o, "%c --> ", node->data);
			node = node->next;
		}
		printf("NULL\n");
		fprintf(fp_o, "NULL\n");
	}
}
