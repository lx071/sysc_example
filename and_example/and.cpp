#include "and.h"

void and2::func(){            // process
    f.write( a.read() & b.read() );
    // 打印输出
    cout << "a = " << a.read() << ", b = " << b.read() << ", f = " << f.read() << endl;
}