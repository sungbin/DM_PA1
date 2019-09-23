#include <stdio.h>
#define N 9
#define f_name "text.txt"

typedef struct _Point {
	int col;
	int row;
} Point;
Point ques_point[N*N];
int ques_cnt = 0;
Point star_point[N];
int star_cnt = 0;

int board[N][N];
void init_board(); // [1-9, 0, -1] = [num, ?, *]


int
main ()
{
	init_board();
	int i, j, r,s,n;
 
	for (i = 1 ; i <= N ; i++)
		for (j = 1 ; j <= N ; j++)
			printf("(declare-const p%d%d Int)\n", i, j) ;

	for(i = 0; i<N; i++) for(j = 0; j<N; j++) {
		if(board[i][j] > 0)
			printf("(assert (= p%d%d %d))",i+1,j+1,board[i][j]);
		else if(board[i][j] == 0) {
			Point point = {i,j};
			ques_point[ques_cnt] = point;
			ques_cnt++;
		}
		else if(board[i][j] == -1) {
			Point point = {i,j};
			star_point[star_cnt] = point;
			star_cnt++;
		}
	}
	


	// Q1
	printf("; Q1\n") ;
	printf("(assert (and ") ;
	for (i = 1 ; i <= N ; i++) {
		printf("(and ") ;
		for (n = 1 ; n <= N ; n++) {
			printf("(or ") ;
			for(j = 1; j <=N; j++) {
				printf("(= p%d%d %d) ", i, j,n) ;
			}
			printf(")") ;
		}
		printf(")") ;
	}
	printf("))\n") ;
	// Q2
	printf("; Q2\n") ;
	printf("(assert (and ") ;
	for (j = 1 ; j <= N ; j++) {
		printf("(and ") ;
		for (n = 1 ; n <= N ; n++) {
			printf("(or ") ;
			for(i = 1; i <=N; i++) {
				printf("(= p%d%d %d) ", i, j,n) ;
			}
			printf(")") ;
		}
		printf(")") ;
	}
	printf("))\n") ;

	
	// Q3
	printf("; Q3\n") ;
	printf("(assert (and ") ;
	for (r = 0 ; r <= 2 ; r++) {
		printf("(and ") ;
		for (s = 0 ; s <= 2 ; s++) {
			printf("(and ") ;
			for(n = 1; n <=N; n++) {
				printf("(or ") ;
				for (i = 1 ; i <= 3 ; i++) {
					printf("(or ") ;
					for(j = 1; j <= 3; j++) {
						printf("(= p%d%d %d) ", 3*r+i, 3*s+j,n) ;
					}
					printf(")") ;
				}
				printf(")") ;
			}
			printf(")") ;
		}
		printf(")") ;
	}
	printf("))\n") ;

	printf("(check-sat)\n(get-model)\n") ;
}
void init_board() {// [1-9, 0, -1] = [num, ?, *]
	FILE* f;
	f = fopen(f_name,"r");
	if(f == NULL) {
		fprintf(stderr,"file open error\n");
		exit(1);
	}
	int c;

	int cnt = 0;
	do {
		c = getc(f);
		int col = cnt / N;
		int row = cnt % N;
		getc(f);

		if(c == ' ' || c == '\t') {
			continue;
		} else if(c == '?') {
			board[col][row] = 0;
		} else if(c == '*') {
			board[col][row] = -1;
		} else {
			board[col][row] = c - '1'+1;
		}
		cnt ++;
	} while(c != EOF && cnt < N * N);

}
