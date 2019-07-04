// ==========================================================================
//
// File      : application.hpp
// Part of   : RFID library
// Copyright : Duur Alblas (c) 2019
// Contact   : duur.alblas@student.hu.nl
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <hwlib.hpp>
#include "supp.hpp"

namespace dnd {
  ///\brief
  ///Playable races
  ///\details
  ///This enum class contains various races and can be expanded up to 127 races.
  enum class races {
    HillDwarf = 0x00,
    MountainDwarf,
    HighElf,
    WoodElf,
    DarkElf,
    LightfootHalfling,
    StoutHalfling,
    Human,
    Dragonborn,
    ForestGnome,
    RockGnome,
    HalfElf,
    HalfOrc,
    Thiefling
  };
  ///\brief
  ///Playable profesions
  ///\details
  ///This enum class contains various profesions and can be expanded up to 127 profesions.
  enum class profesions {
    Barbarian = 0x00,
    Bard,
    Cleric,
    Druid,
    Fighter,
    Monk,
    Paladin,
    Ranger,
    Rogue,
    Sorcerer,
    Warlock,
    Wizard
  };
  ///\brief
  ///Playable allignments
  ///\details
  ///This enum class contains all the allignments.
  enum class allignments {
    LawfullGood = 0x00,
    NeutralGood,
    ChaoticGood,
    LawfullNeutral,
    Neutral,
    ChaoticNeutral,
    LawfullEvil,
    NeutralEvil,
    ChaoticEvil
  };
  ///\brief
  ///Usable languages
  ///\details
  ///This enum class contains various languages and can be expanded up to 127 languages.
  enum class languages {
    Common = 0x00,
    Dwarvish,
    Elvish,
    Giant,
    Gnomish,
    Goblin,
    Halfling,
    Orc
  };
};

///\brief
///A class to contain character sheet data
///\details
///This class stores data associated with a character sheet.\n
///This class is easily expandable to support more stats and dnd enums.
class sheet{
  private:
    std::array<char,32> name;
    dnd::races race;
    dnd::profesions profesion;
    dnd::allignments allignment;
    std::array<dnd::languages, 2> spokenLanguages;
  public:
    ///\brief
    ///The default constructor
    ///\details
    ///This is the default constructor, you need to supply everything since there are no default values.
    sheet(
      std::array<char,32> name,
      dnd::races race,
      dnd::profesions profesion,
      dnd::allignments allignment,
      std::array<dnd::languages, 2> spokenLanguages
    );
    ///\brief
    ///Print race
    ///\details
    ///This function prints some text relative to the supplied race.
    void printRace(dnd::races race);
    ///\brief
    ///Print profesion
    ///\details
    ///This function prints some text relative to the supplied profesion.
    void printProfesion(dnd::profesions profesion);
    ///\brief
    ///Print allignment
    ///\details
     //This function prints some text relative to the supplied allignment.
    void printAllignment(dnd::allignments allignment);
    ///\brief
    ///Print language
    ///\details
    //This function prints some text relative to the supplied language.
    void printLanguage(dnd::languages language);
    ///\brief
    ///Print stored name
    ///\details
    ///This function prints the name currently stored in the class.
    void printName();
    ///\brief
    ///Print all data in class
    ///\details
    ///This function uses all the aforementioned print funcionts to print all the data currently stored in the class.
    void printAll();

    ///\brief
    ///Returns class data in uint8_t array
    ///\details
    ///This function stores all the data except for the name in a array of type uint8_t and a exact size of 16 elements,\n
    ///and then returns the array.
    std::array<uint8_t,16> getMostToArrayUint();
    ///\brief
    ///Return name in uint8_t array
    ///\details
    ///This function stores the name in a array of type uint8_t and a exact size of 32 elements,\n
    ///and then returns the array.
    std::array<uint8_t,32> getNameToArrayUint();

    ///\brief
    ///Set class data from uint8_t array
    ///\details
    ///This function sets most of the classes data using a array of type uint8_t with a size of 16.
    void setMostFromArrayUint(std::array<uint8_t, 16> info);
    ///\brief
    ///Set class name from uint8_t array
    ///\details
    ///This function sets the classes name using a array of type uint8_t with a size of 32.
    void setNameFromArrayUint(std::array<uint8_t, 32> info);
};
///\brief
///Dialog to choose a race
///\details
///A function to choose a race during character creation.
dnd::races chooseRace();
///\brief
///Dialog to choose a profesion
///\details
///A function to choose a profesion during character creation.
dnd::profesions chooseProfesion();
///\brief
///Dialog to choose a allignment
///\details
///A function to choose a allignment during character creation.
dnd::allignments chooseAllignment();
///\brief
///Dialog to choose a language
///\details
///A function to choose a language during character creation.
dnd::languages chooseLanguage();

#endif