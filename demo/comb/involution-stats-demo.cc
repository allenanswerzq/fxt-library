
#include "comb/involution-zero-map-rgs.h"
#include "comb/mixedradix-naf.h"
#include "comb/perm-involution.h"
#include "comb/word-stats.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"

//% Statistics for involutions (self-inverse permutations):
//% Cf. the following OEIS sequences:
//% A099174, A161126, A238889, and A239145.

//#define TIMING  // uncomment to disable printing

int main(int argc, char **argv) {
  ulong n = 5;
  NXARG(n, "Permutations of n elements");

  perm_involution P(n);
  //    involution_zero_map_rgs P(n);
  //    mixedradix_naf P(n, 1);  // non-adjacent form (rising) factorial numbers

  word_stats W(P.data(), n);
  const ulong nst = n + 1;
  //    const ulong nst = n*(n-1)/2 + 1;  // for tableaux by major index
  ulong *st = new ulong[nst];  // stats
  for (ulong k = 0; k < nst; ++k) st[k] = 0;

  ulong sq = 0;
  NXARG(sq,
        "Select stats:\n"
        "     0 ==> by maximal descent\n"
        "     1 ==> by maximal ascent\n"
        "    10 ==> by number of ascents\n"
        "    11 ==> by number of descents\n"
        "    20 ==> by maximal displacement\n"
        //          "    21 ==> by number of largest parts\n"
        "    30 ==> by position of last max val\n"
        "    31 ==> by position of last min val\n"
        //          "    40 ==> by number of flat steps\n"
        //          "    41 ==> by number of non-flat steps\n"
        //          "     ==> by \n"
        //          "    90 ==> by value of largest part\n"
  );

  ulong ct = 0;
  do {
    ++ct;

    ulong s = 0;
    switch (sq) {
      case 0:  // maximal descent: A000000
        s = W.max_descent();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 3, 0, 0,
        // 1, 7, 1, 1, 0,
        // 1, 15, 3, 5, 2, 0,
        // 1, 31, 9, 16, 13, 6, 0,
        // 1, 63, 23, 44, 46, 39, 16, 0,
        // 1, 127, 59, 117, 138, 154, 118, 50, 0,
        // 1, 255, 142, 305, 383, 496, 506, 376, 156, 0,
        // 1, 511, 340, 781, 1045, 1476, 1801, 1743, 1266, 532, 0,

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 2, 0, 0,
        // 3, 1, 0, 0,
        // 5, 4, 1, 0, 0,
        // 8, 10, 6, 2, 0, 0,
        // 13, 25, 22, 12, 4, 0, 0,
        // 21, 54, 69, 50, 28, 10, 0, 0,
        // 34, 118, 198, 186, 130, 72, 26, 0, 0,
        // 55, 242, 522, 627, 528, 366, 204, 76, 0, 0,
        // 89, 498, 1343, 1992, 1998, 1622, 1106, 616, 232, 0, 0,

        // column k=0: A000045

        // mixedradix-NAF: A000000
        // 1,
        // 2, 0,
        // 3, 1, 0,
        // 4, 5, 1, 0,
        // 5, 12, 7, 2, 0,
        // 6, 27, 23, 16, 4, 0,
        // 7, 54, 67, 56, 38, 10, 0,
        // 8, 104, 176, 194, 150, 106, 26, 0,
        // 9, 193, 438, 578, 576, 440, 310, 76, 0,
        // 10, 351, 1047, 1686, 1926, 1870, 1382, 992, 232, 0,
        // 11, 628, 2433, 4658, 6260, 6716, 6302, 4608, 3316, 764, 0,

      case 1:  // maximal ascent: A000000
        s = W.max_ascent();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 1, 2, 0,
        // 1, 3, 3, 3, 0,
        // 1, 3, 7, 9, 6, 0,
        // 1, 7, 13, 20, 21, 14, 0,
        // 1, 7, 23, 44, 64, 57, 36, 0,
        // 1, 15, 41, 93, 154, 192, 166, 102, 0,
        // 1, 15, 70, 177, 367, 552, 614, 516, 308, 0,
        // 1, 31, 122, 371, 807, 1434, 1961, 2075, 1698, 996, 0,

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 2, 1, 0,
        // 1, 4, 3, 2, 0,
        // 1, 6, 9, 6, 4, 0,
        // 1, 9, 22, 20, 14, 10, 0,
        // 1, 12, 46, 61, 50, 36, 26, 0,
        // 1, 16, 91, 168, 172, 138, 102, 76, 0,
        // 1, 20, 167, 418, 552, 512, 410, 308, 232, 0,
        // 1, 25, 296, 996, 1660, 1824, 1630, 1304, 996, 764, 0,

        // mixedradix-NAF: A000000
        // 1,
        // 2, 0,
        // 2, 1, 1,
        // 2, 3, 3, 2,
        // 2, 6, 8, 6, 4,
        // 2, 11, 19, 20, 14, 10,
        // 2, 19, 43, 54, 52, 36, 26,
        // 2, 32, 94, 146, 160, 152, 102, 76,
        // 2, 53, 201, 372, 486, 502, 464, 308, 232,
        // 2, 87, 423, 938, 1400, 1696, 1662, 1528, 996, 764,
        // 2, 142, 880, 2310, 3972, 5320, 6062, 5764, 5240, 3384, 2620,

      case 10:  // number of ascents: A161126
        s = W.num_ascents();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 2, 1, 0,
        // 1, 4, 4, 1, 0,
        // 1, 6, 12, 6, 1, 0,
        // 1, 9, 28, 28, 9, 1, 0,

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 3, 0, 0,
        // 1, 7, 2, 0, 0,
        // 1, 14, 11, 0, 0, 0,
        // 1, 26, 43, 6, 0, 0, 0,
        // 1, 46, 135, 50, 0, 0, 0, 0,
        // 1, 79, 377, 283, 24, 0, 0, 0, 0,
        // 1, 133, 969, 1243, 274, 0, 0, 0, 0, 0,
        // 1, 221, 2355, 4731, 2068, 120, 0, 0, 0, 0, 0,

        // mixedradix-NAF: A000000
        // 1,
        // 2, 0,
        // 2, 2, 0,
        // 2, 8, 0, 0,
        // 2, 16, 8, 0, 0,
        // 2, 26, 48, 0, 0, 0,
        // 2, 38, 144, 48, 0, 0, 0,
        // 2, 52, 326, 384, 0, 0, 0, 0,
        // 2, 68, 630, 1536, 384, 0, 0, 0, 0,
        // 2, 86, 1098, 4470, 3840, 0, 0, 0, 0, 0,
        // 2, 106, 1778, 10770, 19200, 3840, 0, 0, 0, 0, 0,

      case 11:  // number of descents: same as "ascents"
        s = W.num_descents();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 2, 1, 0,
        // 1, 4, 4, 1, 0,
        // 1, 6, 12, 6, 1, 0,

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 2, 0, 0,
        // 3, 1, 0, 0,
        // 5, 5, 0, 0, 0,
        // 8, 16, 2, 0, 0, 0,
        // 13, 46, 17, 0, 0, 0, 0,
        // 21, 118, 87, 6, 0, 0, 0, 0,
        // 34, 288, 368, 74, 0, 0, 0, 0, 0,
        // 55, 671, 1337, 533, 24, 0, 0, 0, 0, 0,
        // 89, 1519, 4457, 3037, 394, 0, 0, 0, 0, 0, 0,

        // column k=0: A000045

        // mixedradix-NAF: A000000
        // 1,
        // 2, 0,
        // 3, 1, 0,
        // 4, 6, 0, 0,
        // 5, 18, 3, 0, 0,
        // 6, 40, 30, 0, 0, 0,
        // 7, 75, 135, 15, 0, 0, 0,
        // 8, 126, 420, 210, 0, 0, 0, 0,
        // 9, 196, 1050, 1260, 105, 0, 0, 0, 0,
        // 10, 288, 2268, 5040, 1890, 0, 0, 0, 0, 0,
        // 11, 405, 4410, 15750, 14175, 945, 0, 0, 0, 0, 0,

      case 20:  // max( abs( a[j] - j ) ): A238889
        s = W.max_displacement();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 2, 1, 0,
        // 1, 4, 3, 2, 0,
        // 1, 7, 7, 7, 4, 0,
        // 1, 12, 16, 19, 18, 10, 0,
        // 1, 20, 35, 47, 55, 48, 26, 0,
        // 1, 33, 74, 117, 151, 170, 142, 76, 0,
        // 1, 54, 153, 284, 399, 515, 544, 438, 232, 0,
        // 1, 88, 312, 675, 1061, 1471, 1826, 1846, 1452, 764, 0,

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 0, 2, 2, 0,
        // 0, 1, 5, 4, 0,
        // 0, 0, 4, 12, 10, 0,
        // 0, 0, 1, 17, 32, 26, 0,
        // 0, 0, 0, 8, 56, 92, 76, 0,
        // 0, 0, 0, 1, 53, 196, 282, 232, 0,
        // 0, 0, 0, 0, 16, 240, 680, 920, 764, 0,
        // 0, 0, 0, 0, 1, 161, 1088, 2474, 3152, 2620, 0,

        // mixedradix-NAF:
        // 1,
        // 1, 1,
        // 1, 3, 0,
        // 0, 6, 4, 0,
        // 0, 0, 16, 10, 0,
        // 0, 0, 0, 50, 26, 0,
        // 0, 0, 0, 0, 156, 76, 0,
        // 0, 0, 0, 0, 0, 532, 232, 0,
        // 0, 0, 0, 0, 0, 0, 1856, 764, 0,
        // 0, 0, 0, 0, 0, 0, 0, 6876, 2620, 0,
        // 0, 0, 0, 0, 0, 0, 0, 0, 26200, 9496, 0,

        // lower diag: A013989

        //        case 21:  // min( abs( a[j] - j ) ):
        //            s = W.min_displacement();
        //            break;

        //        case 24:  // max( abs( a[j] - j ) ) for all a[j] != j: same as
        //        max_displacement()
        //            s = W.max_displacement_nfp();
        //            break;

      case 25:  // min( abs( a[j] - j ) ) for all a[j] != j: A239145
        // cf. A239144
        s = W.min_displacement_nfp();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 2, 1, 0,
        // 1, 5, 3, 1, 0,
        // 1, 13, 8, 3, 1, 0,
        // 1, 39, 22, 10, 3, 1, 0,
        // 1, 120, 65, 32, 10, 3, 1, 0,
        // 1, 401, 208, 103, 37, 10, 3, 1, 0,
        // 1, 1385, 703, 344, 136, 37, 10, 3, 1, 0,
        // 1, 5069, 2517, 1206, 501, 151, 37, 10, 3, 1, 0,

      case 30:  // position of max val: A000000
        s = W.last_max_idx();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 1, 2, 0,
        // 2, 2, 2, 4, 0,
        // 4, 4, 4, 4, 10, 0,
        // 10, 10, 10, 10, 10, 26, 0,
        // 26, 26, 26, 26, 26, 26, 76, 0,
        // 76, 76, 76, 76, 76, 76, 76, 232, 0,
        // 232, 232, 232, 232, 232, 232, 232, 232, 764, 0,
        // 764, 764, 764, 764, 764, 764, 764, 764, 764, 2620, 0,

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 0, 2, 0,
        // 0, 1, 3, 0,
        // 0, 1, 3, 6, 0,
        // 0, 1, 4, 8, 13, 0,
        // 0, 1, 5, 13, 23, 34, 0,
        // 0, 1, 6, 20, 42, 68, 95, 0,
        // 0, 1, 7, 29, 75, 141, 217, 294, 0,
        // 0, 1, 8, 40, 128, 282, 488, 720, 953, 0,
        // 0, 1, 9, 53, 207, 545, 1081, 1769, 2533, 3298, 0,

        // mixedradix-NAF: A000000
        // 1,
        // 2, 0,
        // 1, 3, 0,
        // 1, 2, 7, 0,
        // 1, 3, 6, 16, 0,
        // 1, 4, 12, 15, 44, 0,
        // 1, 6, 18, 39, 43, 125, 0,
        // 1, 9, 34, 63, 141, 124, 392, 0,
        // 1, 14, 60, 143, 239, 496, 391, 1276, 0,
        // 1, 22, 114, 279, 635, 868, 1865, 1275, 4437, 0,
        // 1, 35, 214, 615, 1329, 2644, 3339, 7085, 4436, 15998, 0,

        // column k=1: A001611 (Fibonacci(n) + 1)

      case 31:  // position of min val: reversed rows of "max val"
        s = W.last_min_idx();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 2, 1, 1, 0,
        // 4, 2, 2, 2, 0,
        // 10, 4, 4, 4, 4, 0,
        // 26, 10, 10, 10, 10, 10, 0,
        // 76, 26, 26, 26, 26, 26, 26, 0,
        // 232, 76, 76, 76, 76, 76, 76, 76, 0,
        // 764, 232, 232, 232, 232, 232, 232, 232, 232, 0,

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 0, 2, 2, 0,
        // 0, 2, 4, 4, 0,
        // 0, 0, 6, 10, 10, 0,
        // 0, 0, 6, 18, 26, 26, 0,
        // 0, 0, 0, 24, 56, 76, 76, 0,
        // 0, 0, 0, 24, 96, 180, 232, 232, 0,
        // 0, 0, 0, 0, 120, 360, 612, 764, 764, 0,
        // 0, 0, 0, 0, 120, 600, 1380, 2156, 2620, 2620, 0,

        // mixedradix-NAF:
        // 1,
        // 2, 0,
        // 2, 2, 0,
        // 0, 6, 4, 0,
        // 0, 0, 16, 10, 0,
        // 0, 0, 0, 50, 26, 0,
        // 0, 0, 0, 0, 156, 76, 0,
        // 0, 0, 0, 0, 0, 532, 232, 0,
        // 0, 0, 0, 0, 0, 0, 1856, 764, 0,
        // 0, 0, 0, 0, 0, 0, 0, 6876, 2620, 0,
        // 0, 0, 0, 0, 0, 0, 0, 0, 26200, 9496, 0,

        // lower diag: A013989

      case 40:  // ...
        s = W.num_flat_steps();
        break;

        // zero-map-rgs: A000000
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 1, 2, 1, 0,
        // 1, 5, 3, 1, 0,
        // 1, 8, 12, 4, 1, 0,
        // 1, 15, 32, 22, 5, 1, 0,
        // 1, 22, 83, 84, 35, 6, 1, 0,
        // 1, 37, 193, 299, 175, 51, 7, 1, 0,
        // 1, 52, 418, 944, 810, 316, 70, 8, 1, 0,
        // 1, 83, 890, 2772, 3314, 1816, 518, 92, 9, 1, 0,

        // column k=0: A077866 (expansion of (1-x)^(-1)/(1-x-2*x^2+2*x^3) )

        // mixedradix-NAF: A000000
        // 1,
        // 2, 0,
        // 3, 1, 0,
        // 5, 4, 1, 0,
        // 11, 9, 5, 1, 0,
        // 23, 32, 14, 6, 1, 0,
        // 63, 75, 66, 20, 7, 1, 0,
        // 153, 288, 171, 116, 27, 8, 1, 0,
        // 489, 735, 837, 329, 185, 35, 9, 1, 0,
        // 1329, 3072, 2244, 1950, 570, 276, 44, 10, 1, 0,
        // 4785, 8505, 11580, 5490, 3960, 918, 392, 54, 11, 1, 0,

        // column k=0: A060696 (permutations avoiding 123, 321 and 231)

        //        case 41:  // ...
        //            s = W.num_nonflat_steps();
        //            break;
        //            // zero-map-rgs: reversed rows wrt. "flat-steps"
        //            // mixedradix-NAF: reversed rows wrt. "flat-steps"

      case 50:  // number of fixed points (0-based): A099174
        s = W.num_fixed_points();
        break;
        // colums: A001147
        // 1,
        // 0, 1,
        // 1, 0, 1,
        // 0, 3, 0, 1,
        // 3, 0, 6, 0, 1,
        // 0, 15, 0, 10, 0, 1,
        // 15, 0, 45, 0, 15, 0, 1,
        // 0, 105, 0, 105, 0, 21, 0, 1,
        // 105, 0, 420, 0, 210, 0, 28, 0, 1,
        // 0, 945, 0, 1260, 0, 378, 0, 36, 0, 1,
        // 945, 0, 4725, 0, 3150, 0, 630, 0, 45, 0, 1,

        // zero-map-rgs: A217876 (adjacent transpositions in involutions)
        // 1,
        // 0, 1,
        // 0, 1, 1,
        // 0, 2, 2, 0,
        // 0, 5, 4, 1, 0,
        // 0, 13, 10, 3, 0, 0,
        // 0, 37, 29, 9, 1, 0, 0,
        // 0, 112, 88, 28, 4, 0, 0, 0,
        // 0, 363, 288, 96, 16, 1, 0, 0, 0,
        // 0, 1235, 984, 336, 60, 5, 0, 0, 0, 0,
        // 0, 4427, 3555, 1248, 240, 25, 1, 0, 0, 0, 0,

        // mixedradix-NAF: A000000
        // 1,
        // 1, 1,
        // 1, 2, 1,
        // 3, 5, 2, 0,
        // 6, 12, 7, 1, 0,
        // 18, 35, 20, 3, 0, 0,
        // 48, 101, 67, 15, 1, 0, 0,
        // 156, 329, 222, 53, 4, 0, 0, 0,
        // 492, 1084, 792, 225, 26, 1, 0, 0, 0,
        // 1740, 3872, 2897, 871, 111, 5, 0, 0, 0, 0,
        // 6168, 14120, 11109, 3688, 570, 40, 1, 0, 0, 0, 0,

      case 51:  // number of fixed points, offset 1
        // colum 1: A170941 (no adjacent transpositions), A000000
        s = W.num_fixed_points_1();
        break;
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 2, 2, 0, 0,
        // 5, 4, 1, 0, 0,
        // 13, 10, 3, 0, 0, 0,
        // 37, 29, 9, 1, 0, 0, 0,
        // 112, 88, 28, 4, 0, 0, 0, 0,
        // 363, 288, 96, 16, 1, 0, 0, 0, 0,
        // 1235, 984, 336, 60, 5, 0, 0, 0, 0, 0,
        // 4427, 3555, 1248, 240, 25, 1, 0, 0, 0, 0, 0,

        //        case 60:  // ...
        //            s = W.min_max_diff();
        //            break;

        //        case 90:  // ...
        //            s = W.max_val();
        //            break;

      case 95:  // value of last part: reversed rows wrt. "position of min val"
        s = P.data()[n - 1];
        break;
        // 0,
        // 1, 0,
        // 1, 1, 0,
        // 1, 1, 2, 0,
        // 2, 2, 2, 4, 0,
        // 4, 4, 4, 4, 10, 0,
        // 10, 10, 10, 10, 10, 26, 0,
        // 26, 26, 26, 26, 26, 26, 76, 0,

        // zero-map-rgs:
        // 1,
        // 1, 0,
        // 1, 1, 0,
        // 2, 1, 1, 0,
        // 4, 2, 2, 2, 0,
        // 10, 4, 4, 4, 4, 0,
        // 26, 10, 10, 10, 10, 10, 0,
        // 76, 26, 26, 26, 26, 26, 26, 0,

        // mixedradix-NAF:
        // 0,
        // 1, 1,
        // 2, 1, 1,
        // 4, 2, 2, 2,
        // 10, 4, 4, 4, 4,
        // 26, 10, 10, 10, 10, 10,

      default:
        cerr << "Invalid choice (exiting)." << endl;
        return 1;
    }

    st[s] += 1;

#ifndef TIMING  // whether to print anything
    cout << setw(4) << ct << ":";

    //        P.print("  ");
    P.print1("  ");        // only for perm_involution
    cout << setw(4) << s;  // stats value

    cout << endl;

//        jjassert( s <= nst );
#endif  // TIMING
  } while (P.next());

  ulong sct = 0;
  for (ulong k = 0; k < nst; ++k) {
    cout << st[k] << ", ";
    sct += st[k];
  }
  cout << endl;

  cout << " ct=" << ct;  // A000085
  cout << endl;

  delete[] st;

  return 0;
}
// -------------------------

/*

Print triangle for stats q:

OEIS example "triangle starts":
 q=0; for n in $(seq 0 10) ; do ./bin $n $q | grep ', $' ; done | nl -v0 -s':  '
-w2 -n rz

OEIS example (stats):
./bin 5 20 | cut -d: -f2 | sort | grep '^  \[' | nl -v1 -s':' -w2 -n rz


C++ comment:
 q=0; for n in $(seq 0 10) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/
/'


Extract column c from stats q:
 q=0; c=0;  echo $(for n in $(seq 0 20) ; do ./bin $n $q | grep ', $' ; done |
cut -d, -f$((c+1))) | sed 's/ /, /g;'

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/involution-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/involution-stats-demo.cc
/// DEMOFLAGS=-DTIMING" End:
