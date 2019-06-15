#include "stdio.h"
#include "stdint.h"
#include "time.h"


// Uncomment to run test
// #define __TEST__


inline int64_t collatzA(int64_t num){
	int64_t ct = 0;
	while(num > 1){
		if((num % 2) == 1){
			num = (3 * num) + 1;
			ct++;
		}else{
			num /= 2;
			ct++;
		}
	}
	return ct;
}



inline int64_t collatzB(int64_t num){
	int64_t ct = 0;
	if(num < 2) return 0;
	while(1){
		int64_t x = __builtin_ctz(num);
		if(__builtin_popcount(num) < 2) return ct + x;
		num = (3 * (num >> x)) + 1;
		ct = ct + x + 1;
	}
}


inline int64_t collatzC(int64_t num){
	int64_t ct = 0;
	if(num < 2) return 0;
	while(__builtin_popcount(num) > 1){
		int shift = __builtin_ctz(num);
		ct += shift + 1;
		num = ((num >> shift) * 3) + 1;
	}
	return ct + __builtin_ctz(num);
}


int main(){
	const int ct = 100000000;

	clock_t t0 = clock();
	volatile int64_t x = 0;
	for(int i = 0; i < ct; i++){
		x = collatzA(i);
	}
	t0 = clock() - t0;

	printf("Naive: %f seconds\n", ((float)t0) / CLOCKS_PER_SEC);

	clock_t t1 = clock();
	for(int i = 0; i < ct; i++){
		x = collatzB(i);
	}
	t1 = clock() - t1;

	printf("Optimized: %f seconds\n", ((float)t1) / CLOCKS_PER_SEC);

	clock_t t2 = clock();
	for(int i = 0; i < ct; i++){
		x = collatzC(i);
	}
	t2 = clock() - t2;

	printf("Alt-optimized: %f seconds\n", ((float)t2) / CLOCKS_PER_SEC);

	#ifdef __TEST__
	for(int i = 0; i < 256; i++){
		int a = collatzB(i);
		int b = collatzC(i);
		if(a != b){
			printf("%i :: !! A:%i B:%i !!\n", i, a, b);
		}else{
			printf("%i :: %i\n", i, a);
		}
	}
	#endif

}
