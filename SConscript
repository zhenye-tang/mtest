from building import *

cwd  = GetCurrentDir()
objs = []
path = [cwd + '/src']
src  = Glob('src/mtest.c')

group = DefineGroup('mtest', src, depend = ['PKG_USING_MTEST'], CPPPATH = path)

objs = group

Return('objs')
