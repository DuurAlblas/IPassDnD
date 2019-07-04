// ==========================================================================
//
// File      : rc522.hpp
// Part of   : RFID library
// Copyright : Duur Alblas (c) 2019
// Contact   : d.c.alblas@gmail.com
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
#ifndef RC522_HPP
#define RC522_HPP

#include "supp.hpp"
#include "reader.hpp"

///\brief
///rc522 chip class inherits from spiReader
///\details
///A class that inherits from the spiReader ADT class.
///We need to supply the parameters for the spiReader class and define the read and write functions.
///This class supplies all the registers and basic functionality for the rc522 chip.
class rc522 : public spiReader {
  private:
    uint8_t read( const uint8_t regAddr);
    void write(   const uint8_t regAddr, const uint8_t data);
  protected:
    enum class version{
      error = 0,
      version1,
      version2
    };
  public:
    ///\brief
    ///A enum class with Addressable Registers
    ///\details
    ///This enum class supports all the supplied registers from the documentation of the chip.
    enum class registers {
      // Command and Status
      Reserved_00           = 0x00,
      CommandReg            = 0x01,
      ComlEnReg             = 0x02,
      DivlEnReg             = 0x03,
      ComIrqReg             = 0x04,
      DivIrqReg             = 0x05,
      ErrorReg              = 0x06,
      Status1Reg            = 0x07,
      Status2Reg            = 0x08,
      FIFODataReg           = 0x09,
      FIFOLevelReg          = 0x0A,
      WaterLevelReg         = 0x0B,
      ControlReg            = 0x0C,
      BitFramingReg         = 0x0D,
      CollReg               = 0x0E,
      Reserved_0F           = 0x0F
    };
    ///\brief
    ///A enum class with register commands for the CommandReg
    ///\details
    ///This enum class supports all the supplied command from the documentation of the chip for the CommandReg.
    enum class regCommands {
      Idle                  = 0x00,
      Mem                   = 0x01,
      GenerateRandomID      = 0x02,
      CalcCRC               = 0x03,
      Transmit              = 0x04,
      NoCmdChange           = 0x07,
      Receive               = 0x08,
      Transceive            = 0x0C,
      Reserved              = 0x0D,
      MFAuthent             = 0x0E,
      SoftReset             = 0x0F
    };
    ///\brief
    ///A enum class with Addressable Commands
    ///\details
    ///This enum class supports all the supplied commands from the documentation of the chip.
    enum class commands {
      //Command
      Reserved_10           = 0x10,
      ModeReg               = 0x11,
      TxModeReg             = 0x12,
      RxModeReg             = 0x13,
      TxControlReg          = 0x14,
      TxASKReg              = 0x15,
      TxSelReg              = 0x16,
      RxSelReg              = 0x17,
      RxThresholdReg        = 0x18,
      DemodReg              = 0x19,
      Reserved_1A           = 0x1A,
      Reserved_1B           = 0x1B,
      MfTxReg               = 0x1C,
      MfRxReg               = 0x1D,
      Reserved_1E           = 0x1E,
      SerialSpeedReg        = 0x1F
    };
    ///\brief
    ///A enum class with Addressable Configuration registers
    ///\details
    ///This enum class supports all the supplied configuration registers from the documentation of the chip.
    enum class configuration {
      //Configuration
      Reserved_20           = 0x20,
      CRCResultReg_High     = 0x21,
      CRCResultReg_Low      = 0x22,
      Reserved_23           = 0x23,
      ModWidthReg           = 0x24,
      Reserved_25           = 0x25,
      RFCfgReg              = 0x26,
      GsNReg                = 0x27,
      CWGsPReg              = 0x28,
      ModGsPReg             = 0x29,
      TModeReg              = 0x2A,
      TPrescalerReg         = 0x2B,
      TReloadReg_High       = 0x2C,
      TReloadReg_Low        = 0x2D,
      TCounterValReg_High   = 0x2E,
      TCounterValReg_Low    = 0x2F
    };
    ///\brief
    ///A enum class with Addressable Test registers
    ///\details
    ///This enum class supports all the supplied test registers from the documentation of the chip.
    enum class test {
      //Test Register
      Reserved_30           = 0x30,
      TestSel1Reg           = 0x31,
      TestSel2Reg           = 0x32,
      TestPinEnReg          = 0x33,
      TestPinValueReg       = 0x34,
      TestBusReg            = 0x35,
      AutoTestReg           = 0x36,
      VersionReg            = 0x37,
      AnalogTestReg         = 0x38,
      TestDAC1Reg           = 0x39,
      TestDAC2Reg           = 0x3A,
      TestADCReg            = 0x3B,
      Reserved_3C           = 0x3C,
      Reserved_3D           = 0x3D,
      Reserved_3E           = 0x3E,
      Reserved_3F           = 0x3F
    };

    ///\brief
    ///The default constructor
    ///\details
    ///You need to supply the nss pin_out pin and the spiBus spi_bus_bit_banged_sclk_mosi_miso\n
    ///for the spiReader class since there are no default values.
    rc522(
      hwlib::target::pin_out & nssInput,
      hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
    );

    ///\brief
    ///A read Register function returns uint8_t
    ///\details
    ///The readReg function using the commands enum class.\n
    ///You need to supply a rc522::commands to read from, the functions returns a uint8_t.
    uint8_t readReg(      rc522::commands       regAddr);
    ///\brief
    ///A read Register function returns uint8_t
    ///\details
    ///The readReg function using the registers enum class.\n
    ///You need to supply a rc522::registers to read from, the functions returns a uint8_t.
    uint8_t readReg(      rc522::registers      regAddr);
    ///\brief
    ///A read Register function returns uint8_t
    ///\details
    ///The readReg function using the configuration enum class.\n
    ///You need to supply a rc522::configuration to read from, the functions returns a uint8_t.
    uint8_t readReg(      rc522::configuration  regAddr);
    ///\brief
    ///A read Register function returns uint8_t
    ///\details
    ///The readReg function using the test enum class.\n
    ///You need to supply a rc522::test to read from, the functions returns a uint8_t.
    uint8_t readReg(      rc522::test           regAddr);

    ///\brief
    ///A write Register function
    ///\details
    ///The writeReg function using the commands enum class.\n
    ///You need to supply a rc522::commands to write to.\n
    ///You also need to supply a uint8_t containing the 8 bits to write to the register.\n
    void writeReg(        rc522::commands       regAddr, uint8_t data);
    ///\brief
    ///A write Register function
    ///\details
    ///The writeReg function using the registers enum class.\n
    ///You need to supply a rc522::registers to write to.\n
    ///You also need to supply a uint8_t containing the 8 bits to write to the register.\n
    void writeReg(        rc522::registers      regAddr, uint8_t data);
    ///\brief
    ///A write Register function
    ///\details
    ///The writeReg function using the configuration enum class.\n
    ///You need to supply a rc522::configuration to write to.\n
    ///You also need to supply a uint8_t containing the 8 bits to write to the register.\n
    void writeReg(        rc522::configuration  regAddr, uint8_t data);
    ///\brief
    ///A write Register function
    ///\details
    ///The writeReg function using the test enum class.\n
    ///You need to supply a rc522::test to write to.\n
    ///You also need to supply a uint8_t containing the 8 bits to write to the register.\n
    void writeReg(        rc522::test           regAddr, uint8_t data);
    ///\brief
    ///A write Register function
    ///\details
    ///The writeReg function using the registers enum class, specifically for the CommandReg.\n
    ///You need to supply a rc522::registers to write to.\n
    ///You also need to supply a rc522::regCommands to write to the register.\n
    void writeReg(        rc522::registers      regAddr, rc522::regCommands data);

    ///\brief
    ///A write Register function for array of data
    ///\details
    ///The writeReg function using the registers enum class, specifically for the \FIFODataReg.\n
    ///You need to supply a rc522::registers to write to.\n
    ///You also need to supply a array with type uint8_t and with a maximum size of 64 to write to the register.\n
    template<unsigned int N>
    void writeReg(rc522::registers regAddr, std::array<uint8_t,N> data){
      static_assert(N < 64,"The supplied data array is too large.");
      for (auto byte : data){
        write(static_cast<uint8_t>(regAddr), byte);
      }
    }

    ///\brief
    ///Set a register bit with mask
    ///\details
    ///The setRegBitMask sets certain bits with the supplied mask.\n
    ///You need to supply a rc522::commands and a uint8_t value as the mask.\n
    ///The mask will set the bits that are not set in the supplied rc522::commands register,\n
    ///and will not unset bits that are set.
    void setRegBitMask(   rc522::commands       regAddr, uint8_t mask);
    ///\brief
    ///Set a register bit with mask
    ///\details
    ///The setRegBitMask sets certain bits with the supplied mask.\n
    ///You need to supply a rc522::registers and a uint8_t value as the mask.\n
    ///The mask will set the bits that are not set in the supplied rc522::registers register,\n
    ///and will not unset bits that are set.
    void setRegBitMask(   rc522::registers      regAddr, uint8_t mask);
    ///\brief
    ///Set a register bit with mask
    ///\details
    ///The setRegBitMask sets certain bits with the supplied mask.\n
    ///You need to supply a rc522::configuration and a uint8_t value as the mask.\n
    ///The mask will set the bits that are not set in the supplied rc522::configuration register,\n
    ///and will not unset bits that are set.
    void setRegBitMask(   rc522::configuration  regAddr, uint8_t mask);
    ///\brief
    ///Set a register bit with mask
    ///\details
    ///The setRegBitMask sets certain bits with the supplied mask.\n
    ///You need to supply a rc522::test and a uint8_t value as the mask.\n
    ///The mask will set the bits that are not set in the supplied rc522::test register,\n
    ///and will not unset bits that are set.
    void setRegBitMask(   rc522::test           regAddr, uint8_t mask);

    ///\brief
    ///Unset a register bit with mask
    ///\details
    ///The unsetRegBitMask unsets certain bits with the supplied mask.\n
    ///You need to supply a rc522::commands and a uint8_t value as the mask.\n
    ///The mask will unset the bits that are set in the supplied rc522::commands register,\n
    ///and will not set bits that are unset.
    void unsetRegBitMask( rc522::commands       regAddr, uint8_t mask);
    ///\brief
    ///Unset a register bit with mask
    ///\details
    ///The unsetRegBitMask unsets certain bits with the supplied mask.\n
    ///You need to supply a rc522::registers and a uint8_t value as the mask.\n
    ///The mask will unset the bits that are set in the supplied rc522::registers register,\n
    ///and will not set bits that are unset.
    void unsetRegBitMask( rc522::registers      regAddr, uint8_t mask);
    ///\brief
    ///Unset a register bit with mask
    ///\details
    ///The unsetRegBitMask unsets certain bits with the supplied mask.\n
    ///You need to supply a rc522::configuration and a uint8_t value as the mask.\n
    ///The mask will unset the bits that are set in the supplied rc522::configuration register,\n
    ///and will not set bits that are unset.
    void unsetRegBitMask( rc522::configuration  regAddr, uint8_t mask);
    ///\brief
    ///Unset a register bit with mask
    ///\details
    ///The unsetRegBitMask unsets certain bits with the supplied mask.\n
    ///You need to supply a rc522::test and a uint8_t value as the mask.\n
    ///The mask will unset the bits that are set in the supplied rc522::test register,\n
    ///and will not set bits that are unset.
    void unsetRegBitMask( rc522::test           regAddr, uint8_t mask);

    ///\brief
    ///Turns antenna On
    ///\details
    ///The antennaOn function turn the antenna on.\n
    ///If you supply a true value for the feedback parameter the function will output a before and after state of the rc522::commands::TxControlReg.\n
    ///Using this function while the antenna is on does not turn the antenna off, so you can use it multiple times in succesion.
    void antennaOn(bool feedback);
    ///\brief
    ///Turns antenna Off
    ///\details
    ///The antennaOff function turn the antenna off.\n
    ///If you supply a true value for the feedback parameter the function will output a before and after state of the rc522::commands::TxControlReg.\n
    ///Using this function while the antenna is off does not turn the antenna on, so you can use it multiple times in succesion.
    void antennaOff(bool feedback);

    ///\brief
    ///Executes soft reset
    ///\details
    ///The softReset function performs a soft reset by writing the rc522::regCommands::SoftReset command to the rc522::registers::CommandReg register.\n
    ///We wait for a maximum of 10 loops with a wait of 25 ms so the crystal can start-up or until the power-bit is cleared.
    void softReset();
    ///\brief
    ///Initializes the chip
    ///\details
    ///We perform a softReset, and then we reset the baud rates and the modulation width.\n
    ///We also configure certain registers in preperation for when things go wrong,\n
    ///we do so by configuring the timers so we can get time outs.\n
    ///Next we configure the CRC and turn the antenna on.
    void initialize();

    ///\brief
    ///Compare supplied buffer with versions
    ///\details
    ///The compareVersion function compares the supplied buffer array with 2 arrays to see which version the user has.
    rc522::version compareVersion(std::array<uint8_t,64> buffer);

    ///\brief
    ///Initiates the chips self test
    ///\details
    ///This is the self test as described in the documentation of the rc522 chip.\n
    ///In this test we also compare the chips version with the compareVersion function.
    rc522::status selfTest();

    ///\brief
    ///Calculate CRC of array
    ///\details
    ///The calcCRC function calculates 2 CRC values based on the first and last value in the supplied array.\n
    ///You need to supply dataIn array with a maximum size of 64 and a dataOut array with a minimum size of 2.\n
    ///If your dataIn array contains a CRC you can supply the containsCrc parameter with a true value and the function will\n
    /// fill a temporary array with the data from dataIn - the last 2 bytes which contain the CRC calulations.
    ///The function returns a rc522::status, a rc522::status::SUCCESS when the CRC was successfull.
    template<unsigned int N1,unsigned int N2>
    rc522::status calcCRC(std::array<uint8_t, N1> & dataIn, std::array<uint8_t, N2> & dataOut, bool containsCrc = false) {
      static_assert(N1 < 64, "The dataIn array is too big, no space in FIFO.");
      static_assert(N2 > 1, "The dataOut array is too small, no space for CRC results.");
      std::array<uint8_t, (N1-2)> smallerIn = {};
      if (containsCrc){
        std::copy(begin(dataIn),std::prev(end(dataIn),2), begin(smallerIn));
      }

      writeReg(rc522::registers::CommandReg, rc522::regCommands::Idle);                         // Command Idle
      writeReg(rc522::registers::DivIrqReg, 0x04);                                              // DivIrqReg 0x04 to clear the CRCIrq bit
      writeReg(rc522::registers::FIFOLevelReg, 0x80);                                           // FIFOLevelReg 0x80 to empty the buffer
      if (containsCrc){
        writeReg(rc522::registers::FIFODataReg, smallerIn);
      } else {
        writeReg(rc522::registers::FIFODataReg, dataIn);                                        // FIFODataReg, data to write the data to the buffer
      }
      writeReg(rc522::registers::CommandReg, rc522::regCommands::CalcCRC);                      // CommandReg calcCRC to start the calc

      for (uint16_t i = 5000; i > 0; i--) {
        uint8_t n = readReg(rc522::registers::DivIrqReg);
        if (n & 0x04) {									                                                        // Calc is done, the CRCIrq bit is set
          writeReg(rc522::registers::CommandReg, rc522::regCommands::Idle);                     // Stop the calc for new data
          dataOut[(dataOut.size()-2)] = readReg(rc522::configuration::CRCResultReg_Low);        // put the results in the last 2 bytes of dataOut
          dataOut[(dataOut.size()-1)] = readReg(rc522::configuration::CRCResultReg_High);
          return rc522::status::SUCCESS;
        }
      }
      return rc522::status::TIMEOUTDEV;                                                         // Some time passed communications with the rc522 might be down
    }

    ///\brief
    ///Communicate with card
    ///\details
    ///This function handles communication with a card.\n
    ///You need to supply a bufSend array with a maximum size of 64,\n
    ///a bufReceive array to receive the returned data,\n
    ///a command to execute in the form of a rc522::regCommands command.\n
    ///If you want you can also send the bit frame along, its default value is set to 0 which means all bits are needed.\n
    ///You can also send the waitIrq value along, its default value is set to 0 which means that there are no interupt bits set.\n
    ///You can also send a checkCrc bool along, its default is set to false which means that the function will not check the CRC.\n
    ///The function returns a rc522::status, a rc522::status::SUCCESS the communication went successfull.
    template<unsigned int N1, unsigned int N2>
    rc522::status cardCommunication(
        std::array<uint8_t,N1> & bufSend,
        std::array<uint8_t,N2> & bufReceive,
        rc522::regCommands comData,
        uint8_t bitFraming = 0,
        uint8_t waitIrq = 0,
        bool checkCrc = false
    ){
      static_assert(N1 < 64, "bufSend array too big for FIFO register.");
      writeReg(rc522::registers::CommandReg, rc522::regCommands::Idle);
      writeReg(rc522::registers::ComIrqReg, 0x7F);
      writeReg(rc522::registers::FIFOLevelReg, 0x80);
      for (auto byte : bufSend){
        writeReg(rc522::registers::FIFODataReg, byte);
      }
      writeReg(rc522::registers::BitFramingReg, bitFraming);
      writeReg(rc522::registers::CommandReg, comData);

      if (comData == rc522::regCommands::Transceive){
        setRegBitMask(rc522::registers::BitFramingReg, 0x80); // start communication transceive
      }

  // opdelen in kleinere functions ivm leesbaarheid , groeperen low prio
      // Wait for a response or time out
      uint16_t i;
      for (i = 2000; i > 0; i--) {
        uint8_t regIrq = readReg(rc522::registers::ComIrqReg);
        if (regIrq & waitIrq)  {break;}
        if (regIrq & 0x01)     {return rc522::status::TIMEOUTCOM;}
      }
      if (i == 0)              {return rc522::status::TIMEOUTDEV;}

      uint8_t errorVal = readReg(rc522::registers::ErrorReg); // Check for errors except collision
      if (errorVal & 0x13){return rc522::status::ERROR;}
      // Get returned data
      uint8_t _validBits = 0;
      uint8_t levelFIFO = readReg(rc522::registers::FIFOLevelReg);

      if (levelFIFO > bufReceive.size()) {return rc522::status::NO_SPACE;}
      for (uint8_t i = 0; i < levelFIFO; i++){
        bufReceive[i] = readReg(rc522::registers::FIFODataReg);
      }
      // Check the number of valid bits in the last received byte
      _validBits = readReg(rc522::registers::ControlReg) & 0x07;
      if (bitFraming) {bitFraming = _validBits;}

      // Validate CRC if checkCrc true
      if (bufReceive.size() && checkCrc) {
        if (bufReceive.size() < 2 || _validBits != 0) {return rc522::status::CRC_ERROR;} // We need the CRC value and the 8 bits of the last byte
        // do the calculation and save it
        std::array<uint8_t,2> calcBuf = {};
        rc522::status caclStatus = calcCRC(bufReceive, calcBuf,true);
        if (caclStatus != rc522::status::SUCCESS) {
          return caclStatus;
        }
        if ((calcBuf[0] != bufReceive[bufReceive.size() - 2] ) || (calcBuf[1] != bufReceive[bufReceive.size() - 1])) {
          return rc522::status::CRC_ERROR;
        }
      }
      return rc522::status::SUCCESS;
    }

    ///\brief
    ///Tranceives (Transmit & Receive) to/from card
    ///\details
    ///This function calls the cardCommunication function with some default values such as the rc522::regCommands::Transceive command.\n
    ///You need to supply a bufSend array with a maximum size of 64.\n
    ///You also need to supply a bufReceive array for the returned data.\n
    ///If you want you can also send the bit frame along, its default value is set to 0 which means all bits are needed.\n
    ///You can also send a checkCrc bool along, its default is set to false which means that the function will not check the CRC.\n
    ///The function will set the waitIrq to 0x30 which sets the RxIRq and IdleIRq bits.
    template<unsigned int N1, unsigned int N2>
    rc522::status cardTransceive(
        std::array<uint8_t,N1> & bufSend,
        std::array<uint8_t,N2> & bufReceive,
        uint8_t bitFraming = 0,
        bool checkCrc = false
    ){
      static_assert(N1 < 64, "bufSend is too big for the FIFO register.");
      uint8_t waitIrq = 0x30;
      return cardCommunication(bufSend,bufReceive,rc522::regCommands::Transceive,bitFraming,waitIrq,checkCrc);
    }

    ///\brief
    ///Tranceives (Transmit & Receive) to/from mifare card for array
    ///\details
    ///This function calls the cardCommunication function with some default values such as the rc522::regCommands::Transceive command.\n
    ///You need to supply a bufComData array containing a single or multiple mifare::command 's.\n
    ///You also need to supply a bufReceive array for the returned data.\n
    ///If you want you can also send the bit frame along, its default value is set to 0 which means all bits are needed.\n
    ///You can also send a checkCrc bool along, its default is set to false which means that the function will not check the CRC.\n
    ///The function will set the waitIrq to 0x30 which sets the RxIRq and IdleIRq bits.
    template<unsigned int N1, unsigned int N2>
    rc522::status cardTransceive(
        std::array<mifare::command,N1> & bufComData,
        std::array<uint8_t,N2> & bufReceive,
        uint8_t bitFraming = 0,
        bool checkCrc = false
    ){
      uint8_t waitIrq = 0x30;
      std::array<uint8_t, N1> bufSend = {};
      for (uint8_t i = 0; i < N1; i++) {
        bufSend[i] = static_cast<uint8_t>(bufComData[i]);
      }
      return cardCommunication(bufSend,bufReceive,rc522::regCommands::Transceive,bitFraming,waitIrq,checkCrc);
    }

    ///\brief
    ///Wake up the card
    ///\details
    ///This function is used to wake a mifare card up.\n
    ///You need to supply a mifare::command.\n
    ///We set the bit frame to 7 because in the mifare protocol the REQA and WUPA need to be in a 7 bits frame.\n
    ///The function return a rc522::status, rc522::status::SUCCESS if we succesfully woke the card up.
    rc522::status wakeCard(mifare::command comData);

    ///\brief
    ///Select a mifare card
    ///\details
    ///This function is used to select a mifare card.\n
    ///You need to supply a mifare::card in which the selected cards UID will be stored.\n
    ///First we send a anti-colision command to the card which will return a UID with a back character check.\n
    ///After checking the BCC we store the UID in the mifare::card.\n
    ///Next we try to select the card so we send the select command including the CRC values.\n
    ///For now the function only support the MF1S503yX version which has a NUID with a size of 4 bytes.
    ///This function returns a rc522::status, a rc522::status::SUCCESS means the select action was successfull.
    rc522::status selectCard(mifare::card & curCard);

    ///\brief
    ///Authenticate a block in mifare card
    ///\details
    ///This function tries to authenticate a block on a mifare card.\n
    ///You need to either supply a mifare::command::authKA or mifare::command::authKB mifare::command.\n
    ///You also need to supply a uint8_t value containing the address of the block you want to authenticate.\n
    ///Next you need to supply a mifare::card which will be used to get the key associated with the card,\n
    ///the maximum amount of available block and the UID.\n
    ///This function returns a rc522::status, a rc522::status::SUCCESS means the authenticate action was successfull.
    rc522::status authenticateCard(mifare::command comData, uint8_t blockAddr, mifare::card cardData);

    ///\brief
    ///Stops Crypto1 unit
    ///\details
    ///This function unsets the mifare Crypto1 bit.
    void stopCrypto();

    ///\brief
    ///Read a block from mifare card
    ///\details
    ///This function reads a single block from a mifare card.\n
    ///You need to supply a uint8_t value which contains the block you want to read from.\n
    ///You also need to supply a bufReceive array with a minimum size of 18.\n
    ///We need at least 18 bytes, 16 for all the bytes from the block and 2 for the CRC at the end.
    ///This function returns a rc522::status, a rc522::status::SUCCESS means the read action was successfull.
    template<unsigned int N>
    rc522::status readBlock(uint8_t blockAddr, std::array<uint8_t,N> & bufReceive){
      rc522::status fStatus;
      // explain why deze size
      if ( N < 18){
        return rc522::status::NO_SPACE;
      }
      std::array<uint8_t, 2> bufCom = {
        static_cast<uint8_t>(mifare::command::read),
        blockAddr
      };
      std::array<uint8_t,4>bufSend = {bufCom[0],bufCom[1]};
      fStatus = calcCRC(bufCom,bufSend);
      if (fStatus != rc522::status::SUCCESS){return fStatus;}
      return cardTransceive(bufSend,bufReceive,0,true);
    }

    ///\brief
    ///Write to block on mifare card
    ///\details
    ///This function writes 16 bytes to a block on a mifare card.\n
    ///You need to supply a uint8_t value containing the block address.\n
    ///You also need to supply a dataSend array a maximum size of 16.\n
    ///This function will first send a mifare::command::write to the card.\n
    ///Then we wait for 1 ms so the card has time to send  ACK or NACK.\n
    ///Next we write the data to the card.\n
    ///This function returns a rc522::status, a rc522::status::SUCCESS means the write action was successfull.
    template<unsigned int N>
    rc522::status writeBlock(uint8_t blockAddr, std::array<uint8_t,N> & dataSend){
      static_assert(N < 17,"There is not enough space in the block on the mifare card.");
      rc522::status fStatus;
      std::array<uint8_t,18> bufReceive = {};

      //Create the buffer containing the command to execute and the CRC
      std::array<uint8_t, 2> bufCom = {
        static_cast<uint8_t>(mifare::command::write),
        blockAddr
      };

    // opdelen als er tijd is
      std::array<uint8_t,4>bufSendCom = {bufCom[0],bufCom[1]};
      fStatus = calcCRC(bufCom,bufSendCom);
      if (fStatus != rc522::status::SUCCESS){return fStatus;}
      fStatus = cardTransceive(bufSendCom,bufReceive);
      if (fStatus != rc522::status::SUCCESS){return fStatus;}

      //Give it time to return the ACK
      hwlib::wait_ms(1);


      //Create the buffer containing the data to send and the CRC
      std::array<uint8_t,(N+2)>bufSendData = {};
      std::copy(begin(dataSend),end(dataSend),begin(bufSendData));
      fStatus = calcCRC(dataSend,bufSendData);
      if (fStatus != rc522::status::SUCCESS){return fStatus;}
      return cardTransceive(bufSendData,bufReceive);
    }

    ///\brief
    ///Try a function x times
    ///\details
    ///This function tries to execute x times until the rc522::status we receive is a rc522::status::SUCCESS.\n
    ///You need to supply a lambda function that needs the return type of the function to be rc522::status.\n
    ///You can also supply a uint8_t value which is the amount of times this function will try to exectute this function,\n
    /// default value is 10.\n
    ///This function returns a rc522::status, a rc522::status::SUCCESS means the function was executed successfully.
    template<typename F>
    rc522::status tryFunction(F f , uint8_t tryFor = 10){
      uint8_t countTries = 0;
      rc522::status functionStatus;
      while( countTries < tryFor){
         functionStatus = f();
        if (functionStatus != rc522::status::SUCCESS){
          printPatience(3);
          countTries++;
        } else if (functionStatus == rc522::status::SUCCESS){
          return functionStatus ;
        }
      }
      return functionStatus;
    }
};

#endif