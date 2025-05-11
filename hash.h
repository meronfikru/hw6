#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cctype>
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
      HASH_INDEX_T hashVal = 0;
      int len = k.length();
      int index = len-1;
      int valIndex=4;
      unsigned long long num = 0;
      unsigned long long vals[5]= {0};
      while (len>0){
        num = 0;
        std::string piece ="";
        for (int i =0; i<6 && len >0;++i){
          piece =k[index]+ piece;
          index--;
          len--;
        }
        for(size_t i =0; i<piece.length(); ++i){
          num = num *36 + letterDigitToNumber(piece[i]);
        }
        /*
        for (int i=0; i<6; ++i){
          if (len<=0){break;}
          num = num * 36+ letterDigitToNumber(k[index]);
          std::cout<< k[index]<<std::endl;
          
          
          //if (len<0){
            //num = num * 36;
          //}
          //else{
            //num = num * 36+ letterDigitToNumber(k[index]);
          //}
          
          //index++;
          //len--;
          
        }*/
        //std::cout<< "end of chunk" <<std::endl;
        vals[valIndex] = num;
        valIndex--;

      }
      
      for (int i=0; i<5; ++i){
        hashVal += rValues[i] * vals[i];
        //std::cout << "w[" << i << "]" << vals[i]<<std::endl;
      }
      
      return hashVal;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      if (std::isalpha(letter)){
        if(letter<97){
          return static_cast<HASH_INDEX_T>(letter)-65;
        }
        else{return static_cast<HASH_INDEX_T>(letter)-97;}
      }
      else{return static_cast<HASH_INDEX_T>(letter)-22;}

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
