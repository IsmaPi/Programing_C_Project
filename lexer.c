#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Helper function to match keywords
int match_keyword(char *source, const char *keyword, TokenType type, Token *token) {
    size_t len = strlen(keyword);
    if (strncmp(source, keyword, len) == 0 && (isspace(source[len]) || source[len] == '/0')) {
        token->type = type;
        return (int)len; // Length of the keyword
    }
    return 0;
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
        if (tokenCount >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token));
            if (!tokens) {
                fprintf(stderr, "Failed to reallocate memory\n");
                exit(EXIT_FAILURE);
            }
        }

        if (isdigit(*source) || *source == '.') {
            char *end;
            tokens[tokenCount].type = strtof(source, &end);
            if (end != source){
                tokens[tokenCount].type = (*source == '.') ? TOKEN_FLOAT : TOKEN_INT;
                source = end;
            }

        } else if (isalpha(*source) || *source == '_') {
            char *start = source;
            while (isalnum(*source) || *source == '_') {
                source++;
            }

            size_t len = source - start;
            tokens[tokenCount].varName = malloc(len + 1);
            if (!tokens[tokenCount].varName) {
                fprintf(stderr, "Failed to allocate memory\n");
                exit(EXIT_FAILURE);
            }
            strncpy(tokens[tokenCount].varName, start, len);
            tokens[tokenCount].varName[len] = '\0';
            tokens[tokenCount].type = TOKEN_VARIABLE;
        } else if ((advance_len = match_keyword(source, "cos", TOKEN_COS, &tokens[tokenCount])) ||
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
        case TOKEN_VARIABLE:
            printf("VARIABLE(%s) ", token.varName); 
            break;
        case TOKEN_FLOAT:
            printf("FLOAT(%f) ", token.value); 
            break;
        case TOKEN_EXP:
            printf("EXP "); 
            break;
        case TOKEN_SIN: 
            printf("SIN "); 
            break;
        case TOKEN_COS: 
            printf("COS "); 
            break;
        case TOKEN_ASIN: 
            printf("ASIN "); 
            break;
        case TOKEN_ACOS: 
            printf("ACOS "); 
            break;
        case TOKEN_TAN: 
            printf("TAN "); 
            break;
        case TOKEN_ATAN: 
            printf("ATAN "); 
            break;
        case TOKEN_PI: 
            printf("PI "); 
            break;
        case TOKEN_E: 
            printf("E "); 
            break;
        case TOKEN_SQRT: 
            printf("SQRT "); 
            break;
        case TOKEN_LOG: 
            printf("LOG "); 
            break;
        case TOKEN_ABS: 
            printf("ABS "); 
            break;
        case TOKEN_DERIVATIVE: 
            printf("DERIVATIVE "); 
            break;
        case TOKEN_INTEGRAL: 
            printf("INTEGRAL "); 
            break;
        case TOKEN_POWER: 
            printf("POWER "); 
            break;
        case TOKEN_MODULO: 
            printf("MODULO "); 
            break;
        case TOKEN_EOF: 
            printf("EOF "); 
            break;
    }
}
