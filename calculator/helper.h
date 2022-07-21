/* 
 * File:   helper.h
 * Description: Header file for helper function defintions
 * Author: Gil Hwang
 * Date: JUL 20 2022
 */

#ifndef HELPER_H
#define HELPER_H

// Global Variables
extern bool errorFlag;

// Defines
#define END_CODE "quit"
#define EMPTY 0
#define LEFT 1
#define RIGHT 2
#define NOT_FOUND -1
#define INVALID -1
#define LEFT_BRACKET "("
#define RIGHT_BRACKET ")"
#define ADD -1
#define SUBTRACT -222333.555
#define MULTIPLY -222333.556
#define DIVIDE -222333.557
#define POWER -222333.558
#define IGNORE -222333.568

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Show introduction to calculator app
void introCalc();

// Receive input from user
void receiveInput(string & input);

// Find all positions of character within string
void findCharacter(string strInput, char key, vector<int> & charPositions);

// Pair left&right brackets
void pairBrackets(vector<pair<int,int>> & bracketSets,
                  vector<int> & leftPositions, vector<int> & rightPositions);

// Find pairs within vector
int findPairs(vector<pair<int,int>> & pairSets, vector<int> & expression, int startPos);

// Perform calculation
double calculate(string userInput, const vector<pair<int,int>> & bracketSets);

// Perform calculation of sub-expression
double simpleCalculate(vector<double> calcObjects);

// Print result to user
void printResult(double result);

// Check if brackets are valid
bool checkValidBracket(const vector<int> & leftBrackets, const vector<int> & rightBrackets);

#endif /* HELPER_H */

