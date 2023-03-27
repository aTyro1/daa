#include<bits/stdc++.h>
using namespace std;
/*
 * Part A: 
 * 	I am making a class for Apples. The class will contain function for isLargeApples().
 * 	user will use the object of this class as the test case
 * 	*/
class Apples
{
	private:
		int *apples;  //apples will contain the sizes of apples. This will used by isLargeApples() to compare.
		int size;     
		int *temp;                                          
		short isLargeApples(int,int);
		void mergeSort(int,int);
		void merge(int,int,int);
		int *index_hash;
		void swap(int*,int*);
	public:
		Apples(vector<int> l)  //constructor will read the vector
		{
			size=l.size();
			apples=new int[size];
			temp=new int[size];
			index_hash=new int[100000]{0}; //I am using hasing to track the change of index will merging.
			int i=0;
			for(auto k:l)    //alloting vector apples to apples array
			{	
				index_hash[k]=i;
				temp[i]=k;
				apples[i++]=k;
			}
		}
		vector<int> returnSortedIndex()      //this will return the index of the sorted apples. For sorting I am using merge sort
		{
			mergeSort(0,size-1);
			int i=0;
			vector<int> sorted_index;
			while(i<size)
			{
				sorted_index.push_back(index_hash[apples[i]]);
				i++;
			}
			i=0;
			return sorted_index;
		}
		vector<int> returnSortedApples();
};
vector<int> Apples::returnSortedApples()  // this function will return the sorted apples. It will be used for fitting in boxes
{
	vector<int> result;
	int i=0;
	while(i<size)
	{
		result.push_back(apples[i]);
		i++;
	}
	return result;
}
void Apples::swap(int *a,int *b) //simple swap function. It used address of variables
{
	int t=*a;
	*a=*b;
	*b=t;
}
short Apples::isLargeApples(int i,int j) //function to compare sizes at two indices ( as per the question )
{
	return temp[i]>temp[j] ? 1 : -1;
}
void Apples::mergeSort(int l,int h) //merge sort
{
	if(l<h)
	{
		int m=(l+h)/2;
		mergeSort(l,m);
		mergeSort(m+1,h);
		merge(l,m,h);
	}
}
/*
 * The function to merge used isLargeApples(i,j) to compare two apples. Function only sees the index
 * */
void Apples::merge(int l,int m,int h)
{
	int i,j,k;
	int n1=m-l+1;
	int n2=h-m;
	int L[n1],R[n2];
	i=0;
	while(i<n1)
	{
		L[i]=l+i;
		i++;
	}
	j=0;
	while(j<n2)
	{
		R[j]=m+1+j;
		j++;
	}
	i=0;
	j=0;
	k=l;
	while(i<n1 && j<n2)
	{
		if(isLargeApples(L[i],R[j])!=1)  //isLargeApples(i,j) to compare two apples according to their sizes
		{
			apples[k]=temp[L[i]];
			k++;
			i++;
		}
		else
		{
			apples[k]=temp[R[j]];
			k++;
			j++;
		}
	}
	while(i<n1)
	{
		apples[k]=temp[L[i]];
		k++;
		i++;
	}
	while(j<n2)
	{
		apples[k]=temp[R[j]];
		k++;
		j++;
	}
	i=0;
	while(i<size)
	{
		temp[i]=apples[i];     //Role of temp: to show the final reflection of merging to the original array. 
		i++;
	}

}
/*
 * Part B:
 * 	well, i using part B here.
 * 	for the sake, I have created this class Box.
 * 	The class will have all the functionalities for the operations
 * */
class Box
{
	private:
		int *boxes,size,*apples,*sorted_index;
		void swap(int*,int*);
		int partition(int,int);
		short TightFit(int,int);
	public:
		Box(vector<int> l) //constructor will read vector and store the values of vectors to boxes
		{
			size=l.size();
			boxes=new int[size];
			sorted_index=new int[size];  //sorted_index will keep the track of index while sorting.
			int i=0;
			for(auto k:l)
			{
				sorted_index[i]=i; 
				boxes[i++]=k;
			}
		}
		void quickSort(int low,int high); //I am using quickSort here
		vector<int> findSortedIndex(vector<int> sorted_apples)// this will return the index of boxes sorted according to the fitting capacity of the apples
		{
			int i=0;
			for(auto k:sorted_apples)
				apples[i++]=k;          //the function uses the sorted apples provided by the part A of the question. This vector of apples will be given by user while calling this function
			quickSort(0,size-1);
			vector<int> matched_boxes;
			i=0;
			while(i<size)
			{
				matched_boxes.push_back(sorted_index[i++]);
			}
			return matched_boxes;                  

		}	

};
short Box::TightFit(int i,int j)  //compares the fitting capacity of ith apple to the jth box
{
	if(apples[i]==boxes[j])
		return 0;
	else if(apples[i]<boxes[j])
		return 1;
	else
		return -1;
}
void Box::swap(int* a,int *b) //simple swap function
{
	int t=*a;
	*a=*b;
	*b=t;
}
int Box::partition(int low,int high) //partition around the larget apple at current
{
	int i=(low-1);
	for(int j=low;j<=high-1;j++)
	{
		if(TightFit(high,j)==(-1)) //TightFit(i,j) called here
		{
			i++;
			swap(&boxes[i],&boxes[j]);
			swap(&sorted_index[i],&sorted_index[j]);
		}
	}
	swap(&boxes[i+1],&boxes[high]);
	swap(&sorted_index[i+1],&sorted_index[high]);
	return high--;
}
void Box::quickSort(int low,int high) //normal quick sort
{
	if(low<high)
	{
		int pi=partition(low,high);
		quickSort(low,pi-1);
		quickSort(pi+1,high);
	}
}
int main()
{
	cout<<"Part A:  "<<endl;
	int n,m,x;
	cout<<"enter the no of apples: ";
	cin>>n;
	m=n;
	cout<<"\nenter apples-sizes (none of the function will be using actual size except isLargeApples(i,j) function. Trust me ) "<<endl;
	vector<int> apples;
	while(n--)
	{
		cin>>x;
		apples.push_back(x);
	}
	Apples testCase=apples;
	vector<int> sortedIndex=testCase.returnSortedIndex();
	apples=testCase.returnSortedApples();
	cout<<"Sorted Index of apples as per their sizes: "<<endl;
	for(auto i:sortedIndex)
		cout<<i<<" ";
	cout<<endl;
	char partB;
	cout<<"Do u want to run Part B ? y/n : ";
	cin>>partB;
	if(partB=='y' || partB=='Y')
	{
		cout<<"Part B: "<<endl;
		cout<<"\nenter box-sizes "<<endl;
		vector<int> boxes;
		while(m--)
		{
			cin>>x;
			boxes.push_back(x);
		}
		Box boxSet=boxes;
		vector<int> sortedIndex=boxSet.findSortedIndex(apples);
		cout<<"Sorted Index of Boxes as they fit the sorted apples: "<<endl;
		for(auto i:sortedIndex)
			cout<<i<<" ";
		cout<<endl;
	}

	return 0;
}
