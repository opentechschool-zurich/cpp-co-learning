#include <iostream>
#include <string>
 
template <typename OutputPolicy, typename LanguagePolicy>
class HelloWorld : private OutputPolicy, private LanguagePolicy
{
    using OutputPolicy::print;
    using LanguagePolicy::message;
 
public:
    // Behaviour method
    void run() const
    {
        // Two policy methods
        print(message());
    }
};
 
class OutputPolicyWriteToCout
{
protected:
    template<typename MessageType>
    void print(MessageType const &message) const
    {
        std::cout << message << std::endl;
    }
};
 
class LanguagePolicyEnglish
{
protected:
    std::string message() const
    {
        return "Hello, World!";
    }
};
 
class LanguagePolicyGerman
{
protected:
    std::string message() const
    {
        return "Hallo Welt!";
    }
};
 
int main()
{
    /* Example 1 */
    typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyEnglish> HelloWorldEnglish;
 
    HelloWorldEnglish hello_world;
    hello_world.run(); // prints "Hello, World!"
 
    /* Example 2 
     * Does the same, but uses another language policy */
    typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyGerman> HelloWorldGerman;
 
    HelloWorldGerman hello_world2;
    hello_world2.run(); // prints "Hallo Welt!"
}
