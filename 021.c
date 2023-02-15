#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdio.h>

#define true 1
#define false 0

typedef long long (*Operation)(const long long a, const long long b);

typedef struct monkey {
	int value;
	char is_human;
	Operation op;
	struct monkey *left_monkey;
	struct monkey *right_monkey;
} Monkey;


long long multiply(const long long a, const long long b) {
	return a * b;
}	

long long add(const long long a, const long long b) {
	return a + b;
}

long long subtract(const long long a, const long long b) {
	return a - b;
}	

long long divide(const long long a, const long long b) {
	return a / b;
}	

Operation op_type(char c) {
	if (c == '*') return *multiply;
	if (c == '+') return *add;
	if (c == '-') return *subtract;
	if (c == '/') return *divide;

	return NULL;
}

Monkey *yelling_monkeys(FILE *fp, char *monkey) {

	char left_monkey[5] = {'\0'};
	char operator = '\0';
	char right_monkey[5] = {'\0'};
	
	rewind(fp);

	Monkey *root = malloc(sizeof(Monkey));
	root->value = 0;
	root->is_human = false;
	root->op = NULL;
	root->left_monkey = NULL;
	root->right_monkey = NULL;

	char temp_monkey[5];
	while (fgets(temp_monkey, 5,  fp)) {

		if(strcmp(temp_monkey, monkey) == 0) {
			fgetc(fp);
			fgetc(fp);
			int c = fgetc(fp);
			if (c >= 48 && c <= 57) {
				fseek(fp, -1, SEEK_CUR);
				fscanf(fp, "%d", &c);
				if(strcmp(temp_monkey, "humn") == 0) root->is_human = true;
				root->value = c;
				return root;
			}	

			fseek(fp, -1, SEEK_CUR);

			fscanf(fp, "%4s %c %4s\n", left_monkey, &operator, right_monkey);
			
		} else {
			while (fgetc(fp) != '\n') {}
		}
	}

	root->op = op_type(operator);
	root->left_monkey = yelling_monkeys(fp, left_monkey);		
	root->right_monkey = yelling_monkeys(fp, right_monkey);		
	
	return root;	
}


long long get_monkey_value(Monkey *monkey) {

	if (monkey->value) {
		return monkey->value;
	}	

	return monkey->op(get_monkey_value(monkey->left_monkey), get_monkey_value(monkey->right_monkey));
}

short has_human(Monkey *monkey) {
	if (monkey->is_human) return true;

	if (monkey->value) return false;

	return has_human(monkey->left_monkey) || has_human(monkey->right_monkey);
}	

long long balance_human(Monkey *monkey, long long to_balance) {
	
	if (monkey->is_human) { 
		return to_balance;       	
	}

	Monkey *left = monkey->left_monkey;
	Monkey *right = monkey->right_monkey;

	long long value;

	if (has_human(left)) {
	      	if (right->value) {	
			value = right->value;
		} else {
			value = get_monkey_value(right);
		}

		if (monkey->op == multiply) {
			to_balance = to_balance / value;
		}	
		if (monkey->op == add) {
			to_balance = to_balance - value;
		}	
		if (monkey->op == subtract) {
			to_balance = to_balance + value;
		}	
		if (monkey->op == divide) {
			to_balance = to_balance * value;
		}

		return balance_human(left, to_balance);	
	} else {
	      	if (left->value) {	
			value = left->value;
		} else {
			value = get_monkey_value(left);
		}

		if (monkey->op == multiply) {
			to_balance = to_balance / value;
		}	
		if (monkey->op == add) {
			to_balance = to_balance - value;
		}	
		if (monkey->op == subtract) {
			to_balance = value - to_balance;
		}	
		if (monkey->op == divide) {
			to_balance = value / to_balance;
		}	
		
		return balance_human(right, to_balance);	
	}
}



int main(void) {
	
	char *file = ".//021_input.txt";
	//char *file = ".//test";

	FILE *fp = fopen(file, "r");
	
	char left_monkey[5] = {'\0'};
	char operator = '\0';
	char right_monkey[5] = {'\0'};

	char temp_monkey[5];
	while (fgets(temp_monkey, 5,  fp)) {
		if(strcmp(temp_monkey, "root") == 0) {
			fscanf(fp, ": %4s %c %4s\n", left_monkey, &operator, right_monkey);
		} else {
			while (fgetc(fp) != '\n') {}
		}
	}

	Monkey *root = malloc(sizeof(Monkey));
	root->value = 0;
	root->is_human = false;
	root->op = op_type(operator);
	root->left_monkey = yelling_monkeys(fp, left_monkey);
	root->right_monkey = yelling_monkeys(fp, right_monkey);

	fclose(fp);

	printf("Ans pt1: %lld\n", get_monkey_value(root));
	
	Monkey *left = root->left_monkey;
	Monkey *right = root->right_monkey;
	
	long long l_val = get_monkey_value(left);
	long long r_val = get_monkey_value(right);
	
	if (has_human(left)) {  
		printf("Ans pt2: %lld\n", balance_human(left, r_val));	
	} else {
		printf("Ans pt2: %lld\n", balance_human(right, l_val));	
	}

  	return 0;
}

