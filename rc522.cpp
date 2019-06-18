#include "rc522.hpp"

rc522::rc522(
  hwlib::target::pin_out & nssInput,
  hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
):
  spiReader(nssInput,spiBusInput)
{}

uint8_t rc522::readReg(rc522::commands regAddr){
  uint8_t readBit = 1 << 7;
  uint8_t address = static_cast<uint8_t>(regAddr) << 1;
  address |= readBit;

  hwlib::cout << "address : ";
  bitPrint(address);

  std::array<uint8_t,2> dataIn = {address,0x00};
  std::array<uint8_t,2> dataOut = {0x00};

  hwlib::cout << "Before transaction" << hwlib::endl;
  hwlib::cout << "dataIn 0  : ";
  bitPrint(dataIn[0]);
  hwlib::cout << "dataIn 1  : ";
  bitPrint(dataIn[1]);

  hwlib::cout << "dataOut 0 : ";
  bitPrint(dataOut[0]);
  hwlib::cout << "dataOut 1 : ";
  bitPrint(dataOut[1]);

  auto nssInverted = pin_out_invert(nss);
  spiBus.transaction(nssInverted).write_and_read(dataOut,dataIn);

  hwlib::cout << "After transaction" << hwlib::endl;
  hwlib::cout << "dataIn 0  : ";
  bitPrint(dataIn[0]);
  hwlib::cout << "dataIn 1  : ";
  bitPrint(dataIn[1]);

  hwlib::cout << "dataOut 0 : ";
  bitPrint(dataOut[0]);
  hwlib::cout << "dataOut 1 : ";
  bitPrint(dataOut[1]);

  return static_cast<uint8_t>(dataOut[1]);
}

void rc522::writeCommand(rc522::test regAddr, uint8_t data){
  uint8_t address = static_cast<uint8_t>(regAddr) << 1;
  hwlib::cout << "address : ";
  bitPrint(address);
  hwlib::cout << "data    : ";
  bitPrint(data);
  std::array<uint8_t,2> dataIn = {address,data};
  auto nssInverted = pin_out_invert(nss);
  spiBus.transaction(nssInverted).write(dataIn);
}