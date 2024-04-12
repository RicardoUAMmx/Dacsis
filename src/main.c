#include <stdio.h>
#include <stdlib.h>
#include "dacsis.h"

int main(  ){
	FILE *fp;
	char *streamline = ( char * )malloc( BUFFER_LINE );
	int header = 1;
	char sep = ',';
	long int savepos;
	int columns = 0, lines = 0;
	int c;

	fp = fopen( "data/openings.csv" , "r" );
	if( fp == NULL ){
		printf( "File not found\n" );
		return 0;
	}

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

	printf( "Number of columns: %d\n" , columns );
	printf( "Number of rows: %d\n" , lines - header );
	printf( "\n" );
	printf( "---- Header: ----\n" );
	printf( "******************\n" );
	readLineFile( streamline, fp );
	readLineSplitQuoted( streamline, dataline, sep, '"' );
	for( int i = 0 ; i < columns ; i++ ){
		printf( "%s\n" , dataline[ i ] );
	}
	printf( "******************\n" );
	printf( "\n" );

	for( int i = 0 ; i < columns ; i++ ){
		free( dataline[ i ] );
	}
	free( dataline );
	free( streamline );
	fclose( fp );
	return 0;
}
