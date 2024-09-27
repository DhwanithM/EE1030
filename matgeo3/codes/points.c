#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

void point_gen(FILE *fptr, double **A, double **B, int no_rows, int no_cols, int num_points) {
    for (double i = 0; i <= num_points; i++) {
        double **output;
        if (A != NULL && B != NULL) {
            output = Matadd(A, Matscale(Matsub(B,A,no_rows,no_cols),no_rows,no_cols,(double)i/num_points), no_rows, no_cols);
        } else if (A == NULL) {
            output = Matscale(B, no_rows, no_cols, (double)i/num_points);
        } else if (B == NULL) {
            output = Matscale(A, no_rows, no_cols, (double)i/num_points);
        }
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output,no_rows);
    }
}

int main() {
    double x1, y1, x2, y2;
    x1 = 6; y1 = 2;
    x2 = -6; y2 = -2;

    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **normvector = createMat(m, n);
    double **dirvector = createMat(m, n);
    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;
    dirvector = Matsub(B,A,m,n);
    normvector = normVec(dirvector);
    FILE *fptr;
    fptr = fopen("points.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    point_gen(fptr, A,B , m, n, 20);
    point_gen(fptr, 0, dirvector,m,n,20);
    point_gen(fptr, 0, normvector,m,n,20);
    
    freeMat(A,m);
    freeMat(B,m);
    freeMat(dirvector,m);
    freeMat(normvector,m);
    
    fclose(fptr);
    return 0;
}
