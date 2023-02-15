#include <string.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h> 
#define true 1
#define false 0

#define len 30

typedef struct directory {
	int lvl;
	int file_sizes_sum;
	int dirs_count;
	struct directory *parent_dir;
	struct directory **directories;
	char *dir_name;
} Directory;

int dir_size(Directory dir) {
	int size = dir.file_sizes_sum;

	for (int i = 0; i < dir.dirs_count; i++) {
		size += dir_size(*dir.directories[i]);
	}                  
         
	return size;
}

int ans(Directory dir) {
	int res = 0;
	int size = dir_size(dir);
	if(size <= 100000) res+=size;

	for (int i = 0; i < dir.dirs_count; i++) {
		res += ans(*dir.directories[i]);
	}                  

	return res;
}


int ans2_helper(Directory dir, int need_to_free, int candidate) {
	int size = dir_size(dir);
	if(size >= need_to_free && size < candidate) candidate = size;

	for (int j = 0; j < dir.dirs_count; j++) {
		candidate = ans2_helper(*dir.directories[j], need_to_free, candidate); 
	}                  

	return candidate;
} 

int ans2(Directory dir) {
	int size =  dir_size(dir);
	int need_to_free = 30000000 - (70000000 - size);

	int res = 70000000;

	for (int i = 0; i < dir.dirs_count; i++) {
		res = ans2_helper(*dir.directories[i], need_to_free, res);
	}                  

	return res;	
}

int main(void) {
	
	char file[] = ".//007_input.txt";
	//char file[] = ".//test";

	FILE *fp = fopen(file, "r");

	char temp[len+1];

	fgets(temp, len, fp);
	fgets(temp, len, fp);
	fgets(temp, len, fp);

	Directory dir = {0, 0, 0, NULL, NULL, "/\n"};
	Directory *current_dir = &dir;
	int keep_reading = true;
	while(keep_reading) {
		if (temp[0] == '$') {
			if (temp[2] == 'c') {
				if(!strcmp(temp, "$ cd ..\n")) {
					current_dir = current_dir->parent_dir;
				} else {
					for (int i = 0; i < current_dir->dirs_count; i++) {
						if(!strcmp(&temp[5], (current_dir->directories)[i]->dir_name)) {
							current_dir = current_dir->directories[i];
							break;
						}	
					} 
				}
			}
			fgets(temp, len, fp);
			continue;
		}

		int read_chars = strlen(temp);
	       	int files_num = 0;
		int file_sizes_sum = 0;
		int dirs_count = 0;	

		while(temp[0] != '$') {
			if (temp[0] == 'd') {
				dirs_count++;		
			} else {
				file_sizes_sum+=atoi(temp);
			}
			files_num++;
		 	
			if(!fgets(temp, len, fp)) {
				keep_reading = false;
				break;
			}
			
			read_chars += strlen(temp);
		}

		current_dir->dirs_count = dirs_count;
		current_dir->file_sizes_sum = file_sizes_sum;

		if (!(current_dir->directories)) {
			Directory **dirs =  malloc(dirs_count * sizeof(Directory*));
			current_dir->directories = dirs;
		}

		fseek(fp, -read_chars, SEEK_CUR);

		fgets(temp, len, fp);

		while(files_num > 0) {
			int i = current_dir->dirs_count - dirs_count;
			if (temp[0] == 'd') {
				Directory *sub_dir = malloc(sizeof(Directory));
				sub_dir->lvl = current_dir->lvl + 1;
				sub_dir->file_sizes_sum = 0;
			       	sub_dir->dirs_count = 0;
				sub_dir->parent_dir = current_dir;
			       	sub_dir->directories = NULL;
				sub_dir->dir_name = malloc(len * sizeof(char));
				strcpy(sub_dir->dir_name, &temp[4]);	
				current_dir->directories[i] = sub_dir;
				dirs_count--;
			}
			files_num--;
			fgets(temp, len, fp);
		}
	}

	printf("pt1: %d\n", ans(dir));
	printf("pt2: %d\n", ans2(dir));

	fclose(fp);
  	return 0;
}

