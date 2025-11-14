#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

parser_T* init_parser(lexer_T* lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lerxer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    return parser;
}

void parser_eat(parser_T* parser, int token_type) {
    if (parser->current_token == NULL) {
        printf("Parser error: Unexpected end of input, was expecting token type `%d`\n", token_type);
        exit(1);
    }
    
    if (parser->current_token->type == token_type) {
        parser->current_token = lexer_get_next_token(parser->lerxer);
    } else {
        printf("Unexpected token `%s` (type %d), was expecting type `%d`\n", 
               parser->current_token->value, parser->current_token->type, token_type);
        exit(1);
    }
}

AST_T* parser_parse(parser_T* parser) {
    return parser_parse_statements(parser);
}

AST_T* parser_parse_statement(parser_T* parser) {
    switch (parser->current_token->type) {
        case TOKEN_BUCKET:
            return parser_parse_variable_definition(parser);
        case TOKEN_SHOW:
        case TOKEN_ASK:
        case TOKEN_LEN:
        case TOKEN_PUSH:
        case TOKEN_POP:
        case TOKEN_SAFE_DIVIDE:
        case TOKEN_ERROR:
        case TOKEN_HTTP_GET:
        case TOKEN_HTTP_POST:
        case TOKEN_DOWNLOAD:
        case TOKEN_IS_ONLINE:
        // Math module
        case TOKEN_MATH_SQRT:
        case TOKEN_MATH_POW:
        case TOKEN_MATH_ABS:
        case TOKEN_MATH_MAX:
        case TOKEN_MATH_MIN:
        case TOKEN_MATH_ROUND:
        case TOKEN_MATH_RANDOM:
        case TOKEN_MATH_RANDOM_RANGE:
        // String module
        case TOKEN_STRING_SPLIT:
        case TOKEN_STRING_JOIN:
        case TOKEN_STRING_REPLACE:
        case TOKEN_STRING_TO_UPPER:
        case TOKEN_STRING_TO_LOWER:
        case TOKEN_STRING_TRIM:
        case TOKEN_STRING_CONTAINS:
        case TOKEN_STRING_STARTS_WITH:
        // Array module
        case TOKEN_ARRAY_SORT:
        case TOKEN_ARRAY_REVERSE:
        case TOKEN_ARRAY_UNIQUE:
        case TOKEN_ARRAY_FIND:
        case TOKEN_ARRAY_SLICE:
        // File module
        case TOKEN_FILE_READ:
        case TOKEN_FILE_WRITE:
        case TOKEN_FILE_EXISTS:
        case TOKEN_FILE_DELETE:
        case TOKEN_FILE_SIZE:
        // JSON module
        case TOKEN_JSON_PARSE:
        case TOKEN_JSON_STRINGIFY:
        case TOKEN_JSON_GET:
        case TOKEN_JSON_SET:
        // Time module
        case TOKEN_TIME_NOW:
        case TOKEN_TIME_FORMAT:
        case TOKEN_TIME_SLEEP:
        // System module
        case TOKEN_SYSTEM_RUN:
        case TOKEN_SYSTEM_GET_ENV: {
            // Built-in function calls
            AST_T* func_call = parser_parse_function_call(parser);
            parser_eat(parser, TOKEN_SEMI);
            return func_call;
        }
        case TOKEN_PUTLIB: {
            // Import statement
            return parser_parse_import(parser);
        }
        case TOKEN_NOTE: {
            // Comment handling - skip the note token and everything until end of line
            parser_eat(parser, TOKEN_NOTE);
            parser_eat(parser, TOKEN_COLON);
            
            // Skip all tokens until we find a semicolon or reach end of statement
            while (parser->current_token != NULL && 
                   parser->current_token->type != TOKEN_SEMI &&
                   parser->current_token->type != TOKEN_RBRACE &&
                   parser->current_token->type != TOKEN_BUCKET &&
                   parser->current_token->type != TOKEN_SHOW &&
                   parser->current_token->type != TOKEN_NOTE) {
                parser->current_token = lexer_get_next_token(parser->lerxer);
            }
            
            // Return null to indicate this statement should be ignored
            return NULL;
        }
        case TOKEN_ID: {
            // Check for multi-word keywords
            if (strcmp(parser->current_token->value, "when") == 0) {
                return parser_parse_when_if(parser);
            }
            if (strcmp(parser->current_token->value, "while") == 0) {
                return parser_parse_while_loop(parser);
            }
            if (strcmp(parser->current_token->value, "for") == 0) {
                return parser_parse_for_loop(parser);
            }
            if (strcmp(parser->current_token->value, "make") == 0) {
                return parser_parse_function_definition(parser);
            }
            if (strcmp(parser->current_token->value, "give") == 0) {
                return parser_parse_return(parser);
            }
            // Function call or variable reference
            lexer_T* temp_lexer = parser->lerxer;
            unsigned int saved_pos = temp_lexer->i;
            char saved_char = temp_lexer->c;
            
            // Skip current token
            while (temp_lexer->c != '\0' && (isalnum(temp_lexer->c) || temp_lexer->c == '_')) {
                lexer_advance(temp_lexer);
            }
            lexer_skip_whitespace(temp_lexer);
            
            if (temp_lexer->c == '(') {
                // Restore lexer state
                temp_lexer->i = saved_pos;
                temp_lexer->c = saved_char;
                
                AST_T* func_call = parser_parse_function_call(parser);
                parser_eat(parser, TOKEN_SEMI);
                return func_call;
            } else if (temp_lexer->c == '=') {
                // Assignment statement
                // Restore lexer state
                temp_lexer->i = saved_pos;
                temp_lexer->c = saved_char;
                
                AST_T* assignment = parser_parse_assignment(parser);
                parser_eat(parser, TOKEN_SEMI);
                return assignment;
            } else {
                // Variable reference
                // Restore lexer state
                temp_lexer->i = saved_pos;
                temp_lexer->c = saved_char;
                
                AST_T* var = parser_parse_variable(parser);
                parser_eat(parser, TOKEN_SEMI);
                return var;
            }
        }
    }
    
    return init_ast(AST_COMPOUND);
}

AST_T* parser_parse_statements(parser_T* parser) {
    AST_T* compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));
    
    // Check if we have any statements to parse
    if (parser->current_token == NULL || parser->current_token->type == TOKEN_RBRACE) {
        compound->compound_size = 0;
        return compound;
    }
    
    AST_T* ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;
    
    int statement_count = 0;
    int max_statements = 1000; // Allow up to 1000 statements
    
    while (parser->current_token != NULL && parser->current_token->type != TOKEN_RBRACE && statement_count < max_statements) {
        // Save current token to detect infinite loops
        token_T* prev_token = parser->current_token;
        char* prev_token_value = prev_token ? prev_token->value : NULL;
        
        AST_T* ast_statement = parser_parse_statement(parser);
        
        // Safety check: if token didn't advance AND we got a null statement, try to advance manually
        if (parser->current_token == prev_token && ast_statement == NULL) {
            // Try to advance to next meaningful token
            parser->current_token = lexer_get_next_token(parser->lerxer);
            if (parser->current_token == prev_token) {
                // Still stuck, break to prevent infinite loop
                printf("Parser warning: Skipping unrecognized token and continuing\n");
                break;
            }
        }
        
        // Only add non-null statements (this allows comments to be skipped)
        if (ast_statement) {
            compound->compound_size += 1;
            compound->compound_value = realloc(
                compound->compound_value, 
                compound->compound_size * sizeof(struct AST_STRUCT*)
            );
            compound->compound_value[compound->compound_size-1] = ast_statement;
        }
        
        statement_count++;
    }
    
    return compound;
}

AST_T* parser_parse_expr(parser_T* parser) {
    return parser_parse_binary_op(parser);
}

AST_T* parser_parse_binary_op(parser_T* parser) {
    AST_T* left = parser_parse_term(parser);
    
    while (parser->current_token != NULL && 
           (parser->current_token->type == TOKEN_PLUS ||
            parser->current_token->type == TOKEN_MINUS ||
            parser->current_token->type == TOKEN_MULTIPLY ||
            parser->current_token->type == TOKEN_DIVIDE ||
            parser->current_token->type == TOKEN_EQ ||
            parser->current_token->type == TOKEN_NEQ ||
            parser->current_token->type == TOKEN_GT ||
            parser->current_token->type == TOKEN_LT ||
            parser->current_token->type == TOKEN_GTE ||
            parser->current_token->type == TOKEN_LTE)) {
        
        int op_type = parser->current_token->type;
        parser_eat(parser, op_type);
        
        AST_T* right = parser_parse_term(parser);
        
        AST_T* binary_op = init_ast(AST_BINARY_OP);
        binary_op->binary_op_left = left;
        binary_op->binary_op_right = right;
        binary_op->binary_op_type = op_type;
        
        left = binary_op;
    }
    
    return left;
}

AST_T* parser_parse_factor(parser_T* parser) {
    switch (parser->current_token->type) {
        case TOKEN_LPAREN: {
            parser_eat(parser, TOKEN_LPAREN);
            AST_T* node = parser_parse_expr(parser);
            parser_eat(parser, TOKEN_RPAREN);
            return node;
        }
        case TOKEN_LBRACKET:
            return parser_parse_array(parser);
        case TOKEN_STRING:
            return parser_parse_string(parser);
        case TOKEN_NUMBER:
            return parser_parse_number(parser);
        case TOKEN_FLOAT:
            return parser_parse_float(parser);
        case TOKEN_YES:
        case TOKEN_NO:
            return parser_parse_boolean(parser);
        case TOKEN_SHOW:
        case TOKEN_ASK:
        case TOKEN_LEN:
        case TOKEN_PUSH:
        case TOKEN_POP:
        case TOKEN_SAFE_DIVIDE:
        case TOKEN_ERROR:
        case TOKEN_HTTP_GET:
        case TOKEN_HTTP_POST:
        case TOKEN_DOWNLOAD:
        case TOKEN_IS_ONLINE:
        // Math module
        case TOKEN_MATH_SQRT:
        case TOKEN_MATH_POW:
        case TOKEN_MATH_ABS:
        case TOKEN_MATH_MAX:
        case TOKEN_MATH_MIN:
        case TOKEN_MATH_ROUND:
        case TOKEN_MATH_RANDOM:
        case TOKEN_MATH_RANDOM_RANGE:
        // String module
        case TOKEN_STRING_SPLIT:
        case TOKEN_STRING_JOIN:
        case TOKEN_STRING_REPLACE:
        case TOKEN_STRING_TO_UPPER:
        case TOKEN_STRING_TO_LOWER:
        case TOKEN_STRING_TRIM:
        case TOKEN_STRING_CONTAINS:
        case TOKEN_STRING_STARTS_WITH:
        // Array module
        case TOKEN_ARRAY_SORT:
        case TOKEN_ARRAY_REVERSE:
        case TOKEN_ARRAY_UNIQUE:
        case TOKEN_ARRAY_FIND:
        case TOKEN_ARRAY_SLICE:
        // File module
        case TOKEN_FILE_READ:
        case TOKEN_FILE_WRITE:
        case TOKEN_FILE_EXISTS:
        case TOKEN_FILE_DELETE:
        case TOKEN_FILE_SIZE:
        // JSON module
        case TOKEN_JSON_PARSE:
        case TOKEN_JSON_STRINGIFY:
        case TOKEN_JSON_GET:
        case TOKEN_JSON_SET:
        // Time module
        case TOKEN_TIME_NOW:
        case TOKEN_TIME_FORMAT:
        case TOKEN_TIME_SLEEP:
        // System module
        case TOKEN_SYSTEM_RUN:
        case TOKEN_SYSTEM_GET_ENV:
            // Built-in functions are always function calls
            return parser_parse_function_call(parser);
        case TOKEN_ID: {
            // Look ahead to determine if this is a function call or variable
            lexer_T* temp_lexer = parser->lerxer;
            unsigned int saved_pos = temp_lexer->i;
            char saved_char = temp_lexer->c;
            
            // Skip current identifier
            while (temp_lexer->c != '\0' && (isalnum(temp_lexer->c) || temp_lexer->c == '_')) {
                lexer_advance(temp_lexer);
            }
            lexer_skip_whitespace(temp_lexer);
            
            if (temp_lexer->c == '(') {
                // It's a function call - restore lexer state and parse as function call
                temp_lexer->i = saved_pos;
                temp_lexer->c = saved_char;
                return parser_parse_function_call(parser);
            } else if (temp_lexer->c == '[') {
                // It's array access - restore lexer state and parse normally
                temp_lexer->i = saved_pos;
                temp_lexer->c = saved_char;
                
                char* identifier_value = calloc(strlen(parser->current_token->value) + 1, sizeof(char));
                strcpy(identifier_value, parser->current_token->value);
                parser_eat(parser, TOKEN_ID);
                
                if (parser->current_token->type == TOKEN_LBRACKET) {
                    // It's array access - parse directly without restoring lexer
                    // Current token is already '[', so parse index expression
                    parser_eat(parser, TOKEN_LBRACKET);
                    AST_T* index_expr = parser_parse_expr(parser);
                    parser_eat(parser, TOKEN_RBRACKET);
                    
                    // Create array access AST
                    AST_T* array_access = init_ast(AST_ARRAY_ACCESS);
                    array_access->array_access_name = identifier_value;  // Use the saved identifier
                    array_access->array_access_index = index_expr;
                    return array_access;
                } else {
                    // It's a variable - create variable AST with saved identifier
                    AST_T* ast_variable = init_ast(AST_VARIABLE);
                    ast_variable->variable_name = identifier_value;
                    return ast_variable;
                }
            } else {
                // It's a variable - restore lexer state and parse as variable
                temp_lexer->i = saved_pos;
                temp_lexer->c = saved_char;
                return parser_parse_variable(parser);
            }
        }
    }
    
    return init_ast(AST_COMPOUND);
}

AST_T* parser_parse_term(parser_T* parser) {
    return parser_parse_factor(parser);
}

AST_T* parser_parse_function_call(parser_T* parser) {
    AST_T* function_call = init_ast(AST_FUNCTION_CALL);
    
    function_call->function_call_name = calloc(
        strlen(parser->current_token->value) + 1, sizeof(char)
    );
    strcpy(function_call->function_call_name, parser->current_token->value);
    
    // Accept both TOKEN_ID and keyword tokens as function names
    int current_type = parser->current_token->type;
    parser_eat(parser, current_type);
    
    parser_eat(parser, TOKEN_LPAREN);
    
    function_call->function_call_arguments = calloc(1, sizeof(struct AST_STRUCT*));
    function_call->function_call_arguments_size = 0;
    
    // Check if there are any arguments
    if (parser->current_token->type != TOKEN_RPAREN) {
        AST_T* ast_expr = parser_parse_expr(parser);
        function_call->function_call_arguments[0] = ast_expr;
        function_call->function_call_arguments_size = 1;
        
        while (parser->current_token->type == TOKEN_COMMA) {
            parser_eat(parser, TOKEN_COMMA);
            
            function_call->function_call_arguments_size += 1;
            function_call->function_call_arguments = realloc(
                function_call->function_call_arguments,
                function_call->function_call_arguments_size * sizeof(struct AST_STRUCT*)
            );
            
            AST_T* ast_expr = parser_parse_expr(parser);
            function_call->function_call_arguments[function_call->function_call_arguments_size-1] = ast_expr;
        }
    }
    
    parser_eat(parser, TOKEN_RPAREN);
    
    return function_call;
}

AST_T* parser_parse_variable(parser_T* parser) {
    char* token_value = parser->current_token->value;
    parser_eat(parser, parser->current_token->type);
    
    AST_T* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = calloc(strlen(token_value) + 1, sizeof(char));
    strcpy(ast_variable->variable_name, token_value);
    
    return ast_variable;
}

AST_T* parser_parse_assignment(parser_T* parser) {
    AST_T* assignment = init_ast(AST_ASSIGNMENT);
    
    // Get variable name
    assignment->assignment_variable_name = calloc(
        strlen(parser->current_token->value) + 1, sizeof(char)
    );
    strcpy(assignment->assignment_variable_name, parser->current_token->value);
    
    parser_eat(parser, TOKEN_ID); // eat variable name
    parser_eat(parser, TOKEN_EQUALS); // eat '='
    
    // Parse the value expression
    assignment->assignment_value = parser_parse_expr(parser);
    
    return assignment;
}

AST_T* parser_parse_string(parser_T* parser) {
    AST_T* ast_string = init_ast(AST_STRING);
    ast_string->string_value = calloc(
        strlen(parser->current_token->value) + 1, sizeof(char)
    );
    strcpy(ast_string->string_value, parser->current_token->value);
    
    parser_eat(parser, TOKEN_STRING);
    
    return ast_string;
}

AST_T* parser_parse_variable_definition(parser_T* parser) {
    parser_eat(parser, TOKEN_BUCKET);
    char* variable_definition_variable_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);
    
    // Check for array syntax: bucket name[] = [...]
    if (parser->current_token->type == TOKEN_LBRACKET) {
        parser_eat(parser, TOKEN_LBRACKET);
        parser_eat(parser, TOKEN_RBRACKET); // Empty brackets for array declaration
    }
    
    parser_eat(parser, TOKEN_EQUALS);
    AST_T* variable_definition_value = parser_parse_expr(parser);
    parser_eat(parser, TOKEN_SEMI);
    
    AST_T* variable_definition = init_ast(AST_VARIABLE_DEFINITION);
    variable_definition->variable_definition_variable_name = calloc(
        strlen(variable_definition_variable_name) + 1, sizeof(char)
    );
    strcpy(variable_definition->variable_definition_variable_name, variable_definition_variable_name);
    
    variable_definition->variable_definition_value = variable_definition_value;
    
    return variable_definition;
}

AST_T* parser_parse_number(parser_T* parser) {
    AST_T* ast_number = init_ast(AST_NUMBER);
    ast_number->number_value = atoi(parser->current_token->value);
    parser_eat(parser, TOKEN_NUMBER);
    return ast_number;
}

AST_T* parser_parse_float(parser_T* parser) {
    AST_T* ast_float = init_ast(AST_FLOAT);
    ast_float->float_value = atof(parser->current_token->value);
    parser_eat(parser, TOKEN_FLOAT);
    return ast_float;
}

AST_T* parser_parse_boolean(parser_T* parser) {
    AST_T* ast_boolean = init_ast(AST_BOOLEAN);
    ast_boolean->boolean_value = (parser->current_token->type == TOKEN_YES) ? 1 : 0;
    parser_eat(parser, parser->current_token->type);
    return ast_boolean;
}

AST_T* parser_parse_when_if(parser_T* parser) {
    // Expect "when"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "when") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "when"
    }
    
    // Expect "if"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "if") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "if"
    }
    
    parser_eat(parser, TOKEN_LPAREN);
    AST_T* condition = parser_parse_expr(parser);
    parser_eat(parser, TOKEN_RPAREN);
    
    parser_eat(parser, TOKEN_LBRACE);
    AST_T* if_body = parser_parse_statements(parser);
    parser_eat(parser, TOKEN_RBRACE);
    
    AST_T* when_if = init_ast(AST_WHEN_IF);
    when_if->when_if_condition = condition;
    when_if->when_if_body = if_body;
    
    // Check for "when else"
    if (parser->current_token != NULL && parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "when") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "when"
        
        // Expect "else"
        if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "else") == 0) {
            parser_eat(parser, TOKEN_ID); // eat "else"
        }
        
        parser_eat(parser, TOKEN_LBRACE);
        AST_T* else_body = parser_parse_statements(parser);
        parser_eat(parser, TOKEN_RBRACE);
        
        when_if->when_else_body = else_body;
    }
    
    return when_if;
}

AST_T* parser_parse_while_loop(parser_T* parser) {
    // Expect "while"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "while") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "while"
    }
    
    // Expect "loop"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "loop") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "loop"
    }
    
    parser_eat(parser, TOKEN_LPAREN);
    AST_T* condition = parser_parse_expr(parser);
    parser_eat(parser, TOKEN_RPAREN);
    
    parser_eat(parser, TOKEN_LBRACE);
    AST_T* body = parser_parse_statements(parser);
    parser_eat(parser, TOKEN_RBRACE);
    
    AST_T* while_loop = init_ast(AST_WHILE_LOOP);
    while_loop->while_loop_condition = condition;
    while_loop->while_loop_body = body;
    
    return while_loop;
}

AST_T* parser_parse_array(parser_T* parser) {
    parser_eat(parser, TOKEN_LBRACKET);
    
    AST_T* array = init_ast(AST_ARRAY);
    array->array_elements = calloc(1, sizeof(struct AST_STRUCT*));
    array->array_size = 0;
    
    // Handle empty array []
    if (parser->current_token->type == TOKEN_RBRACKET) {
        parser_eat(parser, TOKEN_RBRACKET);
        return array;
    }
    
    // Parse first element
    AST_T* first_element = parser_parse_expr(parser);
    array->array_elements[0] = first_element;
    array->array_size = 1;
    
    // Parse remaining elements
    while (parser->current_token->type == TOKEN_COMMA) {
        parser_eat(parser, TOKEN_COMMA);
        
        AST_T* element = parser_parse_expr(parser);
        array->array_size++;
        array->array_elements = realloc(
            array->array_elements, 
            array->array_size * sizeof(struct AST_STRUCT*)
        );
        array->array_elements[array->array_size - 1] = element;
    }
    
    parser_eat(parser, TOKEN_RBRACKET);
    return array;
}

AST_T* parser_parse_array_access(parser_T* parser, char* array_name) {
    // Consume array name (caller restored lexer state, so we need to consume it again)
    parser_eat(parser, TOKEN_ID);  // Consume the array name
    parser_eat(parser, TOKEN_LBRACKET);  // Consume '['
    
    // Parse index expression
    AST_T* index_expr = parser_parse_expr(parser);
    
    // Consume ']'
    parser_eat(parser, TOKEN_RBRACKET);
    
    // Create array access AST
    AST_T* array_access = init_ast(AST_ARRAY_ACCESS);
    array_access->array_access_name = calloc(strlen(array_name) + 1, sizeof(char));
    strcpy(array_access->array_access_name, array_name);
    array_access->array_access_index = index_expr;
    
    return array_access;
}

AST_T* parser_parse_for_loop(parser_T* parser) {
    // Expect "for"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "for") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "for"
    }
    
    // Expect "loop"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "loop") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "loop"
    }
    
    parser_eat(parser, TOKEN_LPAREN);
    AST_T* init = parser_parse_statement(parser);
    AST_T* condition = parser_parse_expr(parser);
    parser_eat(parser, TOKEN_SEMI);
    
    // Parse update as assignment (without semicolon)
    AST_T* update = parser_parse_assignment(parser);
    
    parser_eat(parser, TOKEN_RPAREN);
    
    parser_eat(parser, TOKEN_LBRACE);
    AST_T* body = parser_parse_statements(parser);
    parser_eat(parser, TOKEN_RBRACE);
    
    AST_T* for_loop = init_ast(AST_FOR_LOOP);
    for_loop->for_loop_init = init;
    for_loop->for_loop_condition = condition;
    for_loop->for_loop_update = update;
    for_loop->for_loop_body = body;
    
    return for_loop;
}

AST_T* parser_parse_function_definition(parser_T* parser) {
    // Expect "make"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "make") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "make"
    }
    
    // Expect "function"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "function") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "function"
    }
    
    char* function_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);
    
    parser_eat(parser, TOKEN_LPAREN);
    
    AST_T* function_def = init_ast(AST_FUNCTION_DEFINITION);
    function_def->function_def_name = calloc(strlen(function_name) + 1, sizeof(char));
    strcpy(function_def->function_def_name, function_name);
    
    // Parse parameters
    function_def->function_def_params = calloc(1, sizeof(struct AST_STRUCT*));
    function_def->function_def_params_size = 0;
    
    if (parser->current_token->type != TOKEN_RPAREN) {
        // Parse first parameter (bucket name)
        parser_eat(parser, TOKEN_BUCKET); // eat "bucket"
        AST_T* param = parser_parse_variable(parser);
        function_def->function_def_params[0] = param;
        function_def->function_def_params_size = 1;
        
        // Parse additional parameters
        while (parser->current_token->type == TOKEN_COMMA) {
            parser_eat(parser, TOKEN_COMMA);
            
            function_def->function_def_params_size++;
            function_def->function_def_params = realloc(
                function_def->function_def_params,
                function_def->function_def_params_size * sizeof(struct AST_STRUCT*)
            );
            
            parser_eat(parser, TOKEN_BUCKET); // eat "bucket"
            AST_T* param = parser_parse_variable(parser);
            function_def->function_def_params[function_def->function_def_params_size - 1] = param;
        }
    }
    
    parser_eat(parser, TOKEN_RPAREN);
    
    parser_eat(parser, TOKEN_LBRACE);
    AST_T* body = parser_parse_statements(parser);
    parser_eat(parser, TOKEN_RBRACE);
    
    function_def->function_def_body = body;
    
    return function_def;
}

AST_T* parser_parse_return(parser_T* parser) {
    // Expect "give"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "give") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "give"
    }
    
    // Expect "back"
    if (parser->current_token->type == TOKEN_ID && strcmp(parser->current_token->value, "back") == 0) {
        parser_eat(parser, TOKEN_ID); // eat "back"
    }
    
    AST_T* return_stmt = init_ast(AST_RETURN);
    
    if (parser->current_token->type != TOKEN_SEMI) {
        return_stmt->return_value = parser_parse_expr(parser);
    }
    
    parser_eat(parser, TOKEN_SEMI);
    
    return return_stmt;
}

AST_T* parser_parse_import(parser_T* parser) {
    // Consume 'putlib'
    parser_eat(parser, TOKEN_PUTLIB);
    
    AST_T* import_node = init_ast(AST_IMPORT);
    import_node->import_all = 0;
    import_node->import_items = NULL;
    import_node->import_items_count = 0;
    
    // Check if importing all (*)
    if (parser->current_token->type == TOKEN_MULTIPLY) {
        parser_eat(parser, TOKEN_MULTIPLY);
        import_node->import_all = 1;
    } else {
        // Parse list of function names
        import_node->import_items = calloc(1, sizeof(char*));
        import_node->import_items_count = 1;
        
        // First item - can be TOKEN_ID or stdlib function token
        if (parser->current_token->type == TOKEN_ID ||
            parser->current_token->type >= TOKEN_MATH_SQRT) {
            import_node->import_items[0] = calloc(strlen(parser->current_token->value) + 1, sizeof(char));
            strcpy(import_node->import_items[0], parser->current_token->value);
            parser_eat(parser, parser->current_token->type);
        }
        
        // Additional items separated by commas
        while (parser->current_token->type == TOKEN_COMMA) {
            parser_eat(parser, TOKEN_COMMA);
            
            import_node->import_items_count++;
            import_node->import_items = realloc(
                import_node->import_items, 
                import_node->import_items_count * sizeof(char*)
            );
            
            if (parser->current_token->type == TOKEN_ID ||
                parser->current_token->type >= TOKEN_MATH_SQRT) {
                import_node->import_items[import_node->import_items_count - 1] = 
                    calloc(strlen(parser->current_token->value) + 1, sizeof(char));
                strcpy(import_node->import_items[import_node->import_items_count - 1], 
                       parser->current_token->value);
                parser_eat(parser, parser->current_token->type);
            }
        }
    }
    
    // Consume 'from'
    parser_eat(parser, TOKEN_FROM);
    
    // Parse module name
    if (parser->current_token->type == TOKEN_ID) {
        import_node->import_module = calloc(strlen(parser->current_token->value) + 1, sizeof(char));
        strcpy(import_node->import_module, parser->current_token->value);
        parser_eat(parser, TOKEN_ID);
    }
    
    // Consume semicolon
    parser_eat(parser, TOKEN_SEMI);
    
    return import_node;
}
