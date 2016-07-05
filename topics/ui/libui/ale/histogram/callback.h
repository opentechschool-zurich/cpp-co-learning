#ifndef CALLBACK_H
#define CALLBACK_H

/**
 * @brief templates for mapping a c++ class method to a function pointer
 *
 * taken from
 * http://stackoverflow.com/questions/1000663/using-a-c-class-member-function-as-a-c-callback-function
 */
template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args> 
    static Ret callback(Args... args) {                    
        return func(args...);  
    }
    static std::function<Ret(Params...)> func; 
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

// end of the mapping templates
// ----------------------------

#endif
