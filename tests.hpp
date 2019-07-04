#ifndef TESTS_HPP
#define TESTS_HPP

#include <hwlib.hpp>
#include "rc522.hpp"
#include "reader.hpp"
#include "application.hpp"

///\brief
///Output appropriate text to rc522::status
///\default
///This function prints out text that is appropriate for the received rc522::status.
void outputStatus(rc522::status recStatus);

///\brief
/// Test Select card
///\details
///Try to select a card.\n
///You need to supply a rc522::status object, a rc522 reader object, a mifare::card object and a optional bool.\n
bool trySelect(rc522::status & fStatus, rc522 & reader, mifare::card & card, bool showInfo);
///\brief
/// Test Select card
///\details
///Try to select a card.\n
///You need to supply a rc522::status object, a rc522 reader object, a mifare::card object, a uint8_t value and a optional bool.\n
bool tryAuthenticate(rc522::status & fStatus, rc522 & reader, mifare::card & card, uint8_t block, bool showInfo);
///\brief
/// Test Select card
///\details
///Try to select a card.\n
///You need to supply a rc522::status object, a rc522 reader object, a uint8_t value and a optional bool.\n
void tryRead(rc522::status & fStatus, rc522 & reader, uint8_t block, bool showInfo);
///\brief
/// Test Select card
///\details
///Try to select a card.\n
///You need to supply a rc522::status object, a rc522 reader object, a uint8_t value, a array of type uint8_t with a size of 16 and a optional bool.\n
bool tryWrite(rc522::status & fStatus, rc522 & reader, uint8_t block, std::array<uint8_t,16> writeThis, bool showInfo);

///\brief
/// A small demo
///\default
///This function reads a block from a mifare card then writes supplied data to that block and then reads it again.\n
///You need to supply a rc522::status, \n
///next you need to supply a mifare::card and a uint8_t value for the block you wish to write to.\n
///you also need to supply a array with uint8_t values with a size of 16.
///You can also supply a bool, if the bool is true then this function will print text that shows what is happening,\n
/// the default value is false.
void demo(rc522::status & fStatus, rc522 & reader, mifare::card & card, uint8_t block, std::array<uint8_t,16> writeThis, bool showInfo);

sheet testSheet();

#endif