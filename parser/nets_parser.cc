//
// Created by laozhu on 23-11-29.
//

#include "nets_parser.h"
#include <fstream>
#include <sstream>

NetsParser::NetsParser(const std::string &filename) {
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

void NetsParser::parse(NetsDatabase &db) {
    db.get_nets().clear();
    db.net_num = std::stoul(&(file_content_[1].c_str()[file_content_[1].find(':') + 1]));
    db.pin_num = std::stoul(&(file_content_[2].c_str()[file_content_[2].find(':') + 1]));
    NetsDatabase::net_t *new_net = nullptr;
    for (size_t counter = 3; counter < file_content_.size(); ++counter) {
        const auto &line = file_content_[counter];
        if (line.find("NetDegree") != std::string::npos) {
            if (new_net != nullptr) {
                db.get_nets().push_back(*new_net);
                delete new_net;
            }
            new_net = new NetsDatabase::net_t;
            std::string pin_num_str = line.substr(line.find(':') + 1);
            size_t space_pos = pin_num_str.find_last_of(' ');
            if (space_pos != std::string::npos)
                new_net->name = pin_num_str.substr(space_pos);
            else
                new_net->name = pin_num_str.substr(pin_num_str.find('\t'));
            new_net->pin_num = std::stoul(pin_num_str);
        } else {
            NetsDatabase::pin_t new_pin;
            std::vector<std::string> tokens;
            std::string current_token;
            for (auto &character: line) {
                if (character == ' ' || character == '\t') {
                    if (!current_token.empty()) {
                        tokens.push_back(current_token);
                        current_token.clear();
                    }
                } else
                    current_token += character;
            }
            if (!current_token.empty())
                tokens.push_back(current_token);
            new_pin.name = tokens[0];
            new_pin.in_out = tokens[1];
            new_pin.pos_x = std::stod(tokens[3]);
            new_pin.pos_y = std::stod(tokens[4]);
            if (new_net != nullptr)
                new_net->pins.push_back(new_pin);
        }
    }
    if (new_net != nullptr) {
        db.get_nets().push_back(*new_net);
        delete new_net;
    }
}

std::string NetsParser::delete_leading_spaces_(std::string input) {
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
