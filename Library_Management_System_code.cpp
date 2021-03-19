
// LIBRARY MANAGEMENT SYSTEM 

// R# 20L-1403   

// SECTION : 1A1

// DEPARTMENT : EE

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void main_menu();
void available (int,int , char[][45] , char[][45], char [][45], char[][45] , char[][45] , int);
void addbooks (int ,char [][15],int&  ,  int, char[][45] , char[][45], char [][45], char[][45] , char[][45] );
void delete_books (int,int,int, int , int& , char , char [][45] , char[][45] , char[][45], char [][45], char[][45] , char[][45]);
void studentid (char[][7] );
void returnfunc();
void search (int ,int , int ,int , char , char [][45] , char[][45] , char[][45], char [][45], char[][45] , char[][45]  );
void edit (int,int , char[][15],char [][15] ,char[][7],char ,int, int ,int ,char [][45] , char[][45] , char[][45], char [][45], char[][45] , char[][45]);
void change_student_id(char [][7]);
void issue_record(int,char [][15] , int,int,int ,char[][45] , char[][45], char [][45], char[][45] , char[][45] );


int main()
{
	cout <<endl<<endl;
	cout << setw(120)<<"WELCOME TO 'THE LIBRARY MANAGEMENT SYSTEM'" <<endl<<endl;

	char avail[1][15]= {'A','v','a','i','l','a','b','l','e'};
	char unavail[1][15] = {'U','n','a','v','a','i','l','a','b','l','e'};
	char id[1][7];									// to input user id
	studentid( id );
	char ans2 = '11';													
	do
	{
	main_menu();									//Displying main menu
	cin >> ans2;									

	int t=0;
	int j = 0;										// used as an index for controlling rows or column in many functions
	char booknum [7][45];							// used as a temporary array in whole program
	int lines = 0;									// used to count lines in file so used in many funcion such as books that in which line user will enter next book
	int x =1 ;										// used as temporary variable in specially in (IF THEN ELSE)
	char ans = 'u';									// to take answer from user that what task he want to perform in switches in functions
	const int rows = 15;							// number of rows
	char bookname [rows][45] ={};
	char booknumber[rows][45] = {};
	char bookdepartment [rows][45] ={};
	char issue [rows][45] = {};
	int index =0;									// widely used allmost in every function
	char availability [rows][45] = {};				
	int r =0;										// used temporarily as rows 
	int c=0;										// used temporarily as columns

	switch ( ans2 )                                 // initialy it has 11 value ( as loop is do while so it wil; run at least one time
	{		
		case '1' :
			
				available ( c,index , booknumber , bookname , issue , availability , bookdepartment , lines);
				break;
		case '2' :
				
				break;
		case '3' :
				addbooks (c,avail,lines , index,booknumber , bookname , issue , availability , bookdepartment);
				break;
		case '4' :
				delete_books (j,x,c, index ,lines, ans , booknum , booknumber , bookname , issue , availability , bookdepartment);
				break;
		case '5' :
				edit (j,c,unavail,avail ,id,ans ,t,lines , index , booknum , booknumber , bookname , issue , availability , bookdepartment);
				break;
		case '6' :
				search (j,x,lines,index,ans ,  booknum , booknumber , bookname , issue , availability , bookdepartment );
				break;
		case '7' :
				 issue_record (j,unavail,x,index,lines,booknumber , bookname , issue , availability , bookdepartment );
				break;
		case '8' :
			change_student_id(id);
			break;
		default :		

			return 0;								// if user anter any wrong condition the program will end

			break;
	}
	
}
	while ( ans2 != 'e' );							// loop will stop executing when user presses 'e'

	return 0;
}

void addbooks ( int c,char avail[][15] ,int& lines , int index,char booknumber[][45], char bookname[][45] , char issue[][45], char availability[][45] , char bookdepartment[][45])
{
	ifstream in;
	ofstream out;
	in.open("Books.txt");
	lines = 0;
	while ( !in.eof() )
	{
	 	in >> bookname[index] >> booknumber[index] >> bookdepartment[index] >> availability[index] >> issue[index];
		index++;									//index == rows of 2d arrays 
		lines++;									// determine the next line in which book is going to add
	}
	index = 0;
	lines = lines-1;								// because after eof() the file pointer will be 1 line after so subtrated 1
	if ( lines < 11 )								// 11 is used beacuse 1 line is of book name:   book number: etc
	{
		cout <<endl;
	cout << "Enter the book name you want to add : " ;
	scanf(" %[^\n]" , bookname[lines]);				// reads the input enter by user in characte array character by character untill encounters \n(end of line)
	cout <<endl;
	
	cout << " Enter booknumber : "  ;
	scanf(" %[^\n]" , booknumber[lines]);
	cout <<endl;
	
	cout << " Enter Bookdepartment : " ;
	scanf(" %[^\n]" , bookdepartment[lines]);
	cout <<endl<<endl;
		
		for ( index = 0 ; index < 10 ; index ++)
		{
			availability[lines][index] = avail[0][index];		// this loop is assigning available to avilability of that book automatically
		}
		for (index = 0 ; index < 6 ; index++)
		{
		issue[lines][index] = '-';					// assign ------ to the issue details of that book automatically
		}
	
	out.open("Books.txt");
	
	cout <<"							Book added successfully in the Library"<<endl<<endl<<endl;
	
	for ( index=0 ; index <=lines ; index++)		// index <= lines because this time we will display the last line in which book is added
	{ 
		
		cout <<left<<setw(50)<< bookname[index] <<setw(20)<< booknumber[index] <<setw(35)<< bookdepartment[index] <<setw(20)<< availability[index] <<setw(5)<< issue[index]<<endl;
		
			for(c=0 ; c <40 ; c++)					// This loop assigns _(underscore) in place of spaces so that file work fine and no error occurs
			{
				if(bookname[index][c] == ' ')
					bookname[index][c]='_';
				if(bookdepartment[index][c] == ' ')
					bookdepartment[index][c]='_';
			}

		out <<left<<setw(50)<< bookname[index] <<setw(20)<< booknumber[index] <<setw(35)<< bookdepartment[index] <<setw(20)<< availability[index] <<setw(5)<< issue[index]<<endl;
	}
	cout <<endl<<endl;
	
	out.close();
	}
	else                                            // when limit of books will reach to 10 then program will stop adding books
	{
		cout <<endl<<endl;
		cout << " Max Limit of storing books have reached" <<endl;
		cout << " Delete any book to add new book " << endl<<endl;
	}

}

void available (int c ,int index, char booknumber[][45], char bookname[][45] , char issue[][45], char availability[][45] , char bookdepartment[][45] , int lines )
{
	ifstream in;
	in.open("Books.txt");
	cout << "								Available Books in Library " << endl<<endl<<endl;
	while ( !in.eof ()) 
	{
		in >> bookname[index] >> booknumber[index] >> bookdepartment[index] >> availability[index] >> issue[index];
		
		index++;									// index is used as rows of 2d arrays
		lines++;									//checking and counting lines in file
	}

	for(index = 0 ; index <= lines ; index++)		// outer loop: used to display rows on console
	{
		for( c=0 ; c <40 ; c++)						//assigning space to _(underscore) so console look better
			{

				if(bookname[index][c] == '_')
					bookname[index][c]=' ';
				if(bookdepartment[index][c] == '_')
					bookdepartment[index][c]=' ';
				
			}
	cout <<left<<setw(50)<< bookname[index] <<setw(20)<< booknumber[index] <<setw(35)<< bookdepartment[index] <<setw(20)<< availability[index] <<setw(5)<< issue[index]<<endl;
	}

	cout <<endl<<endl;
	in.close();

}

void studentid(char id[][7])
{
	cout << "Enter the Student's ID Number." << endl;
	cout << "#";
	scanf(" %[^\n]" , id[0]);						// taking input in row=0 of 2d array book id
	cout << endl;
	cout << "ID number is verified; Thank you" <<endl<<endl;

}

void delete_books (int j,int x,int c, int index ,int& lines , char ans , char booknum[][45] , char booknumber[][45], char bookname[][45] , char issue[][45], char availability[][45] , char bookdepartment[][45])
{
	int a;
	j=0;
	x=0;
	ifstream in;
	ofstream out;
	in.open("Books.txt");
	a=1;											// later on used to check that if  user want delete we don't display last line
	
		cout <<"									DELETE MODE ENABLED"<<endl<<endl;
		cout << " Enter book number " << endl;
		scanf(" %[^\n]" , booknum[0]);
	
	while ( !in.eof ()) 
	{
		in >> bookname[index] >> booknumber[index] >> bookdepartment[index] >> availability[index] >> issue[index];
		
		index++;
		lines++;

	}
	in.close();
	for ( index = 0 ; index <= lines-1  ; index++ )										// outer loop; for searching in row that if that book is in the library or not
	{
		x=0;
		for (  j = 0 ; j < strlen(booknumber[index]) ; j++ )							// j is used as columns 
		{
			if  (booknumber[index][j] == booknum[0][j]	)								// checking that every character of the book number is eaqual to book number( entered by user)
			{
				x= x+1;
				if ( (strlen(booknum[0])+200) == x+200 )								// 200 is added as check that if two booknumbers are of same length they don't cause errors
				{
					cout <<endl;
					cout << "Found Successfully !" <<endl<<endl;						// loop can only reach once in this part of program when it counters the book number enter by the user
					cout << " Name	      :	        "<< bookname[index] <<endl;
					cout << " Book Number  :		"<< booknumber[index]<<endl;
					cout << " Department   :		"<< bookdepartment[index]<<endl;	// Displaying data of that row in which book encountered
					cout << " Status	      :		"<< availability[index]<<endl;
					cout << " Issue Details:		"<< issue[index]<<endl;
					cout << endl<<endl;
					cout << " Is this the book that you want to delete ? (Enter  'y' for yes & 'n' for no) " <<endl;
					cin >> ans;
					
					
																					// if user want to delete books it will not display the last line
					switch (ans)
					{
						case 'y':
							a=2;													// in answer yes a = 2 so that we don't dispalay the last line 
						for ( int i = 0; i < 40 ; i++)								// 40 is used to control the length of string(character)[max name of book, name etc]
						{ 

						booknumber[index][i] = booknumber[lines-2][i];				// i is used as columns here
						bookname[index][i] = bookname[lines-2][i];
						availability[index][i] = availability[lines-2][i];
						 bookdepartment[index][i] =  bookdepartment[lines-2][i];
						 issue[index][i] = issue[lines-2][i];

						}
						cout <<endl;
						 cout <<"Book Deleted successfully !" <<endl<<endl;
						 cout << "							Updated Books in Library " <<endl<<endl<<endl;
					continue;								//to control loop so that i chech again for booknumber if it repeated but that will still crash the code
					break;									//switch break
					case 'n':
						
						cout << "							Books in Library " <<endl<<endl<<endl;

						break;
				   }
				}
			}
		}
	}
	
	out.open("Books.txt");
	
	for(int i = 0 ; i < (lines-a) ; i++)					// in case n: a=1 & in case y:  a=2
	{
		
		out <<left<<setw(50)<< bookname[i] <<setw(20)<< booknumber[i] <<setw(35)<< bookdepartment[i] <<setw(20)<< availability[i] <<setw(5)<< issue[i]<<endl;

		for(c=0 ; c <40 ; c++)								// c used as columns
			{

				if(bookname[i][c] == '_')					// replacing _ (underscore) to spacess
					bookname[i][c]=' ';
				if(bookdepartment[i][c] == '_')
					bookdepartment[i][c]=' ';
			}

	cout <<left<<setw(50)<< bookname[i] <<setw(20)<< booknumber[i] <<setw(35)<< bookdepartment[i] <<setw(20)<< availability[i] <<setw(5)<< issue[i]<<endl;
	}
	cout <<endl;											
	out.close();
		cout <<"									DELETE MODE DISABLED"<<endl<<endl<<endl;
	
}

void search (int j ,int x, int lines , int index,char ans , char booknum[][45] , char booknumber[][45], char bookname[][45] , char issue[][45], char availability[][45] , char bookdepartment[][45] )
{
	ifstream in;
	in.open("books.txt");
	cout << "										SEARCH  ENABLED " << endl<<endl;
	
		cout << " Enter book number " << endl;
		scanf(" %[^\n]" , booknum[0]);				//temporary Array to store book number entered by user

	lines=0;										// initially made lines = 0 so no error occur
	while ( !in.eof ()) 
	{
		in >> bookname[index] >> booknumber[index] >> bookdepartment[index] >> availability[index] >> issue[index];
		
		index++;
		lines++;
	}
	in.close();
	
	for ( index = 0 ; index <= lines-1  ; index++ )										// outer loop used as rows and searching
	{
		x=0;
		for (  j = 0 ; j < strlen(booknumber[index]) ; j++)								// j is used as columns
		{
			if  (booknumber[index][j] == booknum[0][j]	)								// checking if the entered booknumber found or not
			{
				x= x+1;
				if ( (strlen(booknum[0])+200) == x+200 )
				{
					cout << "Book found !" <<endl<<endl;
					cout << " Name	      :	        "<< bookname[index] <<endl;
					cout << " Book Number  :		"<< booknumber[index]<<endl;
					cout << " Department   :		"<< bookdepartment[index]<<endl;	// dispalying relevant info of found book
					cout << " Status	      :		"<< availability[index]<<endl;
					cout << " Issue Details:		"<< issue[index]<<endl;
					cout << endl<<endl;
					ans = 'x';															//used as check that it found book or not
				}
			}
		}
		
	}
	if ( ans != 'x')																	// if ans is not equal to x it will run this if condition
	{
		cout << " Failed to found " <<endl;
		cout << " Make sure entered 'BOOK NUMBER' is correct " <<endl<<endl;
	}
	cout <<"										SEARCH  DISABLED"<<endl<<endl<<endl;
}

void edit (int j ,int c,char unavail[][15] , char avail[][15] ,char id [][7] ,char ans ,int t,int lines ,int index, char temporary[][45] , char booknumber[][45], char bookname[][45] , char issue[][45], char availability[][45] , char bookdepartment[][45])
{
	
	t=0;
	ifstream in;
	ofstream out;
	in.open("Books.txt");
	
	cout << "										Edit Book enabled " << endl<<endl;
	
		cout << " Enter book number " << endl;
		scanf(" %[^\n]" , temporary[0]);							// temporary array storing booknumber in row=0 of in it
		cout <<endl<<endl;
	
	while ( !in.eof ()) 
	{
		in >> bookname[index] >> booknumber[index] >> bookdepartment[index] >> availability[index] >> issue[index];
		
		index++;
		lines++;
	}
	in.close();
	for ( index = 0 ; index <= lines-1  ; index++ )
	{
		t=0;
		for (  j = 0 ; j < strlen(booknumber[index]) ; j++)			// j used as columns
		{
			if  (booknumber[index][j] == temporary[0][j]	)		// checking
			{
				t= t+1;
				if ( (strlen(temporary[0])+200) == t+200 )
				{

					cout << "Found Successfully !" <<endl<<endl;
					cout << " Name	      :	        "<< bookname[index] <<endl;
					cout << " Book Number  :		"<< booknumber[index]<<endl;
					cout << " Department   :		"<< bookdepartment[index]<<endl;		// diplaying relevant info of that book
					cout << " Status	      :		"<< availability[index]<<endl;
					cout << " Issue Details:		"<< issue[index]<<endl;
					cout << endl<<endl;

					ans = 'u';	
					cout << "Enter     'e'    to edit Book Details"<<endl;					// options
					cout << "Enter     'i'    to issue/unissue book"<<endl;
					cin >> ans;
					switch (ans)															// switch depending on user what option he entered
					{
					case 'e':

					cout << "Now you can edit data for this Book " <<endl;
					cout << " Name	      :	        ";
					scanf(" %[^\n]" , temporary[1]);										// storing data to edit in book later

					cout << " Book Number  :		";
					scanf(" %[^\n]" , temporary[2]);

					cout << " Department   :		";
					scanf(" %[^\n]" , temporary[3]);

					for ( int i = 0; i < 40 ; i++)									
						{ 
						booknumber[index][i] =temporary[2][i];						// replacing data in that row
						bookname[index][i] = temporary[1][i];
						bookdepartment[index][i] = temporary[3][i];
						}

					cout << "							Updated Books in library after editing " <<endl<<endl<<endl;
					break;

					case 'i':
					
					cout << endl<<endl;
					
						ans ='a';													// initializing it so that it don't match to previous one
						cout << "Do you want to issue or unissue the book? ( Press 'i' for ISSUE  &  'u' for UNISSUE )" <<endl;
						cin>>ans;
						switch (ans)
						{
						case 'i':
							for ( int i = 0; i < 40 ; i++)							
						{ 
						availability[index][i]=unavail[0][i];						// if book issued; assigning unavailable to its availability
						issue[index][i] =id[0][i];									// assigning entered id to its issue detail
						}
							cout <<endl;
							cout <<"							Status of Book is updated to Unavailable"<<endl<<endl;
							break;
						case 'u':
							for ( int i = 0; i < 40 ; i++)									// i used as columns
						{ 
						availability[index][i]=avail[0][i];									// assigning unavailable to availability of that book
						
						}
							for (int i = 0 ; i < 6 ; i++)
							{
								issue[index][i] = '-';										// assigning ------ to its issue details
							}
							cout <<endl;
							cout << "							Status of Book is updated to Available"<<endl<<endl;

							break;
						}

					continue;						// to check if there is any other book of same book numbers
					}
				}
			}
		}
	}
	t=0;
	out.open("Books.txt");
	
	for(int i = 0 ; i < (lines-1) ; i++)			// i is used as rows here
	{
		for(c=0 ; c <40 ; c++)						// c is used as columns
			{

				if(bookname[i][c] == '_')			// assigning spaces in place of underscore (_)
					bookname[i][c]=' ';
				if(bookdepartment[i][c] == '_')
					bookdepartment[i][c]=' ';
		
				
			}

		cout <<left<<setw(50)<< bookname[i] <<setw(20)<< booknumber[i] <<setw(35)<< bookdepartment[i] <<setw(20)<< availability[i] <<setw(5)<< issue[i]<<endl;
		for(c=0 ; c <40 ; c++)
			{

				if(bookname[i][c] == ' ')			// assigning underscore (_) in place of spaces
					bookname[i][c]='_';
				if(bookdepartment[i][c] == ' ')
					bookdepartment[i][c]='_';
			}
	out <<left<<setw(50)<< bookname[i] <<setw(20)<< booknumber[i] <<setw(35)<< bookdepartment[i] <<setw(20)<< availability[i] <<setw(5)<< issue[i]<<endl;
	}
	cout <<endl<<endl;											
	out.close();
	
}

void main_menu()
{
	cout << "	Press 1 : To see all available/unavailable books.	" << endl;
	cout << "	Press 2 : To return to Main Menu.	" << endl;
	cout << "	Press 3 : To add new books.	" << endl;
	cout << "	Press 4 : To delete books from availabe books.	" << endl;
	cout << "	Press 5 : To edit the details of a book.	" << endl;
	cout << "	Press 6 : To search a book from Library Management System.	" << endl;
	cout << "	Press 7 : To check the book issue record.	" << endl;
	cout << "	Press 8 : To change student id. "<<endl;
	cout << "	Press E : To exit from LIBRARY MANAGMENT SYSTEM " <<endl<<endl;

	cout << "   Select any option " <<endl;


}

void change_student_id(char id[][7])
{
	studentid(id);
}

void issue_record(int j ,char unavail [][15],int x, int index,int lines, char booknumber[][45], char bookname[][45] , char issue[][45], char availability[][45] , char bookdepartment[][45]  )
{
	
	ifstream in;
	in.open("books.txt");
	cout << "									ISSUED  BOOKS " << endl<<endl;
	
				

	
	lines=0;														// initializing lines = 0 so that no error occurs
	while ( !in.eof ()) 
	{
		in >> bookname[index] >> booknumber[index] >> bookdepartment[index] >> availability[index] >> issue[index];
		index++;
		lines++;
	}
	in.close();
	int a;
	a=1;															// a is used to display BOOK NAME, BOOK NUMBER etc once
	for ( index = 0 ; index <= lines-1  ; index++ )					// index used as rows
	{
		
		x=0;
		for (  j = 0 ; j < strlen( unavail[0]) ; j++)				// j used as columns
		{
			if  ( availability[index][j] == unavail[0][j] )		// checking for unavailabilty
			{
				x= x+1;
				if ( (strlen(unavail[0])+200) == x+200 )
				{
					if (a==1)					// This condition will run once 
					{
					cout <<left<<setw(50)<<" Book Name :"<<setw(20)<< "Book Number :"<<setw(35)<<" Department :"<<setw(20)<<"Status:"<<setw(40)<< "Issue Details: "<<endl<<endl;
					}
					a=0;						// so that above condition never run again
					cout <<left<<setw(50)<< bookname[index] <<setw(20)<< booknumber[index] <<setw(35)<< bookdepartment[index] <<setw(20)<< availability[index] <<setw(40)<< issue[index]<<endl;
					
				}
			}
		}
	}
	cout << endl<<endl;
}

void returnfunc()
{
	main_menu();
}
