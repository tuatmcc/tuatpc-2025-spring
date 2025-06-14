import re
import os
from lib.exceptions import FileNameError
from pathlib import Path


def main():
    paths = [root for root, dirs, _, in os.walk('.') if 'rime-out' in dirs]
    paths = list(map(Path, paths))

    print('[INFO] CHECK: extension')
    for path in paths:
        dir = path / 'rime-out' / 'tests'
        noext = [f for f in dir.glob('*') if not f.suffix]
        noext = [f for f in noext if str(f.stem) not in ['.stamp', 'TESTSET']]
        if noext:
            raise FileNameError()

    print('[INFO] OK')
    print('[INFO] CHECK: file denomination rule')
    for path in paths:
        dir = path / 'rime-out' / 'tests'
        ins = [f.stem for f in dir.glob('*.in')]
        expr = re.compile(r'\d+[_-].*\d+')
        for name in ins:
            if not expr.match(name):
                msg = '先頭に番号を振るような命名にするべき'
                raise FileNameError(msg)

    print('[INFO] OK')


if __name__ == '__main__':
    main()
