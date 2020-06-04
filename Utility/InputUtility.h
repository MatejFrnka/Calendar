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
     * @return Input in type of string
     */
    std::string readString(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    std::string readString(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads date and time from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readDateTime(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    time_t readDateTime(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads date from user's input
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readDate(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    time_t readDate(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads timespan from user's input.
     * @param attr Name of attribute that is being set
     * @param currentVal Value to use instead of waiting for user's input
     * @return Input of type time_t
     */
    time_t readTimeSpan(const std::string &attr, const std::string &currentVal = "", bool required = true) const;

    time_t readTimeSpan(const std::string &attr, std::queue<std::string> &params, bool required = true) const;

    /**
     * Reads integer from user's input
     * @param attr Name of attribute that is being set
     * @return Input of type int
     */
    int readNumber(const std::string &attr) const;

    int readSelect(const std::string &attr, int lenght) const;

    bool readBool(const std::string &attr);

    Event::actionType readActionType(const vector<Event::actionType> &actions) {
        if (actions.empty())
            throw invalid_argument("Actions must not be empty");
        int input = 0;
        if (actions.size() > 1) {
            out << "How many events should be deleted" << endl;
            for (size_t i = 0; i < actions.size(); ++i) {
                if (actions[i] == Event::AllEvents)
                    out << '(' << i << ") " << "All events" << endl;
                if (actions[i] == Event::ThisAndNext)
                    out << '(' << i << ") " << "This and upcoming events" << endl;
                if (actions[i] == Event::OnlyThis)
                    out << '(' << i << ") " << "Only this event" << endl;
            }
            return actions[readSelect("Select mode", actions.size())];
        } else
            return actions[0];
    }

    static time_t getCurrentTime();

    std::ostream &out;

    void noParameterFound(const std::string &param = "") const;

    void eventNotEditable() const;

    void numberDoesNotMatch() const;

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
