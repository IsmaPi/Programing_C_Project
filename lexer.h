#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    TOKEN_INT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF, // End of file/input
} TokenType;

typedef struct {
    TokenType type;
    int value; // Only used for TOKEN_INT
} Token;

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

// ... [Token types and Token struct here] ...

Token *tokenize(char *source) {
    int capacity = 10;
    Token *tokens = malloc(capacity * sizeof(Token));
    int tokenCount = 0;

    while (*source != '\0') {
        // Resize tokens array if necessary
        if (tokenCount >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token));
        }

        if (isdigit(*source)) {
            // Tokenizing a number
            tokens[tokenCount].type = TOKEN_INT;
            tokens[tokenCount].value = strtol(source, &source, 10); // strtol advances the source pointer
        } else {
            switch (*source) {
                case '+': 
                    tokens[tokenCount].type = TOKEN_PLUS; 
                    break;
                case '-': 
                    tokens[tokenCount].type = TOKEN_MINUS; 
                    break;
                case '*': 
                    tokens[tokenCount].type = TOKEN_STAR; 
                    break;
                case '/': 
                    tokens[tokenCount].type = TOKEN_SLASH; 
                    break;
                case '(': 
                    tokens[tokenCount].type = TOKEN_LPAREN; 
                    break;
                case ')': 
                    tokens[tokenCount].type = TOKEN_RPAREN; 
                    break;
                default: 
                    printf("Unexpected character: %c\n", *source);
                    exit(1);
            }
            source++;
        }
        tokenCount++;
    }

    // Mark the end of the tokens
    tokens[tokenCount].type = TOKEN_EOF;
    return tokens;
}

