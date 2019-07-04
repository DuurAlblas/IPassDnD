// ==========================================================================
//
// File      : supp.hpp
// Part of   : RFID library
// Copyright : Duur Alblas (c) 2019
// Contact   : d.c.alblas@gmail.com
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
#ifndef SUPP_HPP
#define SUPP_HPP

#include <hwlib.hpp>


namespace mifare{
  ///\brief
  ///A card class for mifare cards
  ///\details
  ///This class stores data associated with a mifare card.\n
  ///For now this class supports only the MF1S503yX type of the mifare cards.
  class card{
    public:
    ///\brief
    ///A array for the UID (NUID)
    ///\details
    ///We store the UID (NUID in the case of MF1S503yX) with a maximum size of 4 bytes.
    std::array<uint8_t,4> uid;
    ///\brief
    ///A array for Key A
    ///\details
    ///We store Key A in this array with a maximum size of 6 bytes.
    std::array<uint8_t,6> keyA;
    ///\brief
    ///A array for Key B
    ///\details
    ///We store Key B in this array with a maximum size of 6 bytes.
    std::array<uint8_t,6> keyB;
    ///\brief
    ///The maximum amount of blocks available
    ///\details
    ///We store the value of the maximum amount of avaiable blocks here.\n
    ///Because we only support the MF1S503yX maxBlocks is 64 by default.
    uint8_t maxBlocks;
    ///\brief
    ///A constructor with some default values
    ///\default
    ///This constructor can be called without supplying all the parameters because default values have been supplied.
    card(
      std::array<uint8_t,4> uid,
      std::array<uint8_t,6> keyA,
      std::array<uint8_t,6> keyB,
      uint8_t maxBlocks
    );
    ///\brief
    ///Default constructor
    ///\default
    ///This constructor doesn't need any input and only has default values.
    card();
  };
  ///\brief
  ///A enum class mifare card types
  ///\default
  ///This enum class contains the 4 types of mifare cards.\n
  ///For now we only support MF1S503yX.
  enum class type : uint8_t {
    MF1S500yX = 0x44,
    MF1S503yX = 0x04,
    MF1S700yX = 0x42,
    MF1S703yX = 0x02
  };

  ///\brief
  ///A enum class for mifare card SAK
  ///\default
  ///This enum class contains the SAK of the MF1S50yyXV1 cards.
  enum class sak : uint8_t {
    MF1S50yyXV1 = 0x08
  };

  ///\brief
  ///A enum class for mifare card commands
  ///\default
  ///This enum class contains the various command for the mifare cards.\n
  ///The request and wakeup commands need to be in a 7 bit frame.
  enum class command : uint8_t {
    request       = 0x26, // 7-bit
    wakeup        = 0x52, // 7-bit
    cl1           = 0x93,
    cl2           = 0x95,
    anticol       = 0x20,
    select        = 0x70,
    haltP1        = 0x50,
    haltP2        = 0x00,
    authKA        = 0x60,
    authKB        = 0x61,
    persUIDUsage  = 0x40,
    setModType    = 0x43,
    read          = 0x30,
    write         = 0xA0,
    decrement     = 0xC0,
    increment     = 0xC1,
    restore       = 0xC2,
    transfer      = 0xB0
  };
}

///\brief
///Print a uint8_t in binary
///\default
///This function prints a supplied uint8_t in binary.\n
///Made under the guidance of David de Jong.
void bitPrint(uint8_t a);

///\brief
///Prints n times "."
///\default
///This function prints "." n times with a 100 ms wait in between.
void printPatience(uint8_t n);

///\brief
///Compare 2 arrays
///\default
///This function compares 2 arrays with any typename and any size.\n
///If the 2 arrays are equal we return true, else we return false.\n
///Made under the guidance of David de Jong.
template<typename T, unsigned int N>
bool arrayCompare(const std::array<T,N> & a, const std::array<T,N> & b){
  for (unsigned int i = 0; i < N; i++){
    if((a[i] != b[i])){
      return false;
    }
  }
  return true;
}

///\brief
///Prints value from array in hex format
///\default
///This function prints all the values in a supplied array of type uint8_t and of any size.\n
template<unsigned int N>
void hexPrintArr(const std::array<uint8_t,N> & a){
  for (unsigned int i = 0; i < N; i++){
    hwlib::cout << hwlib::hex << "0x" <<  hwlib::setfill('0') << hwlib::setw(2) << a[i] << ", ";
    if ((i%8) == 7){
      hwlib::cout << hwlib::endl;
    }
  }
  hwlib::cout << hwlib::endl;
}
template<typename T, unsigned int N>
void askUserToArrayOfChar(T question, std::array<char,N> & response){
  hwlib::cout << question;
  for (uint8_t i = 0; i < (N-1); i++){
    char temp = {};
    hwlib::cin >> temp;
    if (temp == '\n'){
      break;
    }
    hwlib::cout << temp;
    response[i] = temp;
  }
  hwlib::cout << hwlib::endl;
}

template<unsigned int N>
void printArrayOfChar(std::array<char,N> a){
  for(auto letter : a){
    hwlib::cout << letter;
  }
  hwlib::cout << hwlib::endl;
}

// template<unsigned int N>
// uint16_t arrayOfCharToInt(std::array<char,N> a){
//   uint16_t returnMe = 0;
//   uint8_t numbers = 0;
//   for(auto letter : a){
//     if (letter != '\0'){
//       hwlib::cout << "letter : " << letter << hwlib::endl;
//       hwlib::cout << "getal  : " << (int)letter << hwlib::endl;
//       numbers++;
//     }
//   }
//   hwlib::cout << "Aantal getallen : " << numbers <<hwlib::endl;
//   uint16_t multiplier = 1;
//   if (numbers > 1){
//     for (uint8_t i = 1; i < numbers; i++){
//       multiplier *= 10;
//       hwlib::cout <<"Multiplier : " <<  multiplier << hwlib::endl;
//     }

//   }

//   for (uint8_t i = 0; i < numbers; i++){
//     uint16_t temp = (int)a[i];
//     hwlib::cout << "getal temp " << temp;
//     returnMe += multiplier * temp;
//     multiplier /= 10;
//   }
//   return returnMe;
// }

#endif