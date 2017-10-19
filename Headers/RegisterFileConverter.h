/*
 *
 *  Class for converting input file to .ini and/or .h files
 *
 *  Input file format - <Register_name><tab><Register_address[0]><Register_address[1]><Command>
 *                       Register_address[0], Register_address[1] and Command are one 3-byte HEX number,
 *                       e.g: R267  0x010B07 means:  Name                  = R267
 *                                                   Register_address[0]   = 0x01
 *                                                   Register_address[1]   = 0x0B
 *                                                   Command               = 0x07
 *
 *  Ini output format  - same ordered data without name of register
 *
 *                       e.g:   0x01,  0x13,  0x07,
 *                              0x01,  0x14,  0x20,
 *                              0x01,  0x15,  0x11,
 *                                      ...
 *                              0x05,  0x0B,  0x0D
 *
 *  Header output format - need to include into project
 *
 *                           e.g             #ifndef INPUT_FILE_NAME
 *                                           #define INPUT_FILE_NAME
 *
 *                                           const uint32_t numCommands = 3;
 *                                           const uint8_t LmkConfigCmds[numCommands][3]={
 *                                                  { 0x00, 0x00, 0x80 },
 *                                                  { 0x00, 0x00, 0x00 },
 *                                                  { 0x00, 0x00, 0x80 }
 *                                           };
 *
 *                                           #endif //INPUT_FILE_NAME
 *
 *
 *
 */

#ifndef REGISTERFILEPARSER_REGISTERPARSER_H
#define REGISTERFILEPARSER_REGISTERPARSER_H

#include <fstream>
#include <string>
#include <vector>
#include "RegisterFileParser.h"

class RegisterFileConverter {

public:

    explicit RegisterFileConverter(const std::string& fileName);

    void parseFile();

    void convertToIni() const;

    void convertToHeader() const;

    void convertToHeader(const std::string& fileName) const;

    void convertToIni(const std::string& fileName) const;


private:

    std::string fileName;
    RegisterFileParser parser;
    static const std::string INI_EXTENSION;
    static const std::string HEADER_EXTENSION;
    std::vector<std::vector<std::string>> data;

    std::string cutFileNameExtension(std::string fileName) const ;

    std::string toHeaderName(const std::string &string)const;
};


#endif
