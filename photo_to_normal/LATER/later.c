/* Stuff to add later to the program. */
/* Last edited on 2006-04-29 00:09:26 by stolfi */ 

  PROG_HELP:

  "  [ -nearest | -interpolate ] \\\n" \
  "  [ -resolution NUM ] \\\n" \
  "  [ -cubify ] \\\n" \

  PROG_INFO (LIGHT GAUGES):

  "  The user may specify two or more gauge images.  In that case," \
  " the program will either use the gauge whose nominal position" \
  " {(POSX,POSY)} is nearest to the center of the pixel under" \
  " consideration (if \"-nearest\" was specified), or interpolate" \
  " between nearby gauges (if \"-interpolate\" was specified).\n" \
  "\n" \

  PROG_INFO (OPTIONS):

  "  -nearest\n" \
  "    Specifies that the normal computation for a pixel" \
  " with center at {(x,y)} should use the light field gauge whose" \
  " nominal position is closest to {(x,y)}. The opposite" \
  " of \"-interpolate\".  True by default." \
  "\n" \
  "  -interpolate\n" \
  "    Specifies that the normal computation for a pixel" \
  " with center at {(x,y)} should use an artificial light field gauge" \
  " obtained by interpolating three nearby gauges according"
  " to their distances from {(x,y)}. The opposite" \
  " of \"-nearest\".  False by default." \
  "\n" \

  options_t:
  
    bool_t nearest;     /* Use nearest gauge. */
    bool_t interpolate; /* Interpolate gauges. */
    bool_t cubify;      /* TRUE uses cube bucket grid. */
    double resolution;  /* Resolution of normal table. */
  
  ltn_parse_options:

    o->nearest = argparser_keyword_present(pp, "-nearest");
    o->interpolate = argparser_keyword_present(pp, "-interpolate");
    o->cubify = argparser_keyword_present(pp, "-cubify");
    if (argparser_keyword_present(pp, "-resolution"))
      { o->resolution = argparser_get_next_double(pp, 1.0e-20, 1.0); }
    else
      { o->resolution = 0.005; }


    /* Global consistency checks: */
    if ((o->nearest) && (o->interpolate))
      { argparser_error(pp, "conflicting options \"-nearest\" and \"-interpolate\""); }

    /* Provide defaults: */
    if ((! o->nearest) && (! o->interpolate)) { o->nearest = TRUE; }
