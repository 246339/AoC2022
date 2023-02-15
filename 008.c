#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

#define size 200 

int look(int height, int posx, int width, int posy, int *p) {
	if (posx == 0 || posy == 0 || posx == height - 1 || posy == width -1) return 1; 
	int tree_height = *p;
	
	int res = 1;
	for (int j = 1; j <= posx; j++) {
		if (*(p - (j * size)) >= tree_height) {
			res = 0;	
			break;
		}
	}
	if (res) return 1;
	
	res = 1;
	for (int j = 1; j <= (height - posx); j++) {
		if (*(p + (j * size)) >= tree_height) {
			res = 0;	
			break;
		}
	}
	if (res) return 1;
	
	res = 1;
	for (int j = 1; j <= posy; j++) {
		if (*(p - j) >= tree_height) {
			res = 0;	
			break;
		}
	}
	if (res) return 1;
	
	res = 1;
	for (int j = 1; j <= (width - posy); j++) {
		if (*(p + j) >= tree_height) {
			res = 0;	
			break;
		}
	}

	return res;
}


int calc_score(int height, int posx, int width, int posy, int *p) {
	int tree_height = *p;
	
	int x = 0;
	for (int j = 1; j <= posx; j++) {
		x++;
		if (*(p - (j * size)) >= tree_height) break;
	}
	
	int y = 0;
	for (int j = 1; j < (height - posx); j++) {
		y++;
		if (*(p + (j * size)) >= tree_height) break;
	}

	
	int z = 0;
	for (int j = 1; j <= posy; j++) {
		z++;
		if (*(p - j) >= tree_height) break;
	}

	int q = 0;	
	for (int j = 1; j < (width - posy); j++) {
		q++;
		if (*(p + j) >= tree_height) break;
	}

	return x * y * z * q;
}

int main(void) {

	//char file[] = ".//test";	
	char file[] = ".//008_input.txt";	
	FILE *fp = fopen(file, "r");

	int forrest[size][size] = {0};
	int *p = &forrest[0][0];

	int width = 0;

	for (int i = 0; i < size; i++) {
		if (fgetc(fp) != '\n') {
			width++;
		} else {
			break;
		}
	}

	fseek(fp, 0, SEEK_SET);

	int height = 0;

	int c = fgetc(fp);
	
	while(c != EOF) {
		int *r = p;
		while (c != '\n' && c != '\0' && c != EOF) {
			*r = c - 48;	
			c = fgetc(fp);
			r++;
		}
		
		c = fgetc(fp);
		p += size;
		height++;
	}
	
	int sum = 0;
	int max_score = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			sum += look(height, i, width, j, &forrest[i][j]);
			int score = calc_score(height, i, width, j, &forrest[i][j]);
			if(score > max_score) max_score = score;
		}
	}

	fclose(fp);
	printf("%d\n", sum);	
	printf("%d\n", max_score);	

  	return 0;
}

