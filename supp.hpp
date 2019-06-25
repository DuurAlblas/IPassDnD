#ifndef SUPP_HPP
#define SUPP_HPP

#include <hwlib.hpp>
#include "rc522.hpp"

void bitPrint(uint8_t a);

template<typename T, unsigned int N>
bool arrayCompare(const std::array<T,N> & a, const std::array<T,N> & b){
  for (unsigned int i = 0; i < N; i++){
    if((a[i] != b[i])){
      return false;
    }
  }
  return true;
}

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

#endif