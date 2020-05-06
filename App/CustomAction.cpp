/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#include "CustomAction.h"

template<typename function>
Action::outcome CustomAction<function>::executeAction() {
    return Failed;
}

template<typename function>
CustomAction<function>::CustomAction(function fn_) : fn(fn_){

}
