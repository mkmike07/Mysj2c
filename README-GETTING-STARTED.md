# SJ2-C Getting Started

This guide provides step-by-step instructions to set up your development environment to give you to ability to develop firmware, build firmware, flash firmware onto an attached board, and monitor an attached board over serial.

## Target Outcome

Throughout this guide, we will:

1. Install software to set up your development environment
2. Build the Docker image
3. Build the firmware
4. Flash the firmware

By the end of this guide, you will have the following software installed on your computer:

* Docker
* Python
* Driver for USB-serial
* Visual Studio Code (a.k.a. vscode)
* Clang Format

Additionally by the end of this guide, you will be able to do the following:

* Modify source code
* Build Docker images
* Build firmware using a Docker container
* Flash firmware over a USB to serial connection
* Monitor firmware activity over a USB to serial connection

# Step 1. Installation

## Install Docker

1. Follow this [Docker Engine Installation Guide](https://docs.docker.com/engine/install/).
2. After installation, start Docker and leave it running in the background.
3. Verify Docker is installed correctly:

```bash
# This command should work
docker

# This should not produce a warning that the Docker daemon is not running.
docker info
```

## Install Python

1. For Windows, follow this [Python Installation Guide](installs/README.md#python). Mac and Linux should already have it preinstalled.

2. Verify Python is installed correctly:

```bash
# Ensure this command works on Windows
python --version

# Alternatively, this is fine too for Linux and Mac
python3 --version
```

## Install USB-Serial Driver

1. Install the driver:
    * For Mac, install `installs/drivers/mac/SiLabsUSBDriverDisk.dmg`.
    * For Windows, extract `installs/drivers/windows/CP210x_Windows_Drivers.zip` then run `CP210xVCPInstaller_x64.exe`.
    * For Linux, the driver comes bundled in the kernel, so you don't need to install it separately.

## Install Visual Studio Code

This step is highly recommended; install Visual Studio Code (i.e. VSCode) IDE for code editing.

1. Download and install [Visual Studio Code](https://code.visualstudio.com/download).

### (Optional) Install VSCode Extensions

2. Install Visual Code extensions:
    * [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
    * [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)

#### Install Clang Format

1. For Windows, follow this [Clang Format Dependency Installation Guide](installs/README.md#clang-format-windows-only).
2. Install Clang Format:

```bash
# Alternatively, use 'python3'
python -m pip install clang-format
```

3. Verify Clang Format is installed correctly:

```bash
# 1. Edit your code and save it in Visual Studio Code

# 2. This will run unit tests and compile the `lpc40xx_freertos` project
scons

# 3. Finally, flash the project
python nxp-programmer/flash.py
```

### More advanced stuff
```bash
python ./run build
```

2. Ensure your target device is attached via USB-serial connection.

3. Flash the compiled firmware `.bin` file:

```bash
python ./run flash
```

# Step 4. Familiarize Yourself With the `run` Script

At this point you should be ready for development. This step is optional. In this step, learn more about the `run` script, a multi-purpose tool for development with the ability to build, flash, etc.

Here are some other ways to use the `run` script:

```bash
python nxp-programmer/flash.py --port <Device Port> --input <.bin file path>`
# <Device Port>    is your serial port
# <.bin file path> is the path to your firmware you want to load to the board

# The script can auto-detects your `--port`, so you should be able to flash using:
python nxp-programmer/flash.py --input _build_lpc40xx_freertos/lpc40xx_freertos.bin`
```

### More `flash.py` Examples

Providing an explicit `--port` may be faster to program, but initially you would need to know what `--port` your SJ board is at. Try using `python nxp-programmer/flash.py` which will use the default binary file, and automatically find the port for you, otherwise follow the examples below:

```bash
# All these examples will default to use "_build_lpc40xx_freertos/lpc40xx_freertos.bin"

# Example on Windows:
python nxp-programmer/flash.py --port COM6

# Example on Linux:
python nxp-programmer/flash.py --port /dev/ttyUSB

# Example on Mac:
python nxp-programmer/flash.py --port /dev/tty.SLAB_USBtoUART

# ##################################
# Fully explicit command on windows:
python nxp-programmer/flash.py --port COM6 --input _build_lpc40xx_freertos/lpc40xx_freertos.bin
```

### Advanced Tips

* You can use `-i` (single dash) in place of `--input`
* You can use `-p` (single dash) in place of `--port`
* If `-i` is not provided, then the tool will default to `_build_lpc40xx_freertos/lpc40xx_freertos.bin`
* So, you could use: `python nxp-programmer/flash.py --device /dev/ttyUSB`
