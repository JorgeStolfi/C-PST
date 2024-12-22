// Last edited on 2006-05-12 01:48:05 by stolfi
// Light gauge

#declare light_gauge_radius = 10.0;

#declare light_gauge = 
  sphere { 
    < 0,0,light_gauge_radius >, light_gauge_radius
    texture {
      pigment { color rgb < 1.000, 1.000, 1.000 > }
      finish { ambient 0.00 diffuse 1.00 specular 0.00 roughness 0.05 }
    }
  }
