from building import *

cwd  = GetCurrentDir()
path = [cwd]

src  = Glob('*.c')

group = DefineGroup('mtest', src, depend = [''], CPPPATH = path)

Return('group')
