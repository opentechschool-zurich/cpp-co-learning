#pragma once

#include <functional>

namespace non_gsl {

/**
 * C.30: Define a destructor if a class needs an explicit action at object destruction
 * https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c30-define-a-destructor-if-a-class-needs-an-explicit-action-at-object-destruction
 */
class FinallyAction
{
    public:
        FinallyAction(auto fn) : fn{fn} {}
        ~FinallyAction()
        {
            fn();
        }
    private:
        std::function<void()> fn;
};

FinallyAction finally(auto fn) {
    return FinallyAction{fn};
}

}
