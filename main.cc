#include "main.h"

int main(int argc, char **argv) {
    CMDLine command_line(argc, argv);
    command_line.legality_check();
    if (!command_line.bookshelf.file_available)
        return 1;

    AuxDatabase aux_database;
    AuxParser aux_parser(command_line.aux_file);
    aux_parser.parse(aux_database, command_line.bookshelf.str());
    std::cout << aux_database;

    NodesDatabase nodes_database;
    NodesParser nodes_parser(aux_database.nodes_filename);
    nodes_parser.parse(nodes_database);

    return 0;
}
