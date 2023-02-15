#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int get_priority(char c) {
	if(c >= 97) return c - 96;
 	return c - 38;	
}

char get_common_item(char *a, char *b, char *c) {
	for (int i = 0; i < (int) strlen(a); i++) {
		char candidate = '\0';
		for (int j = 0; j < (int) strlen(b); j++) {
			if (*(a+i) == *(b+j)) { 
			candidate = *(a+i);
			break;
			}
		}		

		for (int k = 0; k < (int) strlen(c); k++) {
			if (*(c+k) == candidate) { 
				return candidate;
			}
		}
	}

	return 0;
}

int main(void) {
	char ch[1000] = "";
	char file_name[] = ".//003_input.txt";
	//char file_name[] = ".//test";
	FILE *fp;

	int priorites_sum = 0;
	int priorites_sum_pt2 = 0;

	fp = fopen(file_name, "r");

	while(fgets(ch, 1000, fp)) {
		char temp[500] = "";

		int compartment_size = (strlen(ch) - 1) / 2;
		
		strcpy(temp, ch + compartment_size);		
		*(ch+compartment_size) = '\0';

		char res = *strpbrk(temp, ch);

		priorites_sum += get_priority(res);
	}
	
	fseek(fp, 0, SEEK_SET);

	while(true) {
		char a[500] = "";
		char b[500] = "";
		char c[500] = "";

		char *p = fgets(a, 500, fp);
		if(!p) break;
		fgets(b, 500, fp);
		fgets(c, 500, fp);

		priorites_sum_pt2 += get_priority(get_common_item(a,b,c));
	}

	fclose(fp);
	printf("%d\n", priorites_sum);
	printf("%d\n", priorites_sum_pt2);

	return 0;
}

