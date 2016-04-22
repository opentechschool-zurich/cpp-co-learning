//
//  main.cpp
//  randomGame
//
//  Created by Xia Zheng on 19/4/16.
//  Copyright © 2016 Xia Zheng. All rights reserved.
//

#include "randomGame.hpp"

int main() {
    
    puts ("Game time!\nGuess a number between 1 and 100.");
    
    srand ((unsigned)time(NULL));   // generate a unique seed by using the time(NULL)
    
    int urAnswer, urTry;
    urTry = 1;
    
    /* generate random number between 1 and 100 */
    int myRand = rand() % 100 + 1;
    
    do {
        cout << urTry << ". guess: ";
        cin >> urAnswer;  // store the answer in urAnswer
        if ( cin.fail() ) {
            urTry++;
            puts ("U need to type a number");
            cin.clear();
            cin.ignore(1000,'\n');
        }
        else if ( urAnswer > myRand ) {
            puts ("It's too big!");
            urTry++;
        }
        else if ( urAnswer < myRand ) {
            puts ("It's too small!");
            urTry++;
        }
        else { puts ("Hurray, congradulations!"); };
    } while( myRand != urAnswer );
    
    cout << "Play again!\n";
    return 0;
}
