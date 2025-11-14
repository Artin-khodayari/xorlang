#include "include/lexer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Keyword checking function
int is_keyword(char* str) {
    if (strcmp(str, "bucket") == 0) return TOKEN_BUCKET;
    if (strcmp(str, "when") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "if") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "else") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "while") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "loop") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "for") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "make") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "function") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "give") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "back") == 0) return TOKEN_ID; // treat as regular identifier
    if (strcmp(str, "show") == 0) return TOKEN_SHOW;
    if (strcmp(str, "ask") == 0) return TOKEN_ASK;
    if (strcmp(str, "len") == 0) return TOKEN_LEN;
    if (strcmp(str, "push") == 0) return TOKEN_PUSH;
    if (strcmp(str, "pop") == 0) return TOKEN_POP;
    if (strcmp(str, "safe_divide") == 0) return TOKEN_SAFE_DIVIDE;
    if (strcmp(str, "error") == 0) return TOKEN_ERROR;
    if (strcmp(str, "http_get") == 0) return TOKEN_HTTP_GET;
    if (strcmp(str, "http_post") == 0) return TOKEN_HTTP_POST;
    if (strcmp(str, "download") == 0) return TOKEN_DOWNLOAD;
    if (strcmp(str, "is_online") == 0) return TOKEN_IS_ONLINE;
    
    // Math module
    if (strcmp(str, "math_sqrt") == 0) return TOKEN_MATH_SQRT;
    if (strcmp(str, "math_pow") == 0) return TOKEN_MATH_POW;
    if (strcmp(str, "math_abs") == 0) return TOKEN_MATH_ABS;
    if (strcmp(str, "math_max") == 0) return TOKEN_MATH_MAX;
    if (strcmp(str, "math_min") == 0) return TOKEN_MATH_MIN;
    if (strcmp(str, "math_round") == 0) return TOKEN_MATH_ROUND;
    if (strcmp(str, "math_random") == 0) return TOKEN_MATH_RANDOM;
    if (strcmp(str, "math_random_range") == 0) return TOKEN_MATH_RANDOM_RANGE;
    
    // String module
    if (strcmp(str, "string_split") == 0) return TOKEN_STRING_SPLIT;
    if (strcmp(str, "string_join") == 0) return TOKEN_STRING_JOIN;
    if (strcmp(str, "string_replace") == 0) return TOKEN_STRING_REPLACE;
    if (strcmp(str, "string_to_upper") == 0) return TOKEN_STRING_TO_UPPER;
    if (strcmp(str, "string_to_lower") == 0) return TOKEN_STRING_TO_LOWER;
    if (strcmp(str, "string_trim") == 0) return TOKEN_STRING_TRIM;
    if (strcmp(str, "string_contains") == 0) return TOKEN_STRING_CONTAINS;
    if (strcmp(str, "string_starts_with") == 0) return TOKEN_STRING_STARTS_WITH;
    
    // Array module
    if (strcmp(str, "array_sort") == 0) return TOKEN_ARRAY_SORT;
    if (strcmp(str, "array_reverse") == 0) return TOKEN_ARRAY_REVERSE;
    if (strcmp(str, "array_unique") == 0) return TOKEN_ARRAY_UNIQUE;
    if (strcmp(str, "array_find") == 0) return TOKEN_ARRAY_FIND;
    if (strcmp(str, "array_slice") == 0) return TOKEN_ARRAY_SLICE;
    
    // File module
    if (strcmp(str, "file_read") == 0) return TOKEN_FILE_READ;
    if (strcmp(str, "file_write") == 0) return TOKEN_FILE_WRITE;
    if (strcmp(str, "file_exists") == 0) return TOKEN_FILE_EXISTS;
    if (strcmp(str, "file_delete") == 0) return TOKEN_FILE_DELETE;
    if (strcmp(str, "file_size") == 0) return TOKEN_FILE_SIZE;
    
    // JSON module
    if (strcmp(str, "json_parse") == 0) return TOKEN_JSON_PARSE;
    if (strcmp(str, "json_stringify") == 0) return TOKEN_JSON_STRINGIFY;
    if (strcmp(str, "json_get") == 0) return TOKEN_JSON_GET;
    if (strcmp(str, "json_set") == 0) return TOKEN_JSON_SET;
    
    // Time module
    if (strcmp(str, "time_now") == 0) return TOKEN_TIME_NOW;
    if (strcmp(str, "time_format") == 0) return TOKEN_TIME_FORMAT;
    if (strcmp(str, "time_sleep") == 0) return TOKEN_TIME_SLEEP;
    
    // System module
    if (strcmp(str, "system_run") == 0) return TOKEN_SYSTEM_RUN;
    if (strcmp(str, "system_get_env") == 0) return TOKEN_SYSTEM_GET_ENV;
    
    // Import system
    if (strcmp(str, "putlib") == 0) return TOKEN_PUTLIB;
    if (strcmp(str, "from") == 0) return TOKEN_FROM;
    if (strcmp(str, "as") == 0) return TOKEN_AS;
    
    if (strcmp(str, "yes") == 0) return TOKEN_YES;
    if (strcmp(str, "no") == 0) return TOKEN_NO;
    if (strcmp(str, "note") == 0) return TOKEN_NOTE;
    return TOKEN_ID;
}

lexer_T* init_lexer(char* contents) {
    lexer_T* lexer = malloc(sizeof(lexer_T));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];
    return lexer;
}

void lexer_advance(lexer_T* lexer) {
    if (lexer->c != '\0') {
        lexer->i++;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T* lexer) {
    while (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t') {
        lexer_advance(lexer);
    }
}

token_T* lexer_get_next_token(lexer_T* lexer) {
    while (lexer->c != '\0') {
        if (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t') {
            lexer_skip_whitespace(lexer);
            continue;
        }

        if (isdigit(lexer->c))
            return collect_number(lexer);

        if (isalnum(lexer->c))
            return collect_id(lexer);

        if (lexer->c == '"' || lexer->c == '\'')
            return collect_string(lexer);

        switch (lexer->c) {
            case '=': {
                lexer_advance(lexer);
                if (lexer->c == '=') {
                    lexer_advance(lexer);
                    return init_token(TOKEN_EQ, "==");
                }
                return init_token(TOKEN_EQUALS, "=");
            }
            case '!': {
                lexer_advance(lexer);
                if (lexer->c == '=') {
                    lexer_advance(lexer);
                    return init_token(TOKEN_NEQ, "!=");
                }
                // Handle single ! later if needed
                break;
            }
            case '>': {
                lexer_advance(lexer);
                if (lexer->c == '=') {
                    lexer_advance(lexer);
                    return init_token(TOKEN_GTE, ">=");
                }
                return init_token(TOKEN_GT, ">");
            }
            case '<': {
                lexer_advance(lexer);
                if (lexer->c == '=') {
                    lexer_advance(lexer);
                    return init_token(TOKEN_LTE, "<=");
                }
                return init_token(TOKEN_LT, "<");
            }
            case '+': return lexer_advance_with_token(lexer, init_token(TOKEN_PLUS, lexer_get_current_char_as_string(lexer)));
            case '-': return lexer_advance_with_token(lexer, init_token(TOKEN_MINUS, lexer_get_current_char_as_string(lexer)));
            case '*': return lexer_advance_with_token(lexer, init_token(TOKEN_MULTIPLY, lexer_get_current_char_as_string(lexer)));
            case '/': return lexer_advance_with_token(lexer, init_token(TOKEN_DIVIDE, lexer_get_current_char_as_string(lexer)));
            case ';': return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
            case '(': return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)));
            case ')': return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer)));
            case '{': return lexer_advance_with_token(lexer, init_token(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer)));
            case '}': return lexer_advance_with_token(lexer, init_token(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer)));
            case '[': return lexer_advance_with_token(lexer, init_token(TOKEN_LBRACKET, lexer_get_current_char_as_string(lexer)));
            case ']': return lexer_advance_with_token(lexer, init_token(TOKEN_RBRACKET, lexer_get_current_char_as_string(lexer)));
            case ',': return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer)));
            case ':': return lexer_advance_with_token(lexer, init_token(TOKEN_COLON, lexer_get_current_char_as_string(lexer)));
        }

        lexer_advance(lexer);
    }

    return NULL;
}

token_T* collect_string(lexer_T* lexer) {
    char quote_char = lexer->c; // Store the quote character (' or ")
    lexer_advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != quote_char && lexer->c != '\0') {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, strlen(value) + strlen(s) + 1);
        strcat(value, s);
        free(s);
        lexer_advance(lexer);
    }

    lexer_advance(lexer); // Skip closing quote
    return init_token(TOKEN_STRING, value);
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token) {
    lexer_advance(lexer);
    return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer) {
    char* s = malloc(2 * sizeof(char));
    s[0] = lexer->c;
    s[1] = '\0';
    return s;
}

token_T* collect_id(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c) || lexer->c == '_') {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, strlen(value) + strlen(s) + 1);
        strcat(value, s);
        free(s);
        lexer_advance(lexer);
    }



    // Check if it's a keyword
    int keyword_type = is_keyword(value);
    return init_token(keyword_type, value);
}

token_T* collect_number(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    int is_float = 0;

    while (isdigit(lexer->c) || lexer->c == '.') {
        if (lexer->c == '.') {
            if (is_float) break; // Second dot, stop
            is_float = 1;
        }
        
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, strlen(value) + strlen(s) + 1);
        strcat(value, s);
        free(s);
        lexer_advance(lexer);
    }

    return init_token(is_float ? TOKEN_FLOAT : TOKEN_NUMBER, value);
}
