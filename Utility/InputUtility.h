/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_UTILITY_INPUT_UTILITY
#define CALENDAR_UTILITY_INPUT_UTILITY

#include <vector>
#include <string>
#include <sstream>

class InputUtility {
public:
    InputUtility(std::istream &in, std::ostream &out);
    /**
     * Splits input by spaces
     * @param input Command to get parameters from
     * @return Parameters extracted from input
     */
    static std::vector<std::string> getParams(const std::string &input);
    /**
     * Reads string from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input in type of string
     */
    std::string readString(std::string attr, std::string currentVal = "");
    /**
     * Reads date and time from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readDate(std::string attr, std::string currentVal = "");
    /**
     * Reads timespan from user's input.
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readTimeSpan(std::string attr, std::string currentVal = "");

private:
    std::istream &in;
    std::ostream &out;
};


#endif
