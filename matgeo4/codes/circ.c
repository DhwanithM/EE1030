#include <stdio.h>

int main() {
   int a=7;
   int b=7;
	// Define the points
    double points[][2] = {
        {0, 0},  // Point 1
        {a , 0},   // Point 2
        {0, b},  // Point 3
        
    };

    // Open file for writing
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write points to file in the format "x y"
    for (int i = 0; i < 3; i++) {
        fprintf(file, "%.2f %.2f\n", points[i][0], points[i][1]);
    }

    // Close the file
    fclose(file);

    printf("Points have been written to output.txt\n");
    return 0;
}
