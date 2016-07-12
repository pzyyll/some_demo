#include <iostream>
#include <fstream>
#include "MyCache.h"

using namespace std;

int main()
{
    MyCache cache;
    cache.init(10);

    cache.write("1111111", 7);
    char buf[20];
    int n = cache.read(buf, 20);
    buf[n] = '\0';

    cout << buf << endl;

    cache.write("00000000", 8);
    n = cache.read(buf, 20);
    buf[n] = '\0';

    cout << buf << endl;

    cache.write("1111111", 7);
    if(cache.write("0000", 4) < 0 ) {
        cout << "fail write" << endl;
    }
    n = cache.read(buf, 20);
    buf[n] = '\0';

    cout << buf << endl;

    if  (cache.read(buf, 20) <= 0) {
        cout << "read fail" << endl;
    }

    cache.deinit();
    return 0;
}
