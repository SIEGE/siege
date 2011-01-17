# run me from git root!

import re
import os
from os import path

rdir = 'include/siege'
adir = path.abspath(rdir)

ridir = None
aidir = path.abspath(ridir) if ridir is not None else None

class Include:
    def __init__(self, head, rel):
        self.head = head
        self.rel = rel

class Header:
    def __init__(self, path, found):
        self.path = path
        self.found = found
        self.includes = []
        self.included = []

    def getPath(self):
        return self.path.replace('\\', '/')

excludes = ['siege.h', 'common.h', 'backend.h']
removeNotFound = True
removeAbsolute = True
removeOrphaned = True
reverseIncluded = False

headers = []
def walk(arg, dirname, fnames):
    dirname = dirname[len(adir)+1:]

    for fname in fnames:
        fname = path.join(dirname, fname)
        if path.isfile(path.join(adir, fname)):
            if fname not in excludes:
                headers.append(Header(fname, True))

def getInclude(includes, header):
    for include in includes:
        if include is header:
            return include
    return None

def getHeader(headers, path):
    for header in headers:
        if header.path == path:
            return header
    return None

path.walk(adir, walk, adir)

append = []
for header in headers:
    f = open(path.join(adir, header.path))

    lines = f.readlines()
    for line in lines:
        m = re.match(r'\s*#\s*include ("(.+)"|<(.+)>)', line)
        if m:
            if m.group(2):
                p = path.relpath(path.join(adir, path.dirname(header.path), m.group(2))[len(adir)+1:])
                if p in excludes:
                    continue
                h = getHeader(headers, p)
                if not h:
                    if removeNotFound:
                        continue
                    h = getHeader(append, p)
                    if not h:
                        h = Header(p, False)
                        append.append(h)

                header.includes.append(Include(h, True))
                header.included.append(Include(header, True))

            elif m.group(3):
                if removeAbsolute:
                    continue

                p = m.group(3)
                h = getHeader(headers, p)
                if not h:
                    if removeNotFound:
                        continue
                    h = getHeader(append, p)
                    if not h:
                        h = Header(p, False)
                        append.append(h)

                header.includes.append(Include(h, False))
                header.included.append(Include(header, False))

    f.close()
headers += append

print 'digraph "SIEGE-Includes" {'

for header in headers:
    if removeOrphaned and len(header.included) == 0:
        continue

    prop = {}
    prop['style'] = 'solid' if header.found else 'dashed'
    prop['color'] = 'black' if header.found else 'gray'

    pairs = []
    for key in prop:
        pairs.append('%s=%s' % (key, prop[key]))

    print '\t"%s" [%s];' % (header.getPath(), ','.join(pairs))

for header in headers:
    for include in header.includes:
        prop = {}
        prop['style'] = 'solid' if include.rel else 'dashed'
        prop['color'] = 'black' if include.rel else 'gray'

        pairs = []
        for key in prop:
            pairs.append('%s=%s' % (key, prop[key]))

        if reverseIncluded:
            print '\t"%s"->"%s" [%s];' % (header.getPath(), include.head.getPath(), ','.join(pairs))
        else:
            print '\t"%s"->"%s" [%s];' % (include.head.getPath(), header.getPath(), ','.join(pairs))

print '}'
