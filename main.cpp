#include<iostream>
#include"LinkedList.hpp"
#include"Node.hpp"
using std::cout;
using std::cin;
using std::endl;

int main(){

	//int array[] = {0,5,2,9,1,3,8};
	int array[] = {0,1,3,2,5,4};

	LinkedList<int> new_list;
	
	cout << "Original List = ";
	for (int i = 1; i < 6 ; i++)
	{
		//insert all elements from array into list
		new_list.insert(i, array[i]);
	}

	//print out the entire list
	for (int d = 1; d <= new_list.getLength(); d++)
	{
		cout << new_list.getEntry(d);
	}
	cout << endl;
	
	new_list.selectionSort();

	//print out the entire sorted list after selection sort is called
	cout << "Sorted List = ";
	for (int d = 1; d <= new_list.getLength(); d++)
	{
		cout << new_list.getEntry(d);
	}

	cout << endl;
	
	
	
	

	

	return 0;
}