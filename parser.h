typedef enum {
    TOKEN_INT, // Integer literals
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH, // Arithmetic operators
    TOKEN_LPAREN, TOKEN_RPAREN, // Parentheses
    TOKEN_SIN, TOKEN_COS, TOKEN_TAN, TOKEN_ATAN, TOKEN_ACOS, TOKEN_ASIN, //Tan, sin, cos
    TOKEN_LOG, TOKEN_EXP, 
    TOKEN_MODULO, TOKEN_POWER, 
    TOKEN_INTEGRATRE, TOKEN_DERIVATIVE, 

} TokenType;

typedef struct Token {
    TokenType type;
    union {
        int intValue;    // For integer values
        char *strValue;  // For strings, like function names
    };
} Token;


typedef enum {
    NODE_NUMBER,
    NODE_UNARY_OP,
    NODE_BINARY_OP
    // Add other node types as needed
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            TokenType operation; // For binary operations
        };
        struct {
            struct ASTNode *operand;
            TokenType function; // For unary operations like sin a
        };
        int value; // For integer literals
    };
} ASTNode;

ASTNode *parse_expression(Token **tokens) {
    ASTNode *node = parse_term(tokens); // parse_term to handle *, /, %

    while ((*tokens)->type == TOKEN_PLUS || (*tokens)->type == TOKEN_MINUS) {
        TokenType operation = (*tokens)->type;
        (*tokens)++; // consume the operator

        ASTNode *right = parse_term(tokens);
        ASTNode *new_node = malloc(sizeof(*new_node));
        new_node->type = NODE_BINARY_OP;
        new_node->operation = operation;
        new_node->left = node;
        new_node->right = right;
        node = new_node;
    }

    return node;
}


ASTNode *parse_term(Token **tokens) {
    ASTNode *node = parse_factor(tokens); // parse_factor to handle numbers, parentheses, etc.

    while ((*tokens)->type == TOKEN_STAR || (*tokens)->type == TOKEN_SLASH || (*tokens)->type == TOKEN_MODULO) {
        TokenType operation = (*tokens)->type;
        (*tokens)++; // consume the operator

        ASTNode *right = parse_factor(tokens);
        ASTNode *new_node = malloc(sizeof(*new_node));
        new_node->type = NODE_BINARY_OP;
        new_node->operation = operation;
        new_node->left = node;
        new_node->right = right;
        node = new_node;
    }

    return node;
}


ASTNode *parse_unary_op(Token **tokens) {
    TokenType functionType = (*tokens)->type;
    (*tokens)++; // Consume the 'sin' token

    if ((*tokens)->type != TOKEN_LPAREN) {
        // Handle error: Expected left parenthesis after 'sin'
    }
    (*tokens)++; // Consume the '(' token

    ASTNode *operand = parse_expression(tokens);

    if ((*tokens)->type != TOKEN_RPAREN) {
        // Handle error: Expected right parenthesis
    }
    (*tokens)++; // Consume the ')' token

    ASTNode *node = malloc(sizeof(*node));
    node->type = NODE_UNARY_OP;
    node->function = functionType;
    node->operand = operand;

    return node;
}





