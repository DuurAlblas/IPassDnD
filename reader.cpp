#include "reader.hpp"

spiReader::spiReader(
  hwlib::target::pin_out & nssInput,
  hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
):
  nss(nssInput),
  spiBus(spiBusInput)
{}