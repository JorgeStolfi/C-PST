//  Basic colors, finishes, etc.
//  Last edited on 2001-08-19 18:05:20 by stolfi

// Colors named by hue

  #declare color_white_basic     = < 1.00, 1.00, 1.00 >;
  #declare color_black_basic     = < 0.00, 0.00, 0.00 >;
                                   
  #declare color_magenta_strong  = < 1.00, 0.10, 0.80 >;
  #declare color_red_basic       = < 1.00, 0.20, 0.00 >;
  #declare color_red_sunset      = < 1.00, 0.10, 0.00 >;
  #declare color_red_electric    = < 1.00, 0.10, 0.05 >;
  #declare color_red_light       = < 1.00, 0.75, 0.50 >;
  #declare color_orange_sunrise  = < 1.00, 0.40, 0.20 >;
  #declare color_orange_amber    = < 1.00, 0.50, 0.10 >;
  #declare color_yellow_danger   = < 1.00, 0.90, 0.00 >;
  #declare color_yellow_electric = < 1.00, 0.75, 0.00 >;
  #declare color_yellow_tungsten = < 1.00, 0.88, 0.50 >;
  #declare color_green_dark      = < 0.02, 0.25, 0.00 >;
  #declare color_green_darkish   = < 0.02, 0.37, 0.00 >;
  #declare color_green_medium    = < 0.05, 0.75, 0.00 >;
  #declare color_green_electric  = < 0.05, 1.00, 0.20 >;
  #declare color_green_emerald   = < 0.00, 1.00, 0.10 >;
  #declare color_green_lizard    = < 0.20, 1.00, 0.00 >;
  #declare color_green_lemon     = < 0.40, 1.00, 0.00 >;
  #declare color_blue_acqua      = < 0.50, 0.89, 1.00 >;
  #declare color_blue_basic      = < 0.25, 0.35, 0.50 >;
  #declare color_blue_electric   = < 0.20, 0.50, 1.00 >;
  #declare color_blue_dark       = < 0.00, 0.10, 0.40 >;
  #declare color_blue_darkish    = < 0.07, 0.20, 0.50 >;
  #declare color_blue_medium     = < 0.00, 0.20, 0.80 >;
  #declare color_blue_dusk       = < 0.00, 0.04, 0.15 >;
  #declare color_blue_night      = < 0.00, 0.01, 0.05 >;
  #declare color_purple_medium   = < 0.50, 0.15, 1.00 >;
                                   
  #declare color_white_bluish    = < 0.95, 0.97, 1.00 >;
  #declare color_grey_bluish     = < 0.50, 0.50, 0.60 >;
  #declare color_grey_light      = < 1.00, 0.95, 0.90 >;
  #declare color_grey_dark       = < 0.25, 0.25, 0.25 >;
  #declare color_grey_yellowish  = < 0.75, 0.73, 0.70 >;
  #declare color_beige_light     = < 0.77, 0.59, 0.31 >;
  #declare color_beige_straw     = < 0.89, 0.72, 0.45 >;
  #declare color_beige_cheese    = < 1.00, 0.85, 0.60 >;
  #declare color_brown_bronze    = < 0.70, 0.35, 0.00 >;
  #declare color_brown_rust      = < 0.30, 0.07, 0.00 >;
  #declare color_brown_wood      = < 0.50, 0.35, 0.10 >;
  #declare color_brown_mahogany  = < 0.35, 0.11, 0.05 >;
  #declare color_brown_ebony     = < 0.10, 0.08, 0.02 >;
  #declare color_pink_basic      = < 1.00, 0.85, 0.70 >;
  #declare color_pink_sunrise    = < 1.00, 0.60, 0.40 >;

// Metallized paint finish:

  #declare metal_finish =
    finish{
      metallic
      ambient 0.1
      diffuse 0.9
      specular 1 roughness 0.05
      brilliance 2
    }

// Enamel paint finish:

  #declare enamel_finish =
    finish{ ambient 0.05 diffuse 0.95 specular 0.40 roughness 0.010 } 
  
