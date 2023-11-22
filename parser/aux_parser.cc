//
// Created by laozhu on 23-11-22.
//

#include "aux_parser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

AuxParser::AuxParser(const std::string &filename) {
    file_content_.clear();
    std::ifstream input_file_(filename);

    if (!input_file_.is_open()) {
        std::cerr << "Failed to open input file " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(input_file_, line)) {
        line = delete_leading_spaces_(line);
        if ((line.c_str()[0] == '/' && line.c_str()[1] == '*') || (line.c_str()[0] == '/' && line.c_str()[1] == '/'))
            continue;
        size_t pos = line.find("//"), space_count = 0;
        if (pos != std::string::npos)
            line.erase(pos);
        for (char c: line)
            if (c == ' ')
                space_count++;
        file_content_ = file_content_ + line;
    }

    input_file_.close();
}

std::string AuxParser::delete_leading_spaces_(std::string input) {
    while (!input.empty() && input.back() == ' ')
        input.pop_back();
    std::size_t firstNonSpace = input.find_first_not_of(' ');
    if (firstNonSpace == std::string::npos)
        return "";
    return input.substr(firstNonSpace);
}

void AuxParser::parse(AuxDatabase &aux_db, const std::string &bookshelf_path) {
    std::vector<std::string> suffixes = {".nodes", ".nets", ".wts", ".pl", ".scl"};

    std::stringstream ss(file_content_);
    std::string item;
    std::vector<std::string> tokens;
    while (ss >> item)
        tokens.push_back(item);

    for (const std::string &token: tokens) {
        for (const std::string &suffix: suffixes) {
            if (token.find(suffix) != std::string::npos) {
                if (suffix == ".nodes")
                    aux_db.nodes_filename = bookshelf_path + "/" + token;
                if (suffix == ".nets")
                    aux_db.nets_filename = bookshelf_path + "/" + token;
                if (suffix == ".wts")
                    aux_db.wts_filename = bookshelf_path + "/" + token;
                if (suffix == ".pl")
                    aux_db.pl_filename = bookshelf_path + "/" + token;
                if (suffix == ".scl")
                    aux_db.scl_filename = bookshelf_path + "/" + token;
            }
        }
    }
}
