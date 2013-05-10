/***
timer.h

Timer class for code timing.

This class depends only on the C++ STL so it ought to be portable. It
uses the std::clock() function which is precise to platform-dependent
fractions of a second, as specified by CLOCKS_PER_SEC.

***

    // do slow initialization before now

    Timer timer;
    // timer is now running, immediately do stuff
    cout << "Elapsed time in seconds: " << timer.elapsed() << endl;

***

This code is open source software released under the MIT/X11 license.

Copyright (c) 2013 Kevin A. Wortman

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _CSUF_TIMER_H
#define _CSUF_TIMER_H

#include <cassert>
#include <ctime>

class Timer {
 public:
  Timer() {
    reset();
  }
    
  void reset() {
    _start = clock();
  }

  double elapsed() const {
    clock_t now = clock();
    assert(now >= _start);
    return double(now - _start) / double(CLOCKS_PER_SEC);
  }

 private:
  clock_t _start;
};

#endif
