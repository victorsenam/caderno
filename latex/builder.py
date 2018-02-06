head = "head"
code_list = "../code/config"
tail = "tail"

from pathlib import Path
import re
text = Path(head).read_text()

codes = Path(code_list).read_text().strip().split('\n')
for c in codes:
	m = re.search("(<.+>) (<.+>)", c)
	a, b = m.group(1), m.group(2)
	text += "\\section{" + a.strip("<>") + "}\n"
	text += "\\lstinputlisting{../code/" + b.strip("<>") + "}\n\n"

text += Path(tail).read_text()

print(text)
