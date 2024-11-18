#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h> 

#define TOLERANCE 1e-6 
#define MAX_ITERATIONS 10000  

// Function declaration
void matrixPrint(double **matrix, int size);
void matrixMultiply(double **A, double **B, double **result, int size);
void hessenbergTransform(double **matrix, int size);
void qrFactorize(double **matrix, int size, double **Q, double **R);
int hasConverged(double **matrix, int size);
void computeComplexEigenvalues(double a, double b, double c, double d, double complex *eig1, double complex *eig2);

int main() {
    int size;

    // Input
    printf("Enter the size (N x N): ");
    scanf("%d", &size);

    // Dynamic memory allocation
    double **A = (double **)malloc(size * sizeof(double *));
    double **Q = (double **)malloc(size * sizeof(double *));
    double **R = (double **)malloc(size * sizeof(double *));
    double **currentMatrix = (double **)malloc(size * sizeof(double *));
    double **tempMatrix = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++) {
        A[i] = (double *)malloc(size * sizeof(double));
        Q[i] = (double *)malloc(size * sizeof(double));
        R[i] = (double *)malloc(size * sizeof(double));
        currentMatrix[i] = (double *)malloc(size * sizeof(double));
        tempMatrix[i] = (double *)malloc(size * sizeof(double));
    }

    // Input
    printf("Enter the elements of the matrix row by row:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%lf", &A[i][j]);
            currentMatrix[i][j] = A[i][j]; 
        }
    }

    
    hessenbergTransform(currentMatrix, size);
    printf("\nHessenberg Form:\n");
    matrixPrint(currentMatrix, size);

    
    int iterationCount = 0;
    while (!hasConverged(currentMatrix, size) && iterationCount < MAX_ITERATIONS) {
        qrFactorize(currentMatrix, size, Q, R); 

        
        matrixMultiply(R, Q, tempMatrix, size);

        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                currentMatrix[i][j] = tempMatrix[i][j];
            }
        }

        iterationCount++;
    }

    if (iterationCount >= MAX_ITERATIONS) {
        printf("\nWarning: Algorithm did not converge within %d iterations.\n", MAX_ITERATIONS);
    }

    
    printf("\nConverged Matrix (Approx. Upper Triangular):\n");
    matrixPrint(currentMatrix, size);

    
    printf("\nEigenvalues:\n");
    for (int i = 0; i < size; i++) {
        if (i < size - 1 && fabs(currentMatrix[i + 1][i]) > TOLERANCE) {
            
            double complex eig1, eig2;
            computeComplexEigenvalues(
                currentMatrix[i][i], currentMatrix[i][i + 1],
                currentMatrix[i + 1][i], currentMatrix[i + 1][i + 1],
                &eig1, &eig2);
            printf("Eigenvalue %d: %.20f + %.20fi\n", i + 1, creal(eig1), cimag(eig1));
            printf("Eigenvalue %d: %.20f + %.20fi\n", i + 2, creal(eig2), cimag(eig2));
            i++; 
        } else {
        
            printf("Eigenvalue %d: %.20f\n", i + 1, currentMatrix[i][i]);
        }
    }

    // Free memory
    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(Q[i]);
        free(R[i]);
        free(currentMatrix[i]);
        free(tempMatrix[i]);
    }
    free(A);
    free(Q);
    free(R);
    free(currentMatrix);
    free(tempMatrix);

    return 0;
}

// Print a matrix
void matrixPrint(double **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%8.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Matrix multiplication
void matrixMultiply(double **A, double **B, double **result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < size; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

//  Hessenberg form
void hessenbergTransform(double **matrix, int size) {
    for (int k = 0; k < size - 2; k++) {
        for (int i = k + 2; i < size; i++) {
            double x = matrix[k + 1][k];
            double y = matrix[i][k];
            double r = hypot(x, y);
            double c = x / r;
            double s = -y / r;

            for (int j = k; j < size; j++) {
                double temp1 = c * matrix[k + 1][j] - s * matrix[i][j];
                double temp2 = s * matrix[k + 1][j] + c * matrix[i][j];
                matrix[k + 1][j] = temp1;
                matrix[i][j] = temp2;
            }

            for (int j = 0; j < size; j++) {
                double temp1 = c * matrix[j][k + 1] - s * matrix[j][i];
                double temp2 = s * matrix[j][k + 1] + c * matrix[j][i];
                matrix[j][k + 1] = temp1;
                matrix[j][i] = temp2;
            }
        }
    }
}

//  QR decomposition
void qrFactorize(double **matrix, int size, double **Q, double **R) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            R[i][j] = 0.0;
        }
    }

    for (int i = 0; i < size; i++) {
        R[i][i] = 0.0;
        for (int k = 0; k < size; k++) {
            R[i][i] += matrix[k][i] * matrix[k][i];
        }
        R[i][i] = sqrt(R[i][i]);

        for (int k = 0; k < size; k++) {
            Q[k][i] = matrix[k][i] / R[i][i];
        }

        for (int j = i + 1; j < size; j++) {
            R[i][j] = 0.0;
            for (int k = 0; k < size; k++) {
                R[i][j] += Q[k][i] * matrix[k][j];
            }
        }

        for (int j = i + 1; j < size; j++) {
            for (int k = 0; k < size; k++) {
                matrix[k][j] -= Q[k][i] * R[i][j];
            }
        }
    }
}

// Check for convergence
int hasConverged(double **matrix, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (fabs(matrix[i + 1][i]) > TOLERANCE) {
            return 0;
        }
    }
    return 1;
}

// Complex eigenvalues of a 2x2 matrix
void computeComplexEigenvalues(double a, double b, double c, double d, double complex *eig1, double complex *eig2) {
    double trace = a + d;
    double determinant = a * d - b * c;
    double discriminant = (trace * trace) / 4.0 - determinant;

    if (discriminant >= 0) {
        *eig1 = trace / 2.0 + sqrt(discriminant);
        *eig2 = trace / 2.0 - sqrt(discriminant);
    } else {
        *eig1 = trace / 2.0 + I * sqrt(-discriminant);
        *eig2 = trace / 2.0 - I * sqrt(-discriminant);
    }
}

