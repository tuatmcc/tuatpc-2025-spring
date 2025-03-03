import os
from pathlib import Path
import shutil
import zipfile

if not os.path.isdir('./testcase'):
    os.mkdir('./testcase')
    os.mkdir('./testcase/input')
    os.mkdir('./testcase/output')

pathlist = Path('./rime-out/tests').glob('*.in')
for path in pathlist:
    casename = path.name[:-3]
    shutil.copy(path, './testcase/input/' + casename + '.txt')
    shutil.copy(str(path)[:-3] + '.diff', './testcase/output/' + casename + '.txt')

shutil.make_archive('converted_testcases', format='zip', root_dir='testcase')
shutil.rmtree('./testcase')