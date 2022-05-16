#include "../../main/headers/parser.h"
#include <cassert>

void testParser() {

  Parser *parser = new Parser((char *)"2 + 2");

  float f = parser->parse();
  assert(f == 4);

  try {
    new Parser((char *)" 2+ 2-");
  } catch (Exception &e) {
    assert(true);
  }

  parser = new Parser((char *)" 2+ 2 - 3 ");
  assert(parser->parse() == 1);

  parser = new Parser((char *)"2-2+2");
  assert(parser->parse() == 2);
}
