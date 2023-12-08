#include "eql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const eql_cmd_def _Move = {"Move", Move, 2};
const eql_cmd_def _Rotate = {"Rotate", Rotate, 1};
const eql_cmd_def _Pick = {"Pick", Pick, 0};

eql_action get_action_type(char *def) {
  if (strcmp(def, _Move.def) == 0) {
    return Move;
  } else if (strcmp(def, _Pick.def) == 0) {
    return Pick;
  } else if (strcmp(def, _Rotate.def) == 0) {
    return Rotate;
  }
  return -1;
}

void action_to_chars(eql_action action, char *dest) {
  switch (action) {
  case Move:
    strcpy(dest, _Move.def);
    break;
  case Rotate:
    strcpy(dest, _Rotate.def);
    break;
  case Pick:
    strcpy(dest, _Pick.def);
    break;
  }
}

int eql_assemble(eql_tokens *tokens, int size, eql_cmd *commands) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    eql_action action = get_action_type(tokens[i].value);
    switch (action) {
    case Move:
      commands[count].action = Move;
      commands[count].x = atoi(tokens[i + 1].value);
      commands[count].y = atoi(tokens[i + 2].value);
      commands[count].angle = -1;
      count++;
      break;
    case Rotate:
      commands[count].action = Rotate;
      commands[count].x = -1;
      commands[count].y = -1;
      commands[count].angle = atoi(tokens[i + 1].value);
      count++;
      break;
    case Pick:
      commands[count].action = Pick;
      commands[count].x = -1;
      commands[count].y = -1;
      commands[count].angle = -1;
      count++;
      break;
    }
  }
  for (int i = 0; i < count; i++) {
    eql_cmd cmd = commands[i];
    char action[TOKEN_SIZE];
    action_to_chars(cmd.action, action);
    printf("action:%s x:%d y:%d angle:%d \n", action, cmd.x, cmd.y, cmd.angle);
  }
  return count;
}

int eql_tokenize(char *text, eql_tokens *tokens) {
  int size = (int)strlen(text);
  char token[TOKEN_SIZE];
  int e = 0;
  int y = 0;
  for (int i = 0; i < size; i++) {
    if (text[i] == INLINE_DELIM || text[i] == NEWLINE_DELIM) {
      strcpy(tokens[y].value, token);
      tokens[y].size = e;
      e = 0;
      y++;
      memset(token, '\0', sizeof(token));
      continue;
    }
    token[e] = text[i];
    e++;
  }
  return y;
}

void eql_register_func(eql_action action, func_ptr f) { f(3, 43); }
