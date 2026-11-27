"""python3 cf/top150_html.py: rebuild cf/top150.html and ledger/data/top150.js.

Reads the list in cf/top150.md and each solution cf/<Name>.cpp, where Name is
the title with every run of non-alphanumeric characters turned into "_".
Run it again after adding or changing a solution.
"""
import html, re, sys
from pathlib import Path

cf = Path(__file__).resolve().parent
root = cf.parent


def file_name(title):
    return re.sub(r"[^A-Za-z0-9]+", "_", title).strip("_") + ".cpp"


def anchor(title):
    return re.sub(r"[^a-z0-9]+", "-", title.lower()).strip("-")


def header_part(code, number):
    # the comment lines under "// <number>. <heading>" up to the next numbered heading
    m = re.search(r"^// %d\. [^\n]*\n((?://    [^\n]*\n)+)" % number, code, re.M)
    if not m:
        return ""
    return " ".join(line[2:].strip() for line in m.group(1).splitlines())


def big_o(text):
    # first O(...) after "time", with nested parentheses
    i = text.find("time O(")
    if i == -1:
        return ""
    i += len("time ")
    depth = 0
    for j in range(i + 1, len(text)):
        if text[j] == "(":
            depth += 1
        elif text[j] == ")":
            depth -= 1
            if depth == 0:
                return text[i:j + 1]
    return ""


sections = []  # (section, [(num, title, url, difficulty)])
for line in (cf / "top150.md").read_text().splitlines():
    if line.startswith("## "):
        sections.append((line[3:], []))
    m = re.match(r"- \[[ x]\] \[(\d+)\. (.+?)\]\((.+?)\) · (\w+)", line)
    if m:
        sections[-1][1].append(m.groups())

missing = [t for _, ps in sections for _, t, _, _ in ps if not (cf / file_name(t)).exists()]
if missing:
    sys.exit("no solution file for: " + ", ".join(missing))

toc, body, rows = [], [], []
for sec, ps in sections:
    toc.append(f'<li><a href="#{anchor(sec)}">{html.escape(sec)}</a> <span>{len(ps)}</span></li>')
    body.append(f'<h2 id="{anchor(sec)}">{html.escape(sec)}</h2>')
    for num, title, url, diff in ps:
        code = (cf / file_name(title)).read_text()
        a = anchor(title)
        body.append(
            f'<details id="{a}"><summary><b>{num}.</b> {html.escape(title)} '
            f'<span class="d {diff.lower()}">{diff}</span></summary>'
            f'<p><a href="{url}">LeetCode</a> · <code>cf/{file_name(title)}</code></p>'
            f'<pre>{html.escape(code)}</pre></details>')
        key = header_part(code, 4)
        rows.append({"name": f"{num}. {title}", "anchor": a, "fam": sec,
                     "inv": html.escape(key[:160] + ("…" if len(key) > 160 else "")),
                     "time": html.escape(big_o(header_part(code, 6)))})

n = sum(len(ps) for _, ps in sections)
page = f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Top Interview 150 · solutions</title>
<style>
:root {{ color-scheme: light dark; --bg:#fbfaf7; --fg:#1d1d1f; --mute:#6b6b70; --line:#e3e1dc; --code:#f3f1ec; }}
@media (prefers-color-scheme: dark) {{ :root {{ --bg:#141416; --fg:#e8e6e1; --mute:#9a9893; --line:#2c2c30; --code:#1c1c20; }} }}
body {{ margin:0; background:var(--bg); color:var(--fg); font:15px/1.5 system-ui, sans-serif; }}
nav {{ position:fixed; top:0; bottom:0; left:0; width:230px; overflow:auto; padding:20px; border-right:1px solid var(--line); box-sizing:border-box; }}
nav ul {{ list-style:none; padding:0; margin:12px 0 0; }}
nav li {{ display:flex; justify-content:space-between; padding:2px 0; }}
nav span, .mute {{ color:var(--mute); }}
a {{ color:inherit; }}
main {{ margin-left:230px; padding:20px 32px 80px; max-width:1000px; }}
input {{ width:100%; box-sizing:border-box; padding:8px 10px; font:inherit; border:1px solid var(--line); border-radius:6px; background:var(--code); color:inherit; }}
h1 {{ margin:0 0 4px; font-size:22px; }}
h2 {{ margin:32px 0 8px; font-size:17px; border-bottom:1px solid var(--line); padding-bottom:4px; }}
details {{ border-bottom:1px solid var(--line); }}
summary {{ cursor:pointer; padding:7px 0; }}
.d {{ font-size:12px; padding:1px 7px; border-radius:10px; margin-left:6px; }}
.easy {{ background:#d8f0dc; color:#1b5e2a; }} .medium {{ background:#f6ead0; color:#6e4b00; }} .hard {{ background:#f6d9d6; color:#7d1f17; }}
details p {{ margin:4px 0 8px; font-size:13px; color:var(--mute); }}
pre {{ background:var(--code); padding:14px; border-radius:6px; overflow:auto; font:12.5px/1.45 ui-monospace, Menlo, monospace; }}
@media (max-width:760px) {{ nav {{ position:static; width:auto; border:0; }} main {{ margin:0; padding:12px; }} }}
</style>
</head>
<body>
<nav>
<b>Top Interview 150</b>
<ul>{''.join(toc)}</ul>
</nav>
<main>
<h1>Top Interview 150 · solutions</h1>
<p class="mute">{n} problems in study-plan order. Click a problem to open its code. Each file starts with the question and the 6-step header.</p>
<input id="q" placeholder="filter by number or title" autofocus>
{''.join(body)}
</main>
<script>
document.getElementById('q').addEventListener('input', function () {{
  var q = this.value.trim().toLowerCase();
  document.querySelectorAll('details').forEach(function (d) {{
    d.hidden = q && d.querySelector('summary').textContent.toLowerCase().indexOf(q) === -1;
  }});
}});
if (location.hash) {{ var d = document.querySelector(location.hash); if (d && d.tagName === 'DETAILS') d.open = true; }}
</script>
</body>
</html>
"""
(cf / "top150.html").write_text(page)


def js(s):
    return "'" + s.replace("\\", "\\\\").replace("'", "\\'") + "'"


lines = [
    "/* ledger/data/top150.js — index rows for cf/top150.html.",
    " * Generated by cf/top150_html.py; edit the solutions, then rerun it. */",
    "LEDGER.add(",
    "  { slug: 'top150',",
    "    topic: 'top150',",
    "    title: \"Top Interview 150\",",
    "    file: 'top150.html',",
    "    part: 1 },",
    "  [",
    ",\n".join("    { name: %s,\n      anchor: %s,\n      fam: %s,\n      inv: %s,\n      time: %s }"
               % (js(r["name"]), js(r["anchor"]), js(r["fam"]), js(r["inv"]), js(r["time"])) for r in rows),
    "  ]",
    ");",
    "",
]
(root / "ledger/data/top150.js").write_text("\n".join(lines))
print(f"wrote cf/top150.html and ledger/data/top150.js: {n} problems")
