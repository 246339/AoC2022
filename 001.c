#include <stdlib.h>
#include <stdio.h>
/*
   

*/
#define true 1
#define false 0

int main(void) {
	char ch[100] = "";
	char file_name[] = ".//001_input.txt";
	//char file_name[] = ".//test";
	FILE *fp;

	int current_sum = 0;
	int max_sum_1 = 0;
	int max_sum_2 = 0;
	int max_sum_3 = 0;

	fp = fopen(file_name, "r");

	int keep_reading = true;
	while(keep_reading) {
		char *p = fgets(ch, 100, fp);
		if(!p) keep_reading = false;

		if (*ch == '\n' || !p) {
			if(current_sum >= max_sum_1) {
				max_sum_3 = max_sum_2;
				max_sum_2 = max_sum_1;
				max_sum_1 = current_sum;
			} else if (current_sum >= max_sum_2) {
				max_sum_3 = max_sum_2;
				max_sum_2 = current_sum;
			} else if (current_sum > max_sum_3) { 
				max_sum_3 = current_sum;
			}
			current_sum = 0;
		} else {
			current_sum += atoi(ch);
		}
	}

	fclose(fp);

	printf("Max:%d\n", max_sum_1);

	printf("Sum: %d\n", max_sum_1 + max_sum_2 + max_sum_3);
	return 0;
}

