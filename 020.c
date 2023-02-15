#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#define true 1
#define false 0

typedef struct node {
	long long i;
	int lp;

	struct node *prev;
	struct node *next;

} Node;

long long decrypt(Node *node, int size, long long key, int rounds) {
	for (int i = 0; i <= size; i++) {
		node->i *= key;
		node = node->next;	
	}
	
	for (int i = 0; i < rounds; i++) {
		int el = 0;
		while (el <= size) {
			while(node->lp != el) {
				node = node->next;
			}
			el++;
			
			Node *temp = node;
			long long num = node->i % (size);

			if (num > 0 && num > size / 2) {
				num = num - size;	
			}

			if (num < 0 && -num > size / 2) {
				num = size + num;
			}

			for (int k = 0; k < (num > 0 ? num : -num + 1); k++) {
				if (num > 0) node = node->next;	
				if (num < 0) node = node->prev;
			}

			if (node == temp) continue;

			temp->next->prev = temp->prev;	
			temp->prev->next = temp->next;
			
			temp->next = node->next;
			temp->prev = node;

			temp->next->prev = temp;
			node->next = temp;
		}
	}	

	
	while(node->i != 0) {
		node = node->next;
	}

	long long sum = 0;
	for (int l = 0; l < 3; l++) {
		for (int j = 0; j < 1000 % (size + 1); j++) {
			node = node->next;
		}
		sum += node->i;
	}

	return sum;
}

void sort_nodes(Node *node) {
	int keep_sorting = true;

	while (keep_sorting) {
		keep_sorting = false;

		while(node->lp != 0) {
			node = node->next;
		}
		
		while(true) {
			if (node->next->lp == 0) break;

			if (node->lp > node->next->lp) {

				Node *temp = node->next;

				node->next = temp->next;	
				temp->next->prev = node;

				node->prev->next = temp;
				temp->prev = node->prev;

				node->prev = temp;
				temp->next = node;

				keep_sorting = true;	
			} else {
				node = node->next;	
			}
		}
	}
}


int main(void) {

	//char *file = ".//test";
	char *file = ".//020_input.txt";

	FILE *fp = fopen(file, "r");

	long long x;
	fscanf(fp, "%lld", &x);
	
	Node *first = malloc(sizeof(Node));
	first->i = x;
	int lines_num = 0;
	first->lp = lines_num;

	Node *node = first;	

	while (fscanf(fp, "%lld", &x) == 1) {
		lines_num++;
		Node *next = malloc(sizeof(Node));
		next->i = x;
		next->lp = lines_num;

		next->prev = node;	
		node->next = next;

		node = next;
	}
	fclose(fp);	


	node->next = first;
	first->prev = node;

	printf("Ans pt1: %lld\n", decrypt(node, lines_num, 1, 1));
	sort_nodes(node);
	printf("Ans pt2: %lld\n", decrypt(node, lines_num, 811589153, 10));
  	return 0;
}
