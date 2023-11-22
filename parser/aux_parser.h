//
// Created by laozhu on 23-11-22.
//

#ifndef TRANSLATOR_PARSER_AUX_PARSER_H
#define TRANSLATOR_PARSER_AUX_PARSER_H

#include <string>

#include "aux_db.h"

class AuxParser {
public:
    explicit AuxParser(const std::string &filename);

    void parse(AuxDatabase &aux_db, const std::string &bookshelf_path);

private:
    std::string file_content_;

    static std::string delete_leading_spaces_(std::string input);
};

#endif // TRANSLATOR_PARSER_AUX_PARSER_H
