#include "supp.hpp"
#include "rc522.hpp"
#include "tests.hpp"
#include "application.hpp"


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
  // rc522::status fStatus;
  mifare::card currentCard =  mifare::card();
  // Program

  // if (newReader.selfTest() == rc522::status::ERROR){
  //   return 0;
  // }
  newReader.initialize();

  std::array<char,33> characterName = {};
  askUserToArrayOfChar("Geef naam (max 32 characters):", characterName);
  std::array<char,17> characterHairColor = {};
  askUserToArrayOfChar("Geef haarkleur (max 16 characters):",characterHairColor);


  sheet myCharater = sheet(
    characterName,
    characterHairColor,
    dnd::races::Human,
    dnd::profesions::Rogue,
    dnd::allignments::Neutral,
    {dnd::languages::Common,dnd::languages::Dwarvish}
  );

  myCharater.printAll();

  // //Send a Request
  // hwlib::cout << "Looking for a card" << hwlib::endl;
  // while (true){
  //   if (newReader.wakeCard(mifare::command::request) == rc522::status::SUCCESS){
  //     hwlib::cout << "Welcome new card!" << hwlib::endl;
  //     break;
  //   } else if (newReader.wakeCard(mifare::command::wakeup) == rc522::status::SUCCESS){
  //     hwlib::cout << "Welcome old card!" << hwlib::endl;
  //     break;
  //   }
  //   printPatience(5);
  // }
  // std::array<uint8_t,16> bufSend = {
  //     0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
  //     0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00
  //   };
  // // std::array<uint8_t,16> bufSendEmpty = {};
  // uint8_t block = 0x01;
  // demo(fStatus,newReader,currentCard,block,bufSend,true);

  // read manufactor block
  hwlib::cout << hwlib::endl << "End of main" << hwlib::endl;
  return 0;
}