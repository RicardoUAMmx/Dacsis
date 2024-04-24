#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dacsis.h"

int main( int argc, char **argv ){
	char *streamline = ( char * )malloc( BUFFER_LINE );
	long int savepos;
	int columns = 0, lines = 0;
	int c;

	int idxs[  ] = { 1, 3, 4, 5, 7, 8, 9, 10, -1 };
	int lenidxs = ( sizeof( idxs ) / sizeof( idxs[ 0 ] ) ) - 1;
	printf( "Selected columns: %d\n" , lenidxs );

	if( argv[1] == NULL ){
		printf( "No filename provided\n" );
		exit( 1 );
	}

	char fnm[32];
	if( strncpy( fnm, argv[1], 32 ) == NULL ){
		printf( "Error copying filename\n" );
		exit( 1 );
	}

	if( argc != 4 ){
		printf( "Usage: %s <filename> <header> <separator>\n" , argv[0] );
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

	while( header-- ){
		while( fgetc( fp ) != '\n' );
	}

	savepos = ftell( fp );
	columns = countCharFile( ',', fp, eol, '"' );
	columns++;
	fseek( fp , savepos , SEEK_SET );

	lines = countCharFile( '\n', fp, eof, '"' );
	fseek( fp , savepos , SEEK_SET );

	char **dataline = ( char ** )malloc( columns * sizeof( char * ) );
	for( int i = 0 ; i < columns ; i++ ){
		dataline[ i ] = ( char * )malloc( BUFFER_WORD );
	}

	char ***dacsis = ( char *** )malloc( lines * sizeof( char ** ) );
	for( int i = 0 ; i < lines ; i++ ){
		dacsis[ i ] = ( char ** )malloc( columns * sizeof( char * ) );
		for( int j = 0 ; j < columns ; j++ ){
			dacsis[ i ][ j ] = ( char * )malloc( BUFFER_WORD );
		}
	}

	printf( "\n" );
	printf( "---- Test Line: ----\n" );
	printf( "******************\n" );
	for( int i = 0 ; i < lines ; i++ ){
		readLineFile( streamline, fp );
		readLineSplitQuoted( streamline, dataline, sep, '"' );
		for( int j = 0; idxs[ j ] != -1 ; j++ ){
			strncpy( dacsis[ i ][ j ], dataline[ idxs[ j ] ], BUFFER_WORD );
		}
	}
	// for( int i = 0 ; i < lines ; i++ ){
	// 	for( int j = 0; j < lenidxs ; j++ ){
	// 		printf( "%s\t", dacsis[ i ][ j ] );
	// 	}
	// 	printf( "\n" );
	// }
	printf( "******************\n" );
	printf( "\n" );

	int repopenings = 0;
	for( int i = 1; i < lines; i++ ){
		for( int j = i - 1; j >= 0; j-- ){
			if( strcmp( dacsis[ i ][ 0 ], dacsis[ j ][ 0 ] ) == 0 ){
				repopenings++;
				break;
			} else {

			}
		}
	}

	char ***openings = ( char *** )malloc( ( lines ) * sizeof( char ** ) );
	for( int i = 0 ; i < lines ; i++ ){
		openings[ i ] = ( char ** )malloc( lenidxs * sizeof( char * ) );
		for( int j = 0 ; j < lenidxs ; j++ ){
			openings[ i ][ j ] = ( char * )malloc( BUFFER_WORD );
		}
	}

	for( int i = 0; i < lines ; i++ ){
		readLineSplit( dacsis[ i ][ 0 ], openings[ i ], ',' );
	}

	for( int i = 0; i < lines ; i++ ){
		for( int j = 0; strlen( openings[ i ][ j ] ) > 0; j++ ){
			printf( "%s\t", openings[ i ][ j ] );
		}
		printf( "\n" );
	}

	printf( "\n" );
	printf( "Number of repeated openings: %d\n" , repopenings );
	printf( "Number of unique values in openings: %d\n" , lines - repopenings);
	printf( "Total Number of columns: %d\n" , columns );
	printf( "Total Number of rows: %d\n" , lines );

	for( int i = 0 ; i < lines ; i++ ){
		for( int j = 0 ; j < columns ; j++ ){
			free( dacsis[ i ][ j ] );
		}
		free( dacsis[ i ] );
	}
	free( dacsis );
	for( int i = 0 ; i < columns ; i++ ){
		free( dataline[ i ] );
	}
	free( dataline );
	free( streamline );
	fclose( fp );
	return 0;
}
