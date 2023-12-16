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
    TOKEN_COS, 
    TOKEN_SIN,
    TOKEN_PI,
    TOKEN_E, 
    TOKEN_SQRT, 
    TOKEN_LOG, 
    TOKEN_EXP, 
    TOKEN_ABS, 
    TOKEN_TAN, 
    TOKEN_ASIN, 
    TOKEN_ACOS, 
    TOKEN_ATAN, 
    TOKEN_DERIVATIVE, 
    TOKEN_INTEGRAL,
    TOKEN_POWER, 
    TOKEN_MODULO, 
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
