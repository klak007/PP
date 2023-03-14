#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct stack
{
	int data;
	struct stack *next;
} stack;

int operand( char op )
{
	switch( op ) {
		case '+':
		case 'x':
		case '-':
		case '/':
			return 2;
		default:
			fputs( "Zly znak", stderr );
			exit( 1 );
	}
}
int pick( stack **front )
{
	if( *front == 0 ) {
		fputs( "Blad stosu\n", stderr );
		exit( 1 );
	} else {
		stack* top = *front;
		int value = top->data;
		*front = top->next;
		free( top );
		return value;
	}
}
void move_f( stack **front, int value )
{
	stack* place = malloc( sizeof(stack) );

	if( place == 0 ) {
		fputs( "Blad, nie ma miejsca\n", stderr );
		exit( 1 );
	} else {
		place->data = value;
		place->next = *front;
		*front = place;
	}
}

int calculate( char op, stack** front )
{
	int temp;
	switch( op ) {
		case '+': return pick(front) + pick(front);
		case 'x': return pick(front) * pick(front);
		case '-': temp = pick(front); return pick(front) - temp;
		case '/': temp = pick(front); return pick(front) / temp;
	}
}

int number_correct( char* number )
{
	for( ; *number; number++ )
		if( *number < '0' || *number > '9' )
			return 0;

	return 1;
}

int main( int argc, char** argv )
{
	int i, temp, stacksize = 0;
	stack* front = 0;

	if( argc == 1 )
	{
		printf("liczba liczba znak\n", argv[0]);
		exit(1);
	}

	for( i = 1; i < argc; i++ ) {
		char* token = argv[i];
		char* endptr;
		char op;

		if( number_correct( token ) ) {
			temp = atoi( token );
			move_f( &front, temp );
			++stacksize;
		} else {
			if( strlen( token ) != 1 ) {
				fprintf( stderr, "Blad\n", token );
				exit( 1 );
			}

			op = token[0];

			if( stacksize < operand( op ) ) {
				fputs( "Blad stosu\n", stderr );
				exit( 1 );
			}

			move_f( &front, calculate( op, &front ) );
			stacksize -= operand( op ) - 1;
		}
	}

	if( stacksize != 1 ) {
		fputs( "Blad stosu\n", stderr );
		exit( 1 );
	}

	printf( "Wynik: %i\n", front->data );

	return 0;
}