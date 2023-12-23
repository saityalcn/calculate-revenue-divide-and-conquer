#include <stdio.h>
#include <stdlib.h>

int calculateRevenue(int* arr, int startIndex, int endIndex){
	int i,revenue=0;
	
	if(endIndex < startIndex)
		return -10000;
	
	for(i=startIndex; i<=endIndex; i++)
		revenue += arr[i];

	return revenue;
}

void calculateMiddleRangeRevenue(int* arr, int startIndex, int endIndex, int middleIndex, int* middleRangeMaxRevenue, int* middleRangeMaxStartIndex, int* middleRangeMaxEndIndex){
	int i,j,revenueSum, leftMax, rightMax, middleSum;
	int leftStartIndex, leftEndIndex, rightStartIndex, rigthEndIndex;
	int rightSum,leftSum;
	int maxi=middleIndex, maxj=middleIndex;
	rightSum = -100000;
	leftSum = -100000;
	revenueSum = 0;
	
	for(i=middleIndex; i>=startIndex; i--){
		revenueSum = revenueSum + arr[i];
		if(revenueSum > leftSum){
			leftSum = revenueSum;
			maxi = i;
		}
	}
	
	revenueSum = 0;
	
	for(j=middleIndex; j<=endIndex; j++){
		revenueSum = revenueSum + arr[j];
		if(revenueSum > rightSum){
			rightSum = revenueSum;
			maxj = j;
		}
	}
	
	middleSum  = leftSum + rightSum - arr[middleIndex];
	
	if(rightSum > leftSum){
		if(rightSum > middleSum){
			*middleRangeMaxStartIndex = middleIndex;
			*middleRangeMaxEndIndex = maxj;
			*middleRangeMaxRevenue = rightSum;
			return;
		}
		
		*middleRangeMaxStartIndex = maxi;
		*middleRangeMaxEndIndex = maxj;
		*middleRangeMaxRevenue = middleSum;
		return;
	}
	
	else if(leftSum > middleSum){
		*middleRangeMaxStartIndex = maxi;
		*middleRangeMaxEndIndex = middleIndex;
		*middleRangeMaxRevenue = leftSum;
		return;	
	}
	
	*middleRangeMaxStartIndex = maxi;
	*middleRangeMaxEndIndex = maxj;
	*middleRangeMaxRevenue = middleSum;
	return;
	
}

void divideAndConquer(int* revenues, int startIndex, int endIndex, int*maxRevenue, int* maxRevenueStartIndex, int* maxRevenueEndIndex){
	int m, revenue,middleRevenue;
	int middleRangeMaxRevenue=-10000, middleRangeMaxStartIndex, middleRangeMaxEndIndex;
	m = (startIndex + endIndex)/2; 
	
	if(startIndex <= endIndex){
		divideAndConquer(revenues, startIndex,m-1,maxRevenue, maxRevenueStartIndex,maxRevenueEndIndex);
		divideAndConquer(revenues, m+1,endIndex,maxRevenue, maxRevenueStartIndex,maxRevenueEndIndex);	
		revenue = calculateRevenue(revenues, startIndex, endIndex);
		calculateMiddleRangeRevenue(revenues,startIndex,endIndex,m, &middleRangeMaxRevenue, &middleRangeMaxStartIndex, &middleRangeMaxEndIndex);	
		if(revenue > *maxRevenue || middleRangeMaxRevenue > *maxRevenue){
			*maxRevenueStartIndex = (middleRangeMaxRevenue > revenue) ? middleRangeMaxStartIndex : startIndex;
			*maxRevenueEndIndex = (middleRangeMaxRevenue > revenue) ?  middleRangeMaxEndIndex : endIndex;
			*maxRevenue = (middleRangeMaxRevenue > revenue) ?  middleRangeMaxRevenue : revenue;
		}	
	}	
}

int bruteForce(int n, int* arr, int* maxRevenueStartIndex, int* maxRevenueEndIndex){
	int i,j,revenue;
	int maxRevenue = -1000;
	
	for(i=0; i<n; i++){
		revenue = 0;
		for(j=i; j<n; j++){
			revenue += arr[j]; 
			if(revenue > maxRevenue){
				maxRevenue = revenue;
				*maxRevenueStartIndex = i;
				*maxRevenueEndIndex = j;
			} 
		}	
	}
	
	return maxRevenue;
}

void printArray(int* array, int n){
	int i;
	
	for(i=0; i<n; i++)
		printf("%d ",array[i]);
		
	printf("\n");
}

int main(void){
	int i,j,costsLength, maxRevenue=-10000,start,end;
	int* costs;
	int maxRevenueStartIndex, maxRevenueEndIndex;
	int bruteForceMaxRevenue, bruteForceMaxRevenueStartIndex, bruteForceMaxRevenueEndIndex;
	int tempArray[] = {8, -30, 36, 2, -6, 52, 8, -1, -11, 10, 4};
	//int tempArray[] = {-1, -3, -2, -5, -6, -5, -8, -1, -11, -10};
	//int tempArray[] = {0,0,0,0,0,0,0,0,0,0};
	//int tempArray[] = {100,100,100,3000,100,23,1,-1,-2,-3,-9999,-18,12};
	//int tempArray[] = {1,1,-15,1,1,1,1,1};
	//int tempArray[] = {-943, -924, -898, -208, -92, 19, 220, 571, 806, 984};
	//int tempArray[] = {-990, -700, -671, -633, -535, -362, -218,- 135, -300, 953};
	//int tempArray[] = {10,-20,-30,-40,-50,-60,9,-70,-9,-10};
	
	costsLength = sizeof(tempArray)/sizeof(int);
		
	end = costsLength;
	start = 0; 
	
	costs = (int*)malloc(costsLength*sizeof(int));

	for(i=0; i<costsLength; i++)
		costs[i] = tempArray[i];
	
	printf("Calculating For Array: ");	
	printArray(costs, costsLength);
		
	bruteForceMaxRevenue = bruteForce(costsLength, costs, &bruteForceMaxRevenueStartIndex, &bruteForceMaxRevenueEndIndex);
	divideAndConquer(costs,start, end-1,&maxRevenue, &maxRevenueStartIndex, &maxRevenueEndIndex);
	
	printf("Brute Force\n");
	printf("Start Index: %d End Index: %d Revenue: %d\n",bruteForceMaxRevenueStartIndex, bruteForceMaxRevenueEndIndex, bruteForceMaxRevenue);
	printf("Divide and Conquer\n");
	printf("Start Index: %d End Index: %d Revenue: %d\n",maxRevenueStartIndex, maxRevenueEndIndex, maxRevenue);
	
	return 0;
}
