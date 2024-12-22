// Last edited on 2006-05-14 21:34:32 by stolfi
// The Kodak Q-13 chart

// All dimensions are in mm

// OVERALL DIMENSIONS

#declare kodak_chart_total_size_x = 203.0;
#declare kodak_chart_total_size_y = 60.0;
  // External dimensions of the Q-13.

#declare kodak_chart_board_thickness = 0.75;
  // Thickness of chart's stock paper, minus gray patches (guessed).

// GRAY SCALE

#declare kodak_chart_scale_size_x = 180.0;
  // X-size of gray scale, minus the first and last patches.

#declare kodak_chart_scale_size_y = 22.0;
  // Y-size of gray scale staircase. 

// GRAY SCALE PATCHES

#declare kodak_chart_num_patches = 20;
  // Number of patches in gray scale, including `white' and `black'. 

#declare kodak_chart_patch_size_x = kodak_chart_scale_size_x/(kodak_chart_num_patches-2);
  // X-size of each gray scale patch, except first and last. 

#declare kodak_chart_end_patch_size_x = (kodak_chart_total_size_x - kodak_chart_scale_size_x)/2;
  // X-size of first and last gray patches. 

// PATCH LABELS

#declare kodak_chart_patch_label_baseline_y = kodak_chart_scale_size_y + 8.00;
  // Dist from chart's bottom edge to baseline of patch numbers (guessed).

#declare kodak_chart_patch_label_size_y = 6.00;
  // Baseline height of patch labels (guessed).

// CHART TITLE

#declare kodak_chart_title_baseline_y = 48.0;
  // Dist from chart's bottom edge to baseline of chart's title (guessed).

#declare kodak_chart_title_margin = 2.75;
  // Dist from chart's left edge to start of chart's title (guessed).

#declare kodak_chart_title_size_y = 10.0;
  // Baseline height of title text (guessed).

// CHART BOARD 

#declare kodak_chart_board_reflectance = 0.224;
  // Reflectance of the gray background area above the gray scale. 

// WHITE MOUNTING FRAME 

#declare kodak_chart_frame_size_x = 10.0;
  // Assumed X-size of white mounting frame (all around).

#declare kodak_chart_frame_thickness = 0.50;
  // Assumed thickness of white mounting frame.

#declare kodak_chart_frame_reflectance = 0.950;
  // Reflectance of the white mounting frame .

// MISCELLANEOUS DIMENSIONS

#declare kodak_chart_ink_thickness = 0.05;

#local eps = 0.2*kodak_chart_ink_thickness; // A tiny amount for surface offsets etc.

#macro kodak_chart_patch(i)
  // Generates the patch {i}.
  // Lower corner is at origin, bottom at Z=0, top and sides slightly inset.
  #if ((i = 0) | (i = 19))
    #local szx = kodak_chart_end_patch_size_x;
  #else
    #local szx = kodak_chart_patch_size_x;
  #end
  #local szy = kodak_chart_scale_size_y;
  #local szz = 0.20;
  #local rf = pow(0.10, i*0.10 + 0.05);
  #debug concat("\n", "patch number ", str(i,-2,0), " rf = ", str(rf,5,3), "\n")
  box { 
    < eps, eps, 0 >,
    < szx-eps, szy-eps, szz-eps >
    texture {
      pigment { color rgb rf * < 1, 1, 1 > }
      finish { ambient 0.00 diffuse 0.95 specular 0.05 roughness 0.05 }
    }
  }
#end

#macro kodak_chart_patch_label(i)
  // Generates the number for patch {i}.
  // Lower corner is at origin, bottom at Z=0, top slightly inset.
  #local szy = kodak_chart_patch_label_size_y;
  #local szz = kodak_chart_ink_thickness;
  #local lab = str(i,-2,0)
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
    translate -(hi.x - lo.x)/2*x
  }
#end

#macro kodak_chart_title()
  // Generates the title for the chart.
  // Lower corner is at origin, bottom at Z=0, top slightly inset.
  #local szy = kodak_chart_title_size_y;
  #local szz = kodak_chart_ink_thickness;
  #local tiny = 0.05*szz;
  text { 
    ttf "tt-fonts/cour.ttf"
    "Simulated Kodak Q-13 chart" szz-tiny, 0.0
    texture {
      pigment { color rgb < 0.980, 0.980, 0.000 > }
      finish { ambient 1.00 diffuse 0.00 specular 0.00 roughness 0.05 }
    }
    scale szy
  }
#end

#macro kodak_chart_board()
  // The chart board.
  // Lower left corner at origin.
  #local szx = kodak_chart_total_size_x;
  #local szy = kodak_chart_total_size_y;
  #local szz = kodak_chart_board_thickness;
  #local rf = kodak_chart_board_reflectance;
  box { 
    < 0+eps, 0+eps, 0+eps >,
    < szx-eps, szy-eps, szz >
    texture {
      pigment { color rgb rf * < 1, 1, 1 > }
      finish { ambient 0.00 diffuse 0.99 specular 0.01 roughness 0.05 }
    }
  }
#end

#macro kodak_chart_frame()
  // A white frame for the Kodak Q-13 chart.
  // Lower left corner of hole is at origin.
  #local eps = 0.05; // Gap between frame and chart. 
  // Frame hole dimensions:
  #local hszx = kodak_chart_total_size_x;
  #local hszy = kodak_chart_total_size_y;
  #local hszz = kodak_chart_board_thickness;
  // Frame size_x:
  #local fwd = kodak_chart_frame_size_x;
  // Outer frame dimensions: 
  #local fszx = kodak_chart_total_size_x + 2*fwd;
  #local fszy = kodak_chart_total_size_y + 2*fwd;
  #local fszz = kodak_chart_frame_thickness;
  #local rf = kodak_chart_frame_reflectance;
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

#macro Kodak_Q_13()
  // The Kodak Q-13 chart.
  // Lower edge on the X axis, horizontally centered.
  #local np = kodak_chart_num_patches;
  #local sink = 0.05; // Vertical sinking of gray patches into base. 
  #local pdy = 0;
  #local pdz = kodak_chart_board_thickness - sink;

  #local ndy = kodak_chart_patch_label_baseline_y;
  #local ndz = kodak_chart_board_thickness;

  #local tdx = kodak_chart_title_margin;
  #local tdy = kodak_chart_title_baseline_y;
  #local tdz = kodak_chart_board_thickness;
  union {
    object { kodak_chart_board() }
    object { kodak_chart_frame() }
    #local i = 0;
    #while (i < np)
      #if (i = 0)
        #local pdx = 0;
      #else
        #local pdx = kodak_chart_end_patch_size_x + (i - 1)*kodak_chart_patch_size_x;
      #end
      #local ndx = kodak_chart_end_patch_size_x/2 + i*kodak_chart_patch_size_x;
      object { 
        kodak_chart_patch(i) 
        translate < pdx, pdy, pdz >
      }
      object { 
        kodak_chart_patch_label(i) 
        translate < ndx, ndy, ndz >
      }
      #local i = i + 1; 
    #end
    object { 
      kodak_chart_title() 
      translate < tdx, tdy, tdz >
    }
    translate -kodak_chart_total_size_x/2*x
  }
#end
