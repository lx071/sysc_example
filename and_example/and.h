#ifndef AND_H
#define AND_H

#include <systemc.h>
//类似于 class module_name : sc_module {...}
SC_MODULE( and2 ){        // module (class) declaration    
    sc_in< sc_uint<1> > a, b;    // ports
    sc_out< sc_uint<1> > f;
    sc_in<bool> clk;
    
    void func();    // process
    
    SC_CTOR( and2 ){    //systemc constructor
        SC_METHOD( func );    // register func to kernel
        sensitive << clk.neg(); // sensitivity list of func
    }
};

#endif  // AND_H