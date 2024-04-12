#include <stdio.h>
#include "dacsis.h"

int countCharFile( const char sep, FILE *fp, enum stopread stop, char quote ){
	int c, counter = 0;
	switch( stop ){
		case eof:
			while( (c = fgetc(fp)) != EOF ){
				if( c == sep ){
					counter++;
				} else if( c == quote ){
					while( (c = fgetc(fp)) != quote );
				}
			}
			break;
		case eol:
			while( (c = fgetc(fp)) != '\n' ){
				if( c == sep ){
					counter++;
				} else if( c == quote ){
					while( (c = fgetc(fp)) != quote );
				}
			}
			break;
	}
	return counter;
}

void readLineFile( char *line, FILE *fp ){
	int c, i = 0;
	while( (c = fgetc(fp)) != '\n' ){
		line[i++] = c;
	}
	line[i] = '\0';
}

void readLineSplit( char *line, char **splitdat, char sep ){
	int i = 0, j = 0, k = 0;
	while( line[i] != '\0' ){
		if( line[i] == sep ){
			splitdat[j][k] = '\0';
			j++;
			k = 0;
		}else{
			splitdat[j][k++] = line[i];
		}
		i++;
	}
	splitdat[j][k] = '\0';
}

void readLineSplitQuoted( char *line, char **splitdat, char sep, char quote ){
	int i = 0, j = 0, k = 0;
	while( line[i] != '\0' ){
		if( line[i] == quote ){
			i++;
			while( line[i] != quote ){
				splitdat[j][k++] = line[i++];
			}
		}else if( line[i] == sep ){
			splitdat[j][k] = '\0';
			j++;
			k = 0;
		} else {
			splitdat[j][k++] = line[i];
		}
		i++;
	}
	splitdat[j][k] = '\0';
}


