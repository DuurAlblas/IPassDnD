// #include "hwlib.hpp"
// #include "../../hwlib/library/hwlib.hpp"
//#include "reader.hpp"
#include "supp.hpp"
#include "rc522.hpp"
#include "deco.hpp"

int main(){
  // Wait so hwlib::cout works
  hwlib::wait_ms(500);

  // Init Vars
  auto sclk = hwlib::target::pin_out(hwlib::target::pins::d8);
  auto mosi = hwlib::target::pin_out(hwlib::target::pins::d9);
  auto miso = hwlib::target::pin_in(hwlib::target::pins::d10);
  auto spiBus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso);
  auto nss = hwlib::target::pin_out(hwlib::target::pins::d11);

  auto testWindow = hwlib::target::pin_out(hwlib::target::pins::d12);

  rc522 newReader = rc522(nss,spiBus);

  hwlib::cout << "Compiled" << hwlib::endl;

  hwlib::cout << "Try SoftReset" << hwlib::endl;
  newReader.writeReg(rc522::registers::CommandReg, 0b00001111);

  hwlib::cout << "TestPinEnReg" << hwlib::endl;
  newReader.readReg(rc522::test::TestPinEnReg);
  newReader.writeReg(rc522::test::TestPinEnReg, 0b01111110);
  newReader.readReg(rc522::test::TestPinEnReg);

  hwlib::cout << "TestPinValueReg" << hwlib::endl;
  newReader.readReg(rc522::test::TestPinValueReg);
  newReader.writeReg(rc522::test::TestPinValueReg, 0b10101010);
  newReader.readReg(rc522::test::TestPinValueReg);
  newReader.writeReg(rc522::test::TestPinValueReg, 0b10111100);
  newReader.readReg(rc522::test::TestPinValueReg);

  hwlib::wait_ms(500);


  return 0;
}