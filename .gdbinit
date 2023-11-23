python
import sys
import os
gccdir = [ dir for dir in os.listdir(sys.path[0] + '/../../') if dir.startswith('gcc-') ][0]
sys.path.insert(0, sys.path[0] + '/../../' + gccdir + '/python')
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end
