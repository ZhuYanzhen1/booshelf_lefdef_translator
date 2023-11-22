//
// Created by laozhu on 23-11-22.
//

#ifndef TRANSLATOR_PARSER_NODES_PARSER_H
#define TRANSLATOR_PARSER_NODES_PARSER_H

#include "nodes_db.h"

class NodesParser {
public:
    explicit NodesParser(const std::string &filename);

    void parse(NodesDatabase &nodes_db);

private:
    std::vector<std::string> file_content_;

    static std::string delete_leading_spaces_(std::string input);
};

#endif //TRANSLATOR_PARSER_NODES_PARSER_H
