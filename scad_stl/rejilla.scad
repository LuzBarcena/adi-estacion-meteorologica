translate([-3, -3, 0]) {
    difference() {
        cube([82,  72, 1]);
        translate([3, 3, 0]) {
            cube([76,  66, 1]);
        }
    }
}
difference() {
    cube([76,  66, 3]);
    translate([6, 6, 0]) {
        cube([64,  54, 6]);
    }
}

module parte(inicio) {
        translate([6, inicio, 0]) {
            difference() {
                cube([64, 5, 7]);
                translate([2, 0, 0]) {
                    cube([60,  8, 6]);
                }
            }
            rotate([-50, 0, 0]) {
                difference() {
                    translate ([0, -2, 1]) cube([64, 10, 8]);
                    translate([2, -2, 0]) {
                        cube([60,  8, 7]);
                    }
                }
            }
        }
}

for(variable = [6 : 9 : 59])
    intersection() {
        cube([70,  72, 8]);
        parte(variable);
    }
