#include "supp.hpp"

void bitPrint(uint8_t a){
  for (int8_t i = 7; i >= 0; --i){
    hwlib::cout << ((((a >> i) & 1) == 1) ? 1 : 0);
    if(i == 4){hwlib::cout << ' ';}
  }
  hwlib::cout << hwlib::endl;
}

void printPatience(uint8_t n){
  for (uint8_t i = 0; i < n; i++){
    hwlib::cout << ".";
    hwlib::wait_ms(100);
  }
  hwlib::cout << hwlib::endl;
}