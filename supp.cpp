#include "supp.hpp"

mifare::card::card(
  std::array<uint8_t,4> uidInput = {},
  std::array<uint8_t,6> keyAInput = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
  std::array<uint8_t,6> keyBInput = {0x00,0x00,0x00,0x00,0x00,0x00},
  uint8_t maxBlocksInput = 64
):
  uid(uidInput),
  keyA(keyAInput),
  keyB(keyBInput),
  maxBlocks(maxBlocksInput)
{}

mifare::card::card():
  uid({}),
  keyA({0xFF,0xFF,0xFF,0xFF,0xFF,0xFF})
{}

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