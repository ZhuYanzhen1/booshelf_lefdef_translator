#include "main.h"

int main(int argc, char **argv) {
    CMDLine command_line(argc, argv);
    command_line.legality_check();
    if (!command_line.bookshelf.file_available)
        return 1;

    AuxDatabase aux_database;
    AuxParser aux_parser(command_line.aux_file);
    aux_parser.parse(aux_database, command_line.bookshelf.str());
    std::cout << aux_database << std::endl;

    NodesDatabase nodes_database;
    NodesParser nodes_parser(aux_database.nodes_filename);
    nodes_parser.parse(nodes_database);
    std::cout << nodes_database << std::endl;

    NetsDatabase nets_database;
    NetsParser nets_parser(aux_database.nets_filename);
    nets_parser.parse(nets_database);
    std::cout << nets_database << std::endl;

    return 0;
}
