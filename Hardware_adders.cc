/******************************************************************************[Hardware_adders.cc]
Copyright (c) 2005-2010, Niklas Een, Niklas Sorensson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************/

#include "Hardware.h"
#include "Debug.h"


int estimatedAdderCost(const Linear& c)
{
  // (sorry about strange implementation -- copy/paste programming)
  vector<Int>    Cs(c.size);
  Int         max_C = -1;
  for (int i = 0; i < c.size; i++){
    Cs[i] = c(i);
    if (Cs[i] > max_C)
      max_C = Cs[i];
  }

  int cost = 0;
  for (; max_C > 0; max_C >>= 1){
    for (int i = 0; i < Cs.size(); i++){
      if ((Cs[i] & 1) != 0)
        cost++;
      Cs[i] >>= 1;
    }
  }

  return cost;
}


void rippleAdder(const vector<Formula>& xs, const vector<Formula>& ys, vector<Formula>& out)
{
  Formula c = _0_;
  out.clear();

  for (int i = 0; i < max(xs.size(),ys.size()); i++){
    Formula x = i < xs.size() ? xs[i] : _0_;
    Formula y = i < ys.size() ? ys[i] : _0_;
    out.push_back(FAs(x,y,c));
    c         = FAc(x,y,c);
  }
  out.push_back(c);

  while (out.back() == _0_)
    out.pop_back();
}


/*_________________________________________________________________________________________________
  |
  |  addPb : (ps : const vec<Formula>&) (Cs_ : const vec<Int>&) (out : vec<Formula>&) (bits : int)
  |            ->  [void]
  |  
  |  Description:
  |    Compute 'C[0]*p[0] + C[1]*p[1] + ... + C[n-1]*P[n-1]' and store in 'out'. Sometimes the higher
  |    order bits are un-interesting, so only the first 'bits' bits will be stored, plus one more
  |    "overflow" bit, so "out.size() <= bits + 1".
  |________________________________________________________________________________________________@*/

void addPb(const vector<Formula>& ps, const vector<Int>& Cs_, vector<Formula>& out, int bits)
{
  assert(ps.size() == Cs_.size());
  vector<vector<Formula> >  pools;
  vector<Int>            Cs(Cs_.size());
  Int                 max_C = -1;
  for (int i = 0; i < Cs_.size(); i++){
    Cs[i] = Cs_[i];
    if (Cs[i] > max_C)
      max_C = Cs[i];
  }

  for (; max_C > 0; max_C >>= 1){
    vector<Formula> dummy;
    pools.push_back(dummy);
    for (int i = 0; i < Cs.size(); i++){
      if ((Cs[i] & 1) != 0)
        pools.back().push_back(ps[i]);
      Cs[i] >>= 1;
    }
  }

  vector<Formula> carry;
  for (int p = 0; p < pools.size(); p++){
    vector<Formula>& pool = pools[p];
    carry.clear();

    if (p == bits){
      Formula overflow = _0_;
      for (; p < pools.size(); p++)
        for (int i = 0; i < pools[p].size(); i++)
          overflow |= pools[p][i];
      out.push_back(overflow);
    }else if (pool.size() == 0)
      out.push_back(_0_);
    else{
      int head = 0;
      while (pool.size()-head >= 3){
        pool .push_back(FAs(pool[head], pool[head+1], pool[head+2]));
        carry.push_back(FAc(pool[head], pool[head+1], pool[head+2]));
        head += 3;
      }
      if (pool.size()-head == 2){
        pool .push_back(FAs(pool[head], pool[head+1], _0_));
        carry.push_back(FAc(pool[head], pool[head+1], _0_));
        head += 2;
      }
      assert(pool.size()-head == 1);
      out.push_back(pool[head]);
    }

    if (carry.size() > 0){
      if (p+1 == pools.size()){
        vector<Formula> dummy;
        pools.push_back(dummy);
      }
      for (int i = 0; i < carry.size(); i++)
        pools[p+1].push_back(carry[i]);
    }
  }

#if 0
  //DEBUG
  for (int p = 0; p < pools.size(); p++){
    printf("pool %d:", (1 << p));
    for (int i = 0; i < pools[p].size(); i++){
      printf(" ");
      dump(pools[p][i]);
    }
    printf("\n");
  }
#endif
}
