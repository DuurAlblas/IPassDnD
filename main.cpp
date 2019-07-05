///\mainpage library documentation
///\section Author
///Duur Alblas (c) 2019\n
///duur.alblas@student.hu.nl
///\section Version
/// Version 1.0 (last modified 4 july 2019)
///\section Copyright
///Boost license
///All D&D related references belong to Wizards of the Coast LLC
#include "supp.hpp"
#include "rc522.hpp"
#include "tests.hpp"
#include "application.hpp"

///\brief
///Create a character sheet
///\details
///This function creates a character sheet using the users input.\n
///It returns a sheet.
sheet createCharacter(){
  std::array<char,32> name ={};
  askUserToArrayOfChar("Character name (Max 30 characters) : ",name);
  dnd::races race = chooseRace();
  dnd::profesions profesion = chooseProfesion();
  dnd::allignments allignment = chooseAllignment();
  std::array<dnd::languages, 2> spokenLanguages = {};
  for (uint8_t i = 0; i < 2; i++){
    spokenLanguages[i] = chooseLanguage();
  }
  return sheet(name,race,profesion,allignment,spokenLanguages);
}

///\brief
///Execute chosen option
///\details
///This function executes the users choice and checks if the users input was acceptable.
bool executeChoice(char choice,sheet & character,rc522 & reader,rc522::status fStatus, mifare::card card){
  uint8_t tmp = ((int)choice - 48);
  switch(tmp){
    case 0:
      hwlib::cout << "Showing stored character sheet :" << hwlib::endl;
      character.printAll();
      break;
    case 1:
      hwlib::cout << "Creating new character sheet :" << hwlib::endl;
      character = createCharacter();
      break;
    case 2:
      hwlib::cout << "Reading from card :" << hwlib::endl;
      if(reader.findCard(true)){
        outputStatus(reader.readSheetFromCard(card,character));
      }
      break;
    case 3:
      hwlib::cout << "Writing to card :" << hwlib::endl;
      if(reader.findCard(true)){
        outputStatus(reader.writeSheetToCard(card,character));
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

///\brief
///Main loop of application
///\details
///This function gives the users choices and is the main loop of this application.
void mainLoop(sheet & character,rc522 & reader,rc522::status fStatus, mifare::card card){
  char choice;
  bool run = true;
  writeLine("Welcome!");
  while(run){
    writeLine("=============================-----------------");
    writeLine("Choose a option: ");
    writeLine("Show sheet                               : 0");
    writeLine("Create new sheet       (overwrites sheet): 1");
    writeLine("Read sheet from card   (overwrites sheet): 2");
    writeLine("Write sheet to card                      : 3");
    writeLine("Exit                                     : 4");
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