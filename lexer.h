#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_VARIABLE, // General variable token type
    TOKEN_EOF,
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    union {
        int intValue;    // For TOKEN_INT
        float floatValue; // For TOKEN_FLOAT
        char* varName;    // For TOKEN_VARIABLE
    };
} Token;

#endif // LEXER_H
