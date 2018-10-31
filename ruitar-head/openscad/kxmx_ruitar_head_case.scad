module headstock (){
  difference() {
    translate ([(192-29)-13,0,0]){
     difference () {
         translate ([0,-20,0]) difference () {
             translate ([-192+29,-30.5,-1]) cube([192,61,1]);
             translate ([29,0,-2]) rotate([0,0,43.5]) cube([50,50,3]);
             translate ([29,0,-2]) rotate([0,0,-133.6]) cube([50,50,3]);
         }
        translate ([-192,-55,-2]) rotate ([0,0,-17]) cube([192,61,3]);
     }
    }
  translate ([-13,0,-2]) rotate ([0,0,39]) cube([20,20,3]);
  }
}

module case (){
  difference() {
    translate ([(192-29)-13,0,0]){
     difference () {
         translate ([0,-20,0]) difference () {
             translate ([-192+29,-30.5,0]) cube([192,61,9.5]);
             translate ([29,0,-1]) rotate([0,0,43.5]) cube([50,50,11]);
             translate ([29,0,-1]) rotate([0,0,-133.6]) cube([50,50,11]);
         }
        translate ([-192,-55,-1]) rotate ([0,0,-17]) cube([192,61,11]);
     }
    }
  translate ([-13,0,-1]) rotate ([0,0,39]) cube([20,20,11]);
  translate ([0,-50,+4]) rotate ([10,0,0]) cube([200,50,11]);
  }
}
color("Pink") case();
headstock();