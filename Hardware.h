/**************************************************************************************[Hardware.h]
Copyright (c) 2005-2010, Niklas Een, Niklas Sorensson

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and
associated documentation files (the "Software"), to deal in the Software without
restriction,
including without limitation the rights to use, copy, modify, merge, publish,
distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom
the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************************************/

#ifndef Hardware_h
#define Hardware_h


#include "PbSolver.h"
#include "FEnv.h"

//=================================================================================================

void clearClausify(void);

int estimatedAdderCost(const Linear& c);
void oddEvenSort(vector<Formula>& fs);
void rippleAdder(const vector<Formula>& xs, const vector<Formula>& ys,
                 vector<Formula>& out);
void addPb(const vector<Formula>& ps, const vector<Int>& Cs_, vector<Formula>& out,
           int bits);

void clausify(SimpSolver& s, const vector<Formula>& fs, vector<Lit>& out);
void clausify(SimpSolver& s, const vector<Formula>& fs);

//=================================================================================================
#endif
