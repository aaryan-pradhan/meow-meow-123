/* ledger/data/strings_1_scans.js — index rows for one child ledger.
 * Adding a problem: append one object to the array. Nothing else to update. */
LEDGER.add(
  { slug: 'strings_1_scans',
    topic: 'strings',
    title: "String Scans",
    file: 'String_Ledger_1_Scans.html',
    part: 1 },
  [
    { name: "DNA Repetition",
      anchor: 'dna-repetition',
      fam: "Run-length scan",
      inv: '\\(c_i = c_{i-1} + 1\\) if \\(s_i = s_{i-1}\\), else \\(1\\); \\(\\text{ans} = \\max c_i\\)',
      time: '\\(O(n)\\)' }
  ]
);
