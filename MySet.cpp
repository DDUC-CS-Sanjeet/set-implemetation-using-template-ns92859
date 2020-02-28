/*
	Name : Neeraj sharma
	Roll No. : 19HCS4037
	Description : To implement important functonalities of sets
*/
#include<iostream>
#include<cmath>
using namespace std;
template<typename t>
class MySet
{
	private : 
		int size;
		t *ar;
	public :
		MySet()//default construtor
		{
			size=1;
			ar=new t[1];
			//ar[0]='N';
		}
		MySet(int sze)//parameterised constructor
		{
			size=sze;
			ar=new t[size];
		}
		int cardinality()
		{
			return size;
		}
		void takeInput()
		{
			cout<<"Enter the elements of your set : ";
			for(int i=0;i<size;i++)
			{
				cin>>ar[i];
			}
			RemovDuplcates(ar,size);
			
		}
		void RemovDuplcates(t ar[],int &size)
		{
			for(int i=0;i<size;i++)
			{
				for(int j=i+1;j<size;j++)
				{
					if(ar[i]==ar[j])
					{
						int temp=j+1;
					for(int k=j;k<size;k++,temp++)
					{
						ar[k]=ar[temp];
					}
					size--;
					}
				}
			}
		}
		void display()
		{
			cout<<"\nYour set is : "<<"\n { ";
			for(int i=0;i<size;i++)
			{
				cout<<ar[i]<<" ";
			}
			cout<<"}\n";
		}
		void powerSet()
		{
			int counter=0,flag;
			int newCounter=0;
			cout<<"\n {   ";
			for(int i=0;i<pow(2,size);i++)
			{
				cout<<"{";
				for(int te=i,j=0;j<size;j++)
				{
					if(te&1)
					{
						if(counter>=1)
						{
							cout<<",";
						}
						cout<<ar[j];
						counter++;
					}
					te=te>>1;
				}
				counter=0;
				cout<<"}";
				if(i<pow(2,size)-1)
				{
					cout<<" , ";
				}
			}
			cout<<" }";
		}
		MySet operator*(MySet obj2);
		MySet operator+(MySet obj2);
		MySet operator-(MySet obj2);
		MySet operator^(MySet obj2);
		void operator==(MySet obj2);
		MySet& operator=(const MySet& obj2);
};
template<typename t>
MySet<t>& MySet<t>::operator=(const MySet<t>& obj2)
{
	this->size=obj2.size;
	this->ar=new t[this->size];
	for(int i=0;i<this->size;i++)
	{
		this->ar[i]=obj2.ar[i];
	}
	return *this;
}
template<typename t>
void MySet<t>::operator==(MySet<t> obj2)
{
	if(size==obj2.size)
	{
		int flag=0;
		for(int i=0;i<size;i++)
		{
			if(ar[i]==obj2.ar[i])
			{
				flag++;
			}
			else
			{
				break;
			}	
		}	
		if(flag==size)
		{
			cout<<"\n Both the sets are equal   \n\n";
		}
		else
		{
			cout<<"\nSets are not equal  \n\n";
		}
	}
	else
	{
		cout<<"\nSets are not equal\n";
	}
}
template<typename t>
MySet<t> MySet<t>::operator^(MySet<t> obj2)
{
	//First we'll find union of the two sets
	int i,j;
	MySet <t>temp1;
	temp1.size=size+obj2.size;
	for(i=0;i<size;i++)
	{
		temp1.ar[i]=ar[i];
	}
	for(i=size,j=0;i<size+obj2.size&&j<obj2.size;i++,j++)
	{
		temp1.ar[i]=obj2.ar[j];
	}
	temp1.RemovDuplcates(temp1.ar,temp1.size);
	//Now we'll find their intersection
	MySet <t>temp2(size);
	int flag=0,counter=0;
		for(int i=0;i<size;i++)
		{
			for(int j=0;j<obj2.size;j++)
			{
				if(ar[i]==obj2.ar[j])
				{
					temp2.ar[flag]=ar[i];
					++flag;
					++counter;
					if(flag==temp2.size-1)
					{
						i=size;
					}
					break;
				}
			}
		}
		temp2.size=counter;
	//Now we'll take the Difference of the sets above formed by doing union and taking intersection 
	MySet <t>Finaltemp(temp1.size);
	 flag=0;
	int indx=0;
	counter=0;
		for(int i=0;i<temp1.size;i++)
		{
			for(int j=0;j<temp2.size;j++)
			{
				if(temp1.ar[i]!=temp2.ar[j])
				{
					flag++;
				}
			}
			if(flag==temp2.size)
			{
				Finaltemp.ar[indx]=temp1.ar[i];
				indx++;
				counter++;
			}
			flag=0;
		}
		Finaltemp.size=counter;
		cout<<"\nAfter taking Symmetric difference of the first two sets ,\n";
		//Finaltemp.display();
		return Finaltemp;
}
template<typename t>
MySet<t> MySet<t>::operator-(MySet<t> obj2)
{
	MySet <t>temp(size);
	int flag=0;
	int indx=0;
	int counter=0;
		for(int i=0;i<size;i++)
		{
			for(int j=0;j<obj2.size;j++)
			{
				if(ar[i]!=obj2.ar[j])
				{
					flag++;
				}
			}
			if(flag==obj2.size)
			{
				temp.ar[indx]=ar[i];
				indx++;
				counter++;
			}
			flag=0;
		}
		temp.size=counter;
		cout<<"\nAfter taking difference of the first two sets ,\n";
		//temp.display();
		return temp;
}
template<typename t>
MySet<t> MySet<t>::operator+(MySet<t> obj2)
{
	int i,j;
	MySet <t>temp;
	temp.size=size+obj2.cardinality();
	for(i=0;i<size;i++)
	{
		temp.ar[i]=ar[i];
	}
	for(i=size,j=0;i<size+obj2.size&&j<obj2.size;i++,j++)
	{
		temp.ar[i]=obj2.ar[j];
	}
	temp.RemovDuplcates(temp.ar,temp.size);
	//temp.display();
	return temp;
}
template<typename t>
MySet<t> MySet<t>::operator*(MySet<t> obj2)
{
	MySet <t>Newtemp(size);
	int counter=0,flag=0;
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<obj2.size;j++)
		{
			if(ar[i]==obj2.ar[j])
			{
				Newtemp.ar[flag]=ar[i];
				++flag;
				++counter;
				if(flag==Newtemp.size-1)
				{
					i=size;
				}
				break;
			}
		}
	}
	Newtemp.size=counter;
	cout<<"\nsize : "<<flag<<"\n";
	cout<<"\nYour set after intersection with union is :\n ";
	//Newtemp.display();
	return Newtemp;
}
void menu()
{
	cout<<"   \nMenu of Sets ... Enter your choice : \n";
	cout<<"\n           1) Print intersection of two sets";
	cout<<"\n           2) Print union of two sets";
	cout<<"\n           3) Print difference of two sets";
	cout<<"\n           4) Print Symmetric difference of two sets";
	cout<<"\n           5) To check if the two sets are equal or not ";
	cout<<"\n           6) To see the cardinality of : \n";
	cout<<"               a) First set\n";
	cout<<"               b) Second set";
	cout<<"\n           7) To print the power sets of : \n";
	cout<<"               a) First set\n";
	cout<<"               b) Second set\n";
	cout<<"\n";
}
void newMenu()
{
	cout<<"\nWelcome \n \n   Enter which type of strings you wish to use for this program : \n";
	cout<<"\n  1) Character";
	cout<<"\n  2) Integer";
	cout<<"\n  3) Decimal\n";
}
template <typename t>
void play(t typeVar)
{
		int size1,size2,wish;
		char choice='y';
			cout<<"\nEnter the size of your first set : ";
				cin>>size1;
				MySet <t>ob1(size1);
				ob1.takeInput();
				ob1.display();
				cout<<"\nEnter the size of your second set : ";
				cin>>size2;
				MySet <t>ob2(size2);
				ob2.takeInput();
				ob2.display();
				MySet <t>ob3(size1+size2);
			do
			{
				menu();
				cout<<"Enter your choice : ";
				cin>>wish;
				switch(wish)
				{
					case 1: ob3=ob1*ob2;
							ob3.display();
							break;
					case 2: ob3=(ob1+ob2);
							ob3.display();
							break;	
					case 3: ob3=ob1-ob2;
							ob3.display();
							break;	
					case 4: ob3=ob1^ob2;
							ob3.display();
							break;
					case 5: ob1==ob2;
							break;
					case 6: cout<<"Press 'a' to see 1st set cardinality or 'b' to see 2nd cardinality : ";
							char cno;
							cin>>cno;
							switch(cno)
							{
								case 'a':cout<<"\nCcadianlity of 1st set is : ";
										cout<<ob1.cardinality();
										break;
								case 'b':cout<<"\nCcadianlity of 2nd set is : ";
										cout<<ob2.cardinality();
										break;
								default:cout<<"Incorrect input :(\n\n";
							}
							break;
					case 7: cout<<"Press 'a' to print the power set of 1st set and 'b' for the 2nd set : ";
							char pwr;
							cin>>pwr;
							switch(pwr)
							{
								case 'a':cout<<"\nPower set of 1st set is : ";
									ob1.powerSet();
									break;
								case 'b':cout<<"\nPower set of 2nd set is : ";
									ob2.powerSet();
									break;
								default:cout<<"Incorrect input :(\n\n";
							}
							break;
							default: cout<<"You've entered an incorrect input :(";		
				}
				cout<<"\nDo you wish to continue, press 'y' to continue : ";
				cin>>choice;
			}while(choice=='y'||choice=='Y');
}
int main()
{
	cout<<"\n      Welcome to sets ....   :)\n\n\n";

	newMenu();
	int strngType;
	cout<<"\nEnter your choice : ";
	cin>>strngType;
	char c;
	int i;
	double d;
	switch(strngType)
	{
		case 1: 
		{
			play(c);
			break;
		}
		case 2 :
		{
			play(i);
			break;
		}
		case 3:
		{
			play(d);			
			break;
		}
		default: cout<<"\nYou've given me an invalid input, so now this program won't work :(\n";
	}
	cout<<"\n\nProgram has ended ...";
	return 0;
}

