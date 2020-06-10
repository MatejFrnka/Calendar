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
#include <queue>
#include <memory>
#include "../Calendar/Person.h"
#include "../Calendar/Event.h"

class InputUtility {
public:
    InputUtility(std::istream &in, std::ostream &out);

    InputUtility(const InputUtility &) = delete;

    InputUtility &operator=(const InputUtility &) = delete;

    /**
     * Splits input by spaces
     * @param input Command to get parameters from
     * @return Parameters extracted from input
     */
    static std::queue<std::string> getParams(const std::string &input);

    /**
     * Reads string from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input in type of string
     */
    std::string readString(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    /**
     * Reads string from user's input
     * @param attr Name of attribute that is being set
     * @param params parameters previously specified
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @param required
     * @return
     */
    std::string readString(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads date and time from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @param required if true, user must provide valid input, if false, function will return -1
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input of type time_t
     */
    time_t readDateTime(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    /**
     * Reads date and time from user's input
     * @param attr Name of attribute that is being set
     * @param params Queue of params already specified by user
     * @param required if true, user must provide valid input, if false, function will return -1
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input of type time_t
     */
    time_t readDateTime(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads date from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @param required if true, user must provide valid input, if false, function will return -1
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input of type time_t
     */
    time_t readDate(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    /**
     * Reads date and time from user's input
     * @param attr Name of attribute that is being set
     * @param params Queue of params already specified by user
     * @param required if true, user must provide valid input, if false, function will return -1
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input of type time_t
     */
    time_t readDate(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads timespan from user's input.
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @param required if true, user must provide valid input, if false, function will return -1
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input of type time_t
     */
    time_t readTimeSpan(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    /**
     * Reads timespan and time from user's input
     * @param attr Name of attribute that is being set
     * @param params Queue of params already specified by user
     * @param required if true, user must provide valid input, if false, function will return -1
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input of type time_t
     */
    time_t readTimeSpan(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads integer from user's input
     * @param attr Name of attribute that is being set
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Input of type int
     */
    int readNumber(const std::string &attr) const;

    /**
     * Reads a number between 0 and attribute lenght from user
     * @param attr Name of attribute that is being set
     * @param Lenght Lenght of array user is choosing from
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return Number between <0, length)
     */
    int readSelect(const std::string &attr, int lenght) const;

    /**
     * Reads boolean from user
     * @param attr Name of attribute that is being set
     * @throws UnexpectedEndOfInputException when end of file input happens during setting an argument
     * @return returns true or false
     */
    bool readBool(const std::string &attr);

    /**
     * Reads Event::actionType enum from user
     * @param actions
     * @throws invalid_argument when no actions were provided
     * @return actionType selected by user
     */
    Event::actionType readActionType(const vector<Event::actionType> &actions);

    /**
     * @return System datetime timestamp
     */
    static time_t getCurrentTime();

    std::ostream &out;

    /**
     * Prints error message that no parameter was found
     * @param param parameter that was not found
     */
    void noParameterFound(const std::string &param = "") const;

    /**
     * Prints error message that event is not editable
     */
    void eventNotEditable() const;

    /**
     * Prints error message that selected number is not in valid range
     */
    void numberDoesNotMatch() const;

    /**
     * Prints success message
     */
    void success() const;

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

    time_t customReadDate(const std::string &attr, const std::string &currentVal, bool required, const std::string &format, const std::string &exampleFormat) const;

    time_t toDate(time_t time) const;

    time_t toDateTimeNoSeconds(time_t time) const;

    std::string tryGetVal(std::queue<std::string> &params) const;
};


#endif
