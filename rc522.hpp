#ifndef RC522_HPP
#define RC522_HPP

#include "reader.hpp"
#include "supp.hpp"
#include "deco.hpp"

class rc522 : public spiReader {
  private:
  protected:
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

    uint8_t readReg(rc522::commands regAddr);

    void writeCommand(rc522::test regAddr, uint8_t data);

};



#endif