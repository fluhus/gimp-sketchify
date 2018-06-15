# GiMP Sketchify

A GiMP effect for turning an image into a sketch.

Implementation of a technique by Vidar Madsen.  
Taken from: https://www.gimp.org/tutorials/Sketch_Effect/

## Installation

### Linux

1. Get gimptool.

       sudo apt-get install libgimp2.0-dev

2. Run in terminal:

       chmod 544 sketchify.py
       $(gimptool-2.0 -n --install-script sketchify.py)/../plug-ins/

### Windows

See [official guide](https://en.wikibooks.org/wiki/GIMP/Installing_Plugins#Windows).

## Example Output

<img src="https://raw.githubusercontent.com/fluhus/gimp-sketchify/master/example.jpg" alt="Example Picture" height="300">

My sister and I being sketch models :-)
