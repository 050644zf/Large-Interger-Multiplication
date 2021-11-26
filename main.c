#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	char* number;	//字符串表示数
	int beg;		//起始位
	int end;		//结束位(不包含)
	int len;		//总位数
	int freeable;	//是否可被释放
}strn;			

/*释放strn*/
void free_strn(strn* n) {
	if (n->freeable)
		free(n->number);
}

/*返回实际位数*/
int digits(strn n) {
	return n.end - n.beg;
}

/*载入数字*/
strn loadNum(char* input, int len, int freeable) {
	strn newNum;
	newNum.number = input;
	newNum.beg = 0;
	newNum.end = len;
	newNum.len = len;
	newNum.freeable = freeable;
	return newNum;
}

/*初始化数字*/
strn initNum(int len) {
	char* num = malloc(sizeof(char) * len+1);
	for (int i = 0; i < len; i++) {
		num[i] = '0';
	}
	num[len] = '\0';
	strn n;
	n.number = num;
	n.beg = 0;
	n.end = len;
	n.len = len;
	n.freeable = 1;
	return n;
}

/*n = n * 10^i*/
void shift(strn* n, int d) {
	n->number = (char*)realloc(n->number, sizeof(char) * (n->len + 1));
	for (int i = n->len; i < d + n->len; i++) {
		n->number[i] = '0';
	}
	n->len += d;
	n->number[n->len] = '\0';
	n->end = n->len;
}

/*移除头部的0*/
void remove0(strn* n) {
	int counter = 0;
	while (n->number[counter] == '0') counter++;
	if (counter == n->len) counter--;
	if (counter) {
		char* newNum = (char*)malloc(sizeof(char) * (n->len - counter + 1));
		int r = strcpy_s(newNum, n->len - counter + 1, &n->number[counter], n->len - counter);
		free(n->number);
		n->number = newNum;
		n->end -= counter;
		n->len -= counter;
	}
}



/*n3 = n1 + n2*/
strn add(strn n1, strn n2) {
	int max_len = max(digits(n1), digits(n2));
	strn n3 = initNum(max_len + 1);
	int p1 = n1.end -1, p2 = n2.end -1, p3 = n3.end -1, carry = 0;
	while (p1 >= n1.beg && p2 >= n2.beg) {
		int result = (n1.number[p1] - '0') + (n2.number[p2] - '0') + carry;
		n3.number[p3] = result % 10 + '0';
		carry = result / 10;
		p1--;
		p2--;
		p3--;
	}
	while (p1 >= n1.beg) {
		int result = n1.number[p1] - '0' + carry;
		n3.number[p3] = result % 10 + '0';
		carry = result / 10;
		p1--;
		p3--;
	}
	while (p2 >= n2.beg) {
		int result = n2.number[p2] - '0' + carry;
		n3.number[p3] = result % 10 + '0';
		carry = result / 10;
		p2--;
		p3--;
	}
	if (carry) n3.number[p3] = '1';
	remove0(&n3);
	return n3;
}

/*往头部添加0到len*/
void add0(strn* n, int len) {
	if (n->len != len) {
		strn t1 = initNum(len);
		for (int i = 0; i <n->len; i++) {
			t1.number[len - n->len + i] = n->number[i];
		}
		free_strn(n);
		*n = t1;
	}
}

/*n3 = n1 -n2 (n1 > n2)*/
strn subtract(strn n1, strn n2) {
	strn n3 = initNum(n1.len);
	int p1 = n1.end - 1, p2 = n2.end - 1, p3 = n3.end - 1, carry = 0;
	while (p1 >= n1.beg && p2 >= n2.beg) {
		int result = (n1.number[p1] - '0') - (n2.number[p2] - '0') + carry;
		n3.number[p3] = (result+10) % 10 + '0';
		carry = result < 0 ? -1 : 0;
		p1--;
		p2--;
		p3--;
	}
	while (p1 >= n1.beg) {
		int result = n1.number[p1] - '0' + carry;
		n3.number[p3] = (result+10) % 10 + '0';
		carry = result < 0 ? -1 : 0;
		p1--;
		p3--;
	}
	remove0(&n3);
	return n3;
}

int partition(strn n, strn* A, strn* B) {
	if (digits(n) == 1) return 0;
	*A = n;
	*B = n;
	int mid = (n.end - n.beg) / 2;
	A->end = mid;
	B->beg = mid;
}


/*Karatsuba Algorithm
n3 = n1 * n2*/
strn mul(strn n1, strn n2) {
	int max_len = max(digits(n1), digits(n2));
	if (max_len == 1) {
		int result = (n1.number[n1.beg] - '0') * (n2.number[n2.beg] - '0');
		strn n3 = initNum(2);
		n3.number[1] = result % 10 + '0';
		n3.number[0] = result / 10 + '0';
		remove0(&n3);
		return n3;
	}
	add0(&n1, max_len);
	add0(&n2, max_len);
	strn A, B, C, D, E, F, AC, BD, EF, EF1, EF2, R1, R2;
	partition(n1, &A, &B);
	partition(n2, &C, &D);
	E = add(A, B);
	F = add(C, D);
	EF = mul(E, F);
	//free_strn(&E);
	//free_strn(&F);
	AC = mul(A, C);
	//free_strn(&A); free_strn(&C);
	BD = mul(B, D);
	//free_strn(&B); free_strn(&D);
	
	EF1 = subtract(EF, AC);
	
	EF2 = subtract(EF1, BD);
	
	shift(&EF2, 1);
	R1 = add(BD, EF2);
	//free_strn(&EF); free_strn(&EF1); free_strn(&BD); free_strn(&EF2);
	shift(&AC, 2);
	R2 = add(R1, AC);
	//free_strn(&AC);
	//free_strn(&E); free_strn(&F); free_strn(&AC); free_strn(&BD); free_strn(&EF); free_strn(&EF1); free_strn(&EF2); free_strn(&R1); 
	return R2;
}




int main() {

	char a1[] = "9";
	char a2[] = "999";
	strn n1 = loadNum(a1, strlen(a1), 0);
	strn n2 = loadNum(a2, strlen(a2), 0);
	strn n3 = mul(n1, n2);
	printf(n3.number);
	


	return 0;
}