//  Guess A Random Number Game

#include "randomNumberGame.hpp"  // header file including general libraries
#include "intValidation.hpp"  // sort of our own library

int main() {
    
    cout << "Game time!\nGuess a number between 1 and 100.\n";
    
    string startGame = "Y";  // default to chose start the game
    
    srand ((unsigned)time(NULL));   // generate a unique seed by using the time(NULL)
    
    int urTry = 1;
    int urAnswer;
    
    do {

        int myRand = rand() % 100 + 1;  // generate random number between 1 and 100
        
        do {
            cout << urTry << ". guess: ";  // ask for a guessed number
            urAnswer = getInt(); // check first, if input is valid
            if ( urAnswer > myRand ) {
                cout << "This number is too big! Try a smaller number.\n";
                urTry++;
            }
            else if ( urAnswer < myRand ) {
                cout << "This number is too small! Try a bigger number.\n";
                urTry++;
            }
            else { 
                cout << "Hurray, congratulations!\n";
                break;
            }  
        } while( myRand != urAnswer );
        
        cout << "Wanna play again? (Y/N): ";
        cin >> startGame;
        if (startGame == "N" || startGame != "Y") break;
        cout << "Guess a number between 1 and 100.\n";
        urTry = 1;

    } while( startGame == "Y" );

    return 0;
}