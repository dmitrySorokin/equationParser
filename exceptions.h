#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

static const std::string bad_parentheses = " parentheses are mismatched ";
static const std::string bad_stack = " not enough numbers in stack to apply operator ";
static const std::string bad_operator = "can not apply operator ";
static const std::string bad_comma = " either the separator was misplaced or parentheses were mismatched ";
static const std::string bad_result =  "nothing to return";
static const std::string bad_argument = "bad function argument";

#endif
