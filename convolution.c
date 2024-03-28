#include <stdio.h>

void CyclicConvolution(int *x, int *h, int *y, int N){
	for (int k = 0; k < N; ++k)
	{
		y[k]=0;
		// compute c_k coefficient
		for (int l = 0; l<N; ++l){
			// printf("the index of h being operated is %d \n", (-l+k+N)%N);
			y[k] += x[l]*h[(-l+k+N)%N];

		}
		// printf("\n");
				
	}
}
	

int main(){
	printf("Hello world\n");
	int x[] = {1, 2, 3, 4}; // First sequence
    	int h[] = {1, 1, 1, 2}; // Second sequence (e.g., a simple filter)
	int N = sizeof(x) / sizeof(x[0]); // The length of the vectors.
	
	int y[N]; // The output array, we initialize it here, but the values in it are "NaN".
	
	CyclicConvolution(x,h,y,N);

	// Print the array y:
	for (int i = 0; i < N; ++i) {
        printf("%d ", y[i]);
    	}
    	printf("\n");

	printf("ByeBye world\n");
}
