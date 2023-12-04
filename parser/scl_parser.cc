#include "scl_parser.h"
#include <sstream>

SclParser::SclParser(const std::string &input_file_name) {
    file_content_.clear();
    if (input_file_name.empty())
        return;
    std::ifstream input_file(input_file_name);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file " << input_file_name << std::endl;
        return;
    }
    std::string file_contents((std::istreambuf_iterator<char>(input_file)),
                              std::istreambuf_iterator<char>());
    size_t space_loc = file_contents.find("\n\n");
    scl_para_ = file_contents.substr(space_loc + 2);
}

void SclParser::parse(SclDatabase &scl_db) {
    size_t space_loc = scl_para_.find("\n\n");
    std::string front_line = scl_para_.substr(0, space_loc);
    scl_db.get_value().num_rows = parsing_number_(front_line);
    scl_para_ = scl_para_.substr(space_loc + 2);

    int counter_int = 0;
    std::stringstream counter_stream(scl_para_);
    std::string counter_line;
    SclDatabase::superset_t counter_superset = {};
    while (getline(counter_stream, counter_line)) {
        std::string counter_line_first;
        size_t back_loc;
        switch (counter_int) {
            case zeroth:
                break;
            case first:
                counter_superset.coordinate = parsing_number_(counter_line);
                break;
            case second:
                counter_superset.height = parsing_number_(counter_line);
                break;
            case third:
                counter_superset.sitewidth = parsing_number_(counter_line);
                break;
            case forth:
                counter_superset.sitespacing = parsing_number_(counter_line);
                break;
            case fifth:
                counter_superset.siteorient = parsing_char_(counter_line);
                break;
            case sixth:
                counter_superset.sitesymmetry = parsing_char_(counter_line);
                break;
            case seventh:
                try {
                    counter_line = upper_to_lower_(counter_line);
                    back_loc = counter_line.find("numsites");
                    counter_line_first = counter_line.substr(0, back_loc);
                    counter_superset.subroworigin = parsing_number_(counter_line_first);
                    counter_line_first = counter_line.substr(back_loc);
                }
                catch (const std::out_of_range &e) {
                    std::cerr << "Caught an exception unable to find the target's numsities" << std::endl;
                }
                counter_superset.numsites = parsing_number_(counter_line_first);
                scl_db.get_value().scl_instance.push_back(counter_superset);
                break;
            default:
                break;


        }

        counter_int = (counter_int + 1) % 9;
    }
}

char SclParser::parsing_char_(const std::string &counter_line) {
    std::string counter_lines;
    char result_char;
    size_t first_colon = counter_line.find(':');
    counter_lines = counter_line.substr(first_colon + 1);
    std::stringstream counter_stream(counter_lines);
    if (counter_stream >> result_char) {
        return result_char;
    } else {
        return ' ';
    }
}

int SclParser::parsing_number_(const std::string &counter_line) {
    std::string counter_lines;
    int result_number;
    size_t first_colon = counter_line.find(':');
    counter_lines = counter_line.substr(first_colon + 1);
    std::stringstream counter_stream(counter_lines);
    if (counter_stream >> result_number)
        return result_number;
    else
        return 0;
}

std::string SclParser::upper_to_lower_(const std::string &counter_line) {
    std::string lower_case = counter_line;
    for (char &counter_char: lower_case) {
        if (std::isalpha(static_cast<unsigned char>(counter_char))) {
            counter_char = std::tolower(static_cast<unsigned char>(counter_char));
        }
    }
    return lower_case;
}
