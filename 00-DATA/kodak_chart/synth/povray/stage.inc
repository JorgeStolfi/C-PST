// Last edited on 2006-05-12 08:58:29 by stolfi
// The stage

// All dimensions are in mm.

#local eps = 0.05;

#macro stage_base(szx,szy,szz)
  // szx, szy, szz = board dimensions.
  // The board's top surface is at Z=0, the other sides are inset by {eps}.

  #local rx = szx/2;
  #local ry = szy/2;
  #local dz = szz;

  box { 
    < -rx+eps, -ry+eps, -dz+eps >,
    < +rx-eps, +ry-eps, 0-eps >
    texture {
      pigment { color rgb < 0.930, 0.930, 0.930 > }
      finish { ambient 0.00 diffuse 1.00 }
    }
  }
#end

#macro stage_grid(nx,ny,step,linewidth)
  // nx,ny = number of grid cells in each direction.
  // step = width and height of each grid cell.
  #local r = linewidth/2;
  #local th = 0.02; // Ink thickness above paper surface.
  union {
    #local ix = 0;
    #while (ix <= nx)
      cylinder {
        < ix*step, 0, 0 >, 
        < ix*step, ny*step, 0 >,
        r
      }
      #local ix = ix + 1;
    #end
    #local iy = 0;
    #while (iy <= ny)
      cylinder {
        < 0, iy*step, 0 >, 
        < nx*step, iy*step,  0 >,
        r
      }
      #local iy = iy + 1;
    #end
    // Round joints:
    sphere { < 0, 0, 0 >, r }
    sphere { < nx*step, 0, 0 >, r }
    sphere { < 0, ny*step, 0 >, r }
    sphere { < nx*step, ny*step, 0 >, r }
    scale < 1, 1, th/r >
    translate -0.5*step*< nx, ny, 0 >
    texture {
      pigment { color rgb < 0.010, 0.010, 0.010 > }
      finish  { ambient 0.00 diffuse 0.80 specular 0.20 roughness 0.01 }
    }
  }
    
#end

#declare stage_size_x = 11*25.4;
#declare stage_size_y = 8.5*25.4;
#declare stage_base_thickness = 10.0;
#declare stage_radius = vlength( < stage_size_x, stage_size_y, 0 >/2 );

#declare stage_grid_nx = 25;
#declare stage_grid_ny = 17;
#declare stage_grid_step = 10.0;
#declare stage_grid_line_width = 0.40;

#macro stage() 
  #local szx = stage_size_x;
  #local szy = stage_size_y;
  #local szz = stage_base_thickness;
  
  #local nx = stage_grid_nx;
  #local ny = stage_grid_ny;
  #local step = stage_grid_step;
  #local lwd = stage_grid_line_width;
  union {
    stage_base(szx,szy,szz)
    stage_grid(nx,ny,step,lwd)
  }
#end
