// Synthetic scene for fni-kodak-adjust test
// Last edited on 2006-05-12 14:41:50 by stolfi

// All scene dimensions in mm

global_settings { assumed_gamma 1.0 }

background{ color rgb < 0.100, 0.100, 0.100 > }

#declare empty = union{ }

#declare highlight_color = color rgb <1.00, 1.00, 1.00>;

// Stage
#include "stage.inc"

// Kodak chart
#include "Kodak-Q-13.inc"

// Kadok chart
#include "Kadok-Q-NN.inc"

// Light gauges
#include "light-gauge.inc"

#declare scene_center = < 0000.0, 0000.0, 0000.0 >;
#declare scene_radius = stage_radius;

#local eps = 0.05;

#declare scene =
  union {
    object { stage() }
    object { Kodak_Q_13()
      translate < 0000.0, +050.0, eps >
    }
    object { Kadok_Q_NN(3)  
      rotate -45*z
      translate < -70.0, -020.0, eps >
    }
    object { light_gauge translate < +050.0, -010.0, eps > }
  }

object { scene } 

// Camera
#declare image_rel_width = 1.1;
#declare image_rel_height = 0.75;
#declare camera_pos = < 0000.0, -100.0, +600.0 >;
#declare camera_focus = scene_center;
#declare camera_radius = scene_radius;
#include "camera.inc"
 
// Lights
#declare lamp_dist = +600.0;
#declare lamp_azim = 30;
#declare lamp_elev = 45;
#declare lamp_dir = vrotate(vrotate(x, -lamp_elev*y), lamp_azim*z);
#declare lamp_power = 1.100;
light_source {
  scene_center + lamp_dist*lamp_dir
  color lamp_power * < 1.000, 1.000, 1.000 >
  fade_distance lamp_dist
  fade_power 2
}
