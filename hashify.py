import hashlib,sys,string
m = hashlib.md5()
for line in sys.stdin.readlines():
	safe = line
	line = "".join(line.split())
	trim = line
	if line.find("//") != -1:
		line = line[:line.find("//")]
	m.update(line.encode('utf-8'))
	hash = m.hexdigest()[:4]
	if trim.endswith("$"):
		hash = "@" + hash + "@" # ignore this
		m = hashlib.md5()
	print("%s %s"%(hash,safe), end='')
