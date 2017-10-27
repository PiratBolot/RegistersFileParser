#include <fstream>
#include <iostream>
#include "../Headers/RegisterFileParser.h"

void RegisterFileParser::parseFile(const std::string &fileName) {
    std::fstream stream;
    stream.open(fileName, std::ios_base::in);
    if (!stream.good()) {
        throw std::runtime_error("Can not open file: " + fileName);
    }
    std::string line;
    fillPreamble();
    while (!stream.eof()) {
        std::smatch res;
        std::getline(stream, line);
        if (std::regex_search(line, res, registerTemplate)) {
            if (!isPreambleOrPostamble(res[0])) {
                addLine(res[0]);
            }
        }
    }
    fillPostamble();
}

bool RegisterFileParser::isPreambleOrPostamble(const std::string &line) const {
    std::smatch register_;
    if (std::regex_search(line, register_, registerTitleTemplate)) {
        int ordinalNumber = std::stoi(register_.str().substr(1));
        if (ordinalNumber >= 0 && ordinalNumber <= 13 || ordinalNumber >= 8189 && ordinalNumber <= 8191) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<std::string>> RegisterFileParser::getData() const {
    return parsedFile;
}

void RegisterFileParser::fillPreamble() {
    parsedFile.emplace_back(std::string("0x00"), std::string("0x00"), std::string("0x80"));
    parsedFile.emplace_back(std::string("0x00"), std::string("0x00"), std::string("0x00"));
}

void RegisterFileParser::fillPostamble() {
    parsedFile.emplace_back(std::string("0x01"), std::string("0x43"), std::string("0xD1"));
    parsedFile.emplace_back(std::string("0x01"), std::string("0x43"), std::string("0xF1"));
    parsedFile.emplace_back(std::string("0x01"), std::string("0x43"), std::string("0xD1"));
    parsedFile.emplace_back(std::string("0x01"), std::string("0x44"), std::string("0xFF"));
    parsedFile.emplace_back(std::string("0x01"), std::string("0x43"), std::string("0x51"));
    parsedFile.emplace_back(std::string("0x01"), std::string("0x43"), std::string("0x52"));
    parsedFile.emplace_back(std::string("0x01"), std::string("0x39"), std::string("0x02"));
}

void RegisterFileParser::addLine(const std::string& line) {
    std::smatch data;
    if (std::regex_search(line, data, registerDataTemplate)) {
        parsedFile.emplace_back(createVector("0x" + data.str().substr(0, 2), "0x" + data.str().substr(2, 2), "0x" + data.str().substr(4, 2)));
    }
}
