#ifndef READER_HPP
#define READER_HPP

#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

class spiReader {
  private:
  protected:
    hwlib::target::pin_out nss;
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spiBus;
  public:
    spiReader(
      hwlib::target::pin_out & nssInput,
      hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
    );
};

#endif