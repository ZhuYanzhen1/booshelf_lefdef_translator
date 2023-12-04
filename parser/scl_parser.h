#include <fstream>
#include <string>
#include <vector>

#include "scl_db.h"

class SclParser {
public:
    explicit SclParser(const std::string &input_file_name);

    void parse(SclDatabase &scl_db);

private:
    enum {
        zeroth,
        first,
        second,
        third,
        forth,
        fifth,
        sixth,
        seventh,
    };
    std::vector<std::string> file_content_;

    static int parsing_number_(const std::string &counter_line);

    static char parsing_char_(const std::string &counter_line);

    std::string scl_para_;

    static std::string upper_to_lower_(const std::string &counter_line);
};
