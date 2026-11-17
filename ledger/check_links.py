"""python3 ledger/check_links.py: exits 1 if any ledger link is broken.

Checks every relative href/src in every .html page, and every row in
ledger/data/*.js: its page (via TOPICS in ledger/data.js) and its #anchor.
"""
import re, sys
from pathlib import Path
from urllib.parse import unquote

root = Path(__file__).resolve().parent.parent
bad = []

for page in root.rglob("*.html"):
    for ref in re.findall(r'(?:href|src)="([^"]+)"', page.read_text()):
        path = unquote(ref.split("#")[0])
        if path and not re.match(r"[a-z]+:", path) and not (page.parent / path).exists():
            bad.append(f"{page.relative_to(root)}: {ref}")

dirs = dict(re.findall(r"(\w+):\s*\{\s*label:[^}]*dir:\s*'([^']+)'", (root / "ledger/data.js").read_text()))
for data in sorted((root / "ledger/data").glob("*.js")):
    t = data.read_text()
    topic, file = re.search(r"topic:\s*'(\w+)'", t)[1], re.search(r"file:\s*'([^']+)'", t)[1]
    page = root / unquote(dirs.get(topic, "?")) / file
    if not page.exists():
        bad.append(f"{data.name}: no page {page.relative_to(root)}")
        continue
    ids = set(re.findall(r'id="([^"]+)"', page.read_text()))
    bad += [f"{data.name}: no #{a} in {file}" for a in re.findall(r"anchor:\s*'([^']+)'", t) if a not in ids]

print("\n".join(bad) or "all ledger links resolve")
sys.exit(1 if bad else 0)
