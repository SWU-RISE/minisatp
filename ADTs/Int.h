/*******************************************************************************************[Int.h]
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

#ifndef Int_h
#define Int_h

typedef  int Int;

//=================================================================================================

struct Exception_IntOverflow {
  char* where;
  Exception_IntOverflow(char* w) : where(w) {}  // (takes ownership of string)
};

//=================================================================================================
// Fake bignums using 'int64':
//=================================================================================================


//-------------------------------------------------------------------------------------------------

#define A1 assert(data != Int_Undef__);
#define A2 assert(data != Int_Undef__), assert(other.data != Int_Undef__);



#define Int_MAX  1000000
#define Int_MIN  -100000



 char*toString(Int &x);



#endif
