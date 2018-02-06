import hashlib,sys

m = hashlib.md5()
for line in sys.stdin.readlines():
	safe = line
	if line.find("//") != -1:
		line = line[:line.find("//")]
	trimmed = line.replace(" ","").replace("\n","").replace("\t","")
	m.update(trimmed.encode('utf-8'))
	hash = m.hexdigest()[:4]
	print("%s %s"%(hash,safe), end='')
