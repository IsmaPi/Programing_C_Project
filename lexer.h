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
    TOKEN_LAMBDA_X,
    TOKEN_LAMBDA_Y,
    TOKEN_EOF,
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    int value; // Only used for TOKEN_INT and TOKEN_FLOAT
} Token;

#endif // LEXER_H
