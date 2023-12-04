#ifndef TRANSLATOR_PARSER_PL_PARSER_H
#define TRANSLATOR_PARSER_PL_PARSER_H

#include "pl_db.h"

#include <fstream>
#include <iostream>
#include <vector>

class PlParser {
public:
    explicit PlParser(const std::string &filename)
            : file_(filename) {
    }

    void parse(PlDatabase &data_base);

    static void delete_terminals(const std::string &src_file, const std::string &dest_file);

private:
    std::ifstream file_;

    static void split_(const std::string &str,
                       const std::string &delimiters,
                       std::vector<std::string> &tokens);
};

#endif  // TRANSLATOR_PARSER_PL_PARSER_H
