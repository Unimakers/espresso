#pragma once

#include <stdio.h>
#include <string.h>

#define INLINE_DELIM 0x20
#define NEWLINE_DELIM 0x0a
#define TOKEN_SIZE 12

typedef enum eql_action {
  Move,
  Rotate,
  Pick,
} eql_action;

// command definition
typedef struct eql_cmd_def {
  char def[TOKEN_SIZE];
  eql_action action;
  int args;
} eql_cmd_def;

typedef struct eql_cmd {
  eql_action action;
  int x;     // in mm
  int y;     // in mm
  int angle; // in degrees
} eql_cmd;

typedef struct eql_tokens {
  char value[TOKEN_SIZE];
  int size;
} eql_tokens;

typedef void (*func_ptr_move)(int, int);

typedef void (*func_ptr_rotate)(int);

typedef void(*func_ptr_pick);

typedef void (*func_ptr)();

// returns the number of tokens found
int eql_tokenize(char *text, eql_tokens *tokens);

int eql_assemble(eql_tokens *tokens, int size, eql_cmd *commands);

void eql_register_func(eql_action act, func_ptr);
