//  Coordinate axes for MP logo
//  Last edited on 2000-10-25 04:19:53 by stolfi

#declare axes = 
  union{
    cylinder{ <0,0,0>, <1.5,0,0>, 0.015
      texture{ pigment{ color rgb <1.0,0.2,0.2> } finish { ambient 1 diffuse 0 } }
    }
    cylinder{ <0,0,0>, <0,1.5,0>, 0.015
      texture{ pigment{ color rgb <0.0,1.0,0.0> } finish { ambient 1 diffuse 0 } }
    }
    cylinder{ <0,0,0>, <0,0,1.5>, 0.015
      texture{ pigment{ color rgb <0.3,0.3,1.0> } finish { ambient 1 diffuse 0 } }
    }
  }
  
