#include <stdio.h>
#include <string.h>

char board[10][10] ;

int main ()
{
	int i, j, n,k;

	char b[128] ;
	char s[128] ;
	char t[128] ;

	// scanf("%s %s", b, b) ;
	for (k = 0 ; k < 81 ; k++) {
		scanf("%s %s %s %s %s", b, s, b, b, t) ;

		i = s[1] - '0' ;
		j = s[2] - '0' ;
		n = t[0] - '0' ;

	//	printf("s,b,t --> %s, %s, %s\n",s, b,t);

		board[i][j] = n ;
	}

	for (i = 1 ; i <= 9 ; i++) {
		for (j = 1 ; j <= 9 ; j++) {
			printf("%d ", board[i][j]) ;
		}
		printf("\n") ;
	}
}
