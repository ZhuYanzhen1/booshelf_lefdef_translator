//
// Created by laozhu on 23-11-22.
//

#include "nodes_parser.h"
#include <iostream>
#include <fstream>
#include <regex>

NodesParser::NodesParser(const std::string &filename) {
    file_content_.clear();
    std::ifstream input_file_(filename);

    if (!input_file_.is_open()) {
        std::cerr << "Failed to open input file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(input_file_, line)) {
        size_t pos = line.find("//");
        if (pos != std::string::npos)
            line.erase(pos);
        line = delete_leading_spaces_(line);
        if ((line.c_str()[0] == '/' && line.c_str()[1] == '*') || (line.c_str()[0] == '/' && line.c_str()[1] == '/') ||
            (line.c_str()[0] == '#'))
            continue;
        if (!line.empty())
            file_content_.push_back(line);
    }
    input_file_.close();
}

std::string NodesParser::delete_leading_spaces_(std::string input) {
    while (!input.empty() && (input.back() == ' ' || input.back() == '\t'))
        input.pop_back();
    std::size_t firstNonSpace = input.find_first_not_of(' ');
    if (firstNonSpace == std::string::npos)
        return "";
    input = input.substr(firstNonSpace);
    std::size_t firstNonTab = input.find_first_not_of('\t');
    if (firstNonTab == std::string::npos)
        return "";
    return input = input.substr(firstNonTab);;
}

void NodesParser::parse(NodesDatabase &nodes_db) {
    std::regex pattern("[ \t]+");
    nodes_db.get_nodes().clear();
    nodes_db.nodes_num = std::stoul(&(file_content_[1].c_str()[file_content_[1].find(':') + 1]));
    nodes_db.terminals_num = std::stoul(&(file_content_[2].c_str()[file_content_[2].find(':') + 1]));
    for (size_t counter = 3; counter < file_content_.size(); ++counter) {
        NodesDatabase::node_info_t new_node;
        std::vector<std::string> tokens(
                std::sregex_token_iterator(file_content_[counter].begin(), file_content_[counter].end(), pattern,
                                           -1), std::sregex_token_iterator());
        new_node.name = tokens[0];
        new_node.width = std::stod(tokens[1]);
        new_node.height = std::stod(tokens[2]);
        if (tokens.size() == 4 && tokens[3] == "terminal")
            new_node.terminal = true;
        else
            new_node.terminal = false;
        nodes_db.get_nodes().push_back(new_node);
    }
}
