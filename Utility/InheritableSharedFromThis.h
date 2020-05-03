/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.05.2020
 */

#ifndef CALENDAR_UTILITY_INHERITABLE_ENABLE_SHARED_FROM_THIS
#define CALENDAR_UTILITY_INHERITABLE_ENABLE_SHARED_FROM_THIS

#include <memory>

class InheritableEnableSharedFromThis : public std::enable_shared_from_this<InheritableEnableSharedFromThis> {
public:
    virtual ~InheritableEnableSharedFromThis() = default;
};

template<class T>
class inheritable_enable_shared_from_this : virtual public InheritableEnableSharedFromThis {
public:
    std::shared_ptr<T> shared_from_this();

    template<class Down>
    std::shared_ptr<Down> downcasted_shared_from_this();
};
template<class T>
std::shared_ptr<T> inheritable_enable_shared_from_this<T>::shared_from_this() {
    return std::dynamic_pointer_cast<T>(InheritableEnableSharedFromThis::shared_from_this());
}

template<class T>
template<class Down>
std::shared_ptr<Down> inheritable_enable_shared_from_this<T>::downcasted_shared_from_this() {
    return std::dynamic_pointer_cast<Down>(InheritableEnableSharedFromThis::shared_from_this());
}


#endif