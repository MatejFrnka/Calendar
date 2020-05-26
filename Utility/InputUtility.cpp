/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include <ctime>
#include <iomanip>
#include "InputUtility.h"

std::vector<std::string> InputUtility::getParams(const std::string &input) {
    std::vector<std::string> result;
    std::istringstream iss(input);
    for (std::string s; iss >> s;)
        result.push_back(s);
    return result;
}

InputUtility::InputUtility(std::istream &in_, std::ostream &out_) : out(out_), in(in_) {

}

std::string InputUtility::readString(const std::string &attr, const std::string &currentVal, bool required) {
    std::string result;
    bool firstTry = true;
    do {
        if (!firstTry) {
            out << attr << " must not be empty" << std::endl;
        }
        out << '\t' << attr << ": " << currentVal;
        if (currentVal.empty() || !firstTry)
            std::getline(in, result);
        else {
            result = currentVal;
            out << std::endl;
        }
        firstTry = false;
    } while (result.empty() || !required);
    return result;
}

time_t InputUtility::readDate(const std::string &attr, const std::string &currentVal, bool required) {
    std::tm time = {};
    bool firstTry = true;
    std::stringstream line;
    do {
        if (!firstTry) {
            out << "Invalid date format. Please use 01-01-2000T12:00 format" << std::endl;
        }
        out << '\t' << attr << ": " << (firstTry ? currentVal : "");
        line = getLine(firstTry && !currentVal.empty(), currentVal);

        if (line.rdbuf()->in_avail() == 0 && !required) {
            return -1;
        }
        line >> std::get_time(&time, "%d-%m-%YT%H:%M");
        firstTry = false;
    } while (line.fail());
    out << "\n";
    return std::mktime(&time);
}

time_t InputUtility::readTimeSpan(const std::string &attr, const std::string &currentVal, bool required) {
    std::stringstream ss;
    bool firstTry = true;
    while (true) {
        out << '\t' << attr << ": " << (firstTry ? currentVal : "");
        ss = getLine(firstTry && !currentVal.empty(), currentVal);
        float value;
        ss >> value;
        if (!ss.fail() && ss.get() == '-') {
            std::string unit;
            ss >> unit;

            auto it = timeDictionary.find(unit);
            if (it != timeDictionary.end())
                return it->second * value;
        }
        out << "Date type was not found, use one of following: ";
        for (const auto &iter : timeDictionary)
            out << iter.first << ", ";
        out << "in format '5-day'" << std::endl;
        firstTry = false;
    }
}

int InputUtility::readNumber(const std::string &attr) {
    int result;
    do {
        out << '\t' << attr << ": ";
        in >> result;
    } while (in.fail());
    return result;
}

int InputUtility::readNumber(const std::string &attr, const std::string& currentVal) {
    int result;
    out << '\t' << attr << ": ";
    std::stringstream input(currentVal);
    input >> result;
    if (input.fail())
        return readNumber(attr);
    return result;
}

std::stringstream InputUtility::getLine(bool useDefault, const std::string &defaultVal) const {
    if (useDefault)
        return std::stringstream(defaultVal);
    else {
        std::string input;
        std::getline(in, input);
        return std::stringstream(input);
    }
}

void InputUtility::noParameterFound(const std::string &param) {
    if (param.empty())
        out << "No parameter found, type 'help' for all available commands";
    else
        out << "Parameter " + param + "was not found, type 'help' for all available commands";
}
