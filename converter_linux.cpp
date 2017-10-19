/**
 *   Main program file for Linux
 *   Usage:         <main_file_name> [parameters]
 *   Parameters:    -f source - set source file name
 *                  -h file - set file name of output header, default - <sourceName>.h
 *                  -i file - set file name of output ini file, default - <sourceName>.ini
 *                  Without -h and -i arguments you can set source file name without -f : <executable_name> <file>
 *
 *
 *
 */

#include <iostream>
#include <getopt.h>
#include "Headers/RegisterFileConverter.h"

int main(int argc, char *argv[]) {

    std::string fileName, headerName, iniName;
    bool customHeaderName = false, customIniName = false;

    if (argc > 2) {
        int optResult = 0;
        while ((optResult = getopt(argc, argv, "f:h:i:")) != -1) {
            switch (optResult) {
                case 'f':
                    fileName = std::string(optarg);
                    break;
                case 'h':
                    headerName = std::string(optarg);
                    customHeaderName = true;
                    break;
                case 'i':
                    iniName = std::string(optarg);
                    customIniName = true;
                    break;
                default:
                    std::cerr << "Incorrect syntax" << std::endl;
                    exit(3);
            };
        };
    } else {
        if (argc == 2) {
            fileName = std::string(argv[argc - 1]);
        } else {
            std::cerr << "Too few arguments" << std::endl;
            std::cout << "Usage:\t\t<executable_name> [parameters]\n"
                    "Parameters:\n\t\t-f source - set source file name\n"
                    "\t\t-h file - set file name of output header, default - <sourceName>.h\n"
                    "\t\t-i file - set file name of output ini file, default - <sourceName>.ini\n"
                    "\t\tWithout -h and -i arguments you can set source file name without -f : <executable_name> <file>"
                      << std::endl;
            exit(1);
        }
    }

    RegisterFileConverter converter(fileName);

    try {
        converter.parseFile();
        if (customHeaderName) {
            converter.convertToHeader(headerName);
        } else {
            converter.convertToHeader();
        }
        if (customIniName) {
            converter.convertToIni(iniName);
        } else {
            converter.convertToIni();
        }
    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
        return 2; // Call the destuctor
    }

    return 0;
}

