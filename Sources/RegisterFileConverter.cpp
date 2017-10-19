#include <iostream>
#include "../Headers/RegisterFileConverter.h"

const std::string RegisterFileConverter::INI_EXTENSION = ".ini";
const std::string RegisterFileConverter::HEADER_EXTENSION = ".h";

RegisterFileConverter::RegisterFileConverter(const std::string& fileName) : fileName(fileName) {};

std::string RegisterFileConverter::cutFileNameExtension(std::string fileName) const {
    return fileName.substr(0, fileName.find_last_of('.'));
}

void RegisterFileConverter::convertToIni() const {
    convertToIni(cutFileNameExtension(fileName) + INI_EXTENSION);
}

void RegisterFileConverter::convertToHeader() const {
    convertToHeader(cutFileNameExtension(fileName) + HEADER_EXTENSION);
}

void RegisterFileConverter::parseFile() {
    parser.parseFile(fileName);
    data = parser.getData();
}

std::string RegisterFileConverter::toHeaderName(const std::string &string)const {
	char separateSymbol = '/';
	if (string.find("\\") != std::string::npos) {
		separateSymbol = '\\';
	}
	else if (string.find("/") != std::string::npos) {
		separateSymbol = '/';
	}		
    std::string headerName(string.substr(string.find_last_of(separateSymbol) + 1));
    std::for_each(headerName.begin(), headerName.end(), [&](char &letter) {
        letter = static_cast<char>(toupper(letter));
        if (letter == '.') {
            letter = '_';
        }
    });
	return headerName;
}

void RegisterFileConverter::convertToIni(const std::string &fileName) const {
    std::ofstream iniFile(fileName, std::ios_base::trunc);
    if (!iniFile) {
        throw std::runtime_error("Error opening file: " + fileName);
    }

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data.at(i).size(); ++j) {
            (data.size() - i == 1 && data.at(i).size() - j == 1) ? iniFile << data.at(i).at(j) : iniFile << data.at(i).at(j) << ", ";
        }
        iniFile << std::endl;
    }
    iniFile.close();
}

void RegisterFileConverter::convertToHeader(const std::string &fileName) const {
    std::ofstream header(fileName);
    if (!header) {
        throw std::runtime_error("Error opening file: " + fileName);
    }
    std::string preProccessor = toHeaderName(fileName);

    header << "#ifndef " << preProccessor << std::endl;
    header << "#define " << preProccessor << std::endl << std::endl;
    header << "const uint32_t numCommands = " << data.size() << ";" << std::endl;
    header << "const uint32_t LmkConfigCmds[numCommands][3] = {" << std::endl;

    for (size_t i = 0; i < data.size(); ++i) {
        header << "\t{ ";
        for (unsigned int j = 0; j < data.at(i).size(); ++j) {
            header << data.at(i).at(j);
            if (j != data.at(i).size() - 1) {
                header << ",  ";
            }
        }
        if (data.size() - i != 1) {
            header << "}, " << std::endl;
        } else {
            header << "}" << std::endl;
        }
    }

    header << "};" << std::endl;
    header << "#endif //" << preProccessor << std::endl;
    header.close();
}


