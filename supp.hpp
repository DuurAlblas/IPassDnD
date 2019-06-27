#ifndef SUPP_HPP
#define SUPP_HPP

#include <hwlib.hpp>

namespace mifare{
  enum class type : uint8_t {
    MF1S500yX = 0x44,
    MF1S503yX = 0x04,
    MF1S700yX = 0x42,
    MF1S703yX = 0x02
  };

  enum class sak : uint8_t {
    MF1S50yyXV1 = 0x08
  };

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

void bitPrint(uint8_t a);

void printPatience(uint8_t n);

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