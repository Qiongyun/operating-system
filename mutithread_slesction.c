#define HAVE_STRUCT_TIMESPEC
#include<stdio.h>
#include<pthread.h>
#pragma comment(lib, "pthreadVC2.lib")
//n�O��J���`�ơAOriginalList�x�s��J���Ʀr�ASortedList�O�Ƨǫ᪺�}�C
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
	// Asking the user for input until user hit the enter �ϥΪ̿�J�Ʀr 
	printf("Please input some digits... \n");
	printf(" *note: press the 'ENTER' button when you don't want to input\n");
	while(1)
	{
		scanf("%d", &input); //Ū���ϥΪ̿�J	 	
		s=getchar();      
		//Dynamical Memory Allocation �ʺA�t�m 
		OriginalList = (int*)realloc(OriginalList, sizeof(int) * (n + 1));	
		//Add the input number to the last place
		OriginalList[n] = input;
		n++;	
		//If hit the "Enter" button then it will be ended ��ϥΪ̤��~���J�ɫ��U"Enter"�� 
		if(s == '\n') break;										
	}
		
	int low = 0;
	int high = n - 1;
	int mid = low + (high - low) / 2; //�����
	parameters *data = (parameters *)malloc(sizeof(parameters));
	//thread1 sort left side
	data->begin = low;
	data->end = mid;
	pthread_t t1;
	pthread_create(&t1, NULL, selection_sort, data); // �إߤl������A�ǤJ data �i��p�� 
	pthread_join(t1, NULL);	// ���ݤl������p�⧹��
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
	parameters *data = (parameters *)arg;  // ���o���
	int low = data->begin;
	int high = data->end;
	int i =0 , j =0, temp =0;
	for (i = low; i < high ; i++)
	{
		int min = i;
		for (j = i + 1; j < high+1; j++)     //���X���ƧǪ�����
		{
			if (OriginalList[j] < OriginalList[min])    //���ثe�̤p��
			{
				min = j;    //�����̤p��
			}
		}
		if (min != i)
		{
			temp = OriginalList[min];  //�洫����ܼ�
			OriginalList[min] = OriginalList[i];
			OriginalList[i] = temp;
		}
	}

}

void *merge_sort(void *arg)
{	int i,j=0;
	parameters *data = (parameters *)arg;  // ���o���
	int low = data->begin; //0
	int high = data->end;  //9
	int Left[n/2], Right[n/2];
	int mid = low + (high - low) / 2;//4
	int Llength = mid - low + 1;
	int Rlength = high - mid;
	//�ƻs��ƨ��Ӥl�}�C
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

	//�N��Ӥl�}�C�����Ʀr�X�֥t�@�ӷs�}�C�A����䤤�@�Ӥl�}�C��
	while (i < Llength && j < Rlength)
	
	{
		SortedList = (int*)realloc(SortedList, sizeof(int) * (k + 1));	
		//�����merge�X�֡A����p������
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
	/* �p�GLeft[]�٦��Ѿl���w�ƧǼƦr�A�N�x�s��mergearray*/
	while (i < Llength)
	{
		SortedList = (int*)realloc(SortedList, sizeof(int) * (k + 1));	
		SortedList[k] = Left[i];
		i++;
		k++;
	}
	/* �p�GRight[]�٦��Ѿl���w�ƧǼƦr�A�N�x�s��mergearray*/
	while (j < Rlength)
	{
		SortedList = (int*)realloc(SortedList, sizeof(int) * (k + 1));	
		SortedList[k] = Right[j];
		j++;
		k++;
	}
}


