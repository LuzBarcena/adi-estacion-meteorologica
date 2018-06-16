//translate([0, 0, 15]) cylinder(2, 15, 15);
module tallo () {
    difference() {
        union () {
            cylinder(17, 13, 13);
        
            translate([0,0,5]) cylinder(2, 16, 16);
        }
        translate([-6.5, -6.5, 0]) cube([13, 13, 25]);
        translate([-7.5, -4.5, 0]) cube([15, 9, 25]);
    }
    translate([-5, -10, 0]) cube([10, 21, 3]);
}

module cabeza() {
    difference () {
        sphere (18);
        translate([0,0,15]) cylinder(10, 20, 20);
        translate([0,0,-30]) cylinder(20, 20, 20);
        translate([0,0,-30]) cylinder(32, 14, 14);
    }
    translate ([0,0,-8.1]) cylinder(20, 5, 5);
}
translate ([38,0,0]) tallo();

translate ([0,0,15]) rotate([180,0,0]) cabeza ();
