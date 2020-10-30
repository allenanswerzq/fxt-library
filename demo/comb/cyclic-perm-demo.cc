
#include "comb/cyclic-perm.h"
// demo-include "comb/fact2cyclic.cc"
// demo-include "comb/mixedradix-gray.h"

#include "aux0/factorial.h"  // for timing
#include "comb/comb-print.h"
#include "comb/fact2perm.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"
#include "perm/perminvert.h"
#include "perm/permq.h"  // is_cyclic()
#include "perm/printcycles.h"

//% Generate all cyclic permutations in minimal-change order, CAT algorithm.

//#define TIMING  // uncomment to disable printing

int main(int argc, char **argv) {
  ulong n = 5;
  NXARG(n, "Cyclic permutations of n elements, n >= 2.");
  jjassert(n >= 2);

  cyclic_perm P(n);

  ulong ct = 0;

#ifdef TIMING

  do {
    ++ct;
  } while (P.next());

  n += (n == 0);
  cout << " ct=" << factorial(n - 1) << endl;

#else  // TIMING

  ulong *t = new ulong[n];
  const ulong *x = P.data();
  const ulong *ix = P.invdata();
  const ulong *a = P.M_->data();
  const ulong z = (n >= 2 ? n - 2 : 0);
  do {
    cout << setw(4) << ct << ":";

    print_perm("    ", x, n);
    //        print_perm("    ", ix, n);

    print_mixedradix("    ", a, z, true);

    cout << "    ";
    print_cycle(x, n - 1);
    cout << endl;

    ffact2cyclic(a, n, t);
    for (ulong i = 0; i < n; ++i) {
      jjassert(t[i] == ix[i]);
    }

    jjassert(is_cyclic(x, n));
    jjassert(is_inverse(x, ix, n));

    ++ct;
  } while (P.next());

  delete[] t;

#endif  // TIMING

  return 0;
}
// -------------------------

/*
Timing:

 time ./bin 13
arg 1: 13 == n  [Cyclic permutations of n elements.]  default=5
./bin 13  8.24s user 0.00s system 99% cpu 8.244 total
 ==> 12!/8.24 == 58,131,262 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 13
arg 1: 13 == n  [Cyclic permutations of n elements.]  default=5
./bin 13  5.26s user 0.00s system 99% cpu 5.261 total
 ==> 12!/5.26 == 91,064,942 per second
*/

/*
BENCHARGS=13
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/cyclic-perm-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/cyclic-perm-demo.cc DEMOFLAGS=-DTIMING"
/// End:
