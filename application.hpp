#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <hwlib.hpp>

namespace dnd {
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

class sheet{
  public:
    std::array<char,33> name;
    std::array<char,17> hairColor;
    dnd::races race;
    dnd::profesions profesion;
    dnd::allignments allignment;
    std::array<dnd::languages, 2> spokenLanguages;
    sheet(
      std::array<char,33> name,
      std::array<char,17> hairColor,
      dnd::races race,
      dnd::profesions profesion,
      dnd::allignments allignment,
      std::array<dnd::languages, 2> spokenLanguages
    );
    void printRace(dnd::races race);
    void printProfesion(dnd::profesions profesion);
    void printAllignment(dnd::allignments allignment);
    void printLanguage(dnd::languages language);
    void printName();
    void printHairColor();
    void printAll();
};

#endif