#include <list>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

class  Bob{
    public:
    string hey(string);
    
    private:
    bool isQuestion(string s);
    bool isExcalmation(string s);
    
};

string Bob::hey(string sentence){
    
    if (isExclamation(sentence)){
        return "Whoa, chill out";
    }
    if (isQuestion(sentence)){
        return "Sure";
    }
    return "Whatever ";
}

// remove_if(str.begin(), str.end(), isspace);

bool Bob::isQuestion(string s){
    // extract the last char     
     s.erase(remove_if(s.begin(), s.end(), [](char c)->bool {return c == ' ';}), s.end());
    // cout << "ab"<< s << "cde"<< endl;
    if(( s.back() ) == '?'){    
        return true;
    }
    return false;
}

bool Bob::isExclamation(string s){
    // extract the last char     
     s.erase(remove_if(s.begin(), s.end(), [](char c)->bool {return c == ' ';}), s.end());
    // cout << "ab"<< s << "cde"<< endl;
    if(( s.back() ) == '!'){    
        return true;
    }
    return false;
}

int main(){
    Bob silvie;
    
    
    if("Whatever " != silvie.hey("Tomaeyo tomeyo")){
        
        cout << "fail1" << endl;
    }
    if("Whoa, chill out" != silvie.hey("WATCH OUT !")){
        
        cout << "fail2" << endl;
    }
    if("Sure" != silvie.hey("new here?")){
        
        cout << "fail3" << endl;
    }
     if("Sure" != silvie.hey("new here? ")){
        
        cout << "fail4" << endl;
    }
    if("Whoa, chill out" != silvie.hey("Go HOme ! ")){
        
        cout << "fail1" << endl;
    }
    if("Whatever " != silvie.hey("Tomaeyo tomeyo")){
        
        cout << "fail" << endl;
    }
     
    
    
    return 0;
}


// cout << "Sure" << endl;

// cout << "Whoa, chill out" << endl;