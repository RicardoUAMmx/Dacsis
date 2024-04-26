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

	if( argc != 5 ){
		printf( "Usage: %s <filename> <header> <separator> <quoted>\n" , argv[0] );
		exit( 1 );
	}

	FILE *fp;
	fp = fopen( fnm , "r" );
	if( fp == NULL ){
		printf( "File not found\n" );
		exit( 1 );
	}
	int header = atoi( argv[2] );
	char sep = argv[3][0];
	int quoted = argv[4][0];

	while( header-- ){
		while( fgetc( fp ) != '\n' );
	}

	long int start = ftell( fp );
	int c;
	int cols = 0;
	while( (c = fgetc( fp )) != '\n' ){
		if( c == sep ){
			cols++;
		} else if( c == quoted ){
			while( (c = fgetc( fp )) != quoted );
		}
	}
	fseek( fp , start , SEEK_SET );

	int i = 0, j = 0;
	char **line = ( char ** )malloc( sizeof( char * ) );
	line[j] = ( char * )malloc( sizeof( char ) * BUFF_CELL );
	while( (c = fgetc( fp )) != EOF ){
		if( c != sep && c != '\n' && c != quoted && i < BUFF_CELL ){
			line[j][i] = c;
			i++;
		} else if( c == quoted ){
			while( (c = fgetc( fp )) != quoted && i < BUFF_CELL ){
				line[j][i] = c;
				i++;
			}
		} else if( c == '\n' ){
			line[j][i] = '\0';
			j++;
			i = 0;
			line = ( char ** )realloc( line , sizeof( char * ) * j+1 );
			line[j] = ( char * )malloc( sizeof( char ) * BUFF_CELL );
		} else if ( c == sep ){
			line[j][i] = '\0';
			j++;
			i = 0;
			line = ( char ** )realloc( line , sizeof( char * ) * j+1 );
			line[j] = ( char * )malloc( sizeof( char ) * BUFF_CELL );
		} else if( i == BUFF_CELL ){
			printf( "Buffer overflow\n" );
			exit( 1 );
		}
	}

	for( i = 0; i < j; i=i+cols+1 ){
		printf( "%70s\n", line[i+1] );
	}

	for( i = 0; i < j+1; i++ ){
		free( line[i] );
	}
	free( line );

	fclose( fp );

	return 0;
}
