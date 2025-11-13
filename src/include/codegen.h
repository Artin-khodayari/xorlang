#ifndef CODEGEN_H
#define CODEGEN_H
#include "AST.h"

typedef struct CODEGEN_STRUCT {
    char* output;
    size_t output_size;
} codegen_T;

codegen_T* init_codegen();
void codegen_write(codegen_T* codegen, const char* str);
void codegen_write_ast(codegen_T* codegen, AST_T* root);
void codegen_write_variable_definition(codegen_T* codegen, AST_T* node);
void codegen_write_assignment(codegen_T* codegen, AST_T* node);
void codegen_write_functions_only(codegen_T* codegen, AST_T* node);
void codegen_write_main_body_only(codegen_T* codegen, AST_T* node);
void codegen_write_function_call(codegen_T* codegen, AST_T* node);
void codegen_write_variable(codegen_T* codegen, AST_T* node);
void codegen_write_string(codegen_T* codegen, AST_T* node);
void codegen_write_compound(codegen_T* codegen, AST_T* node);
void codegen_write_number(codegen_T* codegen, AST_T* node);
void codegen_write_float(codegen_T* codegen, AST_T* node);
void codegen_write_boolean(codegen_T* codegen, AST_T* node);
void codegen_write_binary_op(codegen_T* codegen, AST_T* node);
void codegen_write_when_if(codegen_T* codegen, AST_T* node);
void codegen_write_while_loop(codegen_T* codegen, AST_T* node);
void codegen_write_for_loop(codegen_T* codegen, AST_T* node);
void codegen_write_function_definition(codegen_T* codegen, AST_T* node);
void codegen_write_return(codegen_T* codegen, AST_T* node);
void codegen_write_array(codegen_T* codegen, AST_T* node);
void codegen_write_array_access(codegen_T* codegen, AST_T* node);
void codegen_write_import(codegen_T* codegen, AST_T* node);
char* codegen_generate_c_code(AST_T* root);

#endif
