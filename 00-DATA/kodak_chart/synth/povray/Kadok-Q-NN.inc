// Last edited on 2006-05-14 21:35:10 by stolfi
// A single-patch Kadok-like chart

// All dimensions are in mm

// GRAY SCALE PATCHES

#declare kadok_chart_patch_size_x = 10.0;
  // Width of each gray scale patch. 

#declare kadok_chart_patch_size_y = 15.0;
  // Width of each gray scale patch. 

// GRAY SCALE

#declare kadok_chart_scale_size_y = kadok_chart_patch_size_y;
  // Height of grayscale staircase. 

#declare kadok_chart_white_reflectance = 1.000;
  // Reflectance of brightest patch. 

#declare kadok_chart_black_reflectance = 0.000;
  // Reflectance of darkest patch. 

// PATCH NUMBERS

#declare kadok_chart_label_start_y = kadok_chart_scale_size_y + 8.00;
  // Dist from chart's bottom edge to start of patch numbers.

#declare kadok_chart_label_height = 6.00;
  // Nominal height of patch numbers.

// CHART HEADER

#declare kadok_chart_header_size_y = 28.0;
  // Width of gray background area above patch.

#declare kadok_chart_header_reflectance = 0.500;
  // Reflectance of the gray background area above the gray scale. 

// OVERALL CHART DIMENSIONS

#declare kadok_chart_total_size_y = kadok_chart_scale_size_y + kadok_chart_header_size_y;
  // External dimensions of the chart.

#declare kadok_chart_board_thickness = 0.75;
  // Guessed thickness of chart's stock paper (minus gray patches).

// WHITE MOUNTING FRAME 

#declare kadok_chart_frame_width = 8.0;
  // Assumed width of white mounting frame (all around).

#declare kadok_chart_frame_thickness = 0.50;
  // Assumed thickness of white mounting frame.

#declare kadok_chart_frame_reflectance = 0.950;
  // Reflectance of the white mounting frame .

// MISCELLANEOUS DIMENSIONS

#declare kadok_chart_ink_thickness = 0.05;

#local eps = 0.2*kadok_chart_ink_thickness; // A tiny amount for surface offsets etc.

#macro kadok_chart_patch(rf)
  // Generates a purely Lambertian patch with reflectance {rf}.
  // Lower corner is at origin, bottom at Z=0, top and sides slightly inset.
  #local szx = kadok_chart_patch_size_x;
  #local szy = kadok_chart_patch_size_y;
  #local szz = 0.20;
  #debug concat("\n", "kadok patch rf = ", str(rf,5,3), "\n")
  box { 
    < eps, eps, 0 >,
    < szx-eps, szy-eps, szz-eps >
    texture {
      pigment { color rgb rf * < 1, 1, 1 > }
      finish { ambient 0.00 diffuse 1.00 specular 0.00 }
    }
  }
#end

#macro kadok_chart_patch_label(lab)
  // Generates the label for a patch, given the string {lab}.
  // Lower corner is at origin, baseline along Y axis.
  // Bottom at Z=0, top slightly inset.
  #local szy = kadok_chart_label_height;
  #local szz = kadok_chart_ink_thickness;
  #local clr = (rf < 0.40 ? 0.980 : 0.020);
  #debug concat("label = ", lab)
  #local tiny = 0.05*szz;
  #local txt = 
    text { 
      ttf "tt-fonts/cour.ttf"
      lab szz-tiny, 0.0
      texture {
        pigment { color rgb < 0.980, 0.980, 0.000 > }
        finish { ambient 1.00 diffuse 0.00 specular 0.00 roughness 0.05 }
      }
      scale szy
    }
  #local lo = min_extent(txt);
  #local hi = max_extent(txt);
  object { txt
    rotate 90*z
    translate (hi.y - lo.y)/2*x
  }
#end

#macro kadok_chart_board(np)
  #local szx = np*kadok_chart_patch_size_x;
  #local szy = kadok_chart_total_size_y;
  #local szz = kadok_chart_board_thickness;
  #local rf = kadok_chart_header_reflectance;
  box { 
    < 0+eps, 0+eps, 0+eps >,
    < szx-eps, szy-eps, szz >
    texture {
      pigment { color rgb rf * < 1, 1, 1 > }
      finish { ambient 0.00 diffuse 0.99 specular 0.01 roughness 0.05 }
    }
  }
#end

#macro kadok_chart_frame(np)
  #local eps = 0.05; // Gap between frame and chart. 
  // Frame hole dimensions:
  #local hszx = np*kadok_chart_patch_size_x;
  #local hszy = kadok_chart_total_size_y;
  #local hszz = kadok_chart_board_thickness;
  // Frame width:
  #local fwd = kadok_chart_frame_width;
  // Outer frame dimensions: 
  #local fszx = hszx + 2*fwd;
  #local fszy = hszy + 2*fwd;
  #local fszz = kadok_chart_frame_thickness;
  #local rf = kadok_chart_frame_reflectance;
  difference { 
    box { 
      < 0+eps, 0+eps, 0+eps >,
      < fszx-eps, fszy-eps, fszz-eps >
      translate < -fwd, -fwd, 0 >
    }
    box { 
      < 0-eps, 0-eps, 0-eps >,
      < hszx+eps, hszy+eps, fszz+eps >
    }
    texture {
      pigment { color rgb rf * < 1, 1, 1 > }
      finish { ambient 0.00 diffuse 0.99 specular 0.01 roughness 0.05 }
    }
  }
#end

#macro Kadok_Q_NN(np)
  // The Kadok Q-NN chart with {np} steps.
  // Lower edge on the X axis, horizontally centered.
  #local sink = 0.05; // Vertical sinking of steps into base. 
  #local pdy = 0;
  #local pdz = kadok_chart_board_thickness - sink;
  
  #local ndy = kadok_chart_label_start_y;
  #local ndz = kadok_chart_board_thickness;
  
  #local rf0 = kadok_chart_white_reflectance;
  #local rf1 = kadok_chart_black_reflectance;
  union {
    object { kadok_chart_board(np) }
    object { kadok_chart_frame(np) }
    #local i = 0;
    #while (i < np)
      #local pdx = i*kadok_chart_patch_size_x;
      #local ndx = (i + 0.5)*kadok_chart_patch_size_x;
      #local t1 = (i + 0.0)/(np - 1.0);
      #local t0 = 1.0 - t1;
      #local rf = t0*rf0 + t1*rf1;
      object { 
        kadok_chart_patch(rf) 
        translate < pdx, pdy, pdz >
      }
      object { 
        kadok_chart_patch_label(str(rf,5,3)) 
        translate < ndx, ndy, ndz >
      }
      #local i = i + 1; 
    #end
    translate -np*kadok_chart_patch_size_x/2*x
  }
#end
  
