#ifndef AST_H
#define AST_H
#include <ctype.h>
#include <stdlib.h>
typedef struct AST_STRUCT
{
    enum{
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE,
        AST_ASSIGNMENT,
        AST_FUNCTION_CALL,
        AST_STRING,
        AST_COMPOUND,
        AST_NUMBER,
        AST_FLOAT,
        AST_BOOLEAN,
        AST_BINARY_OP,
        AST_WHEN_IF,
        AST_WHEN_ELSE,
        AST_WHILE_LOOP,
        AST_FOR_LOOP,
        AST_FUNCTION_DEFINITION,
        AST_RETURN,
        AST_ARRAY,
        AST_ARRAY_ACCESS,
        AST_IMPORT
    } type;

    /* AST VAR DEFINITION */
    char* variable_definition_variable_name;
    struct AST_STRUCT* variable_definition_value;

    /* AST_VARIABLE */
    char* variable_name;

    /* AST_ASSIGNMENT */
    char* assignment_variable_name;
    struct AST_STRUCT* assignment_value;

    /* AST_FUNCTION_CALL */
    char* function_call_name;    
    struct AST_STRUCT** function_call_arguments;
    size_t function_call_arguments_size;

    /* AST_STRING */
    char* string_value;

    /* AST_COMPOUND */
    struct AST_STRUCT** compound_value;
    size_t compound_size;

    /* AST_NUMBER */
    int number_value;

    /* AST_FLOAT */
    double float_value;

    /* AST_BOOLEAN */
    int boolean_value;

    /* AST_BINARY_OP */
    struct AST_STRUCT* binary_op_left;
    struct AST_STRUCT* binary_op_right;
    int binary_op_type; // Token type for operator

    /* AST_WHEN_IF */
    struct AST_STRUCT* when_if_condition;
    struct AST_STRUCT* when_if_body;
    struct AST_STRUCT* when_else_body;

    /* AST_WHILE_LOOP */
    struct AST_STRUCT* while_loop_condition;
    struct AST_STRUCT* while_loop_body;

    /* AST_FOR_LOOP */
    struct AST_STRUCT* for_loop_init;
    struct AST_STRUCT* for_loop_condition;
    struct AST_STRUCT* for_loop_update;
    struct AST_STRUCT* for_loop_body;

    /* AST_FUNCTION_DEFINITION */
    char* function_def_name;
    struct AST_STRUCT** function_def_params;
    size_t function_def_params_size;
    struct AST_STRUCT* function_def_body;

    /* AST_RETURN */
    struct AST_STRUCT* return_value;

    /* AST_ARRAY */
    struct AST_STRUCT** array_elements;
    size_t array_size;

    /* AST_ARRAY_ACCESS */
    char* array_access_name;
    struct AST_STRUCT* array_access_index;
    
    /* AST_IMPORT */
    char** import_items;        // List of function names to import
    size_t import_items_count;  // Number of items to import
    char* import_module;        // Module name (e.g., "math", "string")
    int import_all;             // 1 if importing all (*), 0 otherwise
    
} AST_T;

AST_T* init_ast(int type);



#endif