
# How to develop and test the TestDrive Arduino library

## Installation Guide

### Toolbox

#### OS X

Before starting, please make sure you have the following installed:

*	[Arduino IDE](http://arduino.cc/en/main/software) - Download the app from the website
*	[Homebrew](http://mxcl.github.io/homebrew/) - Follow the instructions on their website
*	[Git](http://git-scm.com/) - use `brew install git` to install the latest version

#### Linux

Before starting we need to install `git` and `arduino`:

```Bash
$ sudo apt-get update && sudo apt-get upgrade
$ sudo apt-get install git arduino
```

### 1. Install `avr-gcc`, `binutils`, `avr-libc` and `avrdude`

#### OS X

We've made a [Homebrew](http://brew.sh/) `formula` that you can `tap`:

```Bash
$ brew tap WeAreLeka/avr
$ brew install avr-libc
```

Check that everything has been installed properly by running `avr-gcc -v` and `avrdude -v`. If `avrdude` is missing, install it with:

```Bash
$ brew install avrdude
```

#### Linux

```Bash
$ sudo apt-get install gcc-avr binutils avr-libc avrdude
```

Make sure everything is up and running by running `avr-gcc -v` and `avrdude -v`.

### 2. Clone `TestDrive-Arduino` repository from Github

Simply clone the repo:

```Bash
$ git clone https://github.com/blakejakopovic/TestDrive-Arduino.git
```

Initialize and update submodules:

```Bash
$ cd TestDrive-Arduino
$ git submodule update --init --recursive
```

### 3. Install `pySerial`

To upload the program, we need to reset the Arduino board. This is done using a `python script` stored in `./Arduino-Makefile/bin`

First, if you don't already have Python, you can install it using Homebrew on OS X:

```Bash
$ brew install python
```

Then install `pySerial`:

```Bash
$ pip install pyserial
```

### 4. Build the project

Let's build 'TestDrive-Arduino':

First `cd` to `TestDrive-Arduino` folder and copy the `Makefile-<os name>.mk` for your system:

```Bash
$ cp Makefile-OSX.mk ./Makefile

# or if you're running Linux

$ cp Makefile-Linux.mk ./Makefile
```

Then compile and upload your code to an **Arduino Uno**:

```Bash
$ make
$ make upload
```

If it's not working, make sure everything has been installed correctly and check your `Makefile` configuration. Also make sure you are using and `Arduino Uno`.