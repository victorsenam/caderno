import hashlib,sys,string

m = hashlib.md5()
for line in sys.stdin.readlines():
	safe = line
	line = "".join(line.split())
	if line.endswith("$"):
		m = hashlib.md5()
	if line.find("//") != -1:
		line = line[:line.find("//")]
	m.update(line.encode('utf-8'))
	hash = m.hexdigest()[:4]
	print("%s %s"%(hash,safe), end='')
