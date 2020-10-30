// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "array-len.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"

extern const ulong lowbit_primpoly[] =
    //
    //  Primitive polynomials over Z/2Z
    //  with lowest-most possible set bits.
    //  These are the minimal numbers with the corresponding
    //  polynomial of given degree primitive.
    //
    //  Generated by Joerg Arndt, 2002-December-21
    //
    {
        //  hex_val,  // ==dec_val  (deg)  [weight]
        0x1,           // 1  (0)  [1]
        0x3,           // 3  (1)  [2]
        0x7UL,         // ==7  (2)  [3]
        0xbUL,         // ==11  (3)  [3]
        0x13UL,        // ==19  (4)  [3]
        0x25UL,        // ==37  (5)  [3]
        0x43UL,        // ==67  (6)  [3]
        0x83UL,        // ==131  (7)  [3]
        0x11dUL,       // ==285  (8)  [5]
        0x211UL,       // ==529  (9)  [3]
        0x409UL,       // ==1033  (10)  [3]
        0x805UL,       // ==2053  (11)  [3]
        0x1053UL,      // ==4179  (12)  [5]
        0x201bUL,      // ==8219  (13)  [5]
        0x402bUL,      // ==16427  (14)  [5]
        0x8003UL,      // ==32771  (15)  [3]
        0x1002dUL,     // ==65581  (16)  [5]
        0x20009UL,     // ==131081  (17)  [3]
        0x40027UL,     // ==262183  (18)  [5]
        0x80027UL,     // ==524327  (19)  [5]
        0x100009UL,    // ==1048585  (20)  [3]
        0x200005UL,    // ==2097157  (21)  [3]
        0x400003UL,    // ==4194307  (22)  [3]
        0x800021UL,    // ==8388641  (23)  [3]
        0x100001bUL,   // ==16777243  (24)  [5]
        0x2000009UL,   // ==33554441  (25)  [3]
        0x4000047UL,   // ==67108935  (26)  [5]
        0x8000027UL,   // ==134217767  (27)  [5]
        0x10000009UL,  // ==268435465  (28)  [3]
        0x20000005UL,  // ==536870917  (29)  [3]
        0x40000053UL,  // ==1073741907  (30)  [5]
        0x80000009UL,  // ==2147483657  (31)  [3]

#if (BITS_PER_LONG <= 32)
        0x000000afUL,  // ==4294967471  (32)  [7]  // highest bit stripped
#endif

#if (BITS_PER_LONG > 32)
        0x1000000afUL,         // ==4294967471  (32)  [7]
        0x200000053UL,         // ==8589934675  (33)  [5]
        0x4000000e7UL,         // ==17179869415  (34)  [7]
        0x800000005UL,         // ==34359738373  (35)  [3]
        0x1000000077UL,        // ==68719476855  (36)  [7]
        0x200000003fUL,        // ==137438953535  (37)  [7]
        0x4000000063UL,        // ==274877907043  (38)  [5]
        0x8000000011UL,        // ==549755813905  (39)  [3]
        0x10000000039UL,       // ==1099511627833  (40)  [5]
        0x20000000009UL,       // ==2199023255561  (41)  [3]
        0x4000000003fUL,       // ==4398046511167  (42)  [7]
        0x80000000059UL,       // ==8796093022297  (43)  [5]
        0x100000000065UL,      // ==17592186044517  (44)  [5]
        0x20000000001bUL,      // ==35184372088859  (45)  [5]
        0x40000000012fUL,      // ==70368744177967  (46)  [7]
        0x800000000021UL,      // ==140737488355361  (47)  [3]
        0x10000000000b7UL,     // ==281474976710839  (48)  [7]
        0x2000000000071UL,     // ==562949953421425  (49)  [5]
        0x400000000001dUL,     // ==1125899906842653  (50)  [5]
        0x800000000004bUL,     // ==2251799813685323  (51)  [5]
        0x10000000000009UL,    // ==4503599627370505  (52)  [3]
        0x20000000000047UL,    // ==9007199254741063  (53)  [5]
        0x4000000000007dUL,    // ==18014398509482109  (54)  [7]
        0x80000000000047UL,    // ==36028797018964039  (55)  [5]
        0x100000000000095UL,   // ==72057594037928085  (56)  [5]
        0x20000000000002dUL,   // ==144115188075855917  (57)  [5]
        0x400000000000063UL,   // ==288230376151711843  (58)  [5]
        0x80000000000007bUL,   // ==576460752303423611  (59)  [7]
        0x1000000000000003UL,  // ==1152921504606846979  (60)  [3]
        0x2000000000000027UL,  // ==2305843009213693991  (61)  [5]
        0x4000000000000069UL,  // ==4611686018427388009  (62)  [5]
        0x8000000000000003UL,  // ==9223372036854775811  (63)  [3]
                               //#if 0
        0x1bUL,                // ==27  (64)  [5]
//#endif  // 0
#endif  // ( BITS_PER_LONG > 32 )
};
// -------------------------

extern const ulong lowbit_primpoly_len = ARRAY_LEN(lowbit_primpoly);
