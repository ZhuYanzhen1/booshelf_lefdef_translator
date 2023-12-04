#include "pl_parser.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

void PlParser::parse(PlDatabase &data_base) {
    std::string line;
    std::getline(file_, line);
    while (std::getline(file_, line)) {
        if (line[0] == '#')
            continue;
        if (!line.empty() && ((line[0] >= 'A' && line[0] <= 'Z') || (line[0] >= 'a' && line[0] <= 'z'))) {
            std::vector<std::string> tokens;
            split_(line, " \t", tokens);
            auto *current_cell = new PlDatabase::CellInfo;
            if (tokens[1] == "nan")
                tokens[1] = "0";
            if (tokens[2] == "nan")
                tokens[2] = "0";
            current_cell->loc_xy[0] = std::stoi(tokens[1]);
            current_cell->loc_xy[1] = std::stoi(tokens[2]);
            current_cell->orientation.swap(tokens[4]);
            if (tokens.size() >= 6) {
                if (tokens[5] == "/FIXED")
                    current_cell->fixed = 1;
            } else
                current_cell->fixed = 0;
            data_base.get_map_info().insert(std::pair<std::string, PlDatabase::CellInfo>(tokens[0],
                                                                                         *current_cell));
            delete current_cell;
        }
    }
}

void PlParser::split_(const std::string &str,
                      const std::string &delimiters,
                      std::vector<std::string> &tokens) {
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token)) {
        size_t startPos = 0;
        size_t foundPos;
        while ((foundPos = token.find_first_of(delimiters, startPos)) != std::string::npos) {
            if (foundPos > startPos)
                tokens.push_back(token.substr(startPos, foundPos - startPos));
            startPos = foundPos + 1;
        }
        if (startPos < token.length())
            tokens.push_back(token.substr(startPos));
    }
    tokens.emplace_back(" ");
}

void PlParser::delete_terminals(const std::string &src_file, const std::string &dest_file) {
    std::ofstream outFile;
    std::string line;
    std::ifstream inFile(src_file);
    outFile.open(dest_file);
    std::regex pattern("[T][0-9]+");
    while (std::getline(inFile, line)) {
        if (!std::regex_search(line, pattern))
            outFile << line << std::endl;
    }
    outFile.flush();
    outFile.close();
}
