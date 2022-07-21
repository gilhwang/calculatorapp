/*
 * File: helper.cpp
 * Description: Implementation for helper functions
 * Author: Gil Hwang
 * Date: JUL 20 2022
 */


#include "helper.h"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <valarray>
using namespace std;

// Show introduction to calculator app
void introCalc(){
    cout << "Welcome to Calculator App" << endl;
    cout << "Enter expression or \"quit\" to exit:" << endl;
}

// Receive input from user
void receiveInput(string & input){
    // Local Variable Declaration
    bool empty = true;
    
    while (empty){
        getline(cin, input);
        
        if (input != ""){
            empty = false;
        }
    }
}

// Find all positions of character within string
void findCharacter(string strInput, char key, vector<int> & charPositions){
    
    // Reset the position vector
    charPositions.clear();
    
    for (int pos = 0; pos < strInput.size(); pos++){
        if (strInput.at(pos) == key){
            charPositions.push_back(pos);
        }
    }
      
}

// Pair all left&right brackets
void pairBrackets(vector<pair<int,int>> & bracketSets,
                  vector<int> & leftPositions, vector<int> & rightPositions){
    // Local Variable Declaration
    vector<int> totalBrackets(rightPositions.back()+1, EMPTY);
    int endPosition = 0;
    
    // Initialize combined expression for left&right brackets
    for (auto it = leftPositions.begin(); it != leftPositions.end(); it++){
        totalBrackets[(*it)] = LEFT;
    }
    
    for (auto it = rightPositions.begin(); it != rightPositions.end(); it++){
        totalBrackets[(*it)] = RIGHT;
    }
        
    // Find invalid inputs!!
    
    for (int pos = 0; pos < totalBrackets.size(); pos++){
        if (totalBrackets.at(pos) == LEFT){
            endPosition = findPairs(bracketSets, totalBrackets, pos);
            pos = endPosition;    // jump to find another largest left bracket
        }
    }
    
    cout << "Bracket Sets: ";
    for (auto it = bracketSets.begin(); it != bracketSets.end(); it++){
        cout << "(" << it->first << ", " << it->second << ")";
    }
    cout << endl;
    
    
}

// Find pairs within vector (returns end position)
int findPairs(vector<pair<int,int>> & pairSets, vector<int> & expression, int startPos){
    for (int pos = startPos; pos < expression.size(); pos++){
        // Base Case
        if (expression.at(pos) == RIGHT){
            pairSets.push_back(make_pair(startPos,pos));
            return pos;
        }
        
        // Found another left bracket
        if (expression.at(pos) == LEFT && pos != startPos){
            pos = findPairs(pairSets, expression, pos);   // iterate again to find a pair
        }
    }
    
    errorFlag = true;
    return NOT_FOUND;  
}

// Perform overall calculation
double calculate(string userInput, const vector<pair<int,int>> & bracketSets){
    // Local Variable Declaration
    double num = 0;
    vector<double> calcObjects;
    
    // Check if error is already caught
    if (errorFlag){
        return INVALID;
    }
    
    // Search through input to split calculable objects
    for (int pos = 0; pos < userInput.size(); pos++){
        // Encountered number
        if (userInput.at(pos) >= '0' && userInput.at(pos) <= '9'){
            int powerCount = 0;
            int decimalCount = 1;
            
            while(pos != userInput.size() && userInput.at(pos) >= '0' && userInput.at(pos) <= '9'){
                int currentInt = userInput.at(pos) - '0';
                num = 10*num + currentInt;
                pos++;
                powerCount++;  
            }
            
            if (pos != userInput.size() && userInput.at(pos) == '.'){
                pos++;
                while(pos != userInput.size() && userInput.at(pos) >= '0' && userInput.at(pos) <= '9'){
                    int currentInt = userInput.at(pos) - '0';
                    num = num + currentInt * pow(10,-1*decimalCount);
                    pos++;
                    decimalCount++;
                }
                pos--;
            }
            else{
                pos--;
            }
            
            calcObjects.push_back(num);
            num = 0;    // reset number
            
        }
        
        // Encountered Operation
        else if (userInput.at(pos) == '+' || userInput.at(pos) == '-' ||
            userInput.at(pos) == '*' || userInput.at(pos) == '/' ||
            userInput.at(pos) == '^'){
            switch(userInput.at(pos)){
                case '+':
                    calcObjects.push_back(ADD);
                    break;
                case '-':
                    calcObjects.push_back(SUBTRACT);
                    break;
                case '*':
                    calcObjects.push_back(MULTIPLY);
                    break;
                case '/':
                    calcObjects.push_back(DIVIDE);
                    break;
                case '^':
                    calcObjects.push_back(POWER);
                    break;
                default:
                    break;
            }
        }
        
        // Encountered Bracket
        else if (userInput.at(pos) == '('){
            int posClosed = 0;
            // Find the closing bracket
            for (int i = 0; i < bracketSets.size(); i++){
                if (bracketSets.at(i).first == pos){
                    posClosed = bracketSets.at(i).second;
                }
            }
            
            num = calculate(userInput.substr(pos+1,posClosed-1), bracketSets);
            calcObjects.push_back(num);
            pos = posClosed;
        }
        else if (userInput.at(pos) == ' ' || userInput.at(pos) == ')'){
            // Do nothing
        }
        else{
            errorFlag = true;
            break;
        }
    }
    
    if (errorFlag){
        return INVALID;
    }
    else{
        return simpleCalculate(calcObjects);
    } 
}

// Perform calculation of sub-expression
double simpleCalculate(vector<double> calcObjects){
    // Local Variable Declaration
    double result;
    
    // Perform power first
    for (auto it = calcObjects.begin(); it != calcObjects.end(); it++){
        if (*it == POWER){
            double subResult = pow(*(it-1),*(it+1));
            *it = subResult;
            calcObjects.erase(it+1);
            calcObjects.erase(it-1);
            it = calcObjects.begin();
        }
    }
    
    // Perform multiply&divide next
    for (auto it = calcObjects.begin(); it != calcObjects.end(); it++){
        if (*it == MULTIPLY){
            double subResult = (*(it-1)) * (*(it+1));
            *it = subResult;
            calcObjects.erase(it+1);
            calcObjects.erase(it-1);
            it = calcObjects.begin();
        }
        if (*it == DIVIDE){
            double subResult = (*(it-1)) / (*(it+1));
            *it = subResult;
            calcObjects.erase(it+1);
            calcObjects.erase(it-1);
            it = calcObjects.begin(); 
        }
    }
    
    // Perform add/multiply in arithmetic sequence
    for (auto it = calcObjects.begin(); it != calcObjects.end(); it++){
        if (*it == ADD){
            double subResult = (*(it-1)) + (*(it+1));
            *it = subResult;
            calcObjects.erase(it+1);
            calcObjects.erase(it-1);
            it = calcObjects.begin();
        }
        if (*it == SUBTRACT){
            double subResult = (*(it-1)) - (*(it+1));
            *it = subResult;
            calcObjects.erase(it+1);
            calcObjects.erase(it-1);
            it = calcObjects.begin(); 
        }
    }
    
    
    result = calcObjects.front();
    return result;
}

// Print Result to User
void printResult(double result){
    if (errorFlag){
        cout << "Invalid Input! Please try again." << endl;
    }
    else{
        cout << "The result is: " << result << endl;
    }
}

// Check if brackets are valid
bool checkValidBracket(const vector<int> & leftBrackets, const vector<int> & rightBrackets){
    if (leftBrackets.size() != rightBrackets.size()){
        errorFlag = true;
        return false;
    }
    if (leftBrackets.size() == 0){
        return false;
    }
    
    return true;
}

