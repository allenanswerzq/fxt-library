#if !defined HAVE_PERMAPPLYFUNC_H__
#define HAVE_PERMAPPLYFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray.h"
#include "fxttypes.h"
#include "restrict.h"

template <typename Type>
void apply_permutation(ulong (*x)(ulong), const Type *f, Type *restrict g,
                       ulong n)
// Set g[x(k)] <-- f[k]  for all k
// Must have:  0<=x(k)<n for all k
//
// Example: The following two lines result in identical g[]:
//    apply_permutation(gray_code, f, g, n);
//    gray_permute(f, g, n);
{
  for (ulong k = 0; k < n; ++k) g[x(k)] = f[k];
}
// -------------------------

template <typename Type>
void apply_permutation(ulong (*x)(ulong), Type *restrict f, ulong n,
                       bitarray *bp = nullptr)
// Set f[x(k)] <-- f[k]  for all k
// Must have:  0<=x(k)<n for all k
// In-place version.
{
  bitarray *tp = bp;
  if (nullptr == bp) tp = new bitarray(n);  // tags
  tp->clear_all();

  for (ulong k = 0; k < n; ++k) {
    if (tp->test_clear(k)) continue;  // already processed
    tp->set(k);

    // --- do cycle: ---
    ulong i = k;  // start of cycle
    Type t = f[i];
    ulong g = x(i);
    while (0 == (tp->test_set(g)))  // cf. gray_permute()
    {
      Type tt = f[g];
      f[g] = t;
      t = tt;
      g = x(g);
    }
    f[g] = t;
    // --- end (do cycle) ---
  }

  if (nullptr == bp) delete tp;
}
// -------------------------

template <typename Type>
void apply_inverse_permutation(ulong (*x)(ulong), const Type *f,
                               Type *restrict g, ulong n)
// Set g[k] <-- f[x(k)]  for all k
// Must have:  0<=x(k)<n for all k, and x(i)!=x(j) for all i!=j
{
  for (ulong k = 0; k < n; ++k) g[k] = f[x(k)];
}
// -------------------------

template <typename Type>
void apply_inverse_permutation(ulong (*x)(ulong), Type *f, ulong n,
                               bitarray *bp = nullptr)
// Set f[k] <-- f[x(k)]  for all k
// Must have:  0<=x(k)<n for all k, and x(i)!=x(j) for all i!=j
// In-place version.
{
  bitarray *tp = bp;
  if (nullptr == bp) tp = new bitarray(n);  // tags
  tp->clear_all();

  for (ulong k = 0; k < n; ++k) {
    if (tp->test_clear(k)) continue;  // already processed
    tp->set(k);

    // --- do cycle: ---
    ulong i = k;  // start of cycle
    Type t = f[i];
    ulong g = x(i);
    while (0 == (tp->test_set(g)))  // cf. inverse_gray_permute()
    {
      f[i] = f[g];
      i = g;
      g = x(i);
    }
    f[i] = t;
    // --- end (do cycle) ---
  }

  if (nullptr == bp) delete tp;
}
// -------------------------

#endif  // !defined HAVE_PERMAPPLYFUNC_H__
