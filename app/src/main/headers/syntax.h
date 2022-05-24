#ifndef SYNTAX_H
#define SYNTAX_H
#include "exceptions.h"
#include "queue.h"
#include <cstdlib>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

enum TokensType { NUMBER, OPERATOR, OPERATORM, OP, CP };

class Token {
public:
  TokensType type;
  char *value;
};

class Syntax {

public:
  Syntax(FILE *stream) {
    this->stream = stream;
    this->lastChar = getc(this->stream);
    this->step0();
  }
  Token *getNextToken() { return this->queue->getNext(); }

private:
  void step0() {
    while (1) {
      if (this->lastChar == '#') {
        while (1) {
          this->lastChar = getc(this->stream);
          if (this->lastChar == '\n') {
            break;
          }
        }
      }
      if (this->lastChar == 0 || this->lastChar == EOF ||
          this->lastChar == ';') {
        return;
      }
      if (this->lastChar == ' ' || this->lastChar == '\n' ||
          this->lastChar == '\t' || this->lastChar == '\r') {
        this->lastChar = getc(this->stream);
        continue;
      }
      this->step1();
    }
  }

  void step1() {

    if (this->lastChar == '+' || this->lastChar == '-') {
      Token *newToken = new Token();
      newToken->type = OPERATOR;
      newToken->value = (char *)calloc(2, sizeof(char));
      *newToken->value = this->lastChar;
      this->queue->add(newToken);
      this->lastChar = getc(this->stream);
      return;
    }

    if (this->lastChar == '*' || this->lastChar == '/') {
      Token *newToken = new Token();
      newToken->type = OPERATORM;
      newToken->value = (char *)calloc(2, sizeof(char));
      *newToken->value = this->lastChar;
      this->queue->add(newToken);
      this->lastChar = getc(this->stream);
      return;
    }

    if (this->lastChar == '(' || this->lastChar == ')') {
      Token *newToken = new Token();
      newToken->value = (char *)calloc(2, sizeof(char));
      *newToken->value = this->lastChar;
      this->queue->add(newToken);

      if (this->lastChar == '(') {
        newToken->type = OP;
      }

      if (this->lastChar == ')') {
        newToken->type = CP;
      }
      this->lastChar = getc(this->stream);
      return;
    }

    this->step2();
  }

  void step2() {
    if (this->lastChar < '0' || this->lastChar > '9') {
      throw Exception((char *)"token unexpected");
    }
    Token *newToken = new Token();
    newToken->value = (char *)calloc(255, sizeof(char));
    *newToken->value = this->lastChar;
    newToken->type = NUMBER;
    this->queue->add(newToken);
    this->lastChar = getc(this->stream);
    this->step3(newToken);
  }
  void step3(Token *token) {

    while (true) {

      if (this->lastChar < '0' || this->lastChar > '9') {
        this->step4(token);
        return;
      }

      char newChar[2] = {this->lastChar, 0};
      strcat(token->value, newChar);
      this->lastChar = getc(this->stream);
    }
  }

  void step4(Token *token) {
    if (this->lastChar != '.') {
      return;
    }
    strcat(token->value, ".");

    this->lastChar = getc(this->stream);
    if (this->lastChar < '0' || this->lastChar > '9') {
      throw Exception((char *)"expected one number alter dot");
    }
    char newChar[2] = {this->lastChar, 0};
    strcat(token->value, newChar);
    this->lastChar = getc(this->stream);

    while (true) {
      if (this->lastChar < '0' || this->lastChar > '9') {
        return;
      }
      newChar[0] = this->lastChar;

      strcat(token->value, newChar);
      this->lastChar = getc(this->stream);
    }
  }
  char lastChar;
  FILE *stream;
  Queue<Token *> *queue = new Queue<Token *>;
};

#endif // !SYNTAX_H
