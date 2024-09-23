#include <stdio.h>
#include <math.h>
int main() {
// Function to write vectors to a file
void write_vectors_to_file(const char *filename, float boat_vx, float boat_vy, 
                           float current_vx, float current_vy, 
                           float resultant_vx, float resultant_vy) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    // Write only the velocity values to the file
    fprintf(file, "%.2f %.2f\n", boat_vx, boat_vy);
    fprintf(file, "%.2f %.2f\n", current_vx, current_vy);
    fprintf(file, "%.2f %.2f\n", resultant_vx, resultant_vy);
    
    fclose(file);
}


    // Boat velocity
    float boat_speed = 25.0;  // km/h
    float boat_angle = 0.0;   // Degrees (0 degrees means north)
    
    // Water current velocity
    float current_speed = 10.0; // km/h
    float current_angle = 60.0;  // Degrees east of south

    // Convert boat velocity to Cartesian coordinates
    float boat_vx = boat_speed * sin(boat_angle * M_PI / 180.0);  // Boat's velocity in x-direction (east)
    float boat_vy = boat_speed * cos(boat_angle * M_PI / 180.0);  // Boat's velocity in y-direction (north)
    
    // Convert water current velocity to Cartesian coordinates
    float current_vx = current_speed * cos((90 - current_angle) * M_PI / 180.0);  // Water current's velocity in x-direction (east)
    float current_vy = -current_speed * sin((90 - current_angle) * M_PI / 180.0);  // Water current's velocity in y-direction (north)

    // Compute resultant velocity vector
    float resultant_vx = boat_vx + current_vx;
    float resultant_vy = boat_vy + current_vy;

    // Write vectors to file
    write_vectors_to_file("output.txt", boat_vx, boat_vy, current_vx, current_vy, resultant_vx, resultant_vy);

    // Output the resultant velocity
    printf("Resultant Velocity Vector:\n");
    printf("Vr_x = %.2f km/h\n", resultant_vx);
    printf("Vr_y = %.2f km/h\n", resultant_vy);

    return 0;
}


