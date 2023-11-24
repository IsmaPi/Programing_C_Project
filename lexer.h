#ifndef LEXER_H
#define LEXER_H

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

// Token structure
typedef struct {
    TokenType type;
    int value; // Only used for TOKEN_INT
} Token;

#endif // LEXER_H