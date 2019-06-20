#include "rc522.hpp"

rc522::rc522(
  hwlib::target::pin_out & nssInput,
  hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
):
  spiReader(nssInput,spiBusInput)
{}

uint8_t rc522::read(const uint8_t regAddr){
  bitPrint(regAddr);
  uint8_t readBit = 1 << 7;
  uint8_t address = regAddr << 1;
  address |= readBit;

  std::array<uint8_t,2> dataIn = {address,0x00};
  std::array<uint8_t,2> dataOut = {0x00};

  hwlib::cout << "++ Read ============================== ++" << hwlib::endl;
  hwlib::cout << "In  :";
  bitPrint(dataIn[0]);

  spiBus.transaction(nss).write_and_read(dataIn,dataOut);

  hwlib::cout << "Out :";
  bitPrint(dataOut[1]);
  hwlib::cout << "-- Read End ========================== --" << hwlib::endl << hwlib::endl;

  return static_cast<uint8_t>(dataOut[1]);
}

void rc522::write(const uint8_t regAddr,const uint8_t data){
  uint8_t address = regAddr << 1;

  hwlib::cout << "++ Write ============================= ++" << hwlib::endl;
  hwlib::cout << "address : ";
  bitPrint(address);
  hwlib::cout << "data    : ";
  bitPrint(data);
  hwlib::cout << "-- Write End ========================= --" << hwlib::endl << hwlib::endl;

  std::array<uint8_t,2> dataIn = {address,data};
  spiBus.transaction(nss).write(dataIn);
}

uint8_t rc522::readReg(rc522::commands regAddr){
  return read(static_cast<uint8_t>(regAddr));
}

uint8_t rc522::readReg(rc522::registers regAddr){
  return read(static_cast<uint8_t>(regAddr));
}

uint8_t rc522::readReg(rc522::configuration regAddr){
  return read(static_cast<uint8_t>(regAddr));
}

uint8_t rc522::readReg(rc522::test regAddr){
  return read(static_cast<uint8_t>(regAddr));
}

void rc522::writeReg(rc522::commands regAddr, uint8_t data){
  write(static_cast<uint8_t>(regAddr), data);
}

void rc522::writeReg(rc522::registers regAddr, uint8_t data){
  write(static_cast<uint8_t>(regAddr), data);
}

void rc522::writeReg(rc522::configuration regAddr, uint8_t data){
  write(static_cast<uint8_t>(regAddr), data);
}

void rc522::writeReg(rc522::test regAddr, uint8_t data){
  write(static_cast<uint8_t>(regAddr), data);
}