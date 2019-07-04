#include "tests.hpp"

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

bool trySelect(rc522::status & fStatus, rc522 & reader, mifare::card & card, bool showInfo = false){
  if(showInfo){hwlib::cout << "Try to select the card" << hwlib::endl;}
  fStatus = reader.tryFunction([&]{
    return reader.selectCard( card );
  });
  if (fStatus == rc522::status::SUCCESS ) {
    if(showInfo){
      hwlib::cout << "UID: ";
      hexPrintArr(card.uid);
    }
    if(showInfo){outputStatus(fStatus);}
    return true;
  }
  if(showInfo){outputStatus(fStatus);}
  return false;
}

bool tryAuthenticate(rc522::status & fStatus, rc522 & reader, mifare::card & card, uint8_t block, bool showInfo = false){
    fStatus = reader.tryFunction([&]{
      return reader.authenticateCard(mifare::command::authKA, block, card);
    });
    if(showInfo){hwlib::cout << "Try to authenticate the card" << hwlib::endl;}
    if (fStatus == rc522::status::SUCCESS){
      if(showInfo){outputStatus(fStatus);}
      return true;
    }
    if(showInfo){outputStatus(fStatus);}
    return false;
}

void tryRead(rc522::status & fStatus, rc522 & reader, uint8_t block, bool showInfo = false){
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

bool tryWrite(rc522::status & fStatus, rc522 & reader, uint8_t block, std::array<uint8_t,16> writeThis, bool showInfo = false){
    if(showInfo){hwlib::cout << "Try to write to card" << hwlib::endl;}

    fStatus = reader.tryFunction([&]{
      return reader.writeBlock(block,writeThis);
    });
    if (fStatus == rc522::status::SUCCESS){
      if(showInfo){outputStatus(fStatus);}
      return true;
    }
    if(showInfo){outputStatus(fStatus);}
    return false;
}

void demo(rc522::status & fStatus, rc522 & reader, mifare::card & card, uint8_t block, std::array<uint8_t,16> writeThis, bool showInfo = false){
  bool isSelected = trySelect(fStatus,reader,card,showInfo);
  bool isAuthenticated = false;
  bool isWritten = false;

  if (isSelected){
    isAuthenticated = tryAuthenticate(fStatus,reader,card,block,showInfo);
  }

  if (isAuthenticated){
    tryRead(fStatus,reader,block,showInfo);
  }

  if (isAuthenticated){
    isWritten = tryWrite(fStatus,reader,block,writeThis,showInfo);
  }

  if (isWritten && isAuthenticated){
    tryRead(fStatus,reader,block,showInfo);
  }

  if (isAuthenticated){
    reader.stopCrypto();
   }
}