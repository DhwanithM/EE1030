#include <stdio.h>

int main() {
    // Coordinates of the points
    int x1 = -6, y1 = 8;  // Coordinates of point P
    int x2 = 0, y2 = 0;   // Coordinates of the origin

    // Open a file for writing
    FILE *file = fopen("output.txt", "w");
    
    // Check if the file was created successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the coordinates to the file
    fprintf(file, "%d %d\n", x1, y1);  // Coordinates of point P
    fprintf(file, "%d %d\n", x2, y2);  // Coordinates of the origin

    // Close the file
    fclose(file);

    printf("Coordinates have been written to points.txt\n");

    return 0;
}
