typedef enum {
    TOKEN_INT, // Integer literals
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH, // Arithmetic operators
    TOKEN_LPAREN, TOKEN_RPAREN, // Parentheses
    TOKEN_SIN, TOKEN_COS, TOKEN_TAN, TOKEN_ATAN, TOKEN_ACOS, TOKEN_ASIN, //Tan, sin, cos
    TOKEN_LOG, TOKEN_EXP, 
    TOKEN_MODULO, TOKEN_POWER, 
    TOKEN_INTEGRATRE, TOKEN_DERIVATIVE, 

} TokenType;

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

