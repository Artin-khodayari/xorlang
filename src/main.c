#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/codegen.h"

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';
    
    fclose(file);
    return content;
}

void write_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not create file '%s'\n", filename);
        return;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\033[1;34m XorLang Compiler v1.0\033[0m\n");
        printf("\033[1;37mUsage: %s <input.xor> [output.c]\033[0m\n", argv[0]);
        printf("\033[0;36mExample: %s program.xor\033[0m\n", argv[0]);
        return 1;
    }
    
    const char* input_file = argv[1];
    const char* output_file = argc > 2 ? argv[2] : "output.c";
    
    // Read source file
    char* source_code = read_file(input_file);
    if (!source_code) {
        return 1;
    }
    
    printf("\033[1;35m XorLang Compiler - Compiling %s...\033[0m\n", input_file);
    
    // Lexical analysis
    lexer_T* lexer = init_lexer(source_code);
    
    // Syntax analysis
    parser_T* parser = init_parser(lexer);
    AST_T* ast = parser_parse(parser);
    
    // Code generation
    char* c_code = codegen_generate_c_code(ast);
    
    // Write output
    write_file(output_file, c_code);
    printf("\033[1;36m Generated C code written to %s\033[0m\n", output_file);
    
    // Compile the generated C code with suppressed warnings
    char compile_cmd[512];
    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.out", input_file);
    snprintf(compile_cmd, sizeof(compile_cmd), "gcc %s -lcurl -lm -w -o %s 2>/dev/null", output_file, output_filename);
    
    printf("\033[1;33m⚡ Compiling XorLang program...\033[0m\n");
    int result = system(compile_cmd);
    
    if (result == 0) {
        printf("\033[1;32m Compilation successful! Executable: %s.out\033[0m\n", input_file);
    } else {
        printf("\033[1;31m Compilation failed! Check your XorLang syntax.\033[0m\n");
    }
    
    free(source_code);
    return 0;
}