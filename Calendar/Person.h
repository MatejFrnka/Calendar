/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 27.05.2020
 */

#ifndef CALENDAR_PERSON_H
#define CALENDAR_PERSON_H

#include <utility>

#include "string"

struct Person {
public:
    Person(std::string name_, std::string surname_) : name(std::move(name_)), surname(std::move(surname_)) {};
    std::string name;
    std::string surname;
    std::string phone;
    std::string email;

    friend std::ostream &operator<<(std::ostream &ostream, const Person &person) {
        ostream << person.name << " " << person.surname;
        if (!person.phone.empty())
            ostream << ", " << person.phone;
        if (!person.email.empty())
            ostream << ", " << person.email;
        return ostream;
    }
};


#endif //CALENDAR_PERSON_H
