#include <iostream>
#define n 3
using namespace std;

void crossProduct(double vector_A[], double vector_B[], double c_P[]) {

   c_P[0] = vector_A[1] * vector_B[2] - vector_A[2] * vector_B[1];
   c_P[1] = -(vector_A[0] * vector_B[2] - vector_A[2] * vector_B[0]);
   c_P[2] = vector_A[0] * vector_B[1] - vector_A[1] * vector_B[0];
   
}

void dotProduct(double vector_A[], double vector_B[], double d_P[]){

    d_P[0] = vector_A[0]*vector_B[0] + vector_A[1]*vector_B[1] + vector_A[2]*vector_B[2];

}

int main() {
   
   double vector_A[] = { 7, 6, 4 };
   double vector_B[] = { 2, 1, 3 };
   double c_P[n];
   double d_P[1];

   crossProduct(vector_A, vector_B, c_P);
   dotProduct(vector_A, vector_B, d_P);
   
   cout << "Cross product: ";
   for (int i = 0; i < n; i++){
    cout << c_P[i] << " ";
   }
   
   cout << "\n";
   cout << "Dot product: " << d_P[0];
   
   return 0; 

}

