#include <stdlib.h> 
#include <math.h> 
#include <stdio.h>

int trans_from(char c) {
	if (c == '2') return 2;
	if (c == '1') return 1;
	if (c == '0') return 0;
	if (c == '-') return -1;
	if (c == '=') return -2;
	return c;
}

char trans_to(int c) {
	if (c == 2) return '2';
	if (c == 1) return '1';
	if (c == 0) return '0';
	if (c == -1) return '-';
	if (c == -2) return '=';
	return c;
}

long long helper(int x) {
	if (x <= 0) return 2;
	return 2 * pow(5, x) + helper(x - 1);
}

long long my_pow(int x) {
	if (x == 0) return 1;
	return 5 * my_pow(x - 1);
}

int main(void) {

	//char *file = ".//test";
	char *file = ".//025_input.txt";

	FILE *fp = fopen(file, "r");

	char line[100] = {'\0'};

	long long sum = 0;
	while(fgets(line, 100, fp)) {
		int i = 0;
		int c = line[i];
		while(c != '\n') {
			c = line[i];
			i++;
		}
		i--;
		for (int j = i; j > 0; j--) {
			sum += trans_from(line[j -1]) * my_pow( i - j);  	
		}
	}

	char res[30] = {'\0'};

	int x = 1;
	while (1) {
		if (my_pow(x) >= sum || 2*my_pow(x) >= sum) break;
		x++;
	}

	int index = 0;
	long long temp = sum > my_pow(x) ? 2 * my_pow(x) : my_pow(x);
	res[index] = sum > my_pow(x) ? '2' : '1';

	for (int i = x -1; i >= 0; i--) {
		index++;	
		for (int j = -2; j <= 2; j++) {
			if(llabs(temp + (j *  my_pow(i)) - sum) <= helper(i -1)) {
				
				if (i != 0) {
					temp += j * my_pow(i);
				}
				res[index] = trans_to(j);
				break;
			}
		}
	}

	res[index] = trans_to(sum - temp);

	res[index + 1] = '\0';
	printf("%s\n", res);

  	return 0;
}

