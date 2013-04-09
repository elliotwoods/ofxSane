# ofxSANE

Wraps SANE scanner library for interfacing with data from scanner hardware (e.g. flatbed document scanners).

Original code by Kyle McDonald.

Some amends by Elliot Woods.

ofxSane code published under MIT license.

# Installation

## OSX 

Per project you need to:

1. Drag and drop the contents of `ofxSane/libs` and `ofxSane/src` into your project
2. Add `../../../addons/ofxSane/libs/sane/include` to your `Header Search Paths` project property.

The example should work out of the box on OSX. But if not, then try the following:

1. Clone the GitHub http://git.debian.org/git/sane/sane-backends.git to somewhere on your hard drive `git clone http://git.debian.org/git/sane/sane-backends.git`
2. Using terminal, go inside the repo, and then into the `backend/` directory
3. Type `CC="gcc -m32" ./configure`, hit enter.
3. Type `make -j8`, hit enter.
4. Type `sudo make install`, hit enter.
5. Enter your system password

This should install `libsane.1.dylib` and folder `sane` into `/usr/local/lib`. Drag and drop both of these into your project.