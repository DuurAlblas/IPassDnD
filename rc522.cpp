#include "rc522.hpp"

rc522::rc522(
  hwlib::target::pin_out & nssInput,
  hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
):
  spiReader(nssInput,spiBusInput)
{}

uint8_t rc522::read(const uint8_t regAddr){
  uint8_t readBit = 1 << 7;
  uint8_t address = regAddr << 1;
  address |= readBit;
  std::array<uint8_t,2> dataIn = {address,0x00};
  std::array<uint8_t,2> dataOut = {0x00};
  spiBus.transaction(nss).write_and_read(dataIn,dataOut);
  return static_cast<uint8_t>(dataOut[1]);
}

void rc522::write(const uint8_t regAddr,const uint8_t data){
  uint8_t address = regAddr << 1;
  std::array<uint8_t,2> dataIn = {address,data};
  spiBus.transaction(nss).write(dataIn);
}

uint8_t rc522::readReg(rc522::commands regAddr)                   {return read(static_cast<uint8_t>(regAddr));}
uint8_t rc522::readReg(rc522::registers regAddr)                  {return read(static_cast<uint8_t>(regAddr));}
uint8_t rc522::readReg(rc522::configuration regAddr)              {return read(static_cast<uint8_t>(regAddr));}
uint8_t rc522::readReg(rc522::test regAddr)                       {return read(static_cast<uint8_t>(regAddr));}

void rc522::writeReg(rc522::commands regAddr, uint8_t data)       {write(static_cast<uint8_t>(regAddr), data);}
void rc522::writeReg(rc522::registers regAddr, uint8_t data)      {write(static_cast<uint8_t>(regAddr), data);}
void rc522::writeReg(rc522::configuration regAddr, uint8_t data)  {write(static_cast<uint8_t>(regAddr), data);}
void rc522::writeReg(rc522::test regAddr, uint8_t data)           {write(static_cast<uint8_t>(regAddr), data);}

void rc522::writeReg(rc522::registers regAddr, rc522::regCommands data){
  write(
    static_cast<uint8_t>(regAddr),
    static_cast<uint8_t>(data)
  );
}

void rc522::setRegBitMask(rc522::commands regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp|mask);
}

void rc522::setRegBitMask(rc522::registers regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp|mask);
}

void rc522::setRegBitMask(rc522::configuration regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp|mask);
}

void rc522::setRegBitMask(rc522::test regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp|mask);
}

void rc522::unsetRegBitMask(rc522::commands regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp&(~mask));
}

void rc522::unsetRegBitMask(rc522::registers regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp&(~mask));
}

void rc522::unsetRegBitMask(rc522::configuration regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp&(~mask));
}

void rc522::unsetRegBitMask(rc522::test regAddr, uint8_t mask){
  uint8_t tmp = read(static_cast<uint8_t>(regAddr));
  write(static_cast<uint8_t>(regAddr),tmp&(~mask));
}

void rc522::antennaOn(bool feedback = false){
  if (feedback){
    hwlib::cout << "Initial state: ";
    bitPrint(readReg(rc522::commands::TxControlReg));
  }
  setRegBitMask(rc522::commands::TxControlReg, 0x03);
  if (feedback){
    hwlib::cout << "Renewed state: ";
    bitPrint(readReg(rc522::commands::TxControlReg));
  }
}

void rc522::antennaOff(bool feedback = false){
  if (feedback){
    hwlib::cout << "Initial state: ";
    bitPrint(readReg(rc522::commands::TxControlReg));
  }
  unsetRegBitMask(rc522::commands::TxControlReg, 0x03);
  if (feedback){
    hwlib::cout << "Renewed state: ";
    bitPrint(readReg(rc522::commands::TxControlReg));
  }
}

void rc522::softReset(){
  writeReg(rc522::registers::CommandReg, rc522::regCommands::SoftReset);
  uint8_t loop = 0;
  do {
    hwlib::wait_ms(25);
    loop++;
  } while (loop < 10 && (readReg(rc522::registers::CommandReg) & (1 << 4)));
}


void rc522::initialize(){
  //First do a soft reset
  softReset();

  //Reset the baud rates and the modulation with
  writeReg(rc522::commands::TxModeReg, 0x00);
  writeReg(rc522::commands::RxModeReg, 0x00);
  writeReg(rc522::configuration::ModWidthReg, 0x26);

  //Configure time out values in case things go wrong
  writeReg(rc522::configuration::TModeReg, 0x80); // Timer start automatically after all forms of commincation
  writeReg(rc522::configuration::TPrescalerReg, 0xA9); // 0xA9 == 169, a timer period of 25 us
  writeReg(rc522::configuration::TReloadReg_High, 0x03); // 0x03E8 == 1000, 25ms before we time out
  writeReg(rc522::configuration::TReloadReg_Low, 0xE8);
  writeReg(rc522::commands::TxASKReg, 0x40); // Force100ASK
  writeReg(rc522::commands::ModeReg, 0x3D); // CRC doesnt calc with MSBF and CRCPreset is 6363h
  antennaOn(); // soft reset turned them off
}

rc522::version rc522::compareVersion(std::array<uint8_t, 64> buffer){
    std::array<uint8_t,64> version1 = { 0x00, 0xC6, 0x37, 0xD5, 0x32, 0xB7, 0x57, 0x5C,
                                      0xC2, 0xD8, 0x7C, 0x4D, 0xD9, 0x70, 0xC7, 0x73,
                                      0x10, 0xE6, 0xD2, 0xAA, 0x5E, 0xA1, 0x3E, 0x5A,
                                      0x14, 0xAF, 0x30, 0x61, 0xC9, 0x70, 0xDB, 0x2E,
                                      0x64, 0x22, 0x72, 0xB5, 0xBD, 0x65, 0xF4, 0xEC,
                                      0x22, 0xBC, 0xD3, 0x72, 0x35, 0xCD, 0xAA, 0x41,
                                      0x1F, 0xA7, 0xF3, 0x53, 0x14, 0xDE, 0x7E, 0x02,
                                      0xD9, 0x0F, 0xB5, 0x5E, 0x25, 0x1D, 0x29, 0x79
                                    };
  std::array<uint8_t,64> version2 = { 0x00, 0xEB, 0x66, 0xBA, 0x57, 0xBF, 0x23, 0x95,
                                      0xD0, 0xE3, 0x0D, 0x3D, 0x27, 0x89, 0x5C, 0xDE,
                                      0x9D, 0x3B, 0xA7, 0x00, 0x21, 0x5B, 0x89, 0x82,
                                      0x51, 0x3A, 0xEB, 0x02, 0x0C, 0xA5, 0x00, 0x49,
                                      0x7C, 0x84, 0x4D, 0xB3, 0xCC, 0xD2, 0x1B, 0x81,
                                      0x5D, 0x48, 0x76, 0xD5, 0x71, 0x61, 0x21, 0xA9,
                                      0x86, 0x96, 0x83, 0x38, 0xCF, 0x9D, 0x5B, 0x6D,
                                      0xDC, 0x15, 0xBA, 0x3E, 0x7D, 0x95, 0x3B, 0x2F
                                    };
  if (arrayCompare(buffer, version1)){
    return rc522::version::version1;
  } else if (arrayCompare(buffer, version2)){
    return rc522::version::version2;
  } else {
    return rc522::version::error;
  }
}

// Steps to perfom the self test:
//  1: Perform Soft Reset
//  2: Clear the internal buffer by writing 25 bytes of 00h and implement the Config command
//  3: Enable the self test by writing 09h to the AutoTestReg register
//  4: Write 00h to the FIFO buffer
//  5: Start the self test with the CalcCRC command
//  6: The self test is initiated
//  7: When the self test has completed, the FIFO buffer contains the following 64 bytes
rc522::status rc522::selfTest(){
  std::array<uint8_t,64> myBuffer = { 0x00 };
  writeReg(rc522::registers::CommandReg, 0x0F);
  hwlib::wait_ms(2500);
  for (uint8_t i = 0; i < 25; i++){ writeReg(rc522::registers::FIFODataReg,0x00);}
  writeReg(rc522::registers::CommandReg, 0x01);
  writeReg(rc522::test::AutoTestReg, 0x09);
  writeReg(rc522::registers::FIFODataReg,0x00);
  writeReg(rc522::registers::CommandReg,0x03);
  hwlib::wait_ms(2500);
  uint8_t amountBytes = readReg(rc522::registers::FIFOLevelReg);
  for (uint8_t i = 0; i < amountBytes; i++){ myBuffer[i] = readReg(rc522::registers::FIFODataReg);}
  switch (compareVersion(myBuffer)){
  case rc522::version::version1:
    hwlib::cout << "Chip version 1 not supported.\n";
    break;
  case rc522::version::version2:
    hwlib::cout << "Chip version 2 is supported!\n";
    return rc522::status::SUCCESS;
    break;
  default:
    hwlib::cout << "You're a special snowflake.\n";
    break;
  }
  return rc522::status::ERROR;
}

rc522::status rc522::wakeCard(mifare::command comData){
  std::array<uint8_t,2> bufReceive = {};
  uint8_t bitFraming = 7;
  std::array<uint8_t,1> bufSend = {static_cast<uint8_t>(comData)};
  return cardTransceive(bufSend,bufReceive,bitFraming);
}

rc522::status rc522::selectCard(){
  //Send Col 1 to get NUID
  std::array<mifare::command, 2> bufCol = {mifare::command::cl1, mifare::command::anticol};
  std::array<uint8_t, 5> bufColReceive = {};
  if (cardTransceive(bufCol, bufColReceive) != rc522::status::SUCCESS ){
    return rc522::status::ERROR;
  }
  uint8_t bcc = bufColReceive[0] ^ bufColReceive[1] ^ bufColReceive[2] ^ bufColReceive[3];
  if (bcc != bufColReceive[4]){
    return rc522::status::ERROR;
  }

  //Send Select to card
  std::array<uint8_t, 7> bufCrc = {0x93,0x70,bufColReceive[0],bufColReceive[1],bufColReceive[2],bufColReceive[3],bcc};
  std::array<uint8_t, 9> bufSel = {};
  std::copy(begin(bufCrc), end(bufCrc), begin(bufSel));
  rc522::status calcStatus = calcCRC(bufCrc,bufSel);
  if (calcStatus != rc522::status::SUCCESS){
    return calcStatus;
  }
  std::array<uint8_t, 16> bufSelReceive = {};
  return cardTransceive(bufSel, bufSelReceive,0,true);
}