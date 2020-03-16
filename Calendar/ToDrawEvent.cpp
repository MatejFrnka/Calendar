//
// Created by Matej Frnka on 14.03.2020.
//

#include "ToDrawEvent.h"

ToDrawEvent::ToDrawEvent(Event *event) :Event(event->title, event->startDateUtc, event->endDateUtc){
    originalEvent = event;
}
