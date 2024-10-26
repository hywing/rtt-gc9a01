from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add gc9a01 src files.
if GetDepend('PKG_USING_GC9A01'):
    src += Glob('src/lcd_init.c')
    src += Glob('src/lcd.c')

if GetDepend('PKG_USING_GC9A01_SAMPLE'):
    src += Glob('examples/gc9a01_tests.c')

# add gc9a01 include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('GC9A01', src, depend = ['PKG_USING_GC9A01'], CPPPATH = path)

Return('group')