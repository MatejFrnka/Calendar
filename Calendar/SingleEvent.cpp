/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "SingleEvent.h"

SingleEvent::SingleEvent(string title_, time_t startDateUtc_, time_t duration_) : Event(std::move(title_),
                                                                                        startDateUtc_,
                                                                                        duration_) {

}