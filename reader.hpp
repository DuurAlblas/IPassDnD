// ==========================================================================
//
// File      : reader.hpp
// Part of   : RFID library
// Copyright : Duur Alblas (c) 2019
// Contact   : duur.alblas@student.hu.nl
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
#ifndef READER_HPP
#define READER_HPP

#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"
///\brief
/// spiReader ADT class
///\details
///A ADT class for a reader that implements SPI, built using hwlib./n
///You need to supply a hwlib pin_out for the nss pin,/n
///you also has to supply a hwlib spi_bus_banged_sclk_mosi_miso bus for the spiBus./n
///You also has to define the read and write funcions when you inherit from this class.
class spiReader {
  private:
    virtual uint8_t read( const uint8_t regAddr) = 0;
    virtual void write(   const uint8_t regAddr, const uint8_t data) = 0;
  protected:
    ///\brief
    ///A nss hwlib pin_out by ref.
    ///\details
    ///A nss hwlib pin_out pin used with reference./n
    ///The signal nss is used for to be able to send datastreams./n
    hwlib::target::pin_out & nss;
    ///\brief
    ///A spiBus hwlib spi_bus_bit_banged_sclk_mosi_miso.
    ///\details
    ///A spiBus hwlib spi_bus_bit_banged_sclk_mosi_miso,/n
    ///the user has to create a spi_bus_bit_banged_sclk_mosi_miso containing a sclk, mosi and miso,/n
    ///and supply it to this class.
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spiBus;
  public:
    ///\brief
    ///The default constructor
    ///\details
    ///You need to supply the nss pin_out pin and the spiBus spi_bus_bit_banged_sclk_mosi_miso/n
    ///since there are no default values.
    spiReader(
      hwlib::target::pin_out & nssInput,
      hwlib::spi_bus_bit_banged_sclk_mosi_miso & spiBusInput
    );
    ///\brief
    ///A status enum class
    ///\details
    ///This enum class contains all the various statusses the function return.
    enum class status{
      ERROR       = 0x00,
      FAILED_AUTH,
      SUCCESS,
      SUCCESS_NEWC,
      SUCCESS_OLDC,
      TIMEOUTCOM,
      TIMEOUTDEV,
      TIMEOUT,
      NO_SPACE,
      CRC_ERROR,
      CRC_SUCCESS,
      READY
    };
};

#endif