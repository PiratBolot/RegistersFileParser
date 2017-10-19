/*
 *
 *  Main programm for Windows version
 *  Usage - <main_file_name> <input_file_name> *
 *
 */

#include <fstream>
#include <iostream>
#include "Headers/RegisterFileConverter.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect format of the input data. The number of parameters: " << argc - 1 << std::endl;
        std::cerr << "Usage - <main_file_name> <input_file_name>" << std::endl;
        exit(1); // Don't have any objects yet.
    }
    RegisterFileConverter converter(argv[1]);

    try {
        converter.parseFile();
        converter.convertToHeader();
        converter.convertToIni();
    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
        return 2; // Call the destuctor
    }

    return 0;
}