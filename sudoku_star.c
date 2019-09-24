#include <stdio.h>
#define N 9
#define f_name "text.txt"

typedef struct _Point {
	int col;
	int row;
} Point;
Point star_point[N];
int star_cnt = 0;

int board[N][N];
void init_board(); // [1-9, 0, -1] = [num, ?, *]


int
main ()
{
	FILE * fp = fopen("formula", "w") ;

	init_board();
	int i, j, r,s,n;
 
	for (i = 1 ; i <= N ; i++)
		for (j = 1 ; j <= N ; j++)
			fprintf(fp,"(declare-const p%d%d Int)\n", i, j) ;

	for(i = 0; i<N; i++) for(j = 0; j<N; j++) {
		if(board[i][j] > 0)
			fprintf(fp,"(assert (= p%d%d %d))",i+1,j+1,board[i][j]);
		else if(board[i][j] == -1) {
			Point point = {i,j};
			star_point[star_cnt] = point;
			star_cnt++;
		}
	}
	


	// Q1
	fprintf(fp,"; Q1\n") ;
	fprintf(fp,"(assert (and ") ;
	for (i = 1 ; i <= N ; i++) {
		fprintf(fp,"(and ") ;
		for (n = 1 ; n <= N ; n++) {
			fprintf(fp,"(or ") ;
			for(j = 1; j <=N; j++) {
				fprintf(fp,"(= p%d%d %d) ", i, j,n) ;
			}
			fprintf(fp,")") ;
		}
		fprintf(fp,")") ;
	}
	fprintf(fp,"))\n") ;
	// Q2
	fprintf(fp,"; Q2\n") ;
	fprintf(fp,"(assert (and ") ;
	for (j = 1 ; j <= N ; j++) {
		fprintf(fp,"(and ") ;
		for (n = 1 ; n <= N ; n++) {
			fprintf(fp,"(or ") ;
			for(i = 1; i <=N; i++) {
				fprintf(fp,"(= p%d%d %d) ", i, j,n) ;
			}
			fprintf(fp,")") ;
		}
		fprintf(fp,")") ;
	}
	fprintf(fp,"))\n") ;

	
	// Q3
	fprintf(fp,"; Q3\n") ;
	fprintf(fp,"(assert (and ") ;
	for (r = 0 ; r <= 2 ; r++) {
		fprintf(fp,"(and ") ;
		for (s = 0 ; s <= 2 ; s++) {
			fprintf(fp,"(and ") ;
			for(n = 1; n <=N; n++) {
				fprintf(fp,"(or ") ;
				for (i = 1 ; i <= 3 ; i++) {
					fprintf(fp,"(or ") ;
					for(j = 1; j <= 3; j++) {
						fprintf(fp,"(= p%d%d %d) ", 3*r+i, 3*s+j,n) ;
					}
					fprintf(fp,")") ;
				}
				fprintf(fp,")") ;
			}
			fprintf(fp,")") ;
		}
		fprintf(fp,")") ;
	}
	fprintf(fp,"))\n") ;

	// Q4
	fprintf(fp,"; Q4") ;
	fprintf(fp,"(assert (and ");
	for(i = 1; i < star_cnt; i++) {
		Point p1 = star_point[i] ;
		for(j = 0; j < i; j++) {
			Point p2 = star_point[j];
			
		}

	}
	fprintf(fp,"))\n") ;


	fprintf(fp,"(check-sat)\n(get-model)\n") ;

	fclose(fp);

	FILE * fin = popen("z3 formula", "r") ; //FIXME
	char buf[128] ;
	fscanf(fin, "%s %s", buf, buf) ;
	while (!feof(fin)) {
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
	}
	pclose(fin) ;
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
