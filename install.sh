# Installs sketchify into GIMP.
echo "To install run the following command:"
echo "$(gimptool-2.0 -n --install get_pixels.c)" -std=c99 "&&" "$(gimptool-2.0 -n --install-script sketchify.py)/../plug-ins/"

