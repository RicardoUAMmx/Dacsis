#define BUFFER_LINE 2048
#define BUFFER_WORD 256

enum stopread { eof, eol };

int countCharFile( const char sep, FILE *fp, enum stopread stop, char quote );
void readLineFile( char *line, FILE *fp );
void readLineSplit( char *line, char **splitdat, char sep );
void readLineSplitQuoted( char *line, char **splitdat, char sep, char quote );
int countDacsis( char ***dacsis );
