import os
import re

srcdir = '../include/siege'

tabwidth = 4
private_start = ['_sg', '_SG', '__']
ignore_index = ['_sg', 'sg', 'SG']
repl = {'SG_EXPORT': ''}

sources = []
source = None

class Source:
    def __init__(self, filename):
        global sources, source
        sources.append(self)
        source = self

        self.elements = {}
        self.lastelem = None
        self.lastdoc = ''
        self.newline = False

        self.filename = filename

class Element:
    def __init__(self, name):
        global source
        global private_start
        source.elements[name] = self

        self.public = True
        for private in private_start:
            if name.startswith(private):
                self.public = False
                break

        self.last, self.doc, self.name = source.lastelem, source.lastdoc, name
        source.lastelem = self
        source.lastdoc = ''

    def getIndex(self):
        global ignore_index

        for ignore in ignore_index:
            if self.name.startswith(ignore):
                return self.name[len(ignore):]
        return self.name

class Struct(Element):
    def __init__(self, name):
        Element.__init__(self, name)

    def __str__(self):
        return 'struct %s' % self.name
class Typedef(Element):
    def __init__(self, name):
        Element.__init__(self, name)

    def __str__(self):
        return 'typedef %s' % self.name
class Function(Element):
    def __init__(self, name, rtype, args):
        Element.__init__(self, name)
        self.rtype, self.args = rtype, args

    def __str__(self):
        return 'function %s(%s) => %s' % (self.name, self.args, self.rtype)
class Macro(Element):
    def __init__(self, name, args, val):
        Element.__init__(self, name)
        self.args, self.val = args, val

    def __str__(self):
        return 'macro %s(%s) => %s' % (self.name, self.args, self.val)
class Define(Element):
    def __init__(self, name, val):
        Element.__init__(self, name)
        self.val = val

    def __str__(self):
        return 'define %s => %s' % (self.name, self.val)

re_newline  = re.compile(r'\n+')
re_space    = re.compile(r'\s+')
re_doc_sl   = re.compile(r'///+(.*)$', re.MULTILINE)
re_doc_ml   = re.compile(r'/\*\*(.*?)\*/', re.DOTALL)
re_com_sl   = re.compile(r'//.*$', re.MULTILINE)
re_com_ml   = re.compile(r'/\*.*?\*/', re.DOTALL)
re_struct   = re.compile(r'(?:typedef )?struct (\w+)')
#re_typedef  = re.compile(r'typedef\s+(?:(\w+\s+)+(\w+)|(.+)\s*\(.+?\)\s*\(.+?\))\s*;')
re_typedef  = re.compile(r'typedef\s+(?:(?:[\w*]+\s+)+(\w+)|(?:[\w*]+\s+)+\(\*(.+?)\)\s*\(.*?\))\s*;')
re_function = re.compile(r'((?:[\w*]+\s+)+)(\w+)\s*\((.*?)\)\s*;')
re_macro    = re.compile(r'#[ \t]*define[ \t]+(\w+)\((.*?)\)[ \t]*(.*)$', re.MULTILINE)
re_define   = re.compile(r'#[ \t]*define[ \t]+(\w+)(?:[ \t]+(.*))?$', re.MULTILINE)
re_pre      = re.compile(r'#.*$', re.MULTILINE)
re_ignore   = re.compile(r'.')

def f_newline(m):
    global source
    source.newline = True
def f_doc(m):
    global source
    if not source.newline and source.lastelem:
        source.lastelem.doc += m.group(1) + '\n'
    else:
        source.lastdoc += m.group(1) + '\n'
    source.newline = True
def f_struct(m):
    Struct(m.group(1))
def f_typedef(m):
    if m.group(1):
        Typedef(m.group(1))
    else:
        Typedef(m.group(2))
def f_function(m):
    Function(m.group(2), m.group(1), m.group(3))
def f_macro(m):
    Macro(m.group(1), m.group(2), m.group(3))
def f_define(m):
    Define(m.group(1), m.group(2))
def f_ignore(m):
    pass
    #print('Warning: Ignoring %s' % m.group(0))

res = []
res.append((re_newline, f_newline))
res.append((re_space, None))
res.append((re_doc_sl, f_doc))
res.append((re_doc_ml, f_doc))
res.append((re_com_sl, None))
res.append((re_com_ml, None))
res.append((re_struct, f_struct))
res.append((re_typedef, f_typedef))
res.append((re_function, f_function))
res.append((re_macro, f_macro))
res.append((re_define, f_define))
res.append((re_pre, None))
res.append((re_ignore, f_ignore))

def handle_file(fname):
    Source(fname)

    input = ''
    with open(fname) as f:
        input = f.read()
    # handle different newlines...
    input = input.replace('\r\n', '\n').replace('\r', '\n')
    # handle line splicing
    input = input.replace('\\\n', '')
    # expand tabs
    input = input.expandtabs(tabwidth)

    while len(input):
        for r,f in res:
            m = r.match(input)
            if m:
                if f:
                    f(m)
                input = input[m.end():]
                break
        else:
            raise Exception('Error parsing near %s' % input[0:])

dirs = []
files = []

curdir = os.getcwd()
try:
    os.chdir(srcdir)
    for root, rdirs, rfiles in os.walk('.'):
        dirs.append(root)
        for rfile in rfiles:
            rfile = os.path.join(root, rfile)
            files.append(rfile)
            handle_file(rfile)
finally:
    os.chdir(curdir)

#exit(1)
for source in sources:
    print('%s:' % source.filename[2:])
    for element in source.elements:
        element = source.elements[element]
        print('\t%s%s' % (element, '' if element.public else '*'))
        if element.doc:
            print('\t\t%s' % repr(element.doc))
