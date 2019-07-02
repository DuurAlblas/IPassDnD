#include "supp.hpp"
#include "rc522.hpp"
#include "deco.hpp"

//A function that test whether i can read/write to/from registers
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

  rc522 newReader = rc522(nss,spiBus);
  bool isSelected = false;
  bool isAuthenticated = false;
  bool isWritten = false;
  rc522::status fStatus;
  mifare::card currentCard =  mifare::card();


  // Program

  // if (newReader.selfTest() == rc522::status::ERROR){
  //   return 0;
  // }
  newReader.initialize();

  //Send a Request
  hwlib::cout << "Looking for a card" << hwlib::endl;
  while (true){
    if (newReader.wakeCard(mifare::command::request) == rc522::status::SUCCESS){
      hwlib::cout << "Welcome new card!" << hwlib::endl;
      break;
    } else if (newReader.wakeCard(mifare::command::wakeup) == rc522::status::SUCCESS){
      hwlib::cout << "Welcome old card!" << hwlib::endl;
      break;
    }
    printPatience(5);
  }


  hwlib::cout << "Try to select the card" << hwlib::endl;
  fStatus = newReader.tryFunction([&]{
    return newReader.selectCard( currentCard );
  });
  if (fStatus == rc522::status::SUCCESS ) {
    isSelected = true;
  }
  outputStatus(fStatus);


  if (isSelected){
    fStatus = newReader.tryFunction([&]{
      return newReader.authenticateCard(mifare::command::authKA, 0x01, currentCard);
    });
    hwlib::cout << "Try to authenticate the card" << hwlib::endl;
    if (fStatus == rc522::status::SUCCESS){
      isAuthenticated = true;
    }
    outputStatus(fStatus);
  }

  if (isAuthenticated){
    hwlib::cout << "Try to read from card" << hwlib::endl;
    std::array<uint8_t,18> bufReceive = {};
    fStatus = newReader.tryFunction([&]{
      return newReader.readBlock(0x01,bufReceive);
    });
    if (fStatus == rc522::status::SUCCESS){
      hexPrintArr(currentCard.uid);
      hexPrintArr(bufReceive);
    }
    outputStatus(fStatus);
  }

  if (isAuthenticated){
    hwlib::cout << "Try to write to card" << hwlib::endl;
    std::array<uint8_t,16> bufSend = {
      0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
      0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00
    };
    fStatus = newReader.tryFunction([&]{
      return newReader.writeBlock(0x01,bufSend);
    });
    if (fStatus == rc522::status::SUCCESS){
      isWritten = true;
    }
    outputStatus(fStatus);
  }

  if (isWritten){
    hwlib::cout << "Try to read from card" << hwlib::endl;
    std::array<uint8_t,18> bufReceive = {};
    fStatus = newReader.tryFunction([&]{
      return newReader.readBlock(0x01,bufReceive);
    });
    if (fStatus == rc522::status::SUCCESS){
      hexPrintArr(bufReceive);
    }
    outputStatus(fStatus);
  }

  // read manufactor block

  if (isAuthenticated){
    newReader.stopCrypto();
  }
  hwlib::cout << "End of main" << hwlib::endl;
  return 0;
}