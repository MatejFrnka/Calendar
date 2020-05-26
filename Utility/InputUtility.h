/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_UTILITY_INPUT_UTILITY
#define CALENDAR_UTILITY_INPUT_UTILITY

#include <vector>
#include <string>
#include <sstream>
#include <map>

class InputUtility {
public:
    InputUtility(std::istream &in, std::ostream &out);

    InputUtility(const InputUtility &) = delete;

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
    std::string readString(const std::string &attr, const std::string &currentVal = "", bool required = true);

    /**
     * Reads date and time from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readDateTime(const std::string &attr, const std::string &currentVal = "", bool required = true);

    /**
     * Reads date from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readDate(const std::string &attr, const std::string &currentVal = "", bool required = true);

    /**
     * Reads timespan from user's input.
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readTimeSpan(const std::string &attr, const std::string &currentVal = "", bool required = true);

    /**
     * Reads integer from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type int
     */
    int readNumber(const std::string &attr, const std::string &currentVal);

    /**
     * Reads integer from user's input
     * @param attr Name of attribute that is being set
     * @return Input of type int
     */
    int readNumber(const std::string &attr);

    std::ostream &out;

    void noParameterFound(const std::string &param = "");

private:

    std::istream &in;

    std::stringstream getLine(bool useDefault, const std::string &defaultVal) const;

    std::map<std::string, int> timeDictionary = {
            {"minute", 60},
            {"hour",   3600},
            {"day",    86400},
            {"week",   604800},
            {"month",  2678400},
            {"year",   31556926}
    };

    time_t customReadDate(const std::string &attr, const std::string &currentVal, bool required, const std::string &format, const std::string &exampleFormat);
};


#endif
