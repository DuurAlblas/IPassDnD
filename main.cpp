#include "supp.hpp"
#include "rc522.hpp"
#include "tests.hpp"
#include "application.hpp"

bool executeChoice(char choice,sheet & character,rc522 & reader,rc522::status fStatus, mifare::card card){
  uint8_t tmp = ((int)choice - 48);
      std::array<uint8_t,18> receive = {};
      std::array<uint8_t,16> send = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00
      };
  switch(tmp){
    case 0:
      character.printAll();
      break;
    case 1:
      break;
    case 2:
      if(reader.findCard()){
        outputStatus(reader.executeRead(0x01,receive,card));
        hexPrintArr(receive);
      }
      break;
    case 3:
      if(reader.findCard()){
        outputStatus(reader.executeWrite(0x01,send,card));
      }
      break;
    case 4:
      writeLine("Goodbye!");
      return false;
      break;
    default:
      hwlib::cout << "Something went wrong, maybe you didn't enter a correct number?" << hwlib::endl;
      break;
  }
  return true;
}

void mainLoop(sheet & character,rc522 & reader,rc522::status fStatus, mifare::card card){
  char choice;
  bool run = true;
  writeLine("Welcome!");
  while(run){
    writeLine("=============================-----------------");
    writeLine("Choose a option: ");
    writeLine("Show Sheet           : 0");
    writeLine("Create sheet         : 1");
    writeLine("Read sheet from card : 2");
    writeLine("Write sheet to card  : 3");
    writeLine("Exit                 : 4");
    writeLine("=============================-----------------");
    hwlib::cin >> choice;
    run = executeChoice(choice,character,reader,fStatus,card);
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
  rc522::status fStatus = rc522::status::READY;
  mifare::card currentCard =  mifare::card();
  sheet myCharacter = testSheet();

  // Program
  hwlib::cout << "Initializing";
  printPatience(3);
  if (newReader.selfTest() == rc522::status::ERROR){return 0;}
  newReader.initialize();

  mainLoop(myCharacter,newReader,fStatus,currentCard);

  hwlib::cout << hwlib::endl << "End of main" << hwlib::endl;
  return 0;
}