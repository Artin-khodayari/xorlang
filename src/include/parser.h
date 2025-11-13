#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "AST.h"
typedef struct PARSER_STRUCT
{
    lexer_T* lerxer;
    token_T* current_token;

} parser_T;


parser_T* init_parser(lexer_T* lexer);
void parser_eat(parser_T* parser, int token_type);

AST_T* parser_parse(parser_T* parser);

AST_T* parser_parse_statement(parser_T* parser);
AST_T* parser_parse_statements(parser_T* parser);

AST_T* parser_parse_expr(parser_T* parser);
AST_T* parser_parse_factor(parser_T* parser);
AST_T* parser_parse_term(parser_T* parser);

AST_T* parser_parse_function_call(parser_T* parser);
AST_T* parser_parse_variable(parser_T* parser);
AST_T* parser_parse_string(parser_T* parser);
AST_T* parser_parse_variable_definition(parser_T* parser);
AST_T* parser_parse_assignment(parser_T* parser);
AST_T* parser_parse_number(parser_T* parser);
AST_T* parser_parse_float(parser_T* parser);
AST_T* parser_parse_boolean(parser_T* parser);
AST_T* parser_parse_binary_op(parser_T* parser);
AST_T* parser_parse_when_if(parser_T* parser);
AST_T* parser_parse_while_loop(parser_T* parser);
AST_T* parser_parse_for_loop(parser_T* parser);
AST_T* parser_parse_function_definition(parser_T* parser);
AST_T* parser_parse_return(parser_T* parser);
AST_T* parser_parse_array(parser_T* parser);
AST_T* parser_parse_array_access(parser_T* parser, char* array_name);
AST_T* parser_parse_import(parser_T* parser);

#endif 