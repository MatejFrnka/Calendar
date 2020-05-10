/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include "InputUtility.h"

std::vector<std::string> InputUtility::getParams(const std::string &input) {
    std::vector<std::string> result;
    std::istringstream iss(input);
    for (std::string s; iss >> s;)
        result.push_back(s);
    return result;
}

InputUtility::InputUtility(std::istream &in_, std::ostream &out_) : in(in_), out(out_){

}
