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

void testFifo(rc522 & reader){
  hwlib::cout << "Try SoftReset" << hwlib::endl;
  reader.writeReg(rc522::registers::CommandReg, 0b00001111);
  hwlib::cout << "FIFOLevelReg pointer to 0" << hwlib::endl;
  reader.writeReg(rc522::registers::FIFOLevelReg, 0b10000000);
  hwlib::cout << "Current level: " << reader.readReg(rc522::registers::FIFOLevelReg) << hwlib::endl;
  hwlib::cout << "Write to FIFOBuffer" << hwlib::endl;
  reader.writeReg(rc522::registers::FIFODataReg,0b10010110);
  hwlib::cout << "Current level: " << reader.readReg(rc522::registers::FIFOLevelReg) << hwlib::endl;
  hwlib::cout << "Read from FIFOBuffer" << hwlib::endl;
  bitPrint(reader.readReg(rc522::registers::FIFODataReg));
}

void checkForCard(rc522 & reader){
  uint8_t curLevel = 0;
  hwlib::cout << "Try SoftReset" << hwlib::endl;
  reader.writeReg(rc522::registers::CommandReg, 0b00001111);
  hwlib::cout << "FIFOLevelReg pointer to 0" << hwlib::endl;
  reader.writeReg(rc522::registers::FIFOLevelReg, 0b10000000);
  curLevel = reader.readReg(rc522::registers::FIFOLevelReg);
  hwlib::cout << "Current level: " << curLevel << hwlib::endl;
  if (curLevel != 0){
    hwlib::cout << "FIFO pointer not 0!" << hwlib::endl;
    return;
  }

  hwlib::cout << "Antenna's state ";
  bitPrint(reader.readReg(rc522::commands::TxControlReg));

  hwlib::cout << "Turn on antenna's" << hwlib::endl;
  //reader.setRegBitMask(rc522::commands::TxControlReg, 0b00000011);
  reader.writeReg(rc522::commands::TxControlReg, 0b00000011);

  hwlib::cout << "Antenna's state ";
  bitPrint(reader.readReg(rc522::commands::TxControlReg));

  hwlib::cout << "Send REQA 26h op 7bit" << hwlib::endl;
  // bool gotResponse = false;
  uint8_t reqa = 0x26;
  int tries = 2000;

  reader.writeReg(rc522::registers::CommandReg, 0x00);
  reader.writeReg(rc522::registers::ComIrqReg, 0x7F);
  reader.setRegBitMask(rc522::registers::FIFOLevelReg, 0x80);
  hwlib::cout << hwlib::endl << "=======================================" << hwlib::endl;
  hwlib::cout << "Set bit framing" << hwlib::endl;
  reader.writeReg(rc522::registers::BitFramingReg, 0b00000111);
  bitPrint(reader.readReg(rc522::registers::BitFramingReg));
  reader.writeReg(rc522::registers::FIFODataReg,reqa);
  reader.writeReg(rc522::registers::CommandReg,0x0C);
  reader.setRegBitMask(rc522::registers::BitFramingReg,0b10000000);
  bitPrint(reader.readReg(rc522::registers::BitFramingReg));
  uint8_t n = 0;
  while(! (n & 0x30)){
    n = reader.readReg(rc522::registers::ComIrqReg);
    if (--tries == 0){
      hwlib::cout << "yeeted out of the fuction\n";
      break;
    }
    // hwlib::cout << "Fill FIFO with the 26h REQA" << hwlib::endl;

    // curLevel = reader.readReg(rc522::registers::FIFOLevelReg);
    // hwlib::cout << "Current level before transceive: " << curLevel << hwlib::endl;

    // hwlib::cout << "Transmit from FIFO" << hwlib::endl;

    // curLevel = reader.readReg(rc522::registers::FIFOLevelReg);
    // hwlib::cout << "Current level after transceive: " << curLevel << hwlib::endl;

    // hwlib::cout << "Read from FIFOBuffer ";

    // reader.writeReg(rc522::registers::CommandReg, 0b00000000);


  }
  bitPrint(n);
  bitPrint(reader.readReg(rc522::registers::FIFODataReg));

  hwlib::cout << hwlib::endl << "Read from RxModeReg ";
  bitPrint(reader.readReg(rc522::commands::RxModeReg));

  hwlib::cout << "Read from TxControlReg ";
  bitPrint(reader.readReg(rc522::commands::TxControlReg));

  hwlib::cout << "Read from BitFramingReg ";
  bitPrint(reader.readReg(rc522::registers::BitFramingReg));

  hwlib::cout << "Exiting checkForCard" << hwlib::endl;
}

void checkNewCardREQA(rc522 & reader){
  //Init values
  std::array<uint8_t, 2> bufATQA = {0x00};
  uint8_t bufATQASize = 0x02;
  uint8_t comREQA = 0x26;
  //uint8_t comREQASize = 0x02;
  uint8_t validBits = 0x07;
  uint8_t waitIRQ = 0x30;
  uint8_t rxAlign = 0x00;
  //uint8_t checkCrc = false;

  //Try resetting some registers
  reader.writeReg(rc522::commands::TxModeReg, 0x00);
  reader.writeReg(rc522::commands::RxModeReg, 0x00);
  reader.writeReg(rc522::configuration::ModWidthReg, 0x26);

  //Manipulating values
  uint8_t txLastBits = validBits;
  uint8_t bitFraming = (rxAlign << 4) + txLastBits;

  reader.writeReg(rc522::registers::CommandReg, 0x00);
  reader.writeReg(rc522::registers::ComIrqReg, 0x7F);
  reader.writeReg(rc522::registers::FIFOLevelReg, 0x80);
  reader.writeReg(rc522::registers::FIFODataReg, comREQA);
  reader.writeReg(rc522::registers::BitFramingReg, bitFraming);
  reader.writeReg(rc522::registers::CommandReg, 0x0C);
  reader.setRegBitMask(rc522::registers::BitFramingReg, 0x80);

  uint16_t i;
	for (i = 2000; i > 0; i--) {
		uint8_t n = reader.readReg(rc522::registers::ComIrqReg);
		if (n & waitIRQ) {
			break;
		}
		if (n & 0x01) {
      hwlib::cout << "Time Out: Nothing received" << hwlib::endl;
			return;
		}
	}

  if (i == 0) {
    hwlib::cout << "Time Out: Communication down?" << hwlib::endl;
		return;
	}

  uint8_t errorRegValue = reader.readReg(rc522::registers::ErrorReg);
	if (errorRegValue & 0x13) {
    hwlib::cout << "Error other than collision" << hwlib::endl;
		return;
	}


	uint8_t _validBits = 0;

	// If the caller wants data back, get it from the MFRC522.

  uint8_t n = reader.readReg(rc522::registers::FIFOLevelReg);
  if (n > bufATQASize) {
    hwlib::cout << "No Room for return data" << hwlib::endl;
    return;
  }
  bufATQASize = n;											// Number of bytes returned
  //PCD_ReadRegister(FIFODataReg, n, backData, rxAlign);	// Get received data from FIFO

  for (uint8_t i = 0; i < bufATQASize; i++){
    bufATQA[i] = reader.readReg(rc522::registers::FIFODataReg);
  }

  _validBits = reader.readReg(rc522::registers::ControlReg) & 0x07;
  //PCD_ReadRegister(ControlReg) & 0x07;		// RxLastBits[2:0] indicates the number of valid bits in the last received byte. If this value is 000b, the whole byte is valid.
  if (validBits) {
    validBits = _validBits;
  }

  hexPrintArr(bufATQA);

  hwlib::cout << "Succesfull !" << hwlib::endl;
  return;
}

void outputStatus(rc522::status recStatus){
  switch (recStatus){
  case rc522::status::SUCCESS:
    hwlib::cout << "Succes" << hwlib::endl;
    break;
  case rc522::status::SUCCESS_NEWC:
    hwlib::cout << "Welcome new card!" << hwlib::endl;
    break;
  case rc522::status::SUCCESS_OLDC:
    hwlib::cout << "Welcome old card!" << hwlib::endl;
    break;
  case rc522::status::ERROR:
    hwlib::cout << "Error" << hwlib::endl;
    break;
  case rc522::status::NO_SPACE:
    hwlib::cout << "No space" << hwlib::endl;
    break;
  case rc522::status::TIMEOUTCOM:
    hwlib::cout << "Time out Communication" << hwlib::endl;
    break;
  case rc522::status::TIMEOUTDEV:
    hwlib::cout << "Time out device" << hwlib::endl;
    break;
  case rc522::status::CRC_ERROR:
    hwlib::cout << "CRC Error" << hwlib::endl;
    break;
  case rc522::status::CRC_SUCCESS:
    hwlib::cout << "CRC Success" << hwlib::endl;
    break;
  default:
    hwlib::cout << "You're a special snowflake.\n";
    break;
  }
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
  // if (newReader.selfTest() == rc522::status::ERROR){
  //   return 0;
  // }
  newReader.initialize();

  //Send a Request
  while (true){
    if (newReader.wakeCard(mifare::command::request) == rc522::status::SUCCESS){
      hwlib::cout << "Welcome New Card!" << hwlib::endl;
      break;
    } else if (newReader.wakeCard(mifare::command::wakeup) == rc522::status::SUCCESS){
      hwlib::cout << "Welcome Old Card!" << hwlib::endl;
      break;
    }
    printPatience(5);
  }

  rc522::status cardSelected = newReader.selectCard();
  outputStatus(cardSelected);

  // read manufactor block

  hwlib::cout << "Compiled" << hwlib::endl;
  return 0;
}