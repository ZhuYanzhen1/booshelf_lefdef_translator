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

private:
    std::vector<std::string> file_content_;

    static std::string delete_leading_spaces_(std::string input);
};

#endif // TRANSLATOR_PARSER_NETS_PARSER_H
