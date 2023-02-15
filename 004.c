#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int is_overlaping(char *str, int full_overlap) {
	char temp[30];

	strcpy(temp, str);
	
	char *delim = "-,";

	int a = atoi(strtok(temp, delim));
	int b = atoi(strtok(NULL, delim));

	int x = atoi(strtok(NULL, delim));
	int y = atoi(strtok(NULL, delim));
	
	if (full_overlap) return (a >= x && b <= y) || (x >= a && y <= b) ? 1 : 0; 

	return (a <= x && b >=x) || (a <= y && a >= x) ? 1 : 0;
}



int main(void) {
	char ch[30] = "";
	char file_name[] = ".//004_input.txt";
//	char file_name[] = ".//test";
	FILE *fp;

	int full_overlap_counter = 0;
	int partial_overlap_counter = 0;

	fp = fopen(file_name, "r");

	while(fgets(ch, 30, fp)) {
		full_overlap_counter += is_overlaping(ch, true);
		partial_overlap_counter += is_overlaping(ch, false);
	}

	fclose(fp);

	printf("%d\n", full_overlap_counter);
	printf("%d\n", partial_overlap_counter);

	return 0;
}

