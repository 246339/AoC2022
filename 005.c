#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0


void parse_cmds(char *input, int* cmds) {
	char temp[100] = "";
	strcpy(temp, input);
	
	char *delim = " ";

	strtok(temp, delim);
	*cmds = atoi(strtok(NULL, delim));
	strtok(NULL, delim);
	*(cmds + 1) = atoi(strtok(NULL, delim));
	strtok(NULL, delim);
	*(cmds + 2) = atoi(strtok(NULL, delim));
}

void move_multiple(char piles[20][100], int cmds[3]) {
	char* a = (piles[cmds[1]] + strlen(piles[cmds[1]]));
	char* b = (piles[cmds[2]] + strlen(piles[cmds[2]]));

	for (int i = 0; i < cmds[0]; i++) {
		*(b + i) = *(a - cmds[0] + i);
	}	
	*(b + cmds[0]) = '\0';
	*(a - cmds[0]) = '\0';
}

//void move_one(char piles[20][100], int cmds[3]) {
//	char* a = (piles[cmds[1]] + strlen(piles[cmds[1]]) - 1);
//	char* b = (piles[cmds[2]] + strlen(piles[cmds[2]]));
//
//	for (int i = 0; i < cmds[0]; i++) {
//		*(b + i) = *(a - i);
//	}	
//	*(b + cmds[0]) = '\0';
//	*(a - cmds[0] + 1) = '\0';
//}


int main(void) {
	int max_height = 0;
	int pile_count = 0;

	char ch[100] = "";
	char piles[20][100] = {""};
	char file_name[] = ".//005_input.txt";
	//char file_name[] = ".//test";
	FILE *fp;

	fp = fopen(file_name, "r");
	
	while(true) {
		char *p = fgets(ch, 100, fp);
		if(ch[0] != '\n' && ch[1] == '1') {
			while(*p != '\n') {
				if (*p != ' ') pile_count++;
				p++;
			}
			break;
		} else if (ch[0] != '\n') {
			max_height++;
		}
	}

	fseek(fp, 0, SEEK_SET);
	
	for (int i = max_height -1; i >= 0; i--) {
		fgets(ch, 100, fp);
		for (int j = 0; j < pile_count; j++) {
			char c = ch[j * 4 + 1]; 
			piles[j + 1][i] = c != ' ' ? c : '\0';
		}
	}

	fgets(ch, 100, fp);
	fgets(ch, 100, fp);

	int cmds[3];
	while(fgets(ch, 100, fp)) {
		parse_cmds(ch, cmds);
		//move_one(piles, cmds);
		move_multiple(piles, cmds);
	}
	
	fclose(fp);

	for (int i = 1; i <= pile_count; i++) {
		printf("%c", piles[i][strlen(piles[i]) - 1]);
	}

	return 0;
}

