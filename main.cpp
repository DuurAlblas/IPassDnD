#include "supp.hpp"
#include "rc522.hpp"

///\brief
///Output appropriate text to rc522::status
///\default
///This function prints out text that is appropriate for the received rc522::status.
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

///\brief
/// A small demo
///\default
///This function reads a block from a mifare card then writes supplied data to that block and then reads it again.\n
///You need to supply a rc522::status, \n
///next you need to supply a mifare::card and a uint8_t value for the block you wish to write to.\n
///you also need to supply a array with uint8_t values with a size of 16.
///You can also supply a bool, if the bool is true then this function will print text that shows what is happening,\n
/// the default value is false.
void demo(rc522::status & fStatus, rc522 & reader, mifare::card & card, uint8_t block, std::array<uint8_t,16> writeThis, bool showInfo = false){
  bool isSelected = false;
  bool isAuthenticated = false;
  bool isWritten = false;

  if(showInfo){hwlib::cout << "Try to select the card" << hwlib::endl;}
  fStatus = reader.tryFunction([&]{
    return reader.selectCard( card );
  });
  if (fStatus == rc522::status::SUCCESS ) {
    if(showInfo){
      hwlib::cout << "UID: ";
      hexPrintArr(card.uid);
    }
    isSelected = true;
  }
  if(showInfo){outputStatus(fStatus);}

  if (isSelected){
    fStatus = reader.tryFunction([&]{
      return reader.authenticateCard(mifare::command::authKA, block, card);
    });
    if(showInfo){hwlib::cout << "Try to authenticate the card" << hwlib::endl;}
    if (fStatus == rc522::status::SUCCESS){
      isAuthenticated = true;
    }
    if(showInfo){outputStatus(fStatus);}
  }

  if (isAuthenticated){
    if(showInfo){hwlib::cout << "Try to read from card" << hwlib::endl;}
    std::array<uint8_t,18> bufReceive = {};
    fStatus = reader.tryFunction([&]{
      return reader.readBlock(block,bufReceive);
    });
    if (fStatus == rc522::status::SUCCESS && showInfo){
      hwlib::cout << "Read : " << hwlib::endl;
      hexPrintArr(bufReceive);
    }
    outputStatus(fStatus);
  }

  if (isAuthenticated){
    if(showInfo){hwlib::cout << "Try to write to card" << hwlib::endl;}

    fStatus = reader.tryFunction([&]{
      return reader.writeBlock(block,writeThis);
    });
    if (fStatus == rc522::status::SUCCESS){
      isWritten = true;
    }
    if(showInfo){outputStatus(fStatus);}
  }

  if (isWritten){
    if(showInfo){hwlib::cout << "Try to read from card" << hwlib::endl;}
    std::array<uint8_t,18> bufReceive = {};
    fStatus = reader.tryFunction([&]{
      return reader.readBlock(block,bufReceive);
    });
    if (fStatus == rc522::status::SUCCESS && showInfo){
      hwlib::cout << "Read : " << hwlib::endl;
      hexPrintArr(bufReceive);
    }
    if(showInfo){outputStatus(fStatus);}

    if (isAuthenticated){
      reader.stopCrypto();
    }
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
  std::array<uint8_t,16> bufSend = {
      0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00,
      0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07
    };
  uint8_t block = 0x01;
  demo(fStatus,newReader,currentCard,block,bufSend,true);

  // read manufactor block
  hwlib::cout << "End of main" << hwlib::endl;
  return 0;
}