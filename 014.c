#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>
#include <unistd.h> 
#define true 1
#define false 0
				

void fill_y(int x, int start, int l, char *field, int width) {
	for (int i = 0; i <= abs(l); i++) {
		if (l > 0) {
			*(field + (i + start) * width + x) = '#';
		} else {
			*(field + (-i + start) * width + x) = '#';
		}
	}
}

void fill_x(int y, int start, int l, char *field, int width) {
//	printf("Print\nRow: %d\nCol: %d\nl: %d\n", y, start, l);
	for (int i = 0; i <= abs(l); i++) {
		if (l > 0) {
			*(field + width * y + start + i) = '#';
		} else {
			*(field + width * y + start - i) = '#';
		}	
	}	
}

int drop_path_len(int source, int y, char *field, int width, int height) {
	//printf("%d %d\n", source, y);	

	if (*(field + (y + 1) * width + source) == '_') {
		return 1 + drop_path_len(source, y + 1, field, width, height);
	}

	if (*(field + (y + 1) * width - 1 + source) == '_') {
		return 1 + drop_path_len(source - 1, y + 1, field, width, height);
	}

	if (*(field + (y + 1) * width + 1 + source) == '_') {
		return 1 + drop_path_len(source + 1, y + 1, field, width, height);
	}

	*(field + y * width + source) = '#';

	return 1;
}

int drop(int source, int y, char *field, int width, int height) {
	//printf("%d %d\n", source, y);	
	if (y + 1 > height -2) return 0;

	if (*(field + (y + 1) * width + source) == '_') {
		return drop(source, y + 1, field, width, height);
	}

	if (*(field + (y + 1) * width - 1 + source) == '_') {
		return drop(source - 1, y + 1, field, width, height);
	}

	if (*(field + (y + 1) * width + 1 + source) == '_') {
		return drop(source + 1, y + 1, field, width, height);
	}

	*(field + y * width + source) = '#';

	return 1;
}


int main(void) {

	//char file[] = ".//test";
	char file[] = ".//014_input.txt";

	FILE *fp = fopen(file, "r");
	
	int x, y;
	int width = 800;
	int height;

	fscanf(fp, "%d,%d", &x, &height);
	
	int lines_num = 0;
	int source = 500;

	int c = '\0';	

	while (c != -1) {
		c = fgetc(fp);

		if (c == '\n') lines_num++;
		if (c >= 48 && c <= 57) {
			fseek(fp, -1, SEEK_CUR);
			fscanf(fp, "%d,%d", &x, &y);

			height = y > height ? y : height;	
		}
		if (c == '\n') lines_num++;
	}

	rewind(fp);

	height += 3;


	char *field = malloc(sizeof(char) * width * height);
	
	for (int i = 0; i < width * height; i++) {
		*(field + i) = '_';	
	}


	*(field + source) = '+';	
		
	for (int i = 0; i < lines_num; i++) {
		char ch;
		fscanf(fp, "%d,%d%c", &x, &y, &ch);
		
		while (ch != '\n') {
			int r, s;
			fseek(fp, 3, SEEK_CUR);
			fscanf(fp, "%d,%d%c", &r, &s, &ch);
			if (x == r) {
				fill_y(x, y, s - y, field, width);
			} else {
				fill_x(y, x, r - x, field, width);
			}
			x = r;
			y = s;
		}	
	}

	/*	part1		*/
	
	//int ans_pt1 = 0;	
	//while(drop(source, 0, field, width, height)) {
	//		ans_pt1++;
	//}

	//printf("ans_pt1: %d\n", ans_pt1);
	
	/*	/part1		*/


	/*	part2 		*/
	int ans_pt2 = 1;	
	for (int i = 0; i < width; i++) {
		*(field + width * (height - 1) + i) = '#';	
	} 

	while(drop_path_len(source, 0, field, width, height) > 1) {
		ans_pt2++;
	}
	printf("ans_pt2: %d\n", ans_pt2);
	/*	/part2		*/

	fclose(fp);

  	return 0;
}

