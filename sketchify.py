#!/usr/bin/env python
import os
from gimpfu import *

"""
Implementation of a technique by Vidar Madsen. Taken from:
https://www.gimp.org/tutorials/Sketch_Effect/
"""

def sketchify(image, drawable, blur=7, threshold=80):
	pdb.gimp_image_undo_group_start(image)

	# Create new layer.
	layer2 = drawable.copy()
	pos = pdb.gimp_image_get_item_position(image, drawable)
	image.add_layer(layer2, pos)

	# Apply procedure.
	pdb.plug_in_gauss_rle2(image, layer2, blur, blur)
	pdb.gimp_invert(layer2)
	pdb.gimp_layer_set_opacity(layer2, 50)
	layer3 = pdb.gimp_image_merge_down(image, layer2, EXPAND_AS_NECESSARY)
	pdb.gimp_levels(layer3, 0, 120, 134, 1, 0, 255)
	pdb.gimp_desaturate_full(layer3, DESATURATE_LUMINOSITY)
	if threshold != 0:
		pdb.gimp_threshold(layer3, threshold, 255)

	pdb.gimp_image_undo_group_end(image)

register(
	"sketchify",
	"Sketchify",
	"Truns an image into a sketch.",
	"Amit Lavon", "Amit Lavon", "2016",
	"Sketchify",
	"*",
	[
		(PF_IMAGE, "image", "Input image", None),
		(PF_DRAWABLE, "drawable", "Layer to operate on", None),
		(PF_SLIDER, "blur", "Blur amount (pixels)", 7, (1, 10, 1)),
		(PF_SLIDER, "threshold", "Color threshold",
			80, (0, 255, 1))
	],
	[],
	sketchify, menu="<Image>/Filters")

def sketchify_file(f):
	# Apply filter.
	print("sketchify_file: " + f)
	img = pdb.gimp_file_load(f, f)
	sketchify(img, img.active_layer)

	# Save new file.
	parts = os.path.splitext(f)
	f = parts[0] + ".sketch" + parts[1]
	pdb.gimp_file_save(img, img.active_layer, f, f)
	gimp.delete(img)

register(
	"sketchify-file",
	"Sketchify File",
	"Turns an image file into a sketch.",
	"Amit Lavon", "Amit Lavon", "2016",
	"Sketchify File",
	"*",
	[
		(PF_STRING, "file", "Input file path", None)
	],
	[],
	sketchify_file)

main()

