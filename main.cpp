#include "supp.hpp"
#include "rc522.hpp"
#include "deco.hpp"

//A function that test whether i can read/write to/from registers
void writeReadTest(rc522 & reader){
  hwlib::cout << "Try SoftReset" << hwlib::endl;
  reader.writeReg(rc522::registers::CommandReg, 0b00001111);

  hwlib::cout << "TestPinEnReg" << hwlib::endl;
  reader.readReg(rc522::test::TestPinEnReg);
  reader.writeReg(rc522::test::TestPinEnReg, 0b01111110);
  reader.readReg(rc522::test::TestPinEnReg);

  hwlib::cout << "TestPinValueReg" << hwlib::endl;
  reader.readReg(rc522::test::TestPinValueReg);
  reader.writeReg(rc522::test::TestPinValueReg, 0b10101010);
  reader.readReg(rc522::test::TestPinValueReg);
  reader.writeReg(rc522::test::TestPinValueReg, 0b10111100);
  reader.readReg(rc522::test::TestPinValueReg);
}

int main(){
  // Wait so hwlib::cout works
  hwlib::wait_ms(500);

  // Init Vars
  auto sclk = hwlib::target::pin_out(hwlib::target::pins::d8);
  auto mosi = hwlib::target::pin_out(hwlib::target::pins::d9);
  auto miso = hwlib::target::pin_in(hwlib::target::pins::d10);
  auto spiBus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso);
  auto nss = hwlib::target::pin_out(hwlib::target::pins::d11);

  // Program
  rc522 newReader = rc522(nss,spiBus);
  newReader.selfTest();

  hwlib::cout << "Compiled" << hwlib::endl;
  return 0;
}