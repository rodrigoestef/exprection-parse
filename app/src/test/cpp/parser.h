#include "../../main/headers/parser.h"
#include <cassert>
#include <stdio.h>

void testParser() {

  FILE *stream;
  char *buffer;
  size_t t;

  stream = open_memstream(&buffer, &t);

  fprintf(stream, "2 + 2");
  fflush(stream);

  Parser *parser = new Parser(stream);

  fclose(stream);

  float f = parser->parse();
  assert(f == 4);

  try {

    stream = open_memstream(&buffer, &t);

    fprintf(stream, " 2+ 2-");
    fflush(stream);

    new Parser(stream);
  } catch (Exception &e) {
    assert(true);
  }
  fclose(stream);
  stream = open_memstream(&buffer, &t);

  fprintf(stream, " 2+ 2 - 3 ");
  fflush(stream);
  parser = new Parser(stream);
  fclose(stream);
  assert(parser->parse() == 1);

  stream = open_memstream(&buffer, &t);

  fprintf(stream, "2-2+2");
  fflush(stream);
  parser = new Parser(stream);
  fclose(stream);
  assert(parser->parse() == 2);

  stream = open_memstream(&buffer, &t);

  fprintf(stream, "2-(2+2)");
  fflush(stream);
  parser = new Parser(stream);
  fclose(stream);
  assert(parser->parse() == -2);

  stream = open_memstream(&buffer, &t);

  fprintf(stream, "1+2*2");
  fflush(stream);
  parser = new Parser(stream);
  fclose(stream);
  assert(parser->parse() == 5);

  stream = open_memstream(&buffer, &t);

  fprintf(stream, "2*2+1");
  fflush(stream);
  parser = new Parser(stream);
  fclose(stream);
  assert(parser->parse() == 5);
}
