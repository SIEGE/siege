srcdir = 'include/siege'
mask = r'\.h$'
#mask = r'(?<!backend/audio/)buffer.h$'
expandtabs = True
tabsize = 4

outdir = 'doc'

# --------------------

import re
import os

#srcdir = os.path.abspath(srcdir)

rmask = re.compile(mask)

files = []
dirs = []

def getHeaders(arg, path, ents):
	tpath = path[len(srcdir)+1:]
	for ent in ents:
		if os.path.isfile(os.path.join(path, ent)) and rmask.search(os.path.join(path, ent)):
			files.append((tpath, ent))
		elif os.path.isdir(os.path.join(path, ent)):
			dirs.append((tpath, ent))

os.path.walk(srcdir, getHeaders, None)

#print files

rsc = re.compile(r'///.*$', re.MULTILINE)
rmc = re.compile(r'/\*\*.*?\*/', re.DOTALL)

def prestrip(str):
	prev = ''
	while prev != str:
		prev = str
		str = prev.lstrip().lstrip('*')
	return str

fcomments = []
for file in files:
	text = ''
	comments = []
	with open(os.path.join(srcdir, file[0], file[1]), 'r') as f:
		text = f.read()

	#convert CR and CRLF (if any) to LF
	text = '\n'.join(text.splitlines())

	prevtype = ''
	while True:
		sc = rsc.search(text)
		mc = rmc.search(text)

		min = sc
		if sc is None or (mc is not None and mc.start(0) < sc.start(0)):
			min = mc
		if min is None:
			break

		comment = min.group(0)

		if min is mc: # if multiline comment
			res = ''
			for line in comment[3:-3].splitlines():
				preline = line[0:len(line)-len(prestrip(line))]
				line = line[len(preline):]
				if expandtabs:
					preline = preline.expandtabs(tabsize)
				preline = preline.replace('*', ' ')
				line = preline + line
				res += line + '\n'
			comment = res
		else:
			comment = comment[3:].lstrip('/') # the 3: part is not absolutely required

		#if min.start(0) == 0 and len(comments): # we assume it's part of previous
		if min.start(0) == 0 and prevtype == 'sc' and min is sc : # we only merge if there are no lines in between, and if both are single-lined comments
			comments[-1] += '\n' + comment
		else:
			comments.append(comment)

		text = text[min.end(0):]
		if text.startswith('\n'):
			text = text[1:]

		prevtype = 'mc' if min is mc else 'sc'

	fcomments.append((file[0], file[1], comments))

#if not os.path.isdir(outdir):
#	os.mkdir(outdir)
#for dir in dirs:
#	path = os.path.join(outdir, dir[0], dir[1])
#	if not os.path.isdir(path):
#		os.mkdir(path)

for fcomment in fcomments:
	# don't write empty files...
	if len(''.join(fcomment[2]).strip()) == 0:
		continue
	lines = ''.join(fcomment[2]).splitlines()
	while len(lines) and not len(lines[0].strip()):
		lines = lines[1:]
	text = '\n'.join(lines)

	if not os.path.isdir(os.path.join(outdir, fcomment[0])):
		os.makedirs(os.path.join(outdir, fcomment[0]))
	with open(os.path.join(outdir, fcomment[0], fcomment[1] + '.rst'), 'w') as f:
		f.write(text)
