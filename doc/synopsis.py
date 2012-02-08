#!/usr/bin/env python

#example: http://synopsis.fresco.org/docs/Tutorial/script.html

srcdir = '../include/siege'

from Synopsis.process import process
from Synopsis.Processor import Processor, Parameter, Composite
from Synopsis.Parsers import C
#from Synopsis.Parsers import Python
from Synopsis.Processors import Linker
from Synopsis.Processors import Comments
from Synopsis.Formatters import HTML
from Synopsis.Formatters import Dump

import re

def startswith_any(string, arr):
    for item in arr:
        if string.startswith(item):
            return item
    return None
def startswith_max(string, arr):
    ret = None
    for item in arr:
        if string.startswith(item):
            if ret is None or len(ret) < len(item):
                ret = item
    return ret

class SGNoPrivate(Processor):
    private = Parameter(['_'], 'prefixes considered to be private variables')

    def process(self, ir, **keywords):
        self.set_parameters(keywords)

        self.ir = self.merge_input(ir)

        decls = []
        for decl in self.ir.asg.declarations:
            if startswith_any(decl.name[-1], self.private) is None:
                decls.append(decl)
        self.ir.asg.declarations = decls

        return self.output_and_return_ir()

class SGFilter(Comments.Filter):

    sss = r'^[ \t]*/// ?(.*)$'
    comment = r'/\*\*[ \t]*(?P<text>.*)(?P<lines>(\n[ \t]*\*.*)*?)(\n[ \t]*)?\*/'
    line = r'\n[ \t]*([ \t]*[\*]+(?=[ \t\n]))*(?P<text>.*)'
    #line = r'\n[ \t]*\*[ \t]*(?P<text>.*)'

    def __init__(self, **kwds):
        Comments.Filter.__init__(self, **kwds)

        self.sss = re.compile(SGFilter.sss)
        self.comment = re.compile(SGFilter.comment)
        self.line = re.compile(SGFilter.line)

    def filter_comment(self, comment):
        mo = self.sss.match(comment)
        if mo:
            return mo.group(1)

        text = []
        mo = self.comment.search(comment)
        while mo:
            text.append(mo.group('text'))
            lines = mo.group('lines')
            if lines:
                mol = self.line.search(lines)
                while mol:
                    text.append(mol.group('text'))
                    mol = self.line.search(lines, mol.end())
            mo = self.comment.search(comment, mo.end())
        return '\n'.join(text)

c = C.Parser(base_path=srcdir)

sg = Comments.Translator(markup='javadoc', # rst, javadoc
                         filter=SGFilter(),
                         processor=Composite(Comments.Previous(),
                                             Comments.Grouper()),
                         concatenate=True)

nopriv = SGNoPrivate(private=['`', '_', 'sgm'])
c_nopriv = Composite(c, nopriv)

from Synopsis import ASG
from Synopsis.Formatters.HTML.Views import *
from Synopsis.Formatters.HTML.Parts import *

class SGNameIndex(NameIndex):
    private = Parameter(['_'], 'prefixes considered to be private variables')
    prefix = Parameter(['_'], 'prefixes to ignore in indexing')

    def __init__(self, **keywords):
        NameIndex.__init__(self)

        self.set_parameters(keywords)

    def make_dictionary(self):
        dict = {}
        def hasher(type):
            name = type.name
            try:
                fkey = name[-1]
            except:
                print 'name:',name, 'type:',repr(type), id(type)
                raise
            # ignore private values
            if startswith_any(fkey, self.private) is not None:
                return
            pref = startswith_max(fkey, self.prefix)
            # ignore prefixes
            if pref is not None:
                fkey = fkey[len(pref):]
            if len(fkey):
                key = fkey[0]
            else:
                print 'name:',name, 'type:',repr(type), id(type)
                # uh, let's try this then
                key = ''
            if key >= 'a' and key <= 'z': key = chr(ord(key) - 32)
            if dict.has_key(key): dict[key].append(type)
            else: dict[key] = [type]
        # Fill the dict
        [hasher(t) for t in self.processor.ir.asg.types.values()
         if isinstance(t, ASG.DeclaredTypeId) and
         not isinstance(t.declaration, ASG.Builtin)]

        # Now sort the dict
        def name_cmp(a,b):
            a, b = a.name, b.name
            res = cmp(a[-1],b[-1])
            if res == 0: res = cmp(a,b)
            return res
        for items in dict.values():
            items.sort(name_cmp)

        return dict

process(c_sg=Composite(c_nopriv, sg),
        link=Linker(),
        html=HTML.Formatter(title='SIEGE Reference Manual', index=[FileTree()], content=[
                            Scope(parts=[Summary(),Detail()]),
                            Source(),
                            Directory(src_dir=srcdir, base_path=srcdir),
                            XRef(),
                            FileDetails(),
                            FileIndex(),
                            #InheritanceTree(),
                            #InheritanceGraph(),
                            SGNameIndex(private=['`', '_', 'sgm'], prefix=['_', 'SG_', 'SG', 'sg'])]),
        dump=Dump.Formatter()
        #
        )
