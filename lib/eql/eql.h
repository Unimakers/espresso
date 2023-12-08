#pragma once

#include <stdio.h>
#include <string.h>

#define INLINE_DELIM 0x20
#define NEWLINE_DELIM 0x0a
#define TOKEN_SIZE 12
#define MAX_TOKENS 1500
#define MAX_COMMANDS 500

typedef enum eql_action_t {
  Move,
  Rotate,
  Pick,
} eql_action_t;

// command definition
typedef struct eql_command_def_t {
  char def[TOKEN_SIZE];
  eql_action_t action;
  int args;
} eql_command_def_t;

typedef struct eql_command_t {
  eql_action_t action;
  int x;      // in mm
  int y;      // in mm
  int angle;  // in degrees
} eql_command_t;

typedef struct eql_token_t {
  char value[TOKEN_SIZE];
  int size;
} eql_token_t;

typedef void (*func_ptr_move)(int, int);

typedef void (*func_ptr_rotate)(int);

typedef void(*func_ptr_pick);

typedef void (*func_ptr)();

// returns the number of tokens found
int eql_tokenize(char *text, eql_token_t *tokens);

int eql_assemble(eql_token_t *tokens, int size, eql_command_t *commands);

void eql_register_func(eql_action_t act, func_ptr);
