#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

#define size 200 

int main(void) {

	//char *file = ".//test";
	char *file = ".//010_input.txt";

	FILE *fp = fopen(file, "r");

	char CRT[6][41];

	for (int i = 0; i < 6; i++) {
		for (int k = 0; k < 40; k++) {
			CRT[i][k] = ' ';
		}
		CRT[i][40] = '\0';
	}

	int X = 1;
	int cycle = 0;
	int wait = 1;
	int temp = 0;
	int sum = 0;

	while (cycle < 240) {

		int num;
		if (cycle % 40 == X - 1 || cycle % 40 == X || cycle % 40 == X + 1) {
			CRT[cycle / 40][cycle % 40] = '#';	
		}

		wait--;
		cycle++;

		if ((cycle + 20) % 40 == 0) {
			sum += X * cycle;
		}

		if (wait == 0) {
			char inst[4];
			int read_count = fscanf(fp, "%4c %d\n", inst, &num);
			if (read_count == 2) {
		     		wait = 2;
				temp = num;	
			} 
			if (read_count == 1) {
				wait = 1;
			}
		} else {	
			X += temp;
		}
	}

	printf("%d\n", sum);

	for (int i = 0; i < 6; i++) {
		printf("%s\n", CRT[i]);
	}
	
	fclose(fp);
  	return 0;
}
