//
// Created by laozhu on 23-11-29.
//

#ifndef TRANSLATOR_PARSER_NETS_PARSER_H
#define TRANSLATOR_PARSER_NETS_PARSER_H

#include "nets_db.h"

class NetsParser {
public:
    explicit NetsParser(const std::string &filename);

    void parse(NetsDatabase &db);
};

#endif // TRANSLATOR_PARSER_NETS_PARSER_H
