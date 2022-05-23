#include "exceptions.h"
#include "queue.h"
#include "syntax.h"
#include <cmath>
#include <stdio.h>
class Parser {
public:
  Parser(FILE *stream) { this->syntax = new Syntax(stream); }

  float parse() { return this->expr(); }

private:
  float expr() {
    Token *token = this->getNextToken();
    if (token == 0 || !(token->type == NUMBER || token->type == OP)) {
      throw Exception((char *)"NUMBER or '(' expected");
    }
    if (token->type == NUMBER) {
      this->currentQueue->add(token);
      float num = this->exprm();

      float num2 = this->exprl();
      num = std::isnan(num2) ? num : num + num2;
      return num;
    } else {

      float num = this->expr();
      token = this->getNextToken();
      if (token == 0 || token->type != CP) {
        throw Exception((char *)") expected");
      }

      token = this->getNextToken();
      this->currentQueue->add(token);

      if (token == 0) {
        return num;
      }
      if (token->type == OPERATOR) {
        return num + this->exprl();
      } else if (token->type == OPERATORM) {
        return num * this->exprml();
      } else {
        throw Exception((char *)"OPERATOR expected");
      }
    }
  }
  float exprm() {
    Token *token = this->getNextToken();
    if (token == 0 || !(token->type == NUMBER || token->type == OP)) {
      throw Exception((char *)"NUMBER or '(' expected");
    }
    if (token->type == NUMBER) {

      float num;

      sscanf(token->value, "%f", &num);
      float num2 = this->exprml();
      num = std::isnan(num2) ? num : num * num2;
      return num;
    } else {
      float num = this->expr();
      token = this->getNextToken();
      if (token == 0 || token->type != CP) {
        throw Exception((char *)") expected");
      }

      token = this->getNextToken();
      this->currentQueue->add(token);

      if (token == 0) {
        return num;
      }
      if (token->type == OPERATOR) {
        return num + exprl();
      } else if (token->type == OPERATORM) {
        return num * exprml();
      } else {
        throw Exception((char *)"OPERATOR expected");
      }
    }
  }
  float exprml() {
    Token *token = this->getNextToken();
    if (token == 0) {

      return NAN;
    }
    if (token->type == CP) {
      this->currentQueue->add(token);
      return NAN;
    }
    if (token->type != OPERATORM) {
      this->currentQueue->add(token);
      return NAN;
    }
    char oper = *token->value;
    token = this->getNextToken();
    if (token == 0 || !(token->type == NUMBER || token->type == OP)) {
      throw Exception((char *)"NUMBER or '(' expected");
    }
    if (token->type == NUMBER) {

      float num;
      sscanf(token->value, "%f", &num);

      if (oper == '/') {
        num = 1 / num;
      }
      float num2 = this->exprml();
      num = std::isnan(num2) ? num : num * num2;
      return num;
    } else {
      float exprResult = this->expr();

      token = this->getNextToken();

      if (token == 0 || token->type != CP) {
        throw Exception((char *)") expected");
      }

      if (oper == '/') {
        exprResult = 1 / exprResult;
      }

      token = this->getNextToken();
      this->currentQueue->add(token);

      if (token == 0) {
        return exprResult;
      }
      if (token->type == OPERATOR) {

        return exprResult;
      } else if (token->type == OPERATORM) {

        return exprResult * this->exprml();
      } else {
        throw Exception((char *)"OPERATOR expected");
      }
    }
  }
  float exprl() {
    Token *token = this->getNextToken();
    if (token == 0) {

      return NAN;
    }
    if (token->type == CP) {
      this->currentQueue->add(token);
      return NAN;
    }
    if (token->type != OPERATOR) {
      throw Exception((char *)"OPERATOR expected");
    }
    char oper = *token->value;
    token = this->getNextToken();
    if (token == 0 || !(token->type == NUMBER || token->type == OP)) {
      throw Exception((char *)"NUMBER or '(' expected");
    }
    if (token->type == NUMBER) {

      this->currentQueue->add(token);

      float num = this->exprm();

      if (oper == '-') {
        num = num * (-1);
      }
      float num2 = this->exprl();
      num = std::isnan(num2) ? num : num + num2;
      return num;
    } else {
      float exprResult = this->expr();

      token = this->getNextToken();

      if (token == 0 || token->type != CP) {
        throw Exception((char *)") expected");
      }
      if (oper == '-') {
        exprResult = exprResult * (-1);
      }

      token = this->getNextToken();
      this->currentQueue->add(token);

      if (token == 0) {
        return exprResult;
      }
      if (token->type == OPERATOR) {

        return exprResult + this->exprl();
      } else if (token->type == OPERATORM) {

        return exprResult * this->exprml();
      } else {
        throw Exception((char *)"OPERATOR expected");
      }
    }
  }

  Token *getNextToken() {
    Token *token = this->currentQueue->getNext();
    if (token != 0) {
      return token;
    } else {
      return this->syntax->getNextToken();
    }
  }
  Queue<Token *> *currentQueue = new Queue<Token *>();
  Syntax *syntax;
};
