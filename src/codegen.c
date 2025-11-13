#include "include/codegen.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

codegen_T* init_codegen() {
    codegen_T* codegen = calloc(1, sizeof(struct CODEGEN_STRUCT));
    codegen->output = calloc(1, sizeof(char));
    codegen->output[0] = '\0';
    codegen->output_size = 1;
    return codegen;
}

void codegen_write(codegen_T* codegen, const char* str) {
    size_t str_len = strlen(str);
    codegen->output_size += str_len;
    codegen->output = realloc(codegen->output, codegen->output_size);
    strcat(codegen->output, str);
}

void codegen_write_ast(codegen_T* codegen, AST_T* root) {
    switch (root->type) {
        case AST_VARIABLE_DEFINITION:
            codegen_write_variable_definition(codegen, root);
            break;
        case AST_VARIABLE:
            codegen_write_variable(codegen, root);
            break;
        case AST_ASSIGNMENT:
            codegen_write_assignment(codegen, root);
            break;
        case AST_FUNCTION_CALL:
            codegen_write_function_call(codegen, root);
            break;
        case AST_STRING:
            codegen_write_string(codegen, root);
            break;
        case AST_NUMBER:
            codegen_write_number(codegen, root);
            break;
        case AST_FLOAT:
            codegen_write_float(codegen, root);
            break;
        case AST_BOOLEAN:
            codegen_write_boolean(codegen, root);
            break;
        case AST_BINARY_OP:
            codegen_write_binary_op(codegen, root);
            break;
        case AST_WHEN_IF:
            codegen_write_when_if(codegen, root);
            break;
        case AST_WHILE_LOOP:
            codegen_write_while_loop(codegen, root);
            break;
        case AST_FOR_LOOP:
            codegen_write_for_loop(codegen, root);
            break;
        case AST_FUNCTION_DEFINITION:
            codegen_write_function_definition(codegen, root);
            break;
        case AST_RETURN:
            codegen_write_return(codegen, root);
            break;
        case AST_ARRAY:
            codegen_write_array(codegen, root);
            break;
        case AST_ARRAY_ACCESS:
            codegen_write_array_access(codegen, root);
            break;
        case AST_IMPORT:
            codegen_write_import(codegen, root);
            break;
        case AST_COMPOUND:
            codegen_write_compound(codegen, root);
            break;
        default:
            printf("Uncaught statement of type `%d` in codegen\n", root->type);
            break;
    }
}

void codegen_write_variable_definition(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "    ");
    
    // Determine variable type based on value
    switch (node->variable_definition_value->type) {
        case AST_NUMBER:
            codegen_write(codegen, "int ");
            break;
        case AST_FLOAT:
            codegen_write(codegen, "double ");
            break;
        case AST_BOOLEAN:
            codegen_write(codegen, "int ");
            break;
        case AST_BINARY_OP:
            // Check if this is string concatenation (only if explicit string literals)
            if (node->variable_definition_value->binary_op_type == TOKEN_PLUS) {
                // Only treat as string concatenation if we have explicit string literals
                if (node->variable_definition_value->binary_op_left->type == AST_STRING ||
                    node->variable_definition_value->binary_op_right->type == AST_STRING) {
                    codegen_write(codegen, "char* ");
                } else {
                    // For numeric operations (including with variables), assume int
                    codegen_write(codegen, "int ");
                }
            } else {
                // For other binary operations, assume int
                codegen_write(codegen, "int ");
            }
            break;
        case AST_FUNCTION_CALL:
            // Check for specific function calls with known return types
            if (strcmp(node->variable_definition_value->function_call_name, "ask") == 0 ||
                strcmp(node->variable_definition_value->function_call_name, "http_get") == 0 ||
                strcmp(node->variable_definition_value->function_call_name, "http_post") == 0) {
                codegen_write(codegen, "char* ");
            } else if (strcmp(node->variable_definition_value->function_call_name, "download") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "is_online") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "safe_divide") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "error") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "math_abs") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "math_max") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "math_min") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "math_round") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "math_random_range") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "string_contains") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "string_starts_with") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "file_write") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "file_exists") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "file_delete") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "file_size") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "time_now") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "time_sleep") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "system_run") == 0) {
                codegen_write(codegen, "int ");
            } else if (strcmp(node->variable_definition_value->function_call_name, "string_to_upper") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "string_to_lower") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "string_trim") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "file_read") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "system_get_env") == 0) {
                codegen_write(codegen, "char* ");
            } else if (strcmp(node->variable_definition_value->function_call_name, "math_sqrt") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "math_pow") == 0 ||
                       strcmp(node->variable_definition_value->function_call_name, "math_random") == 0) {
                codegen_write(codegen, "double ");
            } else {
                // For other function calls, assume int return type for now
                codegen_write(codegen, "int ");
            }
            break;
        case AST_ARRAY:
            // For arrays, use int array type (could be improved with mixed type support)
            codegen_write(codegen, "int ");
            break;
        case AST_ARRAY_ACCESS:
            // For array access, assume int type (accessing int array elements)
            codegen_write(codegen, "int ");
            break;
        case AST_STRING:
        default:
            codegen_write(codegen, "char* ");
            break;
    }
    
    codegen_write(codegen, node->variable_definition_variable_name);
    
    // Handle array initialization
    if (node->variable_definition_value->type == AST_ARRAY) {
        char array_size[32];
        // Add extra capacity for push operations (double the initial size)
        size_t capacity = node->variable_definition_value->array_size * 2;
        if (capacity < 10) capacity = 10; // Minimum capacity
        sprintf(array_size, "[%zu]", capacity);
        codegen_write(codegen, array_size);
    }
    
    codegen_write(codegen, " = ");
    codegen_write_ast(codegen, node->variable_definition_value);
    codegen_write(codegen, ";\n");
    
    // Generate size variable for arrays
    if (node->variable_definition_value->type == AST_ARRAY) {
        codegen_write(codegen, "    size_t ");
        codegen_write(codegen, node->variable_definition_variable_name);
        codegen_write(codegen, "_size = ");
        char size_str[32];
        sprintf(size_str, "%zu", node->variable_definition_value->array_size);
        codegen_write(codegen, size_str);
        codegen_write(codegen, ";\n");
    }
}

void codegen_write_assignment(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "    ");
    codegen_write(codegen, node->assignment_variable_name);
    codegen_write(codegen, " = ");
    codegen_write_ast(codegen, node->assignment_value);
    codegen_write(codegen, ";\n");
}

void codegen_write_function_call(codegen_T* codegen, AST_T* node) {
    // Handle built-in functions
    if (strcmp(node->function_call_name, "show") == 0) {
        if (node->function_call_arguments_size > 0) {
            AST_T* arg = node->function_call_arguments[0];
            
            // Use the generic show macro for all types
            codegen_write(codegen, "    show(");
            codegen_write_ast(codegen, arg);
            codegen_write(codegen, ");\n");
        }
    } else if (strcmp(node->function_call_name, "math_sqrt") == 0) {
        // math_sqrt() function - Square root
        if (node->function_call_arguments_size >= 1) {
            AST_T* arg = node->function_call_arguments[0];
            codegen_write(codegen, "sqrt(");
            codegen_write_ast(codegen, arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "math_pow") == 0) {
        // math_pow() function - Power
        if (node->function_call_arguments_size >= 2) {
            AST_T* base_arg = node->function_call_arguments[0];
            AST_T* exp_arg = node->function_call_arguments[1];
            codegen_write(codegen, "pow(");
            codegen_write_ast(codegen, base_arg);
            codegen_write(codegen, ", ");
            codegen_write_ast(codegen, exp_arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "math_abs") == 0) {
        // math_abs() function - Absolute value
        if (node->function_call_arguments_size >= 1) {
            AST_T* arg = node->function_call_arguments[0];
            codegen_write(codegen, "abs(");
            codegen_write_ast(codegen, arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "math_max") == 0) {
        // math_max() function - Maximum of two values
        if (node->function_call_arguments_size >= 2) {
            AST_T* a_arg = node->function_call_arguments[0];
            AST_T* b_arg = node->function_call_arguments[1];
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        int a_val = ");
            codegen_write_ast(codegen, a_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        int b_val = ");
            codegen_write_ast(codegen, b_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        (a_val > b_val) ? a_val : b_val;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "math_min") == 0) {
        // math_min() function - Minimum of two values
        if (node->function_call_arguments_size >= 2) {
            AST_T* a_arg = node->function_call_arguments[0];
            AST_T* b_arg = node->function_call_arguments[1];
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        int a_val = ");
            codegen_write_ast(codegen, a_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        int b_val = ");
            codegen_write_ast(codegen, b_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        (a_val < b_val) ? a_val : b_val;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "math_round") == 0) {
        // math_round() function - Round to nearest integer
        if (node->function_call_arguments_size >= 1) {
            AST_T* arg = node->function_call_arguments[0];
            codegen_write(codegen, "(int)round(");
            codegen_write_ast(codegen, arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "math_random") == 0) {
        // math_random() function - Random number 0.0 to 1.0
        codegen_write(codegen, "((double)rand() / RAND_MAX)");
    } else if (strcmp(node->function_call_name, "math_random_range") == 0) {
        // math_random_range() function - Random number in range
        if (node->function_call_arguments_size >= 2) {
            AST_T* min_arg = node->function_call_arguments[0];
            AST_T* max_arg = node->function_call_arguments[1];
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        int min_val = ");
            codegen_write_ast(codegen, min_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        int max_val = ");
            codegen_write_ast(codegen, max_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        min_val + rand() % (max_val - min_val + 1);\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "string_to_upper") == 0) {
        // string_to_upper() function - Convert to uppercase
        if (node->function_call_arguments_size >= 1) {
            AST_T* str_arg = node->function_call_arguments[0];
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        char* input = ");
            codegen_write_ast(codegen, str_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        char* result = malloc(strlen(input) + 1);\n");
            codegen_write(codegen, "        for (int i = 0; input[i]; i++) {\n");
            codegen_write(codegen, "            result[i] = toupper(input[i]);\n");
            codegen_write(codegen, "        }\n");
            codegen_write(codegen, "        result[strlen(input)] = '\\0';\n");
            codegen_write(codegen, "        result;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "string_to_lower") == 0) {
        // string_to_lower() function - Convert to lowercase
        if (node->function_call_arguments_size >= 1) {
            AST_T* str_arg = node->function_call_arguments[0];
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        char* input = ");
            codegen_write_ast(codegen, str_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        char* result = malloc(strlen(input) + 1);\n");
            codegen_write(codegen, "        for (int i = 0; input[i]; i++) {\n");
            codegen_write(codegen, "            result[i] = tolower(input[i]);\n");
            codegen_write(codegen, "        }\n");
            codegen_write(codegen, "        result[strlen(input)] = '\\0';\n");
            codegen_write(codegen, "        result;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "string_trim") == 0) {
        // string_trim() function - Remove leading/trailing whitespace
        if (node->function_call_arguments_size >= 1) {
            AST_T* str_arg = node->function_call_arguments[0];
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        char* input = ");
            codegen_write_ast(codegen, str_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        char* start = input;\n");
            codegen_write(codegen, "        while (*start && isspace(*start)) start++;\n");
            codegen_write(codegen, "        char* end = start + strlen(start) - 1;\n");
            codegen_write(codegen, "        while (end > start && isspace(*end)) end--;\n");
            codegen_write(codegen, "        int len = end - start + 1;\n");
            codegen_write(codegen, "        char* result = malloc(len + 1);\n");
            codegen_write(codegen, "        strncpy(result, start, len);\n");
            codegen_write(codegen, "        result[len] = '\\0';\n");
            codegen_write(codegen, "        result;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "string_contains") == 0) {
        // string_contains() function - Check if string contains substring
        if (node->function_call_arguments_size >= 2) {
            AST_T* str_arg = node->function_call_arguments[0];
            AST_T* substr_arg = node->function_call_arguments[1];
            codegen_write(codegen, "(strstr(");
            codegen_write_ast(codegen, str_arg);
            codegen_write(codegen, ", ");
            codegen_write_ast(codegen, substr_arg);
            codegen_write(codegen, ") != NULL ? 1 : 0)");
        }
    } else if (strcmp(node->function_call_name, "string_starts_with") == 0) {
        // string_starts_with() function - Check if string starts with prefix
        if (node->function_call_arguments_size >= 2) {
            AST_T* str_arg = node->function_call_arguments[0];
            AST_T* prefix_arg = node->function_call_arguments[1];
            codegen_write(codegen, "(strncmp(");
            codegen_write_ast(codegen, str_arg);
            codegen_write(codegen, ", ");
            codegen_write_ast(codegen, prefix_arg);
            codegen_write(codegen, ", strlen(");
            codegen_write_ast(codegen, prefix_arg);
            codegen_write(codegen, ")) == 0 ? 1 : 0)");
        }
    } else if (strcmp(node->function_call_name, "file_read") == 0) {
        // file_read() function - Read file contents
        if (node->function_call_arguments_size >= 1) {
            AST_T* filename_arg = node->function_call_arguments[0];
            codegen_write(codegen, "xor_file_read(");
            codegen_write_ast(codegen, filename_arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "file_write") == 0) {
        // file_write() function - Write content to file
        if (node->function_call_arguments_size >= 2) {
            AST_T* filename_arg = node->function_call_arguments[0];
            AST_T* content_arg = node->function_call_arguments[1];
            codegen_write(codegen, "xor_file_write(");
            codegen_write_ast(codegen, filename_arg);
            codegen_write(codegen, ", ");
            codegen_write_ast(codegen, content_arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "file_exists") == 0) {
        // file_exists() function - Check if file exists
        if (node->function_call_arguments_size >= 1) {
            AST_T* filename_arg = node->function_call_arguments[0];
            codegen_write(codegen, "xor_file_exists(");
            codegen_write_ast(codegen, filename_arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "file_delete") == 0) {
        // file_delete() function - Delete file
        if (node->function_call_arguments_size >= 1) {
            AST_T* filename_arg = node->function_call_arguments[0];
            codegen_write(codegen, "(remove(");
            codegen_write_ast(codegen, filename_arg);
            codegen_write(codegen, ") == 0 ? 1 : 0)");
        }
    } else if (strcmp(node->function_call_name, "file_size") == 0) {
        // file_size() function - Get file size
        if (node->function_call_arguments_size >= 1) {
            AST_T* filename_arg = node->function_call_arguments[0];
            codegen_write(codegen, "xor_file_size(");
            codegen_write_ast(codegen, filename_arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "time_now") == 0) {
        // time_now() function - Get current timestamp
        codegen_write(codegen, "(int)time(NULL)");
    } else if (strcmp(node->function_call_name, "time_sleep") == 0) {
        // time_sleep() function - Sleep for milliseconds
        if (node->function_call_arguments_size >= 1) {
            AST_T* ms_arg = node->function_call_arguments[0];
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        usleep(");
            codegen_write_ast(codegen, ms_arg);
            codegen_write(codegen, " * 1000);\n");
            codegen_write(codegen, "        1;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "system_run") == 0) {
        // system_run() function - Execute system command
        if (node->function_call_arguments_size >= 1) {
            AST_T* cmd_arg = node->function_call_arguments[0];
            codegen_write(codegen, "system(");
            codegen_write_ast(codegen, cmd_arg);
            codegen_write(codegen, ")");
        }
    } else if (strcmp(node->function_call_name, "system_get_env") == 0) {
        // system_get_env() function - Get environment variable
        if (node->function_call_arguments_size >= 1) {
            AST_T* var_arg = node->function_call_arguments[0];
            codegen_write(codegen, "(getenv(");
            codegen_write_ast(codegen, var_arg);
            codegen_write(codegen, ") ? getenv(");
            codegen_write_ast(codegen, var_arg);
            codegen_write(codegen, ") : \"\")");
        }
    } else if (strcmp(node->function_call_name, "len") == 0) {
        // len() function - handle both strings and arrays
        if (node->function_call_arguments_size > 0) {
            AST_T* arg = node->function_call_arguments[0];
            
            // Check if argument is a variable (could be array or string)
            if (arg->type == AST_VARIABLE) {
                // For arrays, use the size variable directly with int cast
                // We assume if there's a size variable, it's an array
                codegen_write(codegen, "(int)");
                codegen_write_ast(codegen, arg);
                codegen_write(codegen, "_size");
            } else {
                // For string literals, use strlen
                codegen_write(codegen, "(int)strlen(");
                codegen_write_ast(codegen, arg);
                codegen_write(codegen, ")");
            }
        }
    } else if (strcmp(node->function_call_name, "push") == 0) {
        // push() function - add element to array
        if (node->function_call_arguments_size >= 2) {
            AST_T* array_arg = node->function_call_arguments[0];
            AST_T* element_arg = node->function_call_arguments[1];
            
            // Generate simple statements for push operation
            codegen_write_ast(codegen, array_arg);
            codegen_write(codegen, "[");
            codegen_write_ast(codegen, array_arg);
            codegen_write(codegen, "_size] = ");
            codegen_write_ast(codegen, element_arg);
            codegen_write(codegen, "; ");
            codegen_write_ast(codegen, array_arg);
            codegen_write(codegen, "_size++;");
        }
    } else if (strcmp(node->function_call_name, "pop") == 0) {
        // pop() function - remove and return last element from array
        if (node->function_call_arguments_size >= 1) {
            AST_T* array_arg = node->function_call_arguments[0];
            
            // Generate inline code for pop operation
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        int result = ");
            codegen_write_ast(codegen, array_arg);
            codegen_write(codegen, "[");
            codegen_write_ast(codegen, array_arg);
            codegen_write(codegen, "_size - 1];\n");
            codegen_write(codegen, "        ");
            codegen_write_ast(codegen, array_arg);
            codegen_write(codegen, "_size--;\n");
            codegen_write(codegen, "        result;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "safe_divide") == 0) {
        // safe_divide() function - safe division with zero check
        if (node->function_call_arguments_size >= 2) {
            AST_T* dividend_arg = node->function_call_arguments[0];
            AST_T* divisor_arg = node->function_call_arguments[1];
            
            // Generate inline code for safe division
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        int divisor_val = ");
            codegen_write_ast(codegen, divisor_arg);
            codegen_write(codegen, ";\n");
            codegen_write(codegen, "        (divisor_val != 0) ? (");
            codegen_write_ast(codegen, dividend_arg);
            codegen_write(codegen, " / divisor_val) : 0;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "error") == 0) {
        // error() function - print error message and return error code
        if (node->function_call_arguments_size >= 1) {
            AST_T* message_arg = node->function_call_arguments[0];
            
            // Generate inline code for error handling
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        printf(\"ERROR: \");\n");
            codegen_write(codegen, "        printf(");
            codegen_write_ast(codegen, message_arg);
            codegen_write(codegen, ");\n");
            codegen_write(codegen, "        printf(\"\\n\");\n");
            codegen_write(codegen, "        -1;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "http_get") == 0) {
        // http_get() function - HTTP GET request
        if (node->function_call_arguments_size >= 1) {
            AST_T* url_arg = node->function_call_arguments[0];
            
            // Generate inline code for HTTP GET
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        char* response = http_get_request(");
            codegen_write_ast(codegen, url_arg);
            codegen_write(codegen, ");\n");
            codegen_write(codegen, "        response;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "http_post") == 0) {
        // http_post() function - HTTP POST request
        if (node->function_call_arguments_size >= 2) {
            AST_T* url_arg = node->function_call_arguments[0];
            AST_T* data_arg = node->function_call_arguments[1];
            
            // Generate inline code for HTTP POST
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        char* response = http_post_request(");
            codegen_write_ast(codegen, url_arg);
            codegen_write(codegen, ", ");
            codegen_write_ast(codegen, data_arg);
            codegen_write(codegen, ");\n");
            codegen_write(codegen, "        response;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "download") == 0) {
        // download() function - Download file from URL
        if (node->function_call_arguments_size >= 2) {
            AST_T* url_arg = node->function_call_arguments[0];
            AST_T* filename_arg = node->function_call_arguments[1];
            
            // Generate inline code for file download
            codegen_write(codegen, "({\n");
            codegen_write(codegen, "        int result = download_file(");
            codegen_write_ast(codegen, url_arg);
            codegen_write(codegen, ", ");
            codegen_write_ast(codegen, filename_arg);
            codegen_write(codegen, ");\n");
            codegen_write(codegen, "        result;\n");
            codegen_write(codegen, "    })");
        }
    } else if (strcmp(node->function_call_name, "is_online") == 0) {
        // is_online() function - Check internet connectivity
        codegen_write(codegen, "({\n");
        codegen_write(codegen, "        int online = check_internet_connection();\n");
        codegen_write(codegen, "        online;\n");
        codegen_write(codegen, "    })");
    } else if (strcmp(node->function_call_name, "ask") == 0) {
        // Ask function needs special handling - generate inline code
        codegen_write(codegen, "({\n");
        codegen_write(codegen, "        static char input_buffer[256];\n");
        
        if (node->function_call_arguments_size > 0) {
            AST_T* prompt = node->function_call_arguments[0];
            codegen_write(codegen, "        printf(");
            codegen_write_ast(codegen, prompt);
            codegen_write(codegen, ");\n");
        }
        
        codegen_write(codegen, "        fgets(input_buffer, sizeof(input_buffer), stdin);\n");
        codegen_write(codegen, "        size_t len = strlen(input_buffer);\n");
        codegen_write(codegen, "        if (len > 0 && input_buffer[len-1] == '\\n') {\n");
        codegen_write(codegen, "            input_buffer[len-1] = '\\0';\n");
        codegen_write(codegen, "        }\n");
        codegen_write(codegen, "        input_buffer;\n");
        codegen_write(codegen, "    })");
    } else {
        // Regular function call
        codegen_write(codegen, "    ");
        codegen_write(codegen, node->function_call_name);
        codegen_write(codegen, "(");
        
        for (size_t i = 0; i < node->function_call_arguments_size; i++) {
            codegen_write_ast(codegen, node->function_call_arguments[i]);
            if (i < node->function_call_arguments_size - 1) {
                codegen_write(codegen, ", ");
            }
        }
        
        codegen_write(codegen, ");\n");
    }
}

void codegen_write_variable(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, node->variable_name);
}

void codegen_write_string(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "\"");
    codegen_write(codegen, node->string_value);
    codegen_write(codegen, "\"");
}

void codegen_write_compound(codegen_T* codegen, AST_T* node) {
    for (size_t i = 0; i < node->compound_size; i++) {
        codegen_write_ast(codegen, node->compound_value[i]);
    }
}

char* codegen_generate_c_code(AST_T* root) {
    codegen_T* codegen = init_codegen();
    
    // Write C headers
    codegen_write(codegen, "#include <stdio.h>\n");
    codegen_write(codegen, "#include <string.h>\n");
    codegen_write(codegen, "#include <stdlib.h>\n");
    codegen_write(codegen, "#include <math.h>\n");
    codegen_write(codegen, "#include <time.h>\n");
    codegen_write(codegen, "#include <unistd.h>\n");
    codegen_write(codegen, "#include <ctype.h>\n");
    codegen_write(codegen, "#include <curl/curl.h>\n");
    codegen_write(codegen, "#include <sys/socket.h>\n");
    codegen_write(codegen, "#include <netinet/in.h>\n");
    codegen_write(codegen, "#include <arpa/inet.h>\n");
    
    // Write helper function for array printing
    codegen_write(codegen, "void print_int_array(int* arr, size_t size) {\n");
    codegen_write(codegen, "    printf(\"[\");\n");
    codegen_write(codegen, "    for (size_t i = 0; i < size; i++) {\n");
    codegen_write(codegen, "        if (i > 0) printf(\", \");\n");
    codegen_write(codegen, "        printf(\"%d\", arr[i]);\n");
    codegen_write(codegen, "    }\n");
    codegen_write(codegen, "    printf(\"]\\n\");\n");
    codegen_write(codegen, "}\n\n");
    
    // Write string concatenation helper function
    codegen_write(codegen, "char* string_concat(const char* str1, const char* str2) {\n");
    codegen_write(codegen, "    size_t len1 = strlen(str1);\n");
    codegen_write(codegen, "    size_t len2 = strlen(str2);\n");
    codegen_write(codegen, "    char* result = malloc(len1 + len2 + 1);\n");
    codegen_write(codegen, "    strcpy(result, str1);\n");
    codegen_write(codegen, "    strcat(result, str2);\n");
    codegen_write(codegen, "    return result;\n");
    codegen_write(codegen, "}\n\n");
    
    // Write file helper functions
    codegen_write(codegen, "int xor_file_exists(const char* filename) {\n");
    codegen_write(codegen, "    FILE* file = fopen(filename, \"r\");\n");
    codegen_write(codegen, "    if (file) {\n");
    codegen_write(codegen, "        fclose(file);\n");
    codegen_write(codegen, "        return 1;\n");
    codegen_write(codegen, "    }\n");
    codegen_write(codegen, "    return 0;\n");
    codegen_write(codegen, "}\n\n");
    
    codegen_write(codegen, "int xor_file_write(const char* filename, const char* content) {\n");
    codegen_write(codegen, "    FILE* file = fopen(filename, \"w\");\n");
    codegen_write(codegen, "    if (!file) return 0;\n");
    codegen_write(codegen, "    fprintf(file, \"%s\", content);\n");
    codegen_write(codegen, "    fclose(file);\n");
    codegen_write(codegen, "    return 1;\n");
    codegen_write(codegen, "}\n\n");
    
    codegen_write(codegen, "char* xor_file_read(const char* filename) {\n");
    codegen_write(codegen, "    FILE* file = fopen(filename, \"r\");\n");
    codegen_write(codegen, "    if (!file) return \"ERROR: Cannot open file\";\n");
    codegen_write(codegen, "    fseek(file, 0, SEEK_END);\n");
    codegen_write(codegen, "    long size = ftell(file);\n");
    codegen_write(codegen, "    fseek(file, 0, SEEK_SET);\n");
    codegen_write(codegen, "    char* content = malloc(size + 1);\n");
    codegen_write(codegen, "    fread(content, 1, size, file);\n");
    codegen_write(codegen, "    content[size] = '\\0';\n");
    codegen_write(codegen, "    fclose(file);\n");
    codegen_write(codegen, "    return content;\n");
    codegen_write(codegen, "}\n\n");
    
    codegen_write(codegen, "int xor_file_size(const char* filename) {\n");
    codegen_write(codegen, "    FILE* file = fopen(filename, \"r\");\n");
    codegen_write(codegen, "    if (!file) return -1;\n");
    codegen_write(codegen, "    fseek(file, 0, SEEK_END);\n");
    codegen_write(codegen, "    long size = ftell(file);\n");
    codegen_write(codegen, "    fclose(file);\n");
    codegen_write(codegen, "    return (int)size;\n");
    codegen_write(codegen, "}\n\n");
    
    // Write helper macros for show function using _Generic
    codegen_write(codegen, "#define show(x) _Generic((x), \\\n");
    codegen_write(codegen, "    int: printf(\"%d\\n\", x), \\\n");
    codegen_write(codegen, "    double: printf(\"%.2f\\n\", x), \\\n");
    codegen_write(codegen, "    float: printf(\"%.2f\\n\", x), \\\n");
    codegen_write(codegen, "    char*: printf(\"%s\\n\", x), \\\n");
    codegen_write(codegen, "    int*: printf(\"[Array - use show_array() to print]\\n\"), \\\n");
    codegen_write(codegen, "    default: printf(\"%s\\n\", x) \\\n");
    codegen_write(codegen, ")\n\n");
    
    // Write show_array macro for arrays (with manual size)
    codegen_write(codegen, "#define show_array(arr, size) print_int_array(arr, size)\n");
    
    // Write auto_show_array macro that uses generated size variable
    codegen_write(codegen, "#define auto_show_array(arr) print_int_array(arr, arr##_size)\n\n");
    
    // Write networking helper functions
    codegen_write(codegen, "// HTTP response structure\n");
    codegen_write(codegen, "struct HTTPResponse {\n");
    codegen_write(codegen, "    char* data;\n");
    codegen_write(codegen, "    size_t size;\n");
    codegen_write(codegen, "};\n\n");
    
    codegen_write(codegen, "// Callback function for libcurl\n");
    codegen_write(codegen, "size_t WriteCallback(void* contents, size_t size, size_t nmemb, struct HTTPResponse* response) {\n");
    codegen_write(codegen, "    size_t realsize = size * nmemb;\n");
    codegen_write(codegen, "    response->data = realloc(response->data, response->size + realsize + 1);\n");
    codegen_write(codegen, "    if (response->data) {\n");
    codegen_write(codegen, "        memcpy(&(response->data[response->size]), contents, realsize);\n");
    codegen_write(codegen, "        response->size += realsize;\n");
    codegen_write(codegen, "        response->data[response->size] = 0;\n");
    codegen_write(codegen, "    }\n");
    codegen_write(codegen, "    return realsize;\n");
    codegen_write(codegen, "}\n\n");
    
    codegen_write(codegen, "// HTTP GET function\n");
    codegen_write(codegen, "char* http_get_request(const char* url) {\n");
    codegen_write(codegen, "    CURL* curl;\n");
    codegen_write(codegen, "    CURLcode res;\n");
    codegen_write(codegen, "    struct HTTPResponse response = {0};\n");
    codegen_write(codegen, "    \n");
    codegen_write(codegen, "    curl = curl_easy_init();\n");
    codegen_write(codegen, "    if (curl) {\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_URL, url);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);\n");
    codegen_write(codegen, "        res = curl_easy_perform(curl);\n");
    codegen_write(codegen, "        curl_easy_cleanup(curl);\n");
    codegen_write(codegen, "    }\n");
    codegen_write(codegen, "    return response.data ? response.data : strdup(\"ERROR: HTTP request failed\");\n");
    codegen_write(codegen, "}\n\n");
    
    codegen_write(codegen, "// HTTP POST function\n");
    codegen_write(codegen, "char* http_post_request(const char* url, const char* data) {\n");
    codegen_write(codegen, "    CURL* curl;\n");
    codegen_write(codegen, "    CURLcode res;\n");
    codegen_write(codegen, "    struct HTTPResponse response = {0};\n");
    codegen_write(codegen, "    \n");
    codegen_write(codegen, "    curl = curl_easy_init();\n");
    codegen_write(codegen, "    if (curl) {\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_URL, url);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);\n");
    codegen_write(codegen, "        res = curl_easy_perform(curl);\n");
    codegen_write(codegen, "        curl_easy_cleanup(curl);\n");
    codegen_write(codegen, "    }\n");
    codegen_write(codegen, "    return response.data ? response.data : strdup(\"ERROR: HTTP POST failed\");\n");
    codegen_write(codegen, "}\n\n");
    
    codegen_write(codegen, "// Download file function\n");
    codegen_write(codegen, "int download_file(const char* url, const char* filename) {\n");
    codegen_write(codegen, "    CURL* curl;\n");
    codegen_write(codegen, "    FILE* fp;\n");
    codegen_write(codegen, "    CURLcode res;\n");
    codegen_write(codegen, "    \n");
    codegen_write(codegen, "    curl = curl_easy_init();\n");
    codegen_write(codegen, "    if (curl) {\n");
    codegen_write(codegen, "        fp = fopen(filename, \"wb\");\n");
    codegen_write(codegen, "        if (!fp) return 0;\n");
    codegen_write(codegen, "        \n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_URL, url);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);\n");
    codegen_write(codegen, "        res = curl_easy_perform(curl);\n");
    codegen_write(codegen, "        \n");
    codegen_write(codegen, "        curl_easy_cleanup(curl);\n");
    codegen_write(codegen, "        fclose(fp);\n");
    codegen_write(codegen, "        return (res == CURLE_OK) ? 1 : 0;\n");
    codegen_write(codegen, "    }\n");
    codegen_write(codegen, "    return 0;\n");
    codegen_write(codegen, "}\n\n");
    
    codegen_write(codegen, "// Check internet connection function\n");
    codegen_write(codegen, "int check_internet_connection() {\n");
    codegen_write(codegen, "    CURL* curl;\n");
    codegen_write(codegen, "    CURLcode res;\n");
    codegen_write(codegen, "    \n");
    codegen_write(codegen, "    curl = curl_easy_init();\n");
    codegen_write(codegen, "    if (curl) {\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_URL, \"http://www.google.com\");\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);\n");
    codegen_write(codegen, "        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);\n");
    codegen_write(codegen, "        res = curl_easy_perform(curl);\n");
    codegen_write(codegen, "        curl_easy_cleanup(curl);\n");
    codegen_write(codegen, "        return (res == CURLE_OK) ? 1 : 0;\n");
    codegen_write(codegen, "    }\n");
    codegen_write(codegen, "    return 0;\n");
    codegen_write(codegen, "}\n\n");
    
    // First pass: Generate function definitions
    codegen_write_functions_only(codegen, root);
    
    // Write main function
    codegen_write(codegen, "int main() {\n");
    
    // Second pass: Generate main body (everything except function definitions)
    codegen_write_main_body_only(codegen, root);
    
    // Close main function
    codegen_write(codegen, "    return 0;\n");
    codegen_write(codegen, "}\n");
    
    return codegen->output;
}

void codegen_write_number(codegen_T* codegen, AST_T* node) {
    char buffer[32];
    sprintf(buffer, "%d", node->number_value);
    codegen_write(codegen, buffer);
}

void codegen_write_float(codegen_T* codegen, AST_T* node) {
    char buffer[32];
    sprintf(buffer, "%.2f", node->float_value);
    codegen_write(codegen, buffer);
}

void codegen_write_boolean(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, node->boolean_value ? "1" : "0");
}

void codegen_write_binary_op(codegen_T* codegen, AST_T* node) {
    // Special handling for string concatenation with + operator
    if (node->binary_op_type == TOKEN_PLUS) {
        // Check if either operand is a string literal or string variable
        int is_string_op = 0;
        
        // Check if left operand is string literal
        if (node->binary_op_left->type == AST_STRING) {
            is_string_op = 1;
        }
        // Check if right operand is string literal
        else if (node->binary_op_right->type == AST_STRING) {
            is_string_op = 1;
        }
        // Only treat as string operation if we have explicit string literals
        // Variables should use numeric operations by default
        
        if (is_string_op) {
            // Use string concatenation function
            codegen_write(codegen, "string_concat(");
            codegen_write_ast(codegen, node->binary_op_left);
            codegen_write(codegen, ", ");
            codegen_write_ast(codegen, node->binary_op_right);
            codegen_write(codegen, ")");
            return;
        }
    }
    
    // Default numeric operations
    codegen_write(codegen, "(");
    codegen_write_ast(codegen, node->binary_op_left);
    
    switch (node->binary_op_type) {
        case TOKEN_PLUS: codegen_write(codegen, " + "); break;
        case TOKEN_MINUS: codegen_write(codegen, " - "); break;
        case TOKEN_MULTIPLY: codegen_write(codegen, " * "); break;
        case TOKEN_DIVIDE: codegen_write(codegen, " / "); break;
        case TOKEN_EQ: codegen_write(codegen, " == "); break;
        case TOKEN_NEQ: codegen_write(codegen, " != "); break;
        case TOKEN_GT: codegen_write(codegen, " > "); break;
        case TOKEN_LT: codegen_write(codegen, " < "); break;
        case TOKEN_GTE: codegen_write(codegen, " >= "); break;
        case TOKEN_LTE: codegen_write(codegen, " <= "); break;
        default: codegen_write(codegen, " ? "); break;
    }
    
    codegen_write_ast(codegen, node->binary_op_right);
    codegen_write(codegen, ")");
}

void codegen_write_when_if(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "    if (");
    codegen_write_ast(codegen, node->when_if_condition);
    codegen_write(codegen, ") {\n");
    
    codegen_write_ast(codegen, node->when_if_body);
    
    codegen_write(codegen, "    }");
    
    if (node->when_else_body != NULL) {
        codegen_write(codegen, " else {\n");
        codegen_write_ast(codegen, node->when_else_body);
        codegen_write(codegen, "    }");
    }
    
    codegen_write(codegen, "\n");
}

void codegen_write_while_loop(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "    while (");
    codegen_write_ast(codegen, node->while_loop_condition);
    codegen_write(codegen, ") {\n");
    
    codegen_write_ast(codegen, node->while_loop_body);
    
    codegen_write(codegen, "    }\n");
}

void codegen_write_for_loop(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "    for (");
    
    // Init (without semicolon and newline)
    if (node->for_loop_init->type == AST_VARIABLE_DEFINITION) {
        codegen_write(codegen, "int ");
        codegen_write(codegen, node->for_loop_init->variable_definition_variable_name);
        codegen_write(codegen, " = ");
        codegen_write_ast(codegen, node->for_loop_init->variable_definition_value);
    }
    
    codegen_write(codegen, "; ");
    codegen_write_ast(codegen, node->for_loop_condition);
    codegen_write(codegen, "; ");
    
    // Handle update (assignment without semicolon)
    if (node->for_loop_update->type == AST_ASSIGNMENT) {
        codegen_write(codegen, node->for_loop_update->assignment_variable_name);
        codegen_write(codegen, " = ");
        codegen_write_ast(codegen, node->for_loop_update->assignment_value);
    } else {
        codegen_write_ast(codegen, node->for_loop_update);
    }
    
    codegen_write(codegen, ") {\n");
    
    codegen_write_ast(codegen, node->for_loop_body);
    
    codegen_write(codegen, "    }\n");
}

void codegen_write_function_definition(codegen_T* codegen, AST_T* node) {
    // For now, we'll generate simple C functions
    codegen_write(codegen, "int ");
    codegen_write(codegen, node->function_def_name);
    codegen_write(codegen, "(");
    
    for (size_t i = 0; i < node->function_def_params_size; i++) {
        codegen_write(codegen, "int ");
        codegen_write_ast(codegen, node->function_def_params[i]);
        if (i < node->function_def_params_size - 1) {
            codegen_write(codegen, ", ");
        }
    }
    
    codegen_write(codegen, ") {\n");
    codegen_write_ast(codegen, node->function_def_body);
    codegen_write(codegen, "}\n\n");
}

void codegen_write_return(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "    return");
    if (node->return_value != NULL) {
        codegen_write(codegen, " ");
        codegen_write_ast(codegen, node->return_value);
    }
    codegen_write(codegen, ";\n");
}

void codegen_write_array(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, "{");
    
    for (size_t i = 0; i < node->array_size; i++) {
        if (i > 0) {
            codegen_write(codegen, ", ");
        }
        codegen_write_ast(codegen, node->array_elements[i]);
    }
    
    codegen_write(codegen, "}");
}

void codegen_write_array_access(codegen_T* codegen, AST_T* node) {
    codegen_write(codegen, node->array_access_name);
    codegen_write(codegen, "[");
    codegen_write_ast(codegen, node->array_access_index);
    codegen_write(codegen, "]");
}

void codegen_write_functions_only(codegen_T* codegen, AST_T* node) {
    if (node == NULL) return;
    
    if (node->type == AST_FUNCTION_DEFINITION) {
        codegen_write_function_definition(codegen, node);
    } else if (node->type == AST_COMPOUND) {
        for (size_t i = 0; i < node->compound_size; i++) {
            codegen_write_functions_only(codegen, node->compound_value[i]);
        }
    }
}

void codegen_write_main_body_only(codegen_T* codegen, AST_T* node) {
    if (node == NULL) return;
    
    if (node->type == AST_FUNCTION_DEFINITION) {
        // Skip function definitions - they're handled in the first pass
        return;
    } else if (node->type == AST_COMPOUND) {
        for (size_t i = 0; i < node->compound_size; i++) {
            codegen_write_main_body_only(codegen, node->compound_value[i]);
        }
    } else {
        // Write all other AST nodes
        codegen_write_ast(codegen, node);
        // Add semicolon for statement-level function calls
        if (node->type == AST_FUNCTION_CALL) {
            codegen_write(codegen, ";\n");
        }
    }
}

void codegen_write_import(codegen_T* codegen, AST_T* node) {
    // Import statements are processed at compile time
    // They don't generate runtime C code, but affect symbol resolution
    
    // For now, we'll generate a comment to indicate the import
    codegen_write(codegen, "// Import from module: ");
    codegen_write(codegen, node->import_module);
    codegen_write(codegen, "\n");
    
    if (node->import_all) {
        codegen_write(codegen, "// Importing all functions from ");
        codegen_write(codegen, node->import_module);
        codegen_write(codegen, "\n");
    } else {
        codegen_write(codegen, "// Importing specific functions: ");
        for (size_t i = 0; i < node->import_items_count; i++) {
            codegen_write(codegen, node->import_items[i]);
            if (i < node->import_items_count - 1) {
                codegen_write(codegen, ", ");
            }
        }
        codegen_write(codegen, "\n");
    }
}
