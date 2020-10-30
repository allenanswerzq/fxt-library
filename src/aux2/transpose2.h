#if !defined HAVE_TRANSPOSE2_H__
#define HAVE_TRANSPOSE2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2017, 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux2/transpose.h"  // transpose_square()
#include "bits/bit2pow.h"    // ld()
#include "bits/bitrotate.h"
#include "ds/bitarray.h"
#include "fxttypes.h"

#define SRC(k) bit_rotate_left(k, ldnc, ldn)  // = (((k)*nc)%n1)

template <typename Type>
void transpose2(Type *f, ulong nr, ulong nc, bitarray *B = nullptr)
// In-place transposition of an  nr X nc  array
//   that lies in contiguous memory.
// Special case where both nr and nc are a power of 2.
//.
// Use bitarray for tagging moved elements.
{
  if (1 >= nr) return;
  if (1 >= nc) return;

  if (nr == nc)
    transpose_square(f, nr);
  else {
    const ulong n1 = nr * nc - 1;
    const ulong ldnc = ld(nc);
    const ulong ldn = ld(n1 + 1);

    bitarray *tB = nullptr;
    if (nullptr == B)
      tB = new bitarray(n1);
    else
      tB = B;
    tB->clear_all();

    for (ulong k = 0; k < n1;
         k = tB->next_clear(++k))  //  0 and n1 are fixed points
    {
      // do a cycle:
      ulong ks = SRC(k);
      ulong kd = k;
      tB->set(kd);
      Type t = f[kd];
      while (ks != k) {
        f[kd] = f[ks];
        kd = ks;
        tB->set(kd);
        ks = SRC(ks);
      }
      f[kd] = t;
    }

    if (nullptr == B) delete tB;
  }
}
// -------------------------

#undef SRC
#undef DST

#endif  // !defined HAVE_TRANSPOSE2_H__
