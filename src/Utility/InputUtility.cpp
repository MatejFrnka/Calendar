/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include <ctime>
#include <iomanip>
#include <chrono>
#include "InputUtility.h"
#include "Exceptions/UnexpectedEndOfInputException.h"

std::queue<std::string> InputUtility::getParams(const std::string &input) {
    std::queue<std::string> result;
    std::istringstream iss(input);
    for (std::string s; iss >> s;)
        result.push(s);
    return result;
}

InputUtility::InputUtility(std::istream &in_, std::ostream &out_) : out(out_), in(in_) {

}

std::string InputUtility::readString(const std::string &attr, std::queue<std::string> &params, bool required) const {
    return readString(attr, tryGetVal(params), required);
}

std::string InputUtility::readString(const std::string &attr, const std::string &currentVal, bool required) const {
    std::string result;
    bool firstTry = true;
    do {
        if (!firstTry) {
            out << attr << " must not be empty" << std::endl;
        }
        out << '\t' << attr << ": " << currentVal;
        if (currentVal.empty() || !firstTry) {
            if (in.eof())
                throw UnexpectedEndOfInputException();
            std::getline(in, result);
        } else {
            result = currentVal;
            out << std::endl;
        }
        firstTry = false;
    } while (result.empty() && required);
    return result;
}

time_t InputUtility::readDateTime(const std::string &attr, const std::string &currentVal, bool required) const {
    return toDateTimeNoSeconds(customReadDate(attr, currentVal, required, "%d-%m-%YT%H:%M", "01-01-2000T12:00"));
}

time_t InputUtility::readDateTime(const std::string &attr, std::queue<std::string> &params, bool required) const {
    return readDateTime(attr, tryGetVal(params), required);
}

time_t InputUtility::readDate(const std::string &attr, const std::string &currentVal, bool required) const {
    return toDate(customReadDate(attr, currentVal, required, "%d-%m-%Y", "01-01-2000"));
}

time_t InputUtility::readDate(const std::string &attr, std::queue<std::string> &params, bool required) const {
    return readDate(attr, tryGetVal(params), required);
}

time_t InputUtility::readTimeSpan(const std::string &attr, const std::string &currentVal, bool required) const {
    std::stringstream ss;
    bool firstTry = true;
    while (true) {
        out << '\t' << attr << ": " << (firstTry && !currentVal.empty() ? currentVal + "\n" : "");
        ss = getLine(firstTry && !currentVal.empty(), currentVal);
        float value;
        ss >> value;
        if (!ss.fail() && ss.get() == '-') {
            if (value <= 0) {
                out << "Value must be greater than 0" << endl;
                continue;
            }
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

time_t InputUtility::readTimeSpan(const std::string &attr, std::queue<std::string> &params, bool required) const {
    return readTimeSpan(attr, tryGetVal(params), required);
}

int InputUtility::readNumber(const std::string &attr) const {
    int result;
    do {
        out << '\t' << attr << ": ";
        in >> result;
    } while (in.fail());
    return result;
}

bool InputUtility::readBool(const std::string &attr) {
    while (true) {
        out << '\t' << attr << " (y/n): ";
        std::string input;
        if (in.eof())
            throw UnexpectedEndOfInputException();
        getline(in, input);
        if (input == "y" || input == "n")
            return input == "y";
        out << "use 'y' (yes) or 'n' (no)";
    }
}

std::stringstream InputUtility::getLine(bool useDefault, const std::string &defaultVal) const {
    if (useDefault)
        return std::stringstream(defaultVal);
    else {
        std::string input;
        if (in.eof())
            throw UnexpectedEndOfInputException();
        std::getline(in, input);
        return std::stringstream(input);
    }
}

time_t InputUtility::customReadDate(const std::string &attr, const std::string &currentVal, bool required, const std::string &format, const std::string &exampleFormat) const {
    std::tm time = {};
    bool firstTry = true;
    std::stringstream line;
    do {
        if (!firstTry) {
            out << "Invad date format. Please use " << exampleFormat << " format or 'now' for current date" << std::endl;
        }
        out << '\t' << attr << ": " << (firstTry && !currentVal.empty() ? currentVal + "\n" : "");
        line = getLine(firstTry && !currentVal.empty(), currentVal);

        if (line.str() == "now")
            return getCurrentTime();

        if (line.rdbuf()->in_avail() == 0 && !required) {
            return -1;
        }
        line >> std::get_time(&time, "%d-%m-%YT%H:%M");
        firstTry = false;
    } while (line.fail());
    time_t result = std::mktime(&time);
    //Converting to current timezone
    tm *tmp = gmtime(&result);
    return mktime(tmp);
}

time_t InputUtility::getCurrentTime() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}

time_t InputUtility::toDate(time_t time) const {
    if (time < 0)
        return time;
    tm t = *localtime(&time);
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    return mktime(&t);
}

time_t InputUtility::toDateTimeNoSeconds(time_t time) const {
    tm t = *localtime(&time);
    t.tm_sec = 0;
    return mktime(&t);
}

void InputUtility::noParameterFound(const std::string &param) const {
    if (param.empty())
        out << "No parameter found, type 'help' for all available commands" << std::endl;
    else
        out << "Parameter " + param + " was not found, type 'help' for all available commands" << std::endl;
}

void InputUtility::eventNotEditable() const {
    out << "Event is not editable" << std::endl;
}

void InputUtility::numberDoesNotMatch() const {
    out << "Given number does not match any option. Use number in (x) at the beginning of each line" << std::endl;
}

void InputUtility::success() const {
    out << "Operation was successful" << std::endl;
}

std::string InputUtility::tryGetVal(std::queue<std::string> &params) const {
    std::string currentVal;
    if (!params.empty()) {
        currentVal = params.front();
        params.pop();
    }
    return currentVal;
}


int InputUtility::readSelect(const std::string &attr, int lenght) const {
    while (true) {
        int res = readNumber(attr);
        if (res >= 0 && res < lenght)
            return res;
        numberDoesNotMatch();
    }
}