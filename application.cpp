#include "application.hpp"

sheet::sheet(
  std::array<char,33> nameInput,
  std::array<char,17> hairColorInput,
  dnd::races raceInput,
  dnd::profesions profesionInput,
  dnd::allignments allignmentInput,
  std::array<dnd::languages, 2> spokenLanguagesInput
):
  name(nameInput),
  hairColor(hairColorInput),
  race(raceInput),
  profesion(profesionInput),
  allignment(allignmentInput),
  spokenLanguages(spokenLanguagesInput)
{}

void sheet::printRace(dnd::races race){
  switch (race)
  {
  case dnd::races::HillDwarf :
    hwlib::cout << "Hill Dwarf" << hwlib::endl;
    break;
  case dnd::races::MountainDwarf :
    hwlib::cout << "Mountain Dwarf" << hwlib::endl;
    break;
  case dnd::races::HighElf :
    hwlib::cout << "High Elf" << hwlib::endl;
    break;
  case dnd::races::WoodElf :
    hwlib::cout << "Wood Elf" << hwlib::endl;
    break;
  case dnd::races::DarkElf :
    hwlib::cout << "Dark Elf" << hwlib::endl;
    break;
  case dnd::races::LightfootHalfling :
    hwlib::cout << "Lightfoot Halfling" << hwlib::endl;
    break;
  case dnd::races::StoutHalfling :
    hwlib::cout << "Stout Halfling" << hwlib::endl;
    break;
  case dnd::races::Human :
    hwlib::cout << "Human" << hwlib::endl;
    break;
  case dnd::races::Dragonborn :
    hwlib::cout << "Dragonborn" << hwlib::endl;
    break;
  case dnd::races::ForestGnome :
    hwlib::cout << "Forest Gnome" << hwlib::endl;
    break;
  case dnd::races::RockGnome :
    hwlib::cout << "Rock Gnome" << hwlib::endl;
    break;
  case dnd::races::HalfElf :
    hwlib::cout << "Half Elf" << hwlib::endl;
    break;
  case dnd::races::HalfOrc :
    hwlib::cout << "Half Orc" << hwlib::endl;
    break;
  case dnd::races::Thiefling :
    hwlib::cout << "Thiefling" << hwlib::endl;
    break;
  default:
    hwlib::cout << "You're a special snowflake ^^" << hwlib::endl;
    break;
  }
}

void sheet::printProfesion(dnd::profesions profesion){
  switch(profesion)
  {
    case dnd::profesions::Barbarian :
      hwlib::cout << "Barbarian" << hwlib::endl;
      break;
    case dnd::profesions::Bard :
      hwlib::cout << "Bard" << hwlib::endl;
      break;
    case dnd::profesions::Cleric :
      hwlib::cout << "Cleric" << hwlib::endl;
      break;
    case dnd::profesions::Druid :
      hwlib::cout << "Druid" << hwlib::endl;
      break;
    case dnd::profesions::Fighter :
      hwlib::cout << "Fighter" << hwlib::endl;
      break;
    case dnd::profesions::Monk :
      hwlib::cout << "Monk" << hwlib::endl;
      break;
    case dnd::profesions::Paladin :
      hwlib::cout << "Paladin" << hwlib::endl;
      break;
    case dnd::profesions::Ranger :
      hwlib::cout << "Ranger" << hwlib::endl;
      break;
    case dnd::profesions::Rogue :
      hwlib::cout << "Rogue" << hwlib::endl;
      break;
    case dnd::profesions::Sorcerer :
      hwlib::cout << "Sorcerer" << hwlib::endl;
      break;
    case dnd::profesions::Warlock :
      hwlib::cout << "Warlock" << hwlib::endl;
      break;
    case dnd::profesions::Wizard :
      hwlib::cout << "Wizard" << hwlib::endl;
      break;
    default:
      hwlib::cout << "You're a special snowflake ^^" << hwlib::endl;
      break;
  }
}

void sheet::printAllignment(dnd::allignments allignment){
  switch(allignment)
  {
    case dnd::allignments::LawfullGood :
      hwlib::cout << "Lawfull Good" << hwlib::endl;
      break;
    case dnd::allignments::NeutralGood :
      hwlib::cout << "Neutral Good" << hwlib::endl;
      break;
    case dnd::allignments::ChaoticGood :
      hwlib::cout << "Chaotic Good" << hwlib::endl;
      break;
    case dnd::allignments::LawfullNeutral :
      hwlib::cout << "Lawfull Neutral" << hwlib::endl;
      break;
    case dnd::allignments::Neutral :
      hwlib::cout << "Neutral" << hwlib::endl;
      break;
    case dnd::allignments::ChaoticNeutral :
      hwlib::cout << "Chaotic Neutral" << hwlib::endl;
      break;
    case dnd::allignments::LawfullEvil :
      hwlib::cout << "Lawfull Evil" << hwlib::endl;
      break;
    case dnd::allignments::NeutralEvil :
      hwlib::cout << "Neutral Evil" << hwlib::endl;
      break;
    case dnd::allignments::ChaoticEvil :
      hwlib::cout << "Chaotic Evil" << hwlib::endl;
      break;
    default:
      hwlib::cout << "You're a special snowflake ^^" << hwlib::endl;
      break;
  }
}

void sheet::printLanguage(dnd::languages language){
  switch(language)
  {
    case dnd::languages::Common :
      hwlib::cout << "Common" << hwlib::endl;
      break;
    case dnd::languages::Dwarvish :
      hwlib::cout << "Dwarvish" << hwlib::endl;
      break;
    case dnd::languages::Elvish :
      hwlib::cout << "Elvish" << hwlib::endl;
      break;
    case dnd::languages::Giant :
      hwlib::cout << "Giant" << hwlib::endl;
      break;
    case dnd::languages::Gnomish :
      hwlib::cout << "Gnomish" << hwlib::endl;
      break;
    case dnd::languages::Goblin :
      hwlib::cout << "Goblin" << hwlib::endl;
      break;
    case dnd::languages::Halfling :
      hwlib::cout << "Halfling" << hwlib::endl;
      break;
    case dnd::languages::Orc :
      hwlib::cout << "Orc" << hwlib::endl;
      break;
    default:
      hwlib::cout << "You're a special snowflake ^^" << hwlib::endl;
      break;
  }
}

void sheet::printName(){
  for(auto letter : name){
    hwlib::cout << letter;
  }
}

void sheet::printHairColor(){
  for(auto letter : hairColor){
    hwlib::cout << letter;
  }
}

void sheet::printAll(){
  hwlib::cout << "Character name : ";
  printName();
  hwlib::cout << hwlib::endl << "Hair Color : ";
  printHairColor();
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