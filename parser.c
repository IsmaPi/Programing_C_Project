#include "lexer.c"
#include "parser.h"

//hierarchy:
// parse_expression -  for handling addition and subtraction.
// parse_term - for handling multiplication, division, and modulo.
// parse_factor - for handling numbers, parentheses

ASTNode *parse_expression(Token **tokens) {
    ASTNode *node = parse_term(tokens);

    while ((*tokens)->type == TOKEN_PLUS || (*tokens)->type == TOKEN_MINUS) {
        TokenType operation = (*tokens)->type;
        (*tokens)++; // consume the operator

        ASTNode *right = parse_term(tokens);
        ASTNode *new_node = create_node(operation, node, right);
        node = new_node;
    }

    return node;
}

ASTNode *parse_term(Token **tokens) {
    ASTNode *node = parse_factor(tokens);

    while ((*tokens)->type == TOKEN_STAR || (*tokens)->type == TOKEN_SLASH || (*tokens)->type == TOKEN_MODULO) {
        TokenType type = (*tokens)->type;
        (*tokens)++; // consume the operator

        ASTNode *right = parse_factor(tokens);
        ASTNode *new_node = create_node(type, node, right);
        node = new_node;
    }

    return node;
}

ASTNode *parse_power(Token **tokens) {
    ASTNode *node = parse_primary(tokens); // parse_primary handles numbers, parentheses, etc.

    while ((*tokens)->type == TOKEN_POWER) {
        (*tokens)++; // consume the '^'

        // Power is right-associative, so we call parse_power recursively
        ASTNode *right = parse_power(tokens);
        node = create_node(TOKEN_POWER, node, right);
    }

    return node;
}

ASTNode *parse_factor(Token **tokens) {
    if ((*tokens)->type == TOKEN_INT) {
        // Handle integer literals
        int value = (*tokens)->value;
        (*tokens)++; // Consume the number

        ASTNode *node = malloc(sizeof(*node));
        node->type = NODE_NUMBER;
        node->value = value;
        return node;
    } else if ((*tokens)->type == TOKEN_LPAREN) {
        // Handle expressions in parentheses
        (*tokens)++; // Consume the '('
        ASTNode *node = parse_expression(tokens);

        if ((*tokens)->type != TOKEN_RPAREN) {
            // Handle error: Expected ')'
        }
        (*tokens)++; // Consume the ')'
        return node;
    } else if ((*tokens)->type == TOKEN_SIN || (*tokens)->type == TOKEN_COS ||
         (*tokens)->type == TOKEN_TAN || (*tokens)->type == TOKEN_EXP || (*tokens)->type == TOKEN_LOG || (*tokens)->type == TOKEN_ACOS ||
         (*tokens)->type == TOKEN_ATAN || (*tokens)->type == TOKEN_ASIN){
    
        return parse_unary_op(tokens);
    }
    // Handle other cases or errors ... TO DO
}

