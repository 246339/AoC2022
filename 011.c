#include <stdlib.h> 
#include <stdio.h>

typedef long int (*Operation)(const long int *a , const int *b );

typedef int (*Test)(const long int *a, const int *b); 

int divisible(const long int *a, const int *b){
	return *a % *b == 0 ? 1 : 0;
}

struct Monkey {
	long int items[30];
	int constant;
	Operation operation;
	int divisor;
	Test test;
	int cond_true;
	int cond_false;
	long int res;
};

long int multiply(const long int *a, const int *b) {
	long int b_ = *b == 0 ? *a : *b;
	return *a * b_;
}	

long int add(const long int *a, const int *b) {
	return *a + *b;
}

long int subtract(const long int *a, const int *b) {
	return *a - *b;
}	

Operation op_type(char c) {
	if (c == '*') return *multiply;
	if (c == '+') return *add;
	if (c == '-') return *subtract;
	return NULL;
}


int size(long int *arr) {
	int i = 0;
	while (*(arr+i) != 0) i++;
	return i;
}

int main(void) {

	//char * file = ".//test";
	char * file = ".//011_input.txt";

	FILE *fp = fopen(file, "r");
	
	int num_of_lines = 1;
	int c = fgetc(fp);
	while(c != EOF) {
		if (c == '\n') num_of_lines++;
		c = fgetc(fp);
	}
	rewind(fp);

	int num_of_monkeys = num_of_lines / 7;
	struct Monkey *monkeys = malloc(num_of_monkeys * sizeof *monkeys);

	long int divisors_multiplied = 1;

	for (int i = 0; i < num_of_monkeys; i++) {
		struct Monkey monkey = {{0}, 0, NULL, 0, NULL, 0, 0, 0}; 	
		
		c = fgetc(fp);
		while (c != '\n') c = fgetc(fp);
		c = ' ';
		fseek(fp, 17, SEEK_CUR);
		int j = 0;
		while (c != '\n') {
			int num = 0;
			fscanf(fp, "%d", &num);
			monkey.items[j] = num;
			c = fgetc(fp);
			j++;
		}
		fseek(fp, 23, SEEK_CUR);
		
		char op;
		int constant;

		if(fscanf(fp, "%c %d", &op, &constant) == 2) {
			monkey.constant = constant;
		} else {
			monkey.constant = 0;
		}
		monkey.operation = op_type(op);
		
		c = fgetc(fp);
		while (c != '\n') c = fgetc(fp);

		monkey.test = *divisible;
		fseek(fp, 21, SEEK_CUR);
		fscanf(fp, "%d", &monkey.divisor);
	
		divisors_multiplied *= monkey.divisor;

		fseek(fp, 29, SEEK_CUR);
		fscanf(fp, "%d", &monkey.cond_true);

		fseek(fp, 30, SEEK_CUR);
		fscanf(fp, "%d", &monkey.cond_false);

		fgetc(fp);
		fgetc(fp);

		monkey.res = 0;
		monkeys[i] = monkey;	
	}

	for (int k = 0; k < 10000; k++) {
		for (int i = 0; i < num_of_monkeys; i++) {
			int len = size(monkeys[i].items);
			int *b = &monkeys[i].constant;	
			Operation operation = monkeys[i].operation;		
			int *divisor = &monkeys[i].divisor;
			Test test = monkeys[i].test;
			int cond_true = monkeys[i].cond_true;
			int cond_false = monkeys[i].cond_false;
			long int *res = &monkeys[i].res;
			
			for (int j = 0; j < len; j++) {
				long int *item = &monkeys[i].items[j];
				long int new_worry_lvl = operation(item, b) % divisors_multiplied; 	
				//long int new_worry_lvl = operation(item, b) / 3; 	
				if (test(&new_worry_lvl, divisor)) {
					monkeys[cond_true].items[size(monkeys[cond_true].items)] = (new_worry_lvl);	
				} else {
					monkeys[cond_false].items[size(monkeys[cond_false].items)] = (new_worry_lvl);	
				}	
				(*res)++;
				*item = 0;
			}	
		}
	}
	
	long int max = 0;
	long int next_max = 0;
			
	for (int i = 0; i < num_of_monkeys; i++) {
		int num = monkeys[i].res;
		if (num >= max) {
	     		next_max = max;
			max = num;	
		} else if (num > next_max) {
			next_max = num;
		}
	}
	
	printf("%ld\n", max * next_max);

  	return 0;
}
