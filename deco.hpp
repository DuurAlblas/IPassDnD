#ifndef DECO_HPP
#define DECO_HPP

#include "hwlib.hpp"
#include "../../hwlib/library/hwlib.hpp"

class pin_out_invert : public hwlib::pin_out {
private:
   hwlib::pin_out & slave;
public:
   pin_out_invert( hwlib::pin_out & slaveInput );

   void write( bool x ) override {
      slave.write( ! x );
   }
   void flush() override {
      slave.flush();
   }
};

#endif