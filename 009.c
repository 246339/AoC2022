#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define true 1
#define false 0

#define size 300

//#########################################
	#define rope_length 10
//########################################

int main(void) {

	char matrix[size][size] = {'\0'};

	//char *file = ".//test";
	char *file = ".//009_input.txt";

	FILE *fp = fopen(file, "r");

	int xy[rope_length][2];
	for (int i = 0; i < rope_length; i++) {
		xy[i][0] = size/2; 	
		xy[i][1] = size/2; 	
	}

	while(true) {
		char dir;
		int steps;
		if (fscanf(fp, "%c %d", &dir, &steps) <= 0) break;
		
		for (int i = 0; i < steps; i++) {
			
			if (dir == 'U') xy[0][0] -= 1;		
			if (dir == 'D') xy[0][0] += 1;
			if (dir == 'L') xy[0][1] -= 1;
			if (dir == 'R') xy[0][1] += 1;

			for (int j = 0; j < rope_length - 1; j++) {
				int *Hx = &xy[j][0];
				int *Hy = &xy[j][1];

				int *Tx = &xy[j + 1][0];
				int *Ty = &xy[j + 1][1];

				if (*(Hy) - *(Ty) == -2 && *(Hx) - *(Tx) == -2) { 
					(*Ty)--;
					(*Tx)--;
				} else if (*(Hy) - *(Ty) == -2 && *(Hx) - *(Tx) == 2) { 
					(*Ty)--;
					(*Tx)++;
				} else if (*(Hy) - *(Ty) == 2 && *(Hx) - *(Tx) == 2) { 
					(*Ty)++;
					(*Tx)++;
				} else if (*(Hy) - *(Ty) == 2 && *(Hx) - *(Tx) == -2) { 
					(*Ty)++;
					(*Tx)--;
				}

				if (*(Hy) - *(Ty) == -2) { 
					*(Ty) -= 1;
					*(Tx) = *(Hx);
				} else if (*(Hy) - *(Ty) == 2) { 
					*(Ty) += 1;
					*(Tx) = *(Hx);
				} else if (*(Hx) - *(Tx) == -2) { 
					*(Tx) -= 1;
					*(Ty) = *(Hy);
				} else if (*(Hx) - *(Tx) == 2) { 
					*(Tx) += 1;
					*(Ty) = *(Hy);
				}

				matrix[ xy[rope_length - 1][0] ][ xy[rope_length - 1][1] ] = '#';
			}
		}
	}	

	char *p = &matrix[0][0];
	int counter = 0;

	for (int i = 0; i < size * size; i++) {
		if (*(p + i) == '#') counter++;
	}
	
	printf("%d\n", counter);

	fclose(fp);
  	return 0;
}

