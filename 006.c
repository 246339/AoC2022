#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

//###########################
	#define len 14
//###########################

void clear(int *tab, int size) {
	for (int i = 0; i < size; i++) {
		*(tab+i) = 0;
	}
}

int uniqe(int *tab, int size) { 
	int uniqe = 0;
	for (int i = 0; i < size; i++) {
		uniqe += *(tab+i) > 0 ? 1 : 0;
	}
	return uniqe;
}

int main(void) {
	int ref[26] = {0};
	char ch[len + 1] = "";
	char file_name[] = ".//006_input.txt";
	//char file_name[] = ".//test";
	FILE *fp;

	fp = fopen(file_name, "r");

	fgets(ch, len, fp);

	char c[2] = "";
	int pos = len;

	while(fscanf(fp, "%c", c)) {
		for (int i = 0; i < len - 1; i++) {
			ref[ch[i] - 97]++;
		}
		ref[c[0] - 97]++; 			

		if (uniqe(ref, 26) == len) break;

		clear(ref, 26);

		for (int i = 0; i < len - 1; i++) {
			ch[i] = ch[i+1];
		}
		ch[len - 2] = c[0];

		pos++;
	}

	fclose(fp);
	
	printf("%d\n", pos);

	return 0;
}
