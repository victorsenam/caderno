head = "head"
code_list = "../code/config"
tail = "tail"

import re, os, subprocess
text = open(head).read()

os.makedirs('src', exist_ok = True)

codes = open(code_list).read().strip().split('\n')
for c in codes:
	m = re.search("(<.+>) (<.+>)", c)
	a, b = m.group(1).strip("<>"), m.group(2).strip("<>")
	if b.find('/') != -1:
		os.makedirs("src/" + b[:b.find('/')], exist_ok = True)
	subprocess.call(["python3", "hashify.py"], stdin=open("../code/" + b), stdout=open("src/" + b, 'w'))
	text += "\\section{" + a + "}\n"
	text += "\\lstinputlisting{src/" + b + "}\n\n"

text += open(tail).read()

print(text)
