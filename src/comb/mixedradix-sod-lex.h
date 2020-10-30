#if !defined HAVE_MIXEDRADIX_SOD_LEX_H__
#define HAVE_MIXEDRADIX_SOD_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"
#include "comb/is-mixedradix-num.h"
#include "comb/mixedradix-aux.h"
#include "fxttypes.h"

class mixedradix_sod_lex
// Mixed radix numbers with prescribed sum of digits s, in lexicographic order.
// Same as: s-combinations of a multiset.
// Same as: compositions of s with prescribed maximum at each place.
{
 protected:
  ulong n_;    // Number of digits
  ulong s_;    // Sum of digits
  ulong j_;    // rightmost position of last change
  ulong sm_;   // sum of digits (arg s with first())
  ulong *a_;   // digits
  ulong *m1_;  // nines (radix minus one) for each digit

 private:  // have pointer data
  mixedradix_sod_lex(const mixedradix_sod_lex &) = delete;
  mixedradix_sod_lex &operator=(const mixedradix_sod_lex &) = delete;

 public:
  explicit mixedradix_sod_lex(ulong n, ulong mm, const ulong *m = nullptr) {
    n_ = n;

    a_ = new ulong[n_ + 2];
    m1_ = new ulong[n_ + 2];

    a_[n_] = 1;       // sentinel !=0
    m1_[n_] = 2;      // sentinel >a[n]
    a_[n_ + 1] = 0;   // sentinel ==0
    m1_[n_ + 1] = 1;  // sentinel >0

    mixedradix_init(n_, mm, m, m1_);

    ulong s = 0;
    for (ulong i = 0; i < n_; ++i) s += m1_[i];
    sm_ = s;

    j_ = n_ - 1;
  }

  ~mixedradix_sod_lex() {
    delete[] m1_;
    delete[] a_;
  }

  const ulong *data() const { return a_; }
  const ulong *nines() const { return m1_; }
  ulong num_digits() const { return n_; }

  bool first(ulong k) {
    s_ = k;
    if (s_ > sm_) return false;  // too big

    ulong i = 0;
    ulong s = s_;
    while (s) {
      const ulong m1 = m1_[i];
      if (s >= m1) {
        a_[i] = m1;
        s -= m1;
      } else {
        a_[i] = s;
        break;
      }
      ++i;
    }

    while (++i < n_) {
      a_[i] = 0;
    }

    j_ = n_ - 1;
    return true;
  }

  bool next() {
    ulong j = 0;
    ulong s = 0;
    while ((a_[j] == 0) || (a_[j + 1] == m1_[j + 1]))  // can read sentinels
    {
      s += a_[j];
      a_[j] = 0;
      ++j;
    }
    j_ = j + 1;  // record rightmost position of change

    if (j_ >= n_) return false;  // current is last

    s += (a_[j] - 1);
    a_[j] = 0;
    ++a_[j + 1];  // increment next digit

    //        if ( s==0 )  return true;

    ulong i = 0;
    do  // set prefix to lex-first string
    {
      const ulong m1 = m1_[i];
      if (s >= m1) {
        a_[i] = m1;
        s -= m1;
      } else {
        a_[i] = s;
        s = 0;
      }
      ++i;
    } while (s);

    return true;
  }

  ulong pos() const { return j_; }  // position of last change

  void print(const char *bla, bool dfz = false) const
  // If dfz is true then Dots are printed For Zeros.
  {
    print_mixedradix(bla, a_, n_, dfz);
  }

  void print_as_combination(const char *bla) const
  // Digits are a multi- delta set, print corresponding
  // multiset combination of s_ elements.
  {
    print_multi_deltaset_as_set(bla, a_, n_);
  }

  void print_nines(const char *bla) const {
    print_mixedradix(bla, m1_, n_, false);
  }

  bool OK() const {
    if (!is_mixedradix_num(a_, n_, m1_)) return false;

    ulong s = 0;
    for (ulong j = 0; j < n_; ++j) s += a_[j];
    if (s != s_) return false;

    return true;
  }
};
// -------------------------

//#undef MIXEDRADIX_SOD_LEX_MAX_ARRAY_LEN  // better leave in

#endif  // !defined HAVE_MIXEDRADIX_SOD_LEX_H__
