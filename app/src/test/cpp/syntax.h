#include "../../main/headers/exceptions.h"
#include "../../main/headers/syntax.h"
#include <cassert>
#include <stdio.h>
#include <string.h>
void testSyntax() {

  FILE *stream;
  char *buffer;
  size_t size;

  stream = open_memstream(&buffer, &size);

  fprintf(stream, "+ 9 3 50 2.2");
  fflush(stream);

  Syntax *syntax = new Syntax(stream);

  fclose(stream);

  Token *token = syntax->getNextToken();
  assert(token->type == OPERATOR);
  token = syntax->getNextToken();
  assert(token->type == NUMBER);
  token = syntax->getNextToken();
  assert(token->type == NUMBER);

  token = syntax->getNextToken();
  assert(strcmp(token->value, "50") == 0);

  token = syntax->getNextToken();
  assert(strcmp(token->value, "2.2") == 0);

  try {
    stream = open_memstream(&buffer, &size);
    fprintf(stream, "f");
    fflush(stream);
    new Syntax(stream);

    assert(false);
  } catch (Exception &e) {
    assert(true);
  }
}
