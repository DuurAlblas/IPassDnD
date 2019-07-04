#include "application.hpp"

sheet::sheet(
  std::array<char,32> nameInput,
  dnd::races raceInput,
  dnd::profesions profesionInput,
  dnd::allignments allignmentInput,
  std::array<dnd::languages, 2> spokenLanguagesInput
):
  name(nameInput),
  race(raceInput),
  profesion(profesionInput),
  allignment(allignmentInput),
  spokenLanguages(spokenLanguagesInput)
{}

void sheet::printRace(dnd::races race){
  switch (race){
  case dnd::races::HillDwarf :
    writeLine("Hill Dwarf");
    break;
  case dnd::races::MountainDwarf :
    writeLine("Mountain Dwarf");
    break;
  case dnd::races::HighElf :
    writeLine("High Elf");
    break;
  case dnd::races::WoodElf :
    writeLine("Wood Elf");
    break;
  case dnd::races::DarkElf :
    writeLine("Dark Elf");
    break;
  case dnd::races::LightfootHalfling :
    writeLine("Lightfoot Halfling");
    break;
  case dnd::races::StoutHalfling :
    writeLine("Stout Halfling");
    break;
  case dnd::races::Human :
    writeLine("Human");
    break;
  case dnd::races::Dragonborn :
    writeLine("Dragonborn");
    break;
  case dnd::races::ForestGnome :
    writeLine("Forest Gnome");
    break;
  case dnd::races::RockGnome :
    writeLine("Rock Gnome");
    break;
  case dnd::races::HalfElf :
    writeLine("Half Elf");
    break;
  case dnd::races::HalfOrc :
    writeLine("Half Orc");
    break;
  case dnd::races::Thiefling :
    writeLine("Thiefling");
    break;
  default:
    writeLine("You're a special snowflake ^^");
    break;
  }
}

void sheet::printProfesion(dnd::profesions profesion){
  switch(profesion){
    case dnd::profesions::Barbarian :
      writeLine("Barbarian");
      break;
    case dnd::profesions::Bard :
      writeLine("Bard");
      break;
    case dnd::profesions::Cleric :
      writeLine("Cleric");
      break;
    case dnd::profesions::Druid :
      writeLine("Druid");
      break;
    case dnd::profesions::Fighter :
      writeLine("Fighter");
      break;
    case dnd::profesions::Monk :
      writeLine("Monk");
      break;
    case dnd::profesions::Paladin :
      writeLine("Paladin");
      break;
    case dnd::profesions::Ranger :
      writeLine("Ranger");
      break;
    case dnd::profesions::Rogue :
      writeLine("Rogue");
      break;
    case dnd::profesions::Sorcerer :
      writeLine("Sorcerer");
      break;
    case dnd::profesions::Warlock :
      writeLine("Warlock");
      break;
    case dnd::profesions::Wizard :
      writeLine("Wizard");
      break;
    default:
      writeLine("You're a special snowflake ^^");
      break;
  }
}

void sheet::printAllignment(dnd::allignments allignment){
  switch(allignment){
    case dnd::allignments::LawfullGood :
      writeLine("Lawfull Good");
      break;
    case dnd::allignments::NeutralGood :
      writeLine("Neutral Good");
      break;
    case dnd::allignments::ChaoticGood :
      writeLine("Chaotic Good");
      break;
    case dnd::allignments::LawfullNeutral :
      writeLine("Lawfull Neutral");
      break;
    case dnd::allignments::Neutral :
      writeLine("Neutral");
      break;
    case dnd::allignments::ChaoticNeutral :
      writeLine("Chaotic Neutral");
      break;
    case dnd::allignments::LawfullEvil :
      writeLine("Lawfull Evil");
      break;
    case dnd::allignments::NeutralEvil :
      writeLine("Neutral Evil");
      break;
    case dnd::allignments::ChaoticEvil :
      writeLine("Chaotic Evil");
      break;
    default:
      writeLine("You're a special snowflake ^^");
      break;
  }
}

void sheet::printLanguage(dnd::languages language){
  switch(language){
    case dnd::languages::Common :
      writeLine("Common");
      break;
    case dnd::languages::Dwarvish :
      writeLine("Dwarvish");
      break;
    case dnd::languages::Elvish :
      writeLine("Elvish");
      break;
    case dnd::languages::Giant :
      writeLine("Giant");
      break;
    case dnd::languages::Gnomish :
      writeLine("Gnomish");
      break;
    case dnd::languages::Goblin :
      writeLine("Goblin");
      break;
    case dnd::languages::Halfling :
      writeLine("Halfling");
      break;
    case dnd::languages::Orc :
      writeLine("Orc");
      break;
    default:
      writeLine("You're a special snowflake ^^");
      break;
  }
}

void sheet::printName(){
  for(auto letter : name){
    hwlib::cout << letter;
  }
}


void sheet::printAll(){
  hwlib::cout << "Character name : ";
  printName();
  hwlib::cout << hwlib::endl << "Race : ";
  printRace(race);
  hwlib::cout << "Class : ";
  printProfesion(profesion);
  hwlib::cout << "Allignment : ";
  printAllignment(allignment);
  hwlib::cout << "Spoken languages :" << hwlib::endl;
  for (auto language : spokenLanguages){
    printLanguage(language);
  }
}

std::array<uint8_t,16> sheet::getMostToArrayUint(){
  std::array<uint8_t,16> returnMe = {
    static_cast<uint8_t>(race),
    static_cast<uint8_t>(profesion),
    static_cast<uint8_t>(allignment),
    static_cast<uint8_t>(spokenLanguages[0]),
    static_cast<uint8_t>(spokenLanguages[1])
  };
  return returnMe;
}

std::array<uint8_t,32> sheet::getNameToArrayUint(){
  std::array<uint8_t,32> returnMe = {};
  for (uint8_t i = 0; i < (name.size() - 1); i++){
    returnMe[i] = name[i];
  }
  return returnMe;
}

void sheet::setMostFromArrayUint(std::array<uint8_t, 16> info){
  race = static_cast<dnd::races>(info[0]);
  profesion = static_cast<dnd::profesions>(info[1]);
  allignment = static_cast<dnd::allignments>(info[2]);
  spokenLanguages[0] = static_cast<dnd::languages>(info[3]);
  spokenLanguages[1] = static_cast<dnd::languages>(info[4]);
}

void sheet::setNameFromArrayUint(std::array<uint8_t,32> info){
  std::array<char,32> newName = {};
  for (size_t i = 0; i < 32; i++){
    newName[i] = (char)info[i];
  }
  name = newName;
}

dnd::races chooseRace(){
  writeLine("Available Races    :");
  writeLine("Hill Dwarf         : 0");
  writeLine("Mountain Dwarf     : 1");
  writeLine("High Elf           : 2");
  writeLine("Wood Elf           : 3");
  writeLine("Dark Elf           : 4");
  writeLine("Lightfoot Halfling : 5");
  writeLine("Stout Halfling     : 6");
  writeLine("Human              : 7");
  writeLine("Dragonborn         : 8");
  writeLine("Forest Gnome       : 9");
  writeLine("Rock Gnome         : 10");
  writeLine("Half-Elf           : 11");
  writeLine("Half-Orc           : 12");
  writeLine("Thiefling          : 13");
  return static_cast<dnd::races>(askUserToUint8("Pick a race :"));
}

dnd::profesions chooseProfesion(){
  writeLine("Available Classes :");
  writeLine("Barbarian    : 0");
  writeLine("Bard         : 1");
  writeLine("Cleric       : 2");
  writeLine("Druid        : 3");
  writeLine("Fighter      : 4");
  writeLine("Monk         : 5");
  writeLine("Paladin      : 6");
  writeLine("Ranger       : 7");
  writeLine("Rogue        : 8");
  writeLine("Sorcerer     : 9");
  writeLine("Warlock      : 10");
  writeLine("Wizard       : 11");
  return static_cast<dnd::profesions>(askUserToUint8("Pick a class :"));
}

dnd::allignments chooseAllignment(){
  writeLine("Lawfull Good     : 0");
  writeLine("Neutral Good     : 1");
  writeLine("Chaotic Good     : 2");
  writeLine("Lawfull Neutral  : 3");
  writeLine("Neutral          : 4");
  writeLine("Chaotic Neutral  : 5");
  writeLine("Lawfull Evil     : 6");
  writeLine("Neutral Evil     : 7");
  writeLine("Chaotic Evil     : 8");
  return static_cast<dnd::allignments>(askUserToUint8("Pick a alligment :"));
}
dnd::languages chooseLanguage(){
    writeLine("Common     : 0");
    writeLine("Dwarvish   : 1");
    writeLine("Elvish     : 2");
    writeLine("Giant      : 3");
    writeLine("Gnomish    : 4");
    writeLine("Goblin     : 5");
    writeLine("Halfling   : 6");
    writeLine("Orc        : 7");
  return static_cast<dnd::languages>(askUserToUint8("Pick a language :"));
}