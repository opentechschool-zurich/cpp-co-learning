//main.cpp
#include<algorithm>
#include<vector>
#include<iostream>
#include<string>

using namespace std;

  void BOOST_REQUIRE_EQUAL(string label, string goal, string output) {
    if (goal != output)
      {
        cout << "output: " << output << endl;
        throw(label);
      }
  }


namespace bob{


  string hey(string s){


    if (all_of(begin(s), end(s), [](char c) {return !isalpha(c) || isupper(c);}) && any_of(begin(s), end(s), [](char c) {return isupper(c);})) {
      return "Whoa, chill out!";
    }

    if (s.back() == '?'){
      return "Sure."; 
    }
    
    return "Whatever."; 

  }
}

// void assert_equal(string testName, string goal, string output) 

int main(){

  // test 1: 
  if ("Whatever." != bob::hey("Tom-ay-to, tom-aaaah-to.")){
    cout << "FAIL: Tomato 1" << endl;
    return 1; 
  }

  // test 2: 
  if ("Whoa, chill out!" != bob::hey("WATCH OUT!")){
    cout << "FAIL: chill out!" << endl;
    return 1; 
  }

  // test 3:
  if ("Sure." != bob::hey("Does this cryogenic chamber make me look fat?")){
    cout << "FAIL: look fat?" << endl;
    return 1; 
  }
  // test 4:  
  //     BOOST_REQUIRE_EQUAL("Whatever.", bob::hey("Let's go make out behind the gym!"));
  
  if ("Whatever." != bob::hey("Let's go make out behind the gym!"))
    {
      cout << "FAIL: gym!" << endl;
      return 1; 
    
    }

  // test 5:
  if ("Whatever." != bob::hey("It's OK if you don't want to go to the DMV.")){
    cout << "FAIL: DMV" << endl;
    return 1; 
  }

  // test 6:
  if ("Whoa, chill out!" != bob::hey("WHAT THE HELL WERE YOU THINKING?")){
    cout << "FAIL: WHAT THE HELL?" << endl;
    return 1; 
  }    

  // test 7:
  if ("Whoa, chill out!" != bob::hey("1, 2, 3 GO!")){
    cout << "FAIL: GO" << endl;
    return 1; 
  }


  BOOST_REQUIRE_EQUAL("only_numbers", "Whatever.", bob::hey("1, 2, 3"));

  return 0;
}
