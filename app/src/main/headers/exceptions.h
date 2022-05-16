#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class Exception {

public:
  char *message;
  Exception(char *msg) { this->message = msg; }
};

#endif // !EX
