#include <stdlib.h>
#include <libgimp/gimp.h>

static void query (void);
static void run   (const gchar	  *name,
				   gint			  nparams,
				   const GimpParam  *param,
				   gint			 *nreturn_vals,
				   GimpParam	   **return_vals);

GimpPlugInInfo PLUG_IN_INFO =
{
	NULL,
	NULL,
	query,
	run
};

MAIN()

static void query (void)
{
	static GimpParamDef in_args[] =
	{
		{
			GIMP_PDB_INT32,
			"run-mode",
			"Run mode"
		},
		{
			GIMP_PDB_IMAGE,
			"image",
			"Input image"
		},
		{
			GIMP_PDB_DRAWABLE,
			"drawable",
			"Input drawable"
		}
	};

	static GimpParamDef out_args[] =
	{
		{
			GIMP_PDB_INT32,
			"pixels-size",
			"Number of elements in result."
		},
		{
			GIMP_PDB_FLOATARRAY,
			"pixels",
			"A double array representing the pixel values. Dimentions: W*H*BPP."
		}
	};

	gimp_install_procedure (
		"gimp-plugin-get-pixels",
		"Get Pixels",
		"Converts a drawable to an array of doubles, representing the pixel values.",
		"Amit Lavon",
		"Amit Lavon",
		"2016",
		"",  // Menu entry name.
		"RGB*, GRAY*",
		GIMP_PLUGIN,
		G_N_ELEMENTS(in_args), G_N_ELEMENTS(out_args),
		in_args, out_args);

	//gimp_plugin_menu_register ("plug-in-sketchify",
	//						   "<Image>/Filters");
}

static void run(const gchar      *name,
				gint             nparams,
				const GimpParam  *param,
				gint             *nreturn_vals,
				GimpParam        **return_vals)
{
	// Prepare return values.
	static GimpParam result[3];
	*nreturn_vals = G_N_ELEMENTS(result);
	*return_vals  = result;

	result[0].type = GIMP_PDB_STATUS;
	result[0].data.d_status = GIMP_PDB_SUCCESS;

	// Extract metrics from drawable.
	GimpDrawable* drawable = gimp_drawable_get(param[2].data.d_drawable);
	gint h   = drawable->height;
	gint w   = drawable->width;
	gint bpp = drawable->bpp;
	gint n = w*h*bpp;

	result[1].type = GIMP_PDB_INT32;
	result[1].data.d_int32 = n;
	result[2].type = GIMP_PDB_FLOATARRAY;
	result[2].data.d_floatarray = calloc(n, sizeof(gdouble));

	// Get pixel values.
	GimpPixelRgn rgn;
	gimp_pixel_rgn_init(&rgn, drawable, 0, 0, w, h, FALSE, FALSE);
	guchar* buf = calloc(n, sizeof(guchar));
	gimp_pixel_rgn_get_rect(&rgn, buf, 0, 0, w, h);

	for (int i = 0; i < n; i++) {
		result[2].data.d_floatarray[i] = (gdouble)buf[i];
	}
	free(buf);
}

