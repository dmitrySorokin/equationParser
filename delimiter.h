#ifndef DELIMITER_H
#define DELIMITER_H

#include "token.h"

class delimiter:public token{
public:
    delimiter():token("delimiter"){;}
    virtual tokenType getType() const {
        return tokenType::_delimiter;
    };
};

class undefined:public token{
public:
    undefined():token("undefined"){;}
    virtual tokenType getType() const {
        return tokenType::_undefType;
    }
};

static const delimiter Delimiter;
static const undefined Undefined;

const token* readDelimiter(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream);
const token* readUndefined(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream);

#endif
