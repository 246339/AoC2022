#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>


typedef struct list{
	int *num;
	struct list *arr;
	struct list *next;
} List;

int get_pairs_num(FILE *fp) {\
	int c = '\0';
	int count = 1;
	while (c != -1) {
		c = fgetc(fp);
		if (c == '\n') count++;
	}

	int pairs_num = count / 3;

	rewind(fp);
	return pairs_num;
}

char *get_line(FILE *fp) {
		
	int c = fgetc(fp);
	
	if (c == '\n' || c == -1) return NULL;

	int line_len = 1;
	while(c != '\n') {
		c = fgetc(fp);
		line_len++;
	}

	fseek(fp, -line_len, SEEK_CUR);

	char *line = malloc(line_len * sizeof(char));
	line[line_len - 1] = '\0';
	for (int i = 0; i < line_len - 1; i++) {
		line[i] = fgetc(fp);	
	}

	fgetc(fp);

	return line;
}

List *create_list(char *line) {
	
	if (*line == '\0' || *line == ']') return NULL;

	List *arr = malloc(sizeof(List));
	arr->num = NULL;
	arr->arr = NULL;
	arr->next = NULL;

	if(*line == ',') line += 1;
	
	if (*line >= 48 && *line <= 57) { 
		arr->num = malloc(sizeof(int));
		*arr->num = atoi(line);
		
		while(*line >= 48 && *line <= 57) {
			line++;
		}

	} else if(*line == '[') {
		line += 1;
		arr->arr = create_list(line);
		int i = 1;
		while(i != 0) {
			if (*line == '[') i++;	
			if (*line == ']') i--;
			line++;
		}
	}

	arr->next = create_list(line);

	return arr;	
}

void clear_arr(List *arr) {
	if(arr->num) {
		free(arr->num);
	}
	if(arr->arr) {
		clear_arr(arr->arr);
	}	
	if(arr->next) {
		clear_arr(arr->next);
	}
	free(arr);
}

void print_arr(List *arr) {
	printf("[ ");
	while (arr && (arr->num || arr->arr)) {
		if(arr->num) {
			printf("%d ", *arr->num);
		} else if (arr->arr) {
			print_arr(arr->arr);
		}

		arr = arr->next;
	}
	printf(" ]");
}

List *int_to_array(int *num) {
	List *arr = malloc(sizeof(List));
	arr->num = num;
	arr->arr = NULL;
	arr->next = NULL;
	return arr;
}


int compare(List *arr_1, List *arr_2) {
	if(!arr_1 && !arr_2) return 0;
	if(!arr_1) return 1;
	if(!arr_2) return -1;

	if(!arr_1->num && !arr_1->arr && !arr_2->num && !arr_2->arr) return 0;
	if(!arr_1->num && !arr_1->arr) return 1;
	if(!arr_2->num && !arr_2->arr) return -1;

	if (arr_1->num && arr_2->num) {
		if (*arr_1->num != *arr_2->num) {
			return *arr_1->num < *arr_2->num ? 1 : -1;
		} 
	} 

	int res = 0;
	
	if (arr_1->num && arr_2->arr) {
		List *num = int_to_array(arr_1->num);
		res = compare(num, arr_2->arr);
		free(num);
	}

	if (arr_2->num && arr_1->arr) {
		List *num = int_to_array(arr_2->num);
		res = compare(arr_1->arr, num);
		free(num);
	}

       	if (arr_1->arr && arr_2->arr) {
		res = compare(arr_1->arr, arr_2->arr);
	}

	if (res == 0) {
		arr_1 = arr_1->next;
		arr_2 = arr_2->next;
		return compare(arr_1, arr_2);	
      	}

	return res;
}

int main(void) {
//char file[] = ".//test";
char file[] = ".//013_input.txt";
	FILE *fp = fopen(file, "r");

	int pairs_num = get_pairs_num(fp);

	int ans = 0;

	// PART 1
	for (int i = 1; i <= pairs_num; i++) {
		char *line_1 = get_line(fp);
		char *line_2 = get_line(fp);
		fgetc(fp);
		
		List *arr_1 = create_list(line_1);	
		free(line_1);
		List *arr_2 = create_list(line_2);	
		free(line_2);	
		
		ans += (i) * (compare(arr_1, arr_2) == 1 ? 1 : 0);

		clear_arr(arr_1);
		clear_arr(arr_2);
	}
	
	printf("Ans pt1: %d\n", ans);

	// PART 2
	rewind(fp);
	List *div_1 = create_list("[[2]]");
	List *div_2 = create_list("[[6]]");

	int pos_1 = 1;
	int pos_2 = 2;

	for (int i = 1; i <= pairs_num; i++) {
		char *line_1 = get_line(fp);
		char *line_2 = get_line(fp);
		fgetc(fp);
		
		List *arr_1 = create_list(line_1);	
		free(line_1);
		List *arr_2 = create_list(line_2);	
		free(line_2);	
		
		if(compare(div_1, arr_1) == -1) pos_1++; 
		if(compare(div_2, arr_1) == -1) pos_2++; 
		clear_arr(arr_1);

		if(compare(div_1, arr_2) == -1) pos_1++; 
		if(compare(div_2, arr_2) == -1) pos_2++; 
		clear_arr(arr_2);
	}

	printf("Ans pt2: %d\n", pos_1 * pos_2);

	fclose(fp);
  	return 0;
}

