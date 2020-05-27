#define HAVE_STRUCT_TIMESPEC
#include<stdio.h>
#include<pthread.h>
#pragma comment(lib, "pthreadVC2.lib")
//n是輸入的總數，OriginalList儲存輸入的數字，SortedList是排序後的陣列
int* OriginalList = 0; 
int* SortedList = 0; 
int n =0;
void *selection_sort(void *arg);
void *merge_sort(void *arg);


typedef struct 
{
	int begin;
	int end;
	
}parameters;

//main 
int main()
{
	
	int i=0 , input = 0;
	char s ='0';
	// Asking the user for input until user hit the enter 使用者輸入數字 
	printf("Please input some digits... \n");
	printf(" *note: press the 'ENTER' button when you don't want to input\n");
	while(1)
	{
		scanf("%d", &input); //讀取使用者輸入	 	
		s=getchar();      
		//Dynamical Memory Allocation 動態配置 
		OriginalList = (int*)realloc(OriginalList, sizeof(int) * (n + 1));	
		//Add the input number to the last place
		OriginalList[n] = input;
		n++;	
		//If hit the "Enter" button then it will be ended 當使用者不繼續輸入時按下"Enter"鍵 
		if(s == '\n') break;										
	}
		
	int low = 0;
	int high = n - 1;
	int mid = low + (high - low) / 2; //中位數
	parameters *data = (parameters *)malloc(sizeof(parameters));
	//thread1 sort left side
	data->begin = low;
	data->end = mid;
	pthread_t t1;
	pthread_create(&t1, NULL, selection_sort, data); // 建立子執行緒，傳入 data 進行計算 
	pthread_join(t1, NULL);	// 等待子執行緒計算完畢
	//thread2 sort right side
	data->begin = mid + 1;
	data->end = high;
	pthread_t t2;
	pthread_create(&t2, NULL, selection_sort, data); // sort the elements
	pthread_join(t2, NULL);
	//thread3 mergesort
	data->begin = low;
	data->end = high;
	pthread_t t3;
	pthread_create(&t3, NULL, merge_sort, data); // sort the elements
	pthread_join(t3, NULL);
	printf("After sorting.... \n");
	for (i = 0; i < n; i++){
		printf("%d,", SortedList[i]);
	}
		
	system("pause");
}

void *selection_sort(void *arg)
{
	parameters *data = (parameters *)arg;  // 取得資料
	int low = data->begin;
	int high = data->end;
	int i =0 , j =0, temp =0;
	for (i = low; i < high ; i++)
	{
		int min = i;
		for (j = i + 1; j < high+1; j++)     //走訪未排序的元素
		{
			if (OriginalList[j] < OriginalList[min])    //找到目前最小值
			{
				min = j;    //紀錄最小值
			}
		}
		if (min != i)
		{
			temp = OriginalList[min];  //交換兩個變數
			OriginalList[min] = OriginalList[i];
			OriginalList[i] = temp;
		}
	}

}

void *merge_sort(void *arg)
{	int i,j=0;
	parameters *data = (parameters *)arg;  // 取得資料
	int low = data->begin; //0
	int high = data->end;  //9
	int Left[n/2], Right[n/2];
	int mid = low + (high - low) / 2;//4
	int Llength = mid - low + 1;
	int Rlength = high - mid;
	//複製資料到兩個子陣列
	for ( i = 0; i < Llength; i++) {
		Left[i] = OriginalList[low + i];
	}
	for (j = 0; j < Rlength; j++) {
		Right[j] = OriginalList[mid + 1 + j];
	}
	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	int k = low; // Initial index of merged subarray 

	//將兩個子陣列中的數字合併另一個新陣列，直到其中一個子陣列放完
	while (i < Llength && j < Rlength)
	
	{
		SortedList = (int*)realloc(SortedList, sizeof(int) * (k + 1));	
		//比較後merge合併，比較小的放左邊
		if (Left[i] <= Right[j])
		{
			SortedList[k] = Left[i];
			i++;
		}
		else
		{
			SortedList[k] = Right[j];
			j++;
		}
		k++;
	}
	/* 如果Left[]還有剩餘的已排序數字，就儲存到mergearray*/
	while (i < Llength)
	{
		SortedList = (int*)realloc(SortedList, sizeof(int) * (k + 1));	
		SortedList[k] = Left[i];
		i++;
		k++;
	}
	/* 如果Right[]還有剩餘的已排序數字，就儲存到mergearray*/
	while (j < Rlength)
	{
		SortedList = (int*)realloc(SortedList, sizeof(int) * (k + 1));	
		SortedList[k] = Right[j];
		j++;
		k++;
	}
}


