typedef enum {
identifier, keyword, op, delim, 
}
TypeOf;

typedef struct {
	TypeOf type;
	char *instance;
	int lineNum;
	int charPos;
} Token;
