#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <string>
#include <ctime>
#include <cstdlib>
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long letters[5] = {0,0,0,0,0};
        unsigned long long powers[6];
        std::string og = k;

        powers[0]=1;
        for(int i = 1; i<6; i++){
          powers[i] = powers[i-1] *36;
        }
        
        if (k.size()%6 !=0){
          for (size_t i=0; i<(6-k.size()%6);i++){
            og = 'a'+ og;
          }
        }
        //std::cout << "string = " << og << std::endl;

        
        unsigned long long size= og.size();
        int w =4;
        for (size_t i= 0 ; i<og.size()/6; i++){
          letters[w] = powers[5] * letterDigitToNumber(og[size-6]) + powers[4] * letterDigitToNumber(og[size-5]) + powers[3] * letterDigitToNumber(og[size-4]) + powers[2] * letterDigitToNumber(og[size-3]) + powers[1] * letterDigitToNumber(og[size-2]) + powers[0]* letterDigitToNumber(og[size-1]);
          //std::cout << powers[5] << "<-power5" << letterDigitToNumber(og[size-6]) << std::endl;
          //std::cout << powers[5] * letterDigitToNumber(og[size-6]) << "+" << powers[4] * letterDigitToNumber(og[size-5]) << "+" << powers[3] * letterDigitToNumber(og[size-4]) <<"+"<< powers[2] * letterDigitToNumber(og[size-3]) <<"+"<< powers[1] * letterDigitToNumber(og[size-2])<< "+" << powers[0]* letterDigitToNumber(og[size-1])<< std::endl;
          //std::cout << letterDigitToNumber(og[size-1]) << std::endl;
          //std::cout << og[size-1] << std::endl;
          //std::cout << "letterDigitToNumber: "<<letterDigitToNumber('B')<<std::endl;
          size = size-6;
          w--;
        }
        //std::cout << "w0 :" << letters[0] << std::endl;
        //std::cout << "w1 :" << letters[1] << std::endl;
        //std::cout << "w2 :" << letters[2] << std::endl;
        //std::cout << "w3 :" << letters[3] << std::endl;
        //std::cout << "w4 :" << letters[4] << std::endl;
        unsigned long long val = rValues[0] * letters[0] + rValues[1] * letters[1] + rValues[2] * letters[2] + rValues[3] * letters[3] + rValues[4] * letters[4];
        return val;
      

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      unsigned long long num;
      if (isalpha(letter)){
        num = static_cast<int>(letter);
        if(num<97){num+=32;}
        return num-97;
      }
      else {
        num= static_cast<int>(letter);
        return num-22;
      }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
