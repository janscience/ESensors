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
```

## Functions


"""


import re
import os
import sys
import argparse
import datetime as dt
import pandas as pd
from pathlib import Path
from audioio import parse_datetime, replace_datetime


def load_sensors(path):
    data = pd.read_csv(path, sep=',')
    tc = data.columns[0]
    data[tc] = pd.to_datetime(data[tc])
    data[tc] = pd.Series(data[tc].dt.to_pydatetime(), dtype=object)
    header = list(data)[1:]
    return data, header


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
    #start_time = dt.datetime.fromisoformat(start_time)
    name_time = parse_datetime(Path(path).stem)
    data, header = load_sensors(path)
    print(data)
    #print(data[0])
    """
    if name_time is not None:
        p = Path(path)
        np = p.with_stem(replace_datetime(p.stem, start_time))
        if not no_mod:
            os.rename(fp, np)
        print(f'{fp} -> {np}')
    else:
        print(f'{fp}: {orig_time} -> {start_time}')
    """
    
            
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
                        help='new start time of the first file')
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
