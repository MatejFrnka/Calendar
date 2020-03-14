//
// Created by Matej Frnka on 13.03.2020.
//

#include "SingleEvent.h"

SingleEvent::SingleEvent(string title_, time_t startDateUtc_, time_t endDateUtc_) : Event(std::move(title_),
                                                                                          startDateUtc_,
                                                                                          endDateUtc_) {

}

void SingleEvent::test() {
    cout << "test";
}
