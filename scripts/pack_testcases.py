import os
from pathlib import Path
import shutil

def make_zip(problem_path: Path):
    testcase_path = problem_path / 'testcase'

    os.mkdir(testcase_path)
    os.mkdir(testcase_path / 'input')
    os.mkdir(testcase_path / 'output')
    
    for path in (problem_path / 'rime-out/tests').glob('*.in'):
        casename = path.name[:-3]
        shutil.copy(path, testcase_path / 'input' / (casename + '.txt'))
        shutil.copy(str(path)[:-3] + '.diff', testcase_path / 'output' / (casename + '.txt'))

    shutil.make_archive(f'{problem_path.name}', format='zip', root_dir=testcase_path)
    shutil.rmtree(str(testcase_path))

# 各ディレクトリが問題用のディレクトリか判定する
for path in Path('./').glob('*'):
    if path.is_dir() and (path / 'PROBLEM').exists():
        make_zip(path)
        print(f'Converted testcases for {path.name}')