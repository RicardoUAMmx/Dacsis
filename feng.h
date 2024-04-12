#define BUFFER_LINE 1024
#define BUFFER_WORD 128

enum stopread { eof, eol };

int countCharFile( const char sep, FILE *fp, enum stopread stop, char quote );
void readLineFile( char *line, FILE *fp );
void readLineSplit( char *line, char **splitdat, char sep );
void readLineSplitQuoted( char *line, char **splitdat, char sep, char quote );

