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

  rc522 newReader = rc522(nss,spiBus);

  newReader.writeCommand(rc522::test::TestPinEnReg, 2);
  newReader.writeCommand(rc522::test::TestPinValueReg, 130);
  hwlib::wait_ms(1000);
  newReader.writeCommand(rc522::test::TestPinValueReg, 128);

  hwlib::cout << "Compiled" << hwlib::endl;
  return 0;
}