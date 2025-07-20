#!/usr/bin/env python3
from __future__ import print_function

import os
import shutil
import subprocess
import sys
from argparse import ArgumentParser

from nxpprog import NXPPROG_PY

SELF_DIRPATH = os.path.dirname(__file__)
REPO_ROOT_DIRPATH = os.path.join(SELF_DIRPATH, "..")

#DEFAULT_BIN_FILEPATH = os.path.join(REPO_ROOT_DIRPATH, "_build_lpc40xx_freertos", "lpc40xx_freertos.bin")

DEFAULT_BIN_FILEPATH = os.path.join(REPO_ROOT_DIRPATH, "_build_lpc40xx_cmpe30", "lpc40xx_cmpe30.bin")


#DEFAULT_BIN_FILEPATH = os.path.join(REPO_ROOT_DIRPATH, "_build_GPIO", "GPIO.bin")



FAILURE = r"""
_____ _    ___ _    _   _ ____  _____
|  ___/ \  |_ _| |  | | | |  _ \| ____|
| |_ / _ \  | || |  | | | | |_) |  _|
|  _/ ___ \ | || |__| |_| |  _ <| |___
|_|/_/   \_\___|_____\___/|_| \_\_____|
"""

SUCCESS = r"""
 ____  _   _  ____ ____ _____ ____ ____
/ ___|| | | |/ ___/ ___| ____/ ___/ ___|
\___ \| | | | |  | |   |  _| \___ \___ \
 ___) | |_| | |__| |___| |___ ___) |__) |
|____/ \___/ \____\____|_____|____/____/
"""


def get_args():
    arg_parser = ArgumentParser(
        description=r"Example usage: python flash.py -d COM6 -i ..\_build\sjtwo-c.bin"
    )
    arg_parser.add_argument(
        "-i",
        "--input",
        metavar="<FILE>",
        type=str,
        help="File path of firmware (.bin) to flash onto target",
        default=None,
    )

    # --device left here for backward compatibility, use -p or --port
    arg_parser.add_argument(
        "-p",
        "-d",
        "--port",
        "--device",
        metavar="<STRING or FILE>",
        type=str,
        help="USB to Serial device ID (i.e. COM6 or /dev/ttyUSB0)",
        default="",
    )
    arg_parser.add_argument("-v", "--verbose", action="store_true")

    args = arg_parser.parse_args()

    """
    Perform sanity checks against arguments
    """
    if args.input is None:
        args.input = DEFAULT_BIN_FILEPATH
        if not os.path.isfile(args.input):
            print(
                "Default firmware file [{}] does not exist! Specify firmware file path using `-i` option.".format(
                    os.path.abspath(args.input)
                )
            )
            sys.exit(1)  # Exit early

    if not args.input.endswith(".bin"):
        print(
            "The input firmware file [{}] must be in .bin format!".format(
                os.path.abspath(args.input)
            )
        )
        sys.exit(1)  # Exit early

    return args


def main():
    args = get_args()
    input_filepath = os.path.abspath(args.input)
    device_id = args.port
    verbose = args.verbose

    if device_id:
        print(
            "Flashing file [{}] using device ID [{}]".format(input_filepath, device_id)
        )
    else:
        print(
            "Flashing file [{}] using automatic port selection".format(input_filepath)
        )
    sys.stdout.flush()

    cmd = [
<<<<<<< HEAD
        get_python_exe(),
=======
        "python3",
>>>>>>> This is my first commit
        NXPPROG_PY,
        "--binary={}".format(input_filepath),
        "--device={}".format(device_id),
    ]
    if verbose:
        print("Using command:\n{}".format(" ".join(cmd)))
        sys.stdout.flush()

    try:
        error = subprocess.call(cmd)
        if not error:
            print(SUCCESS)
        else:
            print(FAILURE)
    except KeyboardInterrupt:
        error = 0

    return error


def get_python_exe():
    """
    :return: python executable file name, python3 if it exists in PATH else return python.
    For Windows, use python unconditionally. Windows comes installed with both stub `python3` and `python` programs that
    points to the Microsoft Store where the actual Python can be installed.
    Manual Python installations from the Python website directly come with `python` only.
    """

    ret = "python"
    if "win32" != sys.platform:
        test_exe_name = ["python", "python3"]
        for exe_name in test_exe_name:
            if shutil.which(exe_name):
                ret = exe_name
    return ret


if __name__ == "__main__":
    sys.exit(main())
