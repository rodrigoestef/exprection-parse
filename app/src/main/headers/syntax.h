#ifndef SYNTAX_H
#define SYNTAX_H
#include "exceptions.h"
#include "queue.h"
#include <cstdlib>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

enum TokensType { NUMBER, OPERATOR };

class Token {
public:
  TokensType type;
  char *value;
};

class Syntax {

public:
  Syntax(char *stream) {
    this->buf = stream;
    this->step0();
  }
  Token *getNextToken() { return this->queue->getNext(); }

private:
  void step0() {
    while (1) {
      if (*this->buf == 0) {
        return;
      }
      if (*this->buf == ' ' || *this->buf == '\n' || *this->buf == '\t' ||
          *this->buf == '\r') {
        this->buf++;
        continue;
      }
      this->step1();
    }
  }

  void step1() {

    if (*this->buf == '+' || *this->buf == '-') {
      Token *newToken = new Token();
      newToken->type = OPERATOR;
      newToken->value = (char *)calloc(2, sizeof(char));
      *newToken->value = *this->buf;
      this->queue->add(newToken);
      this->buf++;
      return;
    }
    this->step2();
  }

  void step2() {
    if (*this->buf < 48 || *this->buf > 57) {
      throw Exception((char *)"token unexpected");
    }
    Token *newToken = new Token();
    newToken->value = (char *)calloc(255, sizeof(char));
    *newToken->value = *this->buf;
    newToken->type = NUMBER;
    this->queue->add(newToken);
    this->buf++;
    this->step3(newToken);
  }
  void step3(Token *token) {

    while (true) {

      if (*this->buf < 48 || *this->buf > 57) {
        this->step4(token);
        return;
      }

      char newChar[2] = {*this->buf, 0};
      strcat(token->value, newChar);
      this->buf++;
    }
  }

  void step4(Token *token) {
    if (*this->buf != '.') {
      return;
    }
    strcat(token->value, ".");

    this->buf++;
    if (*this->buf < 48 || *this->buf > 57) {
      throw Exception((char *)"expected one number alter dot");
    }
    char newChar[2] = {*this->buf, 0};
    strcat(token->value, newChar);
    this->buf++;

    while (true) {
      if (*this->buf < 47 || *this->buf > 57) {
        return;
      }
      newChar[0] = *this->buf;

      strcat(token->value, newChar);
      this->buf++;
    }
  }
  char *buf;
  Queue<Token *> *queue = new Queue<Token *>;
};

#endif // !SYNTAX_H
