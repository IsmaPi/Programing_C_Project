#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Helper function to match keywords
int match_keyword(char *source, const char *keyword, TokenType type, Token *token) {
    size_t len = strlen(keyword);
    if (strncmp(source, keyword, len) == 0 && !isalnum(source[len]) && source[len] != '_') {
        token->type = type;
        return len; // Length of the keyword
    }
    return 0; // No match
}

Token *tokenize(char *source) {
    int capacity = 10;
    Token *tokens = malloc(capacity * sizeof(Token));
    if (!tokens) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    int tokenCount = 0;
    int advance_len = 0;

    while (*source != '\0') {
        // Resize tokens array if necessary
        if (tokenCount >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token));
            if (!tokens) {
                fprintf(stderr, "Failed to reallocate memory\n");
                exit(EXIT_FAILURE);
            }
        }

        if (isdigit(*source)) {
            tokens[tokenCount].type = TOKEN_INT;
            tokens[tokenCount].value = strtol(source, &source, 10); // strtol advances the source pointer
        } else {
            // Check for mathematical functions and constants
            if ((advance_len = match_keyword(source, "cos", TOKEN_COS, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "sin", TOKEN_SIN, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "pi", TOKEN_PI, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "e", TOKEN_E, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "sqrt", TOKEN_SQRT, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "log", TOKEN_LOG, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "exp", TOKEN_EXP, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "abs", TOKEN_ABS, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "tan", TOKEN_TAN, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "asin", TOKEN_ASIN, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "acos", TOKEN_ACOS, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "atan", TOKEN_ATAN, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "derivative", TOKEN_DERIVATIVE, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "integral", TOKEN_INTEGRAL, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "power", TOKEN_POWER, &tokens[tokenCount])) ||
                (advance_len = match_keyword(source, "modulo", TOKEN_MODULO, &tokens[tokenCount])) ) {
                source += advance_len; // Advance the source pointer by the length of the keyword
            } else {
                // Handle single-character tokens
                switch (*source) {
                    case '+': tokens[tokenCount].type = TOKEN_PLUS; break;
                    case '-': tokens[tokenCount].type = TOKEN_MINUS; break;
                    case '*': tokens[tokenCount].type = TOKEN_STAR; break;
                    case '/': tokens[tokenCount].type = TOKEN_SLASH; break;
                    case '(': tokens[tokenCount].type = TOKEN_LPAREN; break;
                    case ')': tokens[tokenCount].type = TOKEN_RPAREN; break;
                    default: 
                        printf("Unexpected character: %c\n", *source);
                        exit(1);
                }
                source++; // Advance the source pointer by one character
            }
        }
        tokenCount++;
    }

    // Mark the end of the tokens
    tokens[tokenCount].type = TOKEN_EOF;
    return tokens;
}


// Function to print tokens for debugging
void printToken(Token token) {
    switch (token.type) {
        case TOKEN_INT: 
            printf("INT(%d) ", token.value); break;
        case TOKEN_PLUS: 
            printf("PLUS "); 
            break;
        case TOKEN_MINUS: 
            printf("MINUS "); 
            break;
        case TOKEN_STAR: 
            printf("STAR "); 
            break;
        case TOKEN_SLASH: 
            printf("SLASH "); 
            break;
        case TOKEN_LPAREN: 
            printf("LPAREN "); 
            break;
        case TOKEN_RPAREN: 
            printf("RPAREN "); 
            break;
        case TOKEN_EOF: 
            printf("EOF "); 
            break;
    }
}
