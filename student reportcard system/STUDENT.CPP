#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<windows.h>
using namespace std;
class Student
{
	private:
		int roll;
		char name[30];
		int sub1;
		int sub2;
		int sub3;
		int sub4;
		float per;
		char grade;
		int total;
	public:
		void getdata();
		void showdata();
		void calculate();
		int rollnum();
		void tabular();
};
int Student :: rollnum()
{
	return roll;
}
void Student :: getdata()
{
	system("cls");
	cout<<"\nEnter roll number:";
	cin>>roll;
	cout<<"\nEnter name of student:";
	cin.ignore();
	cin.getline(name,30);
	cout<<"\nEnter marks of sub1:";
	cin>>sub1;
	cout<<"\nEnter marks of sub2:";
	cin>>sub2;
	cout<<"\nEnter marks of sub3:";
	cin>>sub3;
	cout<<"\nEnter marks of sub4:";
	cin>>sub4;
	calculate();
}
void Student :: tabular()
{
	cout<<setw(2)<<setfill(' ')<<roll;
	cout<<setw(10)<<setfill(' ')<<name;
	cout<<setw(12)<<setfill(' ')<<sub1;
	cout<<setw(10)<<setfill(' ')<<sub2;
	cout<<setw(6)<<setfill(' ')<<sub3;
	cout<<setw(8)<<setfill(' ')<<sub4;
	cout<<setw(8)<<setfill(' ')<<grade;
	cout<<setw(14)<<setfill(' ')<<per;
	cout<<setw(8)<<setfill(' ')<<total<<endl;
}

void Student :: showdata()
{
	system("cls");
	cout<<"\nRoll number:"<<roll;
	cout<<"\nName of student:"<<name;
	cout<<"\nMarks of sub1:"<<sub1;
	cout<<"\nMarks of sub2:"<<sub2;
	cout<<"\nMarks of sub3:"<<sub3;
	cout<<"\nMarks of sub4:"<<sub4;
	cout<<"\nGrade:"<<grade;
	cout<<"\nTotal marks:"<<total;
	cout<<"\nPercentage:"<<per;
	cout<<endl;
}
void Student :: calculate()
{
	total=sub1+sub2+sub3+sub4;
	per=total/4.0;
	if(per>70)
	{
		grade='A';
	}
	else if (per>60)
	{
		grade='B';
	}
	else if (per>50)
	{
		grade='C';
	}
	else if (per>40)
	{
		grade='D';
	}
	else if (per>30)
	{
		grade='E';
	}
	else
	{
		grade='F';
	}
}
void create_student()
{
	system("cls");
	char opt;
	Student s;
	ofstream outfile;
	outfile.open("student.dat", ios::app | ios::binary);
	s.getdata();
	outfile.write((char*) &s,sizeof(s));
	outfile.close();
	cout<<"\nPress y for adding more data otherwise press n\n";
	cin>>opt;
	if(opt=='y' || opt=='Y')

	{
		create_student();
		system("cls");
	}
	else
	{
		cout<<"\nExisting from creating student record\n";
		cin.ignore();
		cout<<"Press any key to continue\n";
		getchar();
		system("cls");
	}
}
void class_result()
{
	int ch;
	system("cls");
	Student s;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File can not open!!!";
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"___________________________________________________________________________________________\n";
	cout<<"R.No       Name       sub1   sub2   sub3   sub4    Grade   Percentage   Total"<<endl;
	cout<<"___________________________________________________________________________________________\n";
	while(inFile.read((char*) &s, sizeof(s)))
	{
		s.tabular();		
	}
	cout<<"___________________________________________________________________________________________\n";
	inFile.close();
	cin.ignore();
	cout<<"Press any key to continue\n";
	getchar();
	system("cls");
}
void update_student()
{
     Student s;
     ifstream infile("student.dat");
     ofstream outfile("new.dat",ios::binary);
     int roll,flag=0;
     if(!infile)
     {
         cout<<"\nresult not found in the file";
     }
     else
     {   
         cout<<"\nEnter roll number of the student: ";
         cin>>roll;
         system("cls");
         while(infile.read((char*)&s,sizeof(s)))
         {
             if(roll==s.rollnum())
             {
                 cout<<"\nEnter new details";
                 s.getdata();
                 
                 outfile.write((char*)&s,sizeof(s));
                 flag=1;
                 cout<<"\nRecord updated\n";
             }
             else
             { 
                 outfile.write((char*)&s,sizeof(s));
             }
         }
         if(flag==0)
         {
             cout<<"\nRecord not found";
         }
     }
     infile.close();
     outfile.close();
     remove("student.dat");
     rename("new.dat","student.dat");
     cin.ignore();
     cout<<"Press any key to continue\n";
	getchar();
	system("cls");
}
void display()
{
	system("cls");
	Student s;
	ifstream infile;
	infile.open("student.dat",ios::binary);
	if(!infile)
	{
		cout<<"File does not exist\n";
	}
	else
	{
		cout<<"All student record.....\n";
		while(infile.read((char*) &s,sizeof(s)))
		{
			getchar();
			s.showdata();
		}
		infile.close();
	}
	cin.ignore();
	cout<<"Press any key to continue\n";
	getchar();
	system("cls");
}
void delete_student()
{	
	char opt;
	int roll;
	system("cls");
	cout<<"Enter roll number:";
	cin>>roll;
	Student s;
	ifstream infile;
	infile.open("student.dat",ios::binary);
	if(!infile)
	{
		cout<<"\nFile can't link";
	}
	else
	{
		ofstream outfile;
		outfile.open("new.dat",ios::binary);
		while(infile.read((char*) &s,sizeof(s)))
		{
			if(s.rollnum() != roll)
			{
				outfile.write((char*) &s,sizeof(s));
			}
		}
		infile.close();
		outfile.close();
		remove("student.dat");
		rename("new.dat","student.dat");
		cout<<"\nRecord deleted";
		cout<<"\nPress y for deleting more data and n for not deleting the data\n";
		cin>>opt;
		if(opt=='y' || opt=='Y')
		{
			delete_student();
		}
		else
		{
			cout<<"\nExisting........\n";
		}
	}
	cin.ignore();
	cout<<"Press any key to continue\n";
	getchar();
	system("cls");
}
void search_disp()
{
	int roll;
	system("cls");
	cout<<"Enter roll number:";
	cin>>roll;
	Student s;
	ifstream infile;
	infile.open("student.dat",ios::binary);
	if(!infile)
	{
		cout<<"File does not exist\n";
	}
	else
	{
		int ctr=0;
		while(infile.read((char*) &s,sizeof(s)))
		{
			if(s.rollnum() == roll)
			{
				cout<<"\nRecord founded...";
				cout<<"\n...Press any key to see the record...\n";
				getchar();
				s.showdata();
				ctr++;
				infile.close();
				break;
			}
		}
		if(ctr==0)
		{
			cout<<"\n\nRecord not found\n";
		}
	}
	cin.ignore();
	cout<<"Press any key to continue\n";
	getchar();
	system("cls");
}

int main()
{
	char grade;
	int opt,num;
	cout<<"\t\t\t\t\t\t\t\t______________________________________________________________________________________\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t\tSTUDENT REPORT CARD MANEGEMENT SYSTEM"<<endl;
	cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tMade by:ADARSH BADONI"<<endl;
	cout<<"\t\t\t\t\t\t\t\t_______________________________________________________________________________________\n";
		do
		{
			cout<<"\n These are your option:";
			cout<<"\n////////////////////////////////////////////////////////////////////////";
			cout<<"\n0.To exit\n";
			cout<<"1.To create a record\n";
			cout<<"2.To delete a record\n";
			cout<<"3.To read all records from file\n";
			cout<<"4.To Search a record\n";
			cout<<"5.Display all students record in tabular form\n";
			cout<<"6.Update student record\n";
			cout<<"/////////////////////////////////////////////////////////////////////////\n";
			cout<<"\nEnter your choice:";
			cin>>opt;
			switch(opt)
			{
				case 0:
					cout<<"\n exiting the programe thankyou!!\n";
					break;
				case 1:
					create_student();
					break;
				case 2:
					delete_student();
					break;
				case 3:
					display();
					break;
				case 4:
					search_disp();
					break;
				case 5:
					class_result();
					break;
				case 6:
					update_student();
					break;
				default:
					cout<<"Invalid choice";
			}	
		}while(opt!=0);
}
