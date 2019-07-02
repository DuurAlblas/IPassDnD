#ifndef RC522_HPP
#define RC522_HPP

#include "supp.hpp"
#include "reader.hpp"
#include "deco.hpp"

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

    rc522(
      hwlib::target::pin_out & nssInput,
      hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
    );

    uint8_t readReg(      rc522::commands       regAddr);
    uint8_t readReg(      rc522::registers      regAddr);
    uint8_t readReg(      rc522::configuration  regAddr);
    uint8_t readReg(      rc522::test           regAddr);

    void writeReg(        rc522::commands       regAddr, uint8_t data);
    void writeReg(        rc522::registers      regAddr, uint8_t data);
    void writeReg(        rc522::configuration  regAddr, uint8_t data);
    void writeReg(        rc522::test           regAddr, uint8_t data);
    void writeReg(        rc522::registers      regAddr, rc522::regCommands data);

    template<unsigned int N>
    void writeReg(rc522::registers regAddr, std::array<uint8_t,N> data){
      for (unsigned int i = 0; i < N; i++){
        write(static_cast<uint8_t>(regAddr), data[i]);
      }
    }

    void setRegBitMask(   rc522::commands       regAddr, uint8_t mask);
    void setRegBitMask(   rc522::registers      regAddr, uint8_t mask);
    void setRegBitMask(   rc522::configuration  regAddr, uint8_t mask);
    void setRegBitMask(   rc522::test           regAddr, uint8_t mask);

    void unsetRegBitMask( rc522::commands       regAddr, uint8_t mask);
    void unsetRegBitMask( rc522::registers      regAddr, uint8_t mask);
    void unsetRegBitMask( rc522::configuration  regAddr, uint8_t mask);
    void unsetRegBitMask( rc522::test           regAddr, uint8_t mask);

    void antennaOn(bool feedback);
    void antennaOff(bool feedback);

    void softReset();
    void initialize();

    rc522::version compareVersion(std::array<uint8_t,64> buffer);

    rc522::status selfTest();

    template<unsigned int N1,unsigned int N2>
    rc522::status calcCRC(std::array<uint8_t, N1> & dataIn, std::array<uint8_t, N2> & dataOut, bool containsCrc = false) {
      if (N2 < 2){
        return rc522::status::NO_SPACE;
      }
      std::array<uint8_t, (N1-2)> smallerIn = {};
      if (containsCrc){
        //hexPrintArr(dataIn);
        std::copy(begin(dataIn),std::prev(end(dataIn),2), begin(smallerIn));
        //hexPrintArr(smallerIn);
      }

      writeReg(rc522::registers::CommandReg, rc522::regCommands::Idle);       // Command Idle
      writeReg(rc522::registers::DivIrqReg, 0x04);                            // DivIrqReg 0x04 to clear the CRCIrq bit
      writeReg(rc522::registers::FIFOLevelReg, 0x80);                         // FIFOLevelReg 0x80 to empty the buffer
      if (containsCrc){
        writeReg(rc522::registers::FIFODataReg, smallerIn);
      } else {
        writeReg(rc522::registers::FIFODataReg, dataIn);                        // FIFODataReg, data to write the data to the buffer
      }
      writeReg(rc522::registers::CommandReg, rc522::regCommands::CalcCRC);    // CommandReg calcCRC to start the calc

      for (uint16_t i = 5000; i > 0; i--) {
        uint8_t n = readReg(rc522::registers::DivIrqReg);
        if (n & 0x04) {									                                      // Calc is done, the CRCIrq bit is set
          writeReg(rc522::registers::CommandReg, rc522::regCommands::Idle);   // Stop the calc for new data
          dataOut[(dataOut.size()-2)] = readReg(rc522::configuration::CRCResultReg_Low);       // put the results in the last 2 bytes of dataOut
          dataOut[(dataOut.size()-1)] = readReg(rc522::configuration::CRCResultReg_High);
          //hexPrintArr(dataOut);
          return rc522::status::SUCCESS;
        }
      }
      return rc522::status::TIMEOUTDEV;                                       // Some time passed communications with the rc522 might be down
    }

    template<unsigned int N1, unsigned int N2>
    rc522::status cardCommunication(
        std::array<uint8_t,N1> & bufSend,
        std::array<uint8_t,N2> & bufReceive,
        rc522::regCommands comData,
        uint8_t bitFraming,
        uint8_t waitIrq,
        bool checkCrc = false
    ){
      //Try resetting some registers, not necessary to use
      writeReg(rc522::commands::TxModeReg, 0x00);
      writeReg(rc522::commands::RxModeReg, 0x00);
      writeReg(rc522::configuration::ModWidthReg, 0x26);

      writeReg(rc522::registers::CommandReg, rc522::regCommands::Idle);
      writeReg(rc522::registers::ComIrqReg, 0x7F);
      writeReg(rc522::registers::FIFOLevelReg, 0x80);
      for (unsigned int i = 0; i < N1; i++){
        writeReg(rc522::registers::FIFODataReg, bufSend[i]);
      }
      writeReg(rc522::registers::BitFramingReg, bitFraming);
      writeReg(rc522::registers::CommandReg, comData);

      if (comData == rc522::regCommands::Transceive){
        setRegBitMask(rc522::registers::BitFramingReg, 0x80);
      }

      // Wait for a response or time out
      uint16_t i;
      for (i = 2000; i > 0; i--) {
        uint8_t regIrq = readReg(rc522::registers::ComIrqReg);
        if (regIrq & waitIrq)  {break;}
        if (regIrq & 0x01)     {return rc522::status::TIMEOUTCOM;}
      }
      if (i == 0)         {return rc522::status::TIMEOUTDEV;}

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

    template<unsigned int N1, unsigned int N2>
    rc522::status cardTransceive(
        std::array<uint8_t,N1> & bufSend,
        std::array<uint8_t,N2> & bufReceive,
        uint8_t bitFraming = 0,
        bool checkCrc = false
    ){
      uint8_t waitIrq = 0x30;
      return cardCommunication(bufSend,bufReceive,rc522::regCommands::Transceive,bitFraming,waitIrq,checkCrc);
    }

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

    template<unsigned int N1, unsigned int N2>
    rc522::status wakeCard(
      std::array<uint8_t,N1> & bufSend,
      std::array<uint8_t,N2> & bufReceive
    ){
      uint8_t bitFraming = 7;
      return cardTransceive(bufSend,bufReceive,bitFraming);
    }

    rc522::status wakeCard(mifare::command comData);

    template<unsigned int N>
    rc522::status wakeCard(
      mifare::command comData,
      std::array<uint8_t,N> & bufReceive
    ){
      uint8_t bitFraming = 7;
      std::array<uint8_t,1> bufSend = {static_cast<uint8_t>(comData)};
      return cardTransceive(bufSend,bufReceive,bitFraming);
    }

    rc522::status selectCard(mifare::card & curCard);

    rc522::status authenticateCard(mifare::command comData, uint8_t blockAddr, mifare::card cardData);
    void stopCrypto();

    template<unsigned int N>
    rc522::status readBlock(uint8_t blockAddr, std::array<uint8_t,N> & bufReceive){
      rc522::status fStatus;
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

    template<unsigned int N>
    rc522::status writeBlock(uint8_t blockAddr, std::array<uint8_t,N> & dataSend){
      rc522::status fStatus;
      std::array<uint8_t,18> bufReceive = {};
      // Check if there isnt too much data being send
      if ( N > 16){
        return rc522::status::NO_SPACE;
      }

      //Create the buffer containing the command to execute and the CRC
      std::array<uint8_t, 2> bufCom = {
        static_cast<uint8_t>(mifare::command::write),
        blockAddr
      };
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