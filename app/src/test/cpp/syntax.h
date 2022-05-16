#include "../../main/headers/exceptions.h"
#include "../../main/headers/syntax.h"
#include <cassert>
#include <string.h>

void testSyntax() {

  Syntax *syntax = new Syntax((char *)"+ 9 3 50 2.2");

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
    new Syntax((char *)"t");
    assert(false);
  } catch (Exception &e) {
    assert(true);
  }
}
