#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
int score_pt2(char m, char n) {
	if (m == 'A' && n == 'X') { return 0 + 3;  }
	if (m == 'B' && n == 'X') { return 0 + 1;  }
	if (m == 'C' && n == 'X') { return 0 + 2;  }

	if (m == 'A' && n == 'Y') { return 3 + 1;  }
	if (m == 'B' && n == 'Y') { return 3 + 2;  }
	if (m == 'C' && n == 'Y') { return 3 + 3;  }

	if (m == 'A' && n == 'Z') { return 6 + 2;  }
	if (m == 'B' && n == 'Z') { return 6 + 3;  }
	if (m == 'C' && n == 'Z') { return 6 + 1;  }
 	return 0;
}

int score(char m, char n) {
	if(m == 'A' && n == 'A') return 3 + 1;	
	if(m == 'A' && n == 'B') return 6 + 2;
	if(m == 'A' && n == 'C') return 0 + 3;
	
	if(m == 'B' && n == 'B') return 3 + 2;	
	if(m == 'B' && n == 'A') return 0 + 1;	
	if(m == 'B' && n == 'C') return 6 + 3;	

	if(m == 'C' && n == 'C') return 3 + 3;
	if(m == 'C' && n == 'A') return 6 + 1;
	if(m == 'C' && n == 'B') return 0 + 2;

	return 0;
}

char translate(char x, char y, char z, char p) {
	if(p == 'X') return x;
	if(p == 'Y') return y;
	if(p == 'Z') return z;

	return 0;
}


int main(void) {
	char ch[4] = "";
	char file_name[] = ".//002_input.txt";
	//char file_name[] = ".//test";
	FILE *fp = fopen(file_name, "r");;

	int sum_XA_YB_ZC = 0;
	int sum_Xlose_Ydraw_Zwin = 0;

	char X = 'A'; char Y = 'B'; char Z = 'C';
	
	while(fgets(ch, 4, fp)) {
		sum_XA_YB_ZC += score(ch[0], translate(X,Y,Z, ch[2]));
		sum_Xlose_Ydraw_Zwin += score_pt2(ch[0], ch[2]);
	}

	fclose(fp);

	printf("%d\n",sum_XA_YB_ZC);
	printf("%d\n",sum_Xlose_Ydraw_Zwin); 

	return 0;
}
