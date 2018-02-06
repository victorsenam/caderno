head = "head"
code_list = "../code/config"
tail = "tail"

from pathlib import Path
import re, os, subprocess
text = Path(head).read_text()

os.makedirs('src', exist_ok = True)

codes = Path(code_list).read_text().strip().split('\n')
for c in codes:
	m = re.search("(<.+>) (<.+>)", c)
	a, b = m.group(1).strip("<>"), m.group(2).strip("<>")
	if b.find('/') != -1:
		os.makedirs("src/" + b[:b.find('/')], exist_ok = True)
	subprocess.run(["python3", "hashify.py"], stdin=open("../code/" + b), stdout=open("src/" + b, 'w'))
	text += "\\section{" + a + "}\n"
	text += "\\lstinputlisting{src/" + b + "}\n\n"

text += Path(tail).read_text()

print(text)
