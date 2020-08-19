#include<iostream>
#include<stdio.h>
#include<stdlib.h>	
#include<windows.h>
#include<conio.h>
#include<string>
#include<process.h>
#include<ctime>
#include<fstream>
#include<C:\Program Files\MySQL\MySQL Server 8.0\include\mysql.h>
#include<C:\Program Files\MySQL\MySQL Server 8.0\include\mysqld_error.h>

using namespace std;

MYSQL *obj;
MYSQL_RES *result = new MYSQL_RES;
MYSQL_ROW row;
string query_s;
char query[1000];
int execute;

void fullscreen();

string cin_pass();

int is_empty(string);


class online_chatting	{
		
	private:
		void database_connect();
		int choice(int ch);
	protected:	
		string f_name;
		string l_name;
		string username;
		string email;
		string password;
		string r_date;
		string _dob;
		struct dob	{
			int year;
			int month;
			int date;
		}inp;
		int check(dob inp);
	public:
		void front_page();
		void signup();
		int login();
};

class user: public online_chatting	{
	
	
		void u_choice(int);
		int search();
		void profile();
		void f_profile();
		void message(int t=0);
		void logout();
		void acc_delete();
		void pass_change();
		
	public:
			void home_page();		
}u;

int main()	{
	fullscreen();
	u.front_page();
	u.home_page();
}

void online_chatting::front_page()	{
	
	database_connect();
	int ch;
	do	{
		system("cls");
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t    WELCOME TO, ONLINE CHATTING";
		cout<<"\n\n\n\n\n\n\t\t\t\t\t\t\t\t 1. LOGIN";
		cout<<"\t|\t2. SIGN UP";
		cout<<"\n\n\t\t\t\t\t\t\t\t (Press 0 to exit)";
		cout<<"\n\t\t\t\t\t\t\t\t _________________________________\n\t\t\t\t\t\t\t\t Enter your choice: ";
		cin>>ch;
	}while(choice(ch)==1);
}

void online_chatting::database_connect()	{
	obj = mysql_init(NULL);
	if(!obj)	{
		cout<<"An error occured, the object can't be created'. "<<mysql_error(obj);
		getch();
		exit(0);
	}	
	if(!mysql_real_connect(obj, "db4free.net", "shubhamamsa", "100miles", "online_chatting", 3306,NULL,0))	{
		cout<<"It seems your network is down or database server is not working."<<mysql_error(obj);
		cout<<"\n\nPress any key to exit...";
		getch();
		exit(0);
	}
}

int online_chatting::check(dob inp)	{
	
	if(inp.year>2019 || inp.month<1 || inp.month>12 || inp.date<1)
	{
		cout<<"\t\t\tSorry invalid date of birth... Enter again\n";
		return 0;
	}
	if(inp.month==2)
	{
		if((inp.year%4==0 && inp.date>29) || (inp.year%4!=0 && inp.date>28))
		{
			cout<<"\t\t\tSorry invalid date of birth... Enter again\n";
			return 0;
		}
	}
	if((inp.month==1 || inp.month==3 || inp.month==5 || inp.month==7 || inp.month == 8 || inp.month == 10 || inp.month == 12) && inp.date>31)
	{
		cout<<"\t\t\tSorry invalid date of birth... Enter again\n";
		return 0;
	}
	if((inp.month==4 || inp.month==6 || inp.month==9 || inp.month==11) && inp.date>30)
	{
		cout<<"\t\t\tSorry invalid date of birth... Enter again\n";
		return 0;
	}
	return 1;
}

int online_chatting::choice(int ch)	{
	switch(ch)	{
		case 0:
			system("cls");
			cout<<"Exiting...";
			mysql_close(obj);
			exit(0);
		case 1:
			if(login()==1)
				return 0;
			break;
		case 2:
			signup();
			break;
		default:
			cout<<"\n\t\t\t\t\t\t\t\t Sorry wrong choice selected... Enter again.";
			getch();
			break;
	}
	return 1;
}

void online_chatting::signup()	{
	int a=2;
	do	{
		system("cls");
		cout<<"\n\n\t\t\t\t\t\t\t\t\t\tSIGN UP\n\n\t\t\t";
		for(int i=0;i<59;i++)
			cout<<"==";
		cin.ignore();
		do	{
		cout<<"\n\n\t\t\tEnter your first name: ";
		getline(cin, f_name);
		if(is_empty(f_name))
			cout<<"\t\t\tField cannot be blank.";
		}while(is_empty(f_name));
		do	{
		cout<<"\n\t\t\tEnter your last name: ";
		getline(cin, l_name);
		if(is_empty(l_name))
			cout<<"\t\t\tField cannot be blank.";
		}while(is_empty(l_name));
		do	{
			cout<<"\n\t\t\tEnter date of birth: \n\t\t\t Enter year (in YYYY): ";
			cin>>inp.year;
			cout<<"\t\t\tEnter month (in MM): ";
			cin>>inp.month;
			cout<<"\t\t\tEnter date (in DD): ";
			cin>>inp.date;
		}while(check(inp)==0);
		cin.ignore();
		do	{
		cout<<"\n\t\t\tEnter your email: ";
		getline(cin, email);
		if(is_empty(email))
			cout<<"\t\t\tField cannot be blank.";
		}while(is_empty(email));
		do	{
		cout<<"\n\t\t\tEnter your username: ";
		getline(cin, username);
		if(is_empty(username))
			cout<<"\t\t\tField cannot be blank.";
		}while(is_empty(username));
		do	{
		cout<<"\n\t\t\tEnter your password: ";
		password = cin_pass();
		if(is_empty(password))
			cout<<"\n\t\t\tField cannot be blank.";
		}while(is_empty(password));
		//MYSQL QUERY STARTS
		char y[10]={0},d[10]={0},m[10]={0};
		itoa(inp.year,y,10);
		itoa(inp.month,m,10);
		itoa(inp.date,d,10);
		query_s = "INSERT INTO users (f_name,l_name,dob,email,username,pass,r_date) VALUES('"+f_name+"','"+l_name+"','"+y+"-"+m+"-"+d+"','"+email+"','"+username+"','"+password+"',now())";
		strcpy(query, query_s.c_str());
		execute = mysql_query(obj, query);
		if(execute)
		{
			cout<<"\n\t\t\tSorry some error occured. MySQL error("<<mysql_error(obj)<<")"<<endl;
			cout<<"\n\t\t\tDo you want to enter again.(Yes -> 1 ... No -> 0): ";
			cin>>a;
		}
		//MYSQL QUERY ENDS
	}while(a==1);
	if(a==0)
		cout<<"\n\t\t\tRequest aborted.";
	else
		cout<<"\n\t\t\tSuccessfully registered... Please login to continue";
	getch();
}

int online_chatting::login()	{
	system("cls");
	cout<<"\n\n\t\t\t\t\t\t\t\t\t\tLOGIN\n\n\t\t\t";
	for(int i=0;i<59;i++)
		cout<<"==";
	cin.ignore();
	do	{
	cout<<"\n\n\t\t\tEnter your username: ";
	getline(cin, username);
	if(is_empty(username))
		cout<<"\t\t\tField cannot be blank.";
	}while(is_empty(username));
	do	{
	cout<<"\n\n\t\t\tEnter your password: ";
	password = cin_pass();
	if(is_empty(password))
		cout<<"\n\t\t\tField cannot be blank.";
	}while(is_empty(password));
	query_s = "SELECT * FROM users where username='"+username+"'";
	strcpy(query,query_s.c_str());
	execute = mysql_query(obj, query);
	if(execute)	{
			cout<<"\n\n\t\t\tAn error occured MYSQL("<<mysql_error(obj)<<")";
			getch();
			return 0;
		}
		result = mysql_store_result(obj);
		row=mysql_fetch_row(result);
			if(row==NULL)	{
				cout<<"\n\n\t\t\tUsername not found...";
				getch();
				return 0;
			}
		if((row[6]!=password))	{
			cout<<"\n\n\t\t\tWrong username and password";
			getch();
			return 0;
		}
		f_name=row[1];
		l_name=row[2];
		_dob=row[3];
		email=row[4];
		r_date=row[7];
	return 1;
}

void user::home_page()	{
	time_t now = time(0);
	char* dt = ctime(&now);
	int ch;
	do	{
	system("cls");
	cout<<"\n\n\t\t\t\t\t\t\t\t\t\tHOME PAGE\n\n\t\t\t";
	for(int i=0;i<59;i++)
		cout<<"==";
	cout<<"\n\n\t\t\t Welcome, "<<f_name<<"\t\t\t\t\t\t\t\t\t   "<<dt<<"\t\t\t";
	for(int i=0;i<59;i++)
		cout<<"==";
	cout<<"\n\n\n\n\n\t\t\t\t\t1. Send Message\n\n\n\t\t\t\t\t2. Search Profile\n\n\n\t\t\t\t\t3. Go to your Profile\n\n\n\t\t\t\t\t4. Logout";
	cout<<"\n\n\n\n\t\t\t\t\tEnter your choice: ";
	cin>>ch;
	u_choice(ch);
	}while(1);
}

void user::u_choice(int ch)	{
	switch(ch)
	{
		case 1:
			message();
			break;
		case 2:
			f_profile();
			break;
		case 3:
			profile();
			break;
		case 4:
			logout();
			break;
		default:
			cout<<"You have entered wrong choice... Enter again.";
			getch();
			break;
	}
}

int user::search()	{
	
	system("cls");
	string usr;
	cin.ignore();
	cout<<"\n\t\tEnter username to search: ";
	getline(cin, usr);
	query_s = "SELECT * FROM users where username = '"+usr+"'";
	strcpy(query, query_s.c_str());
	execute = mysql_query(obj, query);
	if(execute)	{
		cout<<"\n\t\tUh Oh! Some error occured MYSQL("<<mysql_error(obj)<<")";
		getch();
		return 0;
	}
	result = mysql_store_result(obj);
	row = mysql_fetch_row(result);
		if(row == NULL)	{
			cout<<"\n\t\tNo user found with this username.";
			getch();
			return 0;
		}
	return 1;	
}

void user::f_profile()	{
	
	if(search()==0)
		return;
	system("cls");
		cout<<"\n\t\t\t\t\t\t\t\t\t\t"<<row[1]<<"'s Profile\n\t\t\t\t\t";
		for(int i=0;i<50;i++)
			cout<<"__";
		cout<<"\n\n\n\n\n\n\t\t\t\t\t Name: "<<row[1]<<" "<<row[2];
		cout<<"\n\n\n\t\t\t\t\t Email: "<<row[4];
		cout<<"\n\n\n\t\t\t\t\t Username: "<<row[5];
		cout<<"\n\n\n\t\t\t\t\t Date of Birth: "<<row[3];
		cout<<"\n\n\n\t\t\t\t\t Registration Date: "<<row[7];
		cout<<"\n\n\n\n\n\n\n\t\t\t\t\t\t\t 1. MESSAGE\t\t|\t\t2. GO TO HOMEPAGE";
		cout<<"\n\n\t\t\t\t\t\t\t Enter your choice: ";
		int a;
		cin>>a;
		do {
			if(a==1)
			message(1);
			else if(a==2)
				return;
			else	{
				cout<<"Wrong input.. Enter again";
				getch();
			}
		}while(a!=1 || a!=2);
}

void user::logout()	{
	
	char ch;
	cout<<"\n\t\t\t\t\t\tDo you want to logout(Y/N): ";
	cin>>ch;
	if(ch=='Y' || ch=='y')	{
		front_page();
	}
	else if(ch=='N' || ch=='n')	{
		return;
	}
	else	{
		cout<<"\t\t\t\t\t\t\tWrong input...";
		getch();
	}
}

void user::profile()	{
	
	int a;
	do	{
	system("cls");
	cout<<"\n\t\t\t\t\t\t\t\t\t\tYour Profile\n\t\t\t\t\t";
	for(int i=0;i<50;i++)
		cout<<"__";
	cout<<"\n\n\n\n\n\n\t\t\t\t\t Name: "<<f_name<<" "<<l_name;
	cout<<"\n\n\n\t\t\t\t\t Email: "<<email;
	cout<<"\n\n\n\t\t\t\t\t Username: "<<username;
	cout<<"\n\n\n\t\t\t\t\t Date of Birth: "<<_dob;
	cout<<"\n\n\n\t\t\t\t\t Registration Date: "<<r_date;
	cout<<"\n\n\n\n\n\n\n\t\t\t\t\t\t 1. HOMEPAGE\t|\t 2. CHANGE PASSWORD\t|\t 3. DELETE YOUR ACCOUNT";
	cout<<"\n\n\t\t\t\t\t\t Enter your choice: ";
	cin>>a;
	switch(a)	{
		case 1:
			return;
		case 2:
			pass_change();
			break;
		case 3:
			acc_delete();
			break;
		default:
			cout<<"Wrong input enter again";
			getch();
			break;
	}
	}while(a>3||a<1);
}

void user::pass_change()	{
	
	
	system("cls");
	string pass;
	cout<<"\n\n\t\t\t Enter your current password: ";
	cin.ignore();
	pass = cin_pass();
	if(pass != password)	{
		cout<<"\n\t\t\t Sorry wrong password";
		getch();
		return;
	}
	cout<<"\n\n\t\t\t Enter new password: ";
	pass = cin_pass();
	query_s = "UPDATE users set pass = '"+pass+"'";
	strcpy(query, query_s.c_str());
	execute = mysql_query(obj, query);
	if(!execute)	{
		cout<<"\n\t\t\tPassword changed... Login again";
		getch();
		front_page();
	}
	else	{
		cout<<"\n\t\t\tAn error occured MYSQL("<<mysql_error(obj)<<")";
		getch();
	}
}

void user::acc_delete()	{
	
	system("cls");
	char ch;
	cout<<"\n\n\t\t\t ALL YOUR DATA WILL BE DELETED! DO YOU WANT TO DELETE YOUR ACCOUNT(Y/N): ";
	cin>>ch;
	if(ch=='Y' || ch=='y')	{
		query_s = "DELETE FROM users where username = '"+username+"'";
		strcpy(query, query_s.c_str());
		execute = mysql_query(obj, query);
		if(!execute)	{
			system("cls");
			cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t ACCOUNT DELETED SUCCESSFULLY";
			getch();
			front_page();
		}
		else	{
			cout<<"\n\t\t\t An error occured MYSQL("<<mysql_error(obj)<<")";
			getch();
		}
	}
	else if(ch=='N' || ch=='n');
	else	{
		cout<<"\n\t\t\t Wrong input";
		getch();
	}
}

void user::message(int t)	{
		
		if(t==0)
			if(search()==0)
				return;
		int ch=1;
		string usr, msg;
		usr = row[5];
		do	{
		system("cls");
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t"<<usr<<"\n\t\t\t\t\t";
		for(int i=0;i<50;i++)
			cout<<"__";
		query_s = "SELECT f_name, message from msg where uid = '"+username+usr+"' OR uid = '"+usr+username+"'";
		strcpy(query, query_s.c_str());
		execute = mysql_query(obj, query);
		if(!execute)	{
			
			result = mysql_store_result(obj);
			while(row = mysql_fetch_row(result))	{
				
				if(row == NULL)	{
					cout<<"\n\n\n\n\t\t\t\t\t\t\t\t\tNo messages yet.";
					getch();
					break;
				}
				cout<<"\n\n\t\t\t\t\t"<<row[0]<<": "<<row[1]<<endl<<endl;
			}
		cout<<"\n\t\t\t\t\t";
		for(int i=0;i<50;i++)
			cout<<"__";
		cout<<"\n\n\t\t\t\t\t";
		cout<<"1. Refresh \t\t\t\t 2. Reply \t\t\t\t 3. Home Page";
		cout<<"\n\n\t\t\t\t\t";
		cout<<"Enter your choice: ";
		cin>>ch;
		switch(ch)	{
			case 1:
				break;
			case 2:
				cin.ignore();
				do	{
				cout<<"\n\n\t\t\t\t\t";	
				cout<<"Enter message: ";
				getline(cin, msg);
				if(is_empty(msg))
					cout<<"\t\t\t\t\tSorry blank message is not allowed.";
				}while(is_empty(msg));
				query_s = "INSERT INTO msg values('"+username+usr+"','"+f_name+"','"+msg+"')";
				strcpy(query, query_s.c_str());
				execute = mysql_query(obj, query);
				if(execute)	{
					cout<<"\n\t\t\t\t\tSorry an error occured MYSQL("<<mysql_error<<")";
				}
				break;
			case 3:
				home_page();
			default:
				cout<<"\n\n\t\t\t\t\t";
				cout<<"Sorry wrong input enter again";
				getch();
				break;
		}	
		}
		else	{
			cout<<"\n\t\t\t\t\tSorry an error occured MYSQL("<<mysql_error(obj)<<")";
			return;
		}
	}while(ch==1 || ch == 2);
}

string cin_pass()	{
	
	char ch, pass[40];
	string password;
	int i=0;
	while(ch!=13)
	{
		ch=getch();
		if(ch!=8)
		{
			pass[i]=ch;
			i++;
		}
		else if(ch==8)
			if(i>0)
			i--;
	}
	pass[i-1]='\0';
	password = pass;
	return password;
}

int is_empty(string ch)	{
	
	if(ch=="")
		return 1;
	else
		return 0;
}

void fullscreen()	{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
