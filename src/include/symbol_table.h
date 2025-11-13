#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum {
    VAR_TYPE_STRING,
    VAR_TYPE_INT,
    VAR_TYPE_DOUBLE,
    VAR_TYPE_BOOL
} var_type_t;

typedef struct symbol {
    char* name;
    var_type_t type;
    struct symbol* next;
} symbol_t;

typedef struct symbol_table {
    symbol_t* head;
} symbol_table_t;

symbol_table_t* init_symbol_table();
void add_symbol(symbol_table_t* table, const char* name, var_type_t type);
var_type_t get_symbol_type(symbol_table_t* table, const char* name);
void free_symbol_table(symbol_table_t* table);

#endif
