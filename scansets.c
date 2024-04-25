#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_FNAME 32
#define BUFF_CELL 256

int main( int argc, char **argv ){
	if( argv[1] == NULL ){
		printf( "No filename provided\n" );
		exit( 1 );
	}

	char fnm[BUFF_FNAME];
	strncpy( fnm , argv[1] , BUFF_FNAME );

	FILE *fp;
	fp = fopen( fnm , "r" );
	if( fp == NULL ){
		printf( "File not found\n" );
		exit( 1 );
	}
	char sep = ',';
	char quoted = '"';

	int c, i = 0, j = 0;
	char **line = ( char ** )malloc( sizeof( char * ) );
	line[j] = ( char * )malloc( sizeof( char ) * BUFF_CELL );
	while( (c = fgetc( fp )) != EOF ){
		if( c != sep && c != '\n' && c != quoted && i < BUFF_CELL ){
			printf("Debug: %c\n", c);
			line[j][i] = c;
			i++;
		} else if ( c == quoted ){
			while( (c = fgetc( fp )) != quoted && i < BUFF_CELL ){
				printf("Debug: %c\n", c);
				line[j][i] = c;
				i++;
			}
		} else if( c == '\n' ){
			line[j][i] = '\0';
			j++;
			line = ( char ** )realloc( line , sizeof( char * ) * j+1 );
		} else {
			line[j][i] = '\0';
			j++;
			line = ( char ** )realloc( line , sizeof( char * ) * j+1 );
		}
	}

	printf( "Debug: %d\n" , j );
	for( i = 0; i < j+1; i++ ){
		printf( "%s\n" , line[i] );
	}

	for( i = 0; i < j+1; i++ ){
		free( line[i] );
	}
	free( line );

	fclose( fp );

	return 0;
}
