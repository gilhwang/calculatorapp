/* 
 * File: main.cpp
 * Description: main function to operate calculator application
 * Author: Gil Hwang
 * Date: JUL 20 2022
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "helper.h"

using namespace std;

// Global Variable
bool errorFlag = false;

int main() {
    // Local Variable Declaration  
    string userInput;
    char leftBracket = '(';
    char rightBracket = ')';
    
    introCalc();
    
    while (true){
        // Local Variable Declaration
        vector<int> posLeftBracket, posRightBracket;
        vector<pair<int,int>> bracketSets;
        double result;
        
        cout << "> ";
        receiveInput(userInput);
        
        if (userInput == END_CODE){
            break;
        }
        
        // Find Bracket positions
        findCharacter(userInput, leftBracket, posLeftBracket);
        findCharacter(userInput, rightBracket, posRightBracket);
        
        if (checkValidBracket(posLeftBracket,posRightBracket)){
            pairBrackets(bracketSets, posLeftBracket, posRightBracket);
        }

        result = calculate(userInput, bracketSets);
        printResult(result);  

        errorFlag = false;  // reset flag
    }
    
    cout << "Program Ended." << endl;
    
    return 0;
}

