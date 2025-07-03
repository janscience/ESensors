"""Fix sensor time stamps.

## Command line script

The module can be run as a script from the command line:

```sh
> fixsensortimestamps -s 20250701T173420 logger-20190101T000012-sensors.csv
```

Running
```sh
fixsensortimestamps --help
```
prints
```text
usage: fixsensortimestamps.py [-h] [--version] -s STARTTIME [-n] file

Fix time stamps in sensors file.

positional arguments:
  file          sensors file

options:
  -h, --help    show this help message and exit
  --version     show program's version number and exit
  -s STARTTIME  new start time of the first sensor reading
  -n            do not modify the files, just report what would be done.

version 1.0 by Benda-Lab (2025-2025)
```

## Functions

- `write_sensors()`: write sensors data to file and modify time stamps.

"""


import os
import sys
import argparse
import datetime as dt
from pathlib import Path
from audioio import replace_datetime


def write_sensors(path, lines, start_time):
    """ Write sensors data to file and modify time stamps.
    
    Parameters
    ----------
    path: str
        Path where to write modified sensors data.
    lines: list of str
        Content of the original file.
    start_time: datatime
        Time of the first sensor reading.
    """
    if len(lines) < 2:
        return
    with open(path, 'w') as df:
        df.write(lines.pop(0))
        file_time = dt.datetime.fromisoformat(lines[0].split(',')[0])
        delta_t = start_time - file_time
        for line in lines:
            parts = line.split(',')
            time = dt.datetime.fromisoformat(parts[0])
            time += delta_t
            parts[0] = time.isoformat()
            df.write(','.join(parts))


def demo(start_time, path, no_mod=False):
    """Modify time stamps of sensors file.

    Parameters
    ----------
    start_time: str
        Time stamp of the first reading.
    path: str
        Path of sensor file.
    no_mod: bool
        Do not modify the file, just report what would be done.    
    """
    start_time = dt.datetime.fromisoformat(start_time)
    lines = []
    with open(path, 'r') as sf:
        lines = sf.readlines()
    write_sensors(path, lines, start_time)
    p = Path(path)
    new_path = p.with_stem(replace_datetime(p.stem, start_time))
    os.rename(path, new_path)
    print(f'{path} -> {new_path}')
    
            
def main(*cargs):
    """Call demo with command line arguments.

    Parameters
    ----------
    cargs: list of strings
        Command line arguments as provided by sys.argv[1:]
    """
    __version__ = '1.0'
    __year__ = '2025'
    # command line arguments:
    parser = argparse.ArgumentParser(add_help=True,
        description='Fix time stamps in sensors file.',
        epilog=f'version {__version__} by Benda-Lab (2025-{__year__})')
    parser.add_argument('--version', action='version', version=__version__)
    parser.add_argument('-s', dest='starttime', default=None, type=str, required=True,
                        help='new start time of the first sensor reading')
    parser.add_argument('-n', dest='nomod', action='store_true',
                        help='do not modify the files, just report what would be done.')
    parser.add_argument('file', type=str, nargs=1,
                        help='sensors file')
    if len(cargs) == 0:
        cargs = None
    args = parser.parse_args(cargs)

    demo(args.starttime, args.file[0], args.nomod)


if __name__ == "__main__":
    main(*sys.argv[1:])
