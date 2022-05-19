#include "exceptions.h"
#include "syntax.h"
#include <stdio.h>
class Parser {
public:
  Parser(FILE *stream) { this->syntax = new Syntax(stream); }

  float parse() { return this->expr(); }

private:
  float expr() {
    Token *token = this->syntax->getNextToken();
    if (token == 0 || !(token->type == NUMBER || token->type == OP)) {
      throw Exception((char *)"NUMBER or '(' expected");
    }
    if (token->type == NUMBER) {

      float num;

      sscanf(token->value, "%f", &num);
      return num + this->exprl();
    } else {
      return this->expr() + this->exprl();
    }
  }
  float exprl() {
    Token *token = this->syntax->getNextToken();
    if (token == 0 || token->type == CP) {
      return 0;
    }
    if (token->type != OPERATOR) {
      throw Exception((char *)"OPERATOR expected");
    }
    char oper = *token->value;
    token = this->syntax->getNextToken();
    if (token == 0 || !(token->type == NUMBER || token->type == OP)) {
      throw Exception((char *)"NUMBER or '(' expected");
    }
    if (token->type == NUMBER) {

      float num;
      sscanf(token->value, "%f", &num);

      if (oper == '-') {
        num = num * (-1);
      }
      return num + this->exprl();
    } else {
      float exprResult = this->expr();
      if (oper == '-') {
        exprResult = exprResult * (-1);
      }
      return exprResult + this->exprl();
    }
  }
  Syntax *syntax;
};
