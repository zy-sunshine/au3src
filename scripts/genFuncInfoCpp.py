import os
import sys
import re
from os.path import join as pathjoin, exists as pathexists, basename, splitext
from collections import OrderedDict
from jinja2 import Environment

class FuncInfoCppGenner(object):
    def __init__(self, rootdir):
        self.rootdir = rootdir
        self.env = Environment()

    def work(self):
        moduleHPaths = []
        for root, dirs, files in os.walk(self.rootdir):
            for fname in files:
                if fname.startswith('Module') and fname.endswith('.h'):
                    moduleHPaths.append(pathjoin(root, fname))

        genMap = OrderedDict()
        for fpath in moduleHPaths:
            genMap[fpath] = self.parseHFileFuncInfos(fpath)

        allFuncInfos = []
        chunks = []
        for fpath, funcInfos in genMap.items():
            outPath = pathjoin('gen', basename(fpath))
            chunk = self.genFileChunk(fpath, funcInfos, outPath)
            chunks.append(chunk)
            allFuncInfos.extend(funcInfos)

        allFuncInfos.sort(key=lambda x: x['szName'])
        fileContent = self.genFile(chunks, allFuncInfos)
        if not pathexists('src/gen'):
            os.makedirs('src/gen')

        with open('src/gen/ModulesGen.h', 'wt') as fp:
            fp.write(fileContent)

    def genFile(self, chunks, allFuncInfos):
        return self.env.from_string('''#pragma once
{% for chunk in chunks %}{{ chunk }}{% endfor %}
AU3_FuncInfo funcInfo[] = {
{% for info in funcInfos %}
    {NULL, "{{ info["szModule"] }}", "{{ info["szName"].upper() }}", &F_{{ info["szName"] }}, {{ info["nMin"] }}, {{ info["nMax"] }}},
{% endfor %}
};
        ''').render(
            chunks=chunks,
            funcInfos=allFuncInfos,
        )

    # AUT_RESULT    F_BitAND(VectorVariant &vParams, Variant &vResult);
    FUNC_PATTERN = re.compile(r'AUT_RESULT\W+F_([\w\d_]+)\(.*')
    def parseHFileFuncInfos(self, fpath):
        moduleHPath, moduleCls = self.pathToModule(fpath)
        result = []
        with open(fpath, 'rt') as fp:
            for line in fp.readlines():
                line = line.strip()
                if line.startswith('//'): continue
                idx = line.find('//')
                comment = ''
                if idx >= 0:
                    line = line[:idx]
                    comment = line[idx+2:]
                match = self.FUNC_PATTERN.search(line)
                if match:
                    szName = match.groups()[0]
                    if comment:
                        slist = [ int(item) for item in comment.split(',') ]
                        nMin, nMax = slist[0], slist[1]
                    else:
                        nMin, nMax = 1, 1
                    result.append({
                        'szModule': moduleCls,
                        'szName': szName,
                        'nMin': nMin,
                        'nMax': nMax,
                    })
        return result

    def pathToModule(self, fpath):
        idx = fpath.find('Modules')
        moduleHPath = fpath[idx:].replace('\\', '/')
        moduleCls = splitext(basename(fpath))[0]
        return moduleHPath, moduleCls

    def genFileChunk(self, fpath, funcInfos, outPath):
        moduleHPath, moduleCls = self.pathToModule(fpath)
        content = self.env.from_string('''
#include "{{ moduleHPath }}"
{% for info in funcInfos %}
AUT_RESULT F_{{ info["szName"] }}(void *self, VectorVariant &vParams, Variant &vResult)
{ return (({{ moduleCls }}*)self)->F_{{ info["szName"] }}(vParams, vResult); }
{% endfor %}
            ''').render(
            moduleHPath=moduleHPath, moduleCls=moduleCls,
            funcInfos=funcInfos
        )
        return content

if __name__ == '__main__':
    FuncInfoCppGenner(sys.argv[1]).work()
