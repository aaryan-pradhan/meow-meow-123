/* ledger/data/arrays_4_sweep_ordered.js — index rows for one child ledger.
 * Adding a problem: append one object to the array. Nothing else to update. */
LEDGER.add(
  { slug: 'arrays_4_sweep_ordered',     // must match <body data-slug>
    topic: 'arrays',                    // key in LEDGER.TOPICS
    title: 'Sweep &amp; Ordered Set',   // shown on the master page card
    file: 'Array_Ledger_4_Sweep_Ordered.html',
    part: 4 },
  [
    { name: 'Restaurant Customers',
      anchor: 'restaurant-customers',
      fam: 'interval sweep',
      inv: '\\(a_i \\to +1,\\ b_i \\to -1\\); \\(\\text{ans} = \\max_e \\sum_{f \\le e} \\delta_f\\)',
      time: '\\(O(n \\log n)\\)' },

    { name: 'Union of Painted Bricks',
      anchor: 'union-of-painted-bricks',
      fam: 'interval sweep',
      inv: 'sort by \\(L\\); \\(l \\le c_R \\Rightarrow c_R \\leftarrow \\max(c_R, r)\\), else add \\(c_R - c_L + 1\\)',
      time: '\\(O(N \\log N)\\)' },

    { name: 'Nested Ranges Check',
      anchor: 'nested-ranges-check',
      fam: 'interval sweep',
      inv: 'sort \\(l\\uparrow, r\\downarrow\\); fwd \\(r_i \\le \\max r\\) ⇒ inside; bwd \\(r_i \\ge \\min r\\) ⇒ contains',
      time: '\\(O(n \\log n)\\)' },

    { name: 'Room Allocation',
      anchor: 'room-allocation',
      fam: 'interval assignment',
      inv: 'ties \\(+1\\) before \\(-1\\); \\(k = \\max_t \\#\\{i : a_i \\le t \\le b_i\\}\\); free-room stack',
      time: '\\(O(n \\log n)\\)' },

    { name: 'Tower of Cubes',
      anchor: 'tower-of-cubes',
      fam: 'ordered-set greedy',
      inv: '\\(t^* = \\min\\{t \\in T : t \\gt c\\}\\); replace \\(t^*\\) by \\(c\\), else insert; \\(\\text{ans} = |T|\\)',
      time: '\\(O(n \\log n)\\)' },

    { name: 'Traffic Lights',
      anchor: 'traffic-lights',
      fam: 'ordered-set greedy',
      inv: '\\(G \\leftarrow G - \\{hi - lo\\} + \\{p - lo,\\ hi - p\\}\\); \\(\\text{ans} = \\max G\\)',
      time: '\\(O(n \\log n)\\)' },
    { name: 'Concert Tickets',
      anchor: 'concert-tickets',
      fam: 'ordered-set greedy',
      inv: '\\(\\max\\{h \\in H : h \\le t_j\\}\\) = <code>prev(upper_bound(t))</code>; erase one copy',
      time: '\\(O((n+m) \\log n)\\)' }
  ],
  [
    { file: 'arrays/Nested_Ranges_Count.cpp',
      why: 'compiles clean but wrong on its own sample — expected "2 0 0 0", produces ' +
           '"1 0 0 0". It is the Check sweep with ans1[idx]=1 swapped for ans1[idx]++, ' +
           'and each index is visited once per pass, so the counter can never exceed 1. ' +
           'The counting variant needs a Fenwick/segment tree over compressed endpoints.' }
  ]
);
