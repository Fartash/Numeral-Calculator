/* 
 * File:   main.cpp
 * Author: Fartash M. Nejad
 * Developed as accompanying a job application
 * to Gateprotect Company
 * Created on June 10, 2011, 9:38 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <map>

using namespace std;


/*************************************************
 *class numeralToDigitConverter encapsulates the *
 *functionality needed to convert numerals into  *
 *digits. It has an attribute named convertTable *
 *which is filled in by the constructor and does *
 *the role of a dictionary in conversions.       *
 *************************************************/


class numeralToDigitConverter{
public:
    numeralToDigitConverter();
    ~numeralToDigitConverter();
    int convert(string&);
    bool checkInput(string&);
private:
    map<string, int> convertTable;
    int subConvert(string[], int);
    
};
numeralToDigitConverter::numeralToDigitConverter(){
    convertTable["zero"] = 0;
    convertTable["one"] = 1;
    convertTable["two"] = 2;
    convertTable["three"] = 3;
    convertTable["four"] = 4;
    convertTable["five"] = 5;
    convertTable["six"] = 6;
    convertTable["seven"] = 7;
    convertTable["eight"] = 8;
    convertTable["nine"] = 9;
    convertTable["ten"] = 10;
    convertTable["eleven"] = 11;
    convertTable["twelve"] = 12;
    convertTable["thirteen"] = 13;
    convertTable["fourteen"] = 14;
    convertTable["fifteen"] = 15;
    convertTable["sixteen"] = 16;
    convertTable["seventeen"] = 17;
    convertTable["eighteen"] = 18;
    convertTable["nineteen"] = 19;
    convertTable["twenty"] = 20;
    convertTable["thirty"] = 30;
    convertTable["forty"] = 40;
    convertTable["fifty"] = 50;
    convertTable["sixty"] = 60;
    convertTable["seventy"] = 70;
    convertTable["eighty"] = 80;
    convertTable["ninety"] = 90;
    convertTable["hundred"] = 100;
    convertTable["thousand"] = 1000;
    convertTable["million"] = 1000000;
    
    /********************************
     *This part of the map is only  *
     *for accuracy control of the   *
     *input.                        *
     ********************************/
    
    convertTable["add"];
    convertTable["subtract"];
    convertTable["multiply"];
    convertTable["divide"];
    convertTable["and"];
    convertTable["*"];
    convertTable["-"];
    convertTable["+"];
    convertTable["/"];
    
}
numeralToDigitConverter::~numeralToDigitConverter(){
    
}

/********************************************************
 *This function evaluates the input string to determine *
 *if the input consists of correct words.               *
 ********************************************************/

bool numeralToDigitConverter::checkInput(string& input){
    int i,j;
    bool mistypeExists[15];
    bool inputAccurate = true;
    string tokens[15];
    map<string, int>::iterator it;
    
    for(i=0,j=0;i<input.length();++i)
        if(input[i]!= ' ')
            tokens[j].append(1,input[i]);
        else
            ++j;
    
    
    
    for(i=0; i<15; ++i)
        mistypeExists[i] = false;

    
    for(i=0; i<=j; ++i){
        for(it = convertTable.begin(); it != convertTable.end(); ++it) {
             if(tokens[i] == it->first)
                  mistypeExists[i] = true;
             }
    }
    
    
    for(i=0;i<=j;++i)
        if(mistypeExists[i] == false)
            inputAccurate = false;
    
    
    return inputAccurate;
}

/********************************************************
 *This function takes a numeral as argument and converts*
 *it into the digital form                              *
 ********************************************************/

int numeralToDigitConverter::convert(string& numeral){
    bool isMinus = false;
    int number = 0;
    int subToken1ElementsNo = 0;
    int subToken2ElementsNo = 0;
    int subToken3ElementsNo = 0;
    int i,j,r,w,x = 0;
    string tokens[15], subToken1[10], subToken2[10], subToken3[10];
    
    if(numeral.find("minus") != string::npos)
        isMinus = true;
        
    /*******************************************************
     *Tokenizing the input string so that it can be parsed *
     *using primitive tools                                *
     *******************************************************/
    
    for(i=0,j=0;i<numeral.length();++i)
        if(numeral[i]!= ' ')
            tokens[j].append(1,numeral[i]);
        else
            ++j;
    
    //elimination of minus keyword
    
    if(isMinus){
        for(i=0;i<j;++i)
                tokens[i] = tokens[i+1];
        --j;
    }
        
    
    //elimination of "and"s from the input
    
    for(i=0;i<=j;++i)
        if(tokens[i] == "and"){
            for(r=i;r<=j;++r)
                tokens[r] = tokens[r+1];
            ++x;
        }
    j -= x;

    
    for(i=j;i>=0;--i){
        if(tokens[i] == "thousand"){
            for(r=0;i>=0;--i,++r){
                if(tokens[i] == "million"){
                    ++i;
                    break;
                }
                subToken2[r] = tokens[i];
                ++subToken2ElementsNo;
            }
            for(w=0;w<subToken2ElementsNo;++w)
                subToken2[w] = subToken2[w+1];
        }
        else if(tokens[i] == "million"){
            for(r=0;i>=0;--i,++r){
                subToken3[r] = tokens[i];
                ++subToken3ElementsNo;
            }
            for(w=0;w<subToken3ElementsNo;++w)
                subToken3[w] = subToken3[w+1];
        }
        else{
            for(r=0;i>=0;--i,++r){
                if(tokens[i] == "million" ||
                        tokens[i] == "thousand"){
                    ++i;
                    break;
                }
                subToken1[r] = tokens[i];
                ++subToken1ElementsNo;
            }
        }
    }
    
    
    
    number += subConvert(subToken1, subToken1ElementsNo);
    number += (subConvert(subToken2, subToken2ElementsNo) * 1000);
    number += (subConvert(subToken3, subToken3ElementsNo) * 1000000);
    
    if(isMinus)
        return -number;
    else
        return number;
}

/********************************************************
 *This function converts numerals smaller than 1000 into*
 *digits. It takes an array of strings, and the size of *
 *of the array as argument and returns the digital      *
 * equivalent of the numeral.                           *                 
 ********************************************************/

int numeralToDigitConverter::subConvert(string tokens[], int size){
    
    int i;
    int result = 0;
   
    
    for(i=0;i<size;++i){
        if(tokens[i] == "hundred")
            result += convertTable[tokens[i]] * convertTable[tokens[++i]];
        else
            result += convertTable[tokens[i]];
    }
    return result;
}

int main(int argc, char** argv) {
    char p;
    string input;
    string firstNumeral, secondNumeral;
    int firstNumber, secondNumber;
    int output;
    int opType;
    size_t firstNumeralEnd;
    numeralToDigitConverter conv;
    
    
    /*Asking the user for input*/
    
    
    for(;;){
        
        cout<<"Please enter expression:"<<endl;
 
        getline (cin,input);
    
        if(!conv.checkInput(input)){
            cout<<"There are mistypes in your input string! Please try again"<<endl;
            continue;
        }
        
            
  
    
    /************************************************
     *The following If-Else structure determines    *
     *the type of operation (i.e. add, multiply etc)*
     *and then divides the input into two elements  *
     ************************************************/
    
        if (input.find("multiply") != string::npos){
             opType = 0;
             firstNumeralEnd = input.find("multiply");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
             secondNumeral = input.substr(firstNumeralEnd+9);
        
        }
        else if (input.find("*") != string::npos){
             opType = 0;
             firstNumeralEnd = input.find("*");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
             secondNumeral = input.substr(firstNumeralEnd+2);
        
        }
        else if (input.find("/") != string::npos){
             opType = 1;
             firstNumeralEnd = input.find("/");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
             secondNumeral = input.substr(firstNumeralEnd+2);
        
        }
        else if (input.find("divide") != string::npos){
             opType = 1;
             firstNumeralEnd = input.find("divide");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
             secondNumeral = input.substr(firstNumeralEnd+7);
        
        }
        else if (input.find("subtract") != string::npos){
             opType = 2;
             firstNumeralEnd = input.find("subtract");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
             secondNumeral = input.substr(firstNumeralEnd+9);
        
        }
        else if (input.find("-") != string::npos){
             opType = 2;
             firstNumeralEnd = input.find("-");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
             secondNumeral = input.substr(firstNumeralEnd+2);
        
        }
        else if (input.find("add") != string::npos){
             opType = 3;
             firstNumeralEnd = input.find("add");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
             secondNumeral = input.substr(firstNumeralEnd+4);
        }
        else if (input.find("+") != string::npos){
             opType = 3;
             firstNumeralEnd = input.find("+");
             firstNumeral = input.substr(0,firstNumeralEnd-1);
            secondNumeral = input.substr(firstNumeralEnd+2);
        }
    
    /*Converting numerals into digits*/
    
        firstNumber = conv.convert(firstNumeral);
        secondNumber = conv.convert(secondNumeral);
    
    /***************************************************
     *Depending on the type of operation, appropriate***
     *operation is performed and the result is printed*
     ***************************************************/
    
        switch (opType){
                case 0:
                        output = firstNumber * secondNumber;
                        cout<<output<<endl;
                        break;
                case 1:
                        if(secondNumber == 0){
                                cout<<"Division by zero is invalid!"<<endl;
                                continue;
                        }
                        output = firstNumber / secondNumber;
                        cout<<output<<endl;
                        break;
                case 2:
                        output = firstNumber - secondNumber;
                        cout<<output<<endl;
                        break;
                case 3:
                        output = firstNumber + secondNumber;
                        cout<<output<<"\n"<<endl;
                        break;
        }
    
        cout << "Do you want to continue? (y/n)"<<endl;
        cin>>p;
        if(p=='y' || p=='Y'){
                cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                continue;
        }
        else
                break;
        }
        return 0;
}

