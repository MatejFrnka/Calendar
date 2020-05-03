/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.05.2020
 */

#pragma once

#include <memory>

/**
 * Ins
 */
class InheritableEnableSharedFromThis : public std::enable_shared_from_this<InheritableEnableSharedFromThis> {
public:
    virtual ~InheritableEnableSharedFromThis() {}
};

template<class T>
class inheritable_enable_shared_from_this : virtual public InheritableEnableSharedFromThis {
public:
    std::shared_ptr<T> shared_from_this() {
        return std::dynamic_pointer_cast<T>(InheritableEnableSharedFromThis::shared_from_this());
    }

    template<class Down>
    std::shared_ptr<Down> downcasted_shared_from_this() {
        return std::dynamic_pointer_cast<Down>(InheritableEnableSharedFromThis::shared_from_this());
    }
};
