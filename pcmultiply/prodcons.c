/*
 *  prodcons module
 *  Producer Consumer module
 *
 *  Implements routines for the producer consumer module based on
 *  chapter 30, section 2 of Operating Systems: Three Easy Pieces
 *
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 */

// Include only libraries for this module
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "counter.h"
#include "matrix.h"
#include "pcmatrix.h"
#include "prodcons.h"


// Define Locks, Condition variables, and so on here



// Bounded buffer put() get()
int put(Matrix * value)
{

}

Matrix * get()
{
  return NULL;
}

// Matrix PRODUCER worker thread
void *prod_worker(void *arg) {
    for (int i = 0; i < NUMBER_OF_MATRICES; i++) {
        Matrix *mat = GenMatrixRandom();
        pthread_mutex_lock(&mutex);
        while (buffer is full) {
            pthread_cond_wait(&cond_produce, &mutex);
        }
        put(mat); // Your implementation of put adds the matrix to the buffer
        pthread_cond_signal(&cond_consume); // Signal to consumer that a matrix is available
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


// Matrix CONSUMER worker thread
void *cons_worker(void *arg) {
    while (true) { // Replace true with a condition to terminate properly
        pthread_mutex_lock(&mutex);
        while (buffer is empty) {
            pthread_cond_wait(&cond_consume, &mutex);
        }
        Matrix *m1 = get(); // Retrieve first matrix
        Matrix *m2 = get(); // Retrieve second matrix for multiplication

        Matrix *m3 = MatrixMultiply(m1, m2); // Attempt to multiply
        if (m3 == NULL) { // If multiplication is not possible
            FreeMatrix(m2); // Free second matrix
            // Try getting another matrix for m2 and repeat or handle appropriately
        } else {
            DisplayMatrix(m3, stdout); // Display result
            FreeMatrix(m1); // Free consumed matrices
            FreeMatrix(m2);
            FreeMatrix(m3); // Also free the result matrix after displaying
        }
        pthread_cond_signal(&cond_produce); // Signal producers if needed
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
