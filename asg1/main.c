#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAX_SIZE 30

typedef struct _Maxtrix
{
    char* name;
    int **array;
    int row;
    int col;
} Matrix_t;

Matrix_t* create_maxtrix()
{
    Matrix_t* matrix;

    matrix = (Matrix_t *)malloc(1 * sizeof(Matrix_t));
    if(!matrix) {
        printf("Failed to allocate\n");
        exit(EXIT_FAILURE);
    }

    matrix->name = (char *)malloc(MAX_SIZE * sizeof(char));
    if(matrix->name == NULL) {
        printf("Failed to allocate\n");
        exit(EXIT_FAILURE);        
    }

    printf("Maxtrix ");
    fflush(stdin);
    scanf("%s", matrix->name);
    
    printf("Matrix %s Row: ", matrix->name);
    scanf("%d", &matrix->row);
    printf("Matrix %s Col: ", matrix->name);
    scanf("%d", &matrix->col);

    matrix->array = malloc(matrix->row * sizeof(int *));
    for(int i = 0; i < matrix->row; i++) {
        matrix->array[i] = malloc(matrix->col * sizeof(int));
        if (matrix->array[i] == NULL) {
            printf("Failed to allocate\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Maxtrix %s: \n", matrix->name);
    for(int i = 0; i < matrix->row; i++) {
        for(int j = 0; j < matrix->col; j++) {
            scanf("%d", &matrix->array[i][j]);
        }
    }

    printf("\n");
    return matrix;
}

void print_matrix(Matrix_t *matrix)
{
    if(!matrix) {
        printf("Matrix doesn't exist\n");
        return;
    }
    printf("\n");
    printf("Matrix %s\n", matrix->name);

    for(int i = 0; i < matrix->row; i++) {
        for(int j = 0; j < matrix->col; j++) {
            printf("%d ", matrix->array[i][j]);
        }
        printf("\n");
    } 

    printf("\n");   
}

Matrix_t* cal_sum(Matrix_t *mA, Matrix_t *mB) {

    if (mA->row != mB->row || mA->col != mB->col) {
        printf("Matrix %s, Matrix %s can’t add together\n", mA->name, mB->name);
        return NULL;
    }

    Matrix_t* result = (Matrix_t *)malloc(sizeof(Matrix_t));
    if (!result) {
        printf("Failed to allocate\n");
        exit(EXIT_FAILURE);
    }

    result->name = (char *)malloc(MAX_SIZE * sizeof(char));
    if (result->name == NULL) {
        printf("Failed to allocate\n");
        exit(EXIT_FAILURE);
    }

    snprintf(result->name, MAX_SIZE, "Matrix %s + Matrix %s", mA->name, mB->name);
    result->row = mA->row;
    result->col = mA->col;

    result->array = malloc(result->row * sizeof(int *));
    for (int i = 0; i < result->row; i++) {
        result->array[i] = malloc(result->col * sizeof(int));
        if (result->array[i] == NULL) {
            printf("Failed to allocate\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < result->row; i++) {
        for (int j = 0; j < result->col; j++) {
            result->array[i][j] = mA->array[i][j] + mB->array[i][j];
        }
    }

    return result;
}

Matrix_t* cal_product(Matrix_t *mA, Matrix_t *mB) 
{
    if (mA->col != mB->row) {
        printf("Matrix %s, Matrix %s can't multiply together\n", mA->name, mB->name);
        return NULL;
    }

    Matrix_t* result = (Matrix_t *)malloc(sizeof(Matrix_t));
    if (!result) {
        printf("Failed to allocate\n");
        exit(EXIT_FAILURE);
    }

    result->name = (char *)malloc(MAX_SIZE * sizeof(char));
    if (result->name == NULL) {
        printf("Failed to allocate\n");
        exit(EXIT_FAILURE);
    }

    snprintf(result->name, MAX_SIZE, "Matrix %s * Matrix %s", mA->name, mB->name);
    result->row = mA->row;
    result->col = mB->col;

    result->array = malloc(result->row * sizeof(int *));
    for (int i = 0; i < result->row; i++) {
        result->array[i] = malloc(result->col * sizeof(int));
        if (result->array[i] == NULL) {
            printf("Failed to allocate\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < result->row; i++) {
        for (int j = 0; j < result->col; j++) {
            result->array[i][j] = 0;
            for(int z = 0; z < mA->col; z++)
                result->array[i][j] += mA->array[i][z] * mB->array[z][j];
        }
    }

    return result;
}

int main()
{
    Matrix_t *mA, *mB;
    Matrix_t *sum, *product;

    mA = create_maxtrix();
    mB = create_maxtrix();

    print_matrix(mA);
    print_matrix(mB);
    
    sum = cal_sum(mA, mB);
    print_matrix(sum);
    product = cal_product(mA, mB);
    print_matrix(product);

    return 0;
}

