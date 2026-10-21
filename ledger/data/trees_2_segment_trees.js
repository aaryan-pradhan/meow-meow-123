/* ledger/data/trees_2_segment_trees.js — index rows for one child ledger.
 * Adding a problem: append one object to the array. Nothing else to update. */
LEDGER.add(
  { slug: 'trees_2_segment_trees',
    topic: 'trees',
    title: "Segment Trees & Flattening",
    file: 'Tree_Ledger_2_Segment_Trees.html',
    part: 2 },
  [
    { name: "Subtree Queries",
      anchor: 'subtree-queries',
      fam: "Euler tour + segment tree",
      inv: '\\(\\text{subtree}(s) = [\\text{tin}(s), \\text{tout}(s)]\\); point set at \\(\\text{tin}\\), range sum',
      time: '\\(O((n+q) \\log n)\\)' },
    { name: "Hotel Queries",
      anchor: 'hotel-queries',
      fam: "Segment tree descent",
      inv: 'max tree; go left if \\(\\max(\\text{left}) \\ge r\\); leaf \\(\\mathrel{-}= r\\)',
      time: '\\(O((n+m) \\log n)\\)' },
    { name: "List Removals",
      anchor: 'list-removals',
      fam: "Segment tree descent",
      inv: '0/1 count tree; \\(\\text{cnt}(\\text{left}) \\ge k\\) ? left : right with \\(k - \\text{cnt}(\\text{left})\\)',
      time: '\\(O(n \\log n)\\)' },
    { name: "Range Update Queries",
      anchor: 'range-update-queries',
      fam: "Lazy propagation",
      inv: 'push: \\(\\text{sum} \\mathrel{+}= (r-l+1)\\cdot \\text{lazy}\\), children \\(\\text{lazy} \\mathrel{+}= \\text{lazy}\\)',
      time: '\\(O((n+q) \\log n)\\)' },
    { name: "Forest Queries",
      anchor: 'forest-queries',
      fam: "2D prefix sums",
      inv: '\\(P(y_2,x_2) - P(y_1{-}1,x_2) - P(y_2,x_1{-}1) + P(y_1{-}1,x_1{-}1)\\)',
      time: '\\(O(n^{2} + q)\\)' }
  ],
  [
    { file: 'trees/Path_Queries.cpp', why: "unfinished: 'algodebug.h' not found; stnode used before declaration; query has no body" },
    { file: 'trees/Salary_Queries.cpp', why: "empty template: 'algodebug.h' not found; solve() empty" }
  ]
);
