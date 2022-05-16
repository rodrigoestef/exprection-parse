#include "exceptions.h"
#include "syntax.h"
#include <stdio.h>
class Parser {
public:
  Parser(char *text) { this->syntax = new Syntax(text); }

  float parse() { return this->expr(); }

private:
  float expr() {
    Token *token = this->syntax->getNextToken();
    if (token == 0 || token->type != NUMBER) {
      throw Exception((char *)"NUMBER expected");
    }
    float num;

    sscanf(token->value, "%f", &num);
    return num + this->exprl();
  }
  float exprl() {
    Token *token = this->syntax->getNextToken();
    if (token == 0) {
      return 0;
    }
    if (token->type != OPERATOR) {
      throw Exception((char *)"OPERATOR expected");
    }
    char oper = *token->value;
    token = this->syntax->getNextToken();
    if (token == 0 || token->type != NUMBER) {
      throw Exception((char *)"NUMBER expected");
    }

    float num;
    sscanf(token->value, "%f", &num);

    if (oper == '-') {
      num = num * (-1);
    }
    return num + this->exprl();
  }
  Syntax *syntax;
};
