/*
 *  Class for parsing input file
 *
 */

#ifndef REGISTERFILEPARSER_REGISTERFILEPARSER_H
#define REGISTERFILEPARSER_REGISTERFILEPARSER_H

#include <string>
#include <vector>
#include <regex>

class RegisterFileParser {
    public:

        void parseFile(const std::string &fileName);

        std::vector<std::vector<std::string>> getData() const;


    private:

        std::vector<std::vector<std::string>> parsedFile;

        const std::regex registerTitleTemplate = std::regex("R[0-9]+");
        const std::regex registerTemplate = std::regex("R[0-9]+.*0x[[:alnum:]]{6}");
        const std::regex registerDataTemplate = std::regex("[[:alnum:]]{6}");

        bool isPreambleOrPostamble(const std::string& line) const;

        void fillPreamble();

        void fillPostamble();

        void addLine(const std::string& line);

        std::vector<std::string> createVector(std::string, std::string, std::string);
};

#endif
