#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

bool isNumeric(string s)
{
	for(int i=0; i<s.length(); i++)
	{
		if(!(s[i] >='0' && s[i] <= '9'))
			return false;
	}
	return true;
}

int toInt(string s)
{
	unsigned int mul=1;
	int n=0;
	if(s[0] != '@' && !(isNumeric(s)))
	{
		return -1;
	}
	for(int i = s.length()-1; i>=0; i--)
	{
		if(s[i] >='0' && s[i] <= '9')
		{
			n += (s[i]-48)*mul;
			mul *= 10;
		}
	}
	return n;
}

string stripSpace(string s)
{
	string n;
	stringstream t;
	int i,j;
	for(i=0; i<s.length(); i++)
	{
		if(!(s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		{
			t<<s[i];
		}	
	}
	t >> n;
	return n;
}

void toBin(bool arr[],int n)
{
	for(int i=15; i>=0; i--)
	{
		arr[i] = n%2;
		n=n/2;
	}
}

int comp(bool arr[], string s)
{
	arr[3] = (s.find('M') == -1)? 0: 1;
	char c = (arr[3])? 'M': 'A';
	string t = "";
	t += c;
	if(s=="0")
	{
		arr[4] = arr[6] = arr[8] = 1;
	}
	else if(s=="1")
	{
		arr[4] = arr[5] = arr[6] = arr[7] = arr[8] = arr[9] = 1;
	}
	else if(s=="-1")
	{
		arr[4] = arr[5] = arr[6] = arr[8] = 1;
	}
	else if(s=="D")
	{
		arr[6] = arr[7] = 1;
	}
	else if(s==t)
	{
		arr[4] = arr[5] = 1;
	}
	else if(s=="!D")
	{
		arr[6] = arr[7] = arr[9] = 1;
	}
	else if(s=="!"+t)
	{
		arr[4] = arr[5] = arr[9] = 1;
	}
	else if(s=="-D")
	{
		arr[6] = arr[7] = arr[8] = arr[9] = 1;
	}
	else if(s=="-"+t)
	{
		arr[4] = arr[5] = arr[8] = arr[9] = 1;
	}
	else if(s=="D+1")
	{
		arr[5] = arr[6] = arr[7] = arr[8] = arr[9] = 1;
	}
	else if(s==t+"+1")
	{
		arr[4] = arr[5] = arr[7] = arr[8] = arr[9] = 1;
	}
	else if(s=="D-1")
	{
		arr[6] = arr[7] = arr[8] = 1;
	}
	else if(s==t+"-1")
	{
		arr[4] = arr[5] = arr[8] = 1;
	}
	else if(s=="D+"+t || s==t+"+D")
	{
		arr[8] = 1;
	}
	else if(s=="D-"+t)
	{
		arr[8] = arr[5] = arr[9] = 1;
	}
	else if(s==t+"-D")
	{
		arr[7] = arr[8] = arr[9] = 1;
	}
	else if(s=="D&"+t)
	{
		arr[4] = arr[5] = arr[6] = arr[7] = arr[8] = arr[9] = 0;
	}
	else if(s=="D|"+t)
	{
		arr[5] = arr[7] = arr[9] = 1;
	}
	else
	{
		return -1;
	}
	return 0;
}

int main()
{
	string name,line,t;
	int addr,l=0,ic=0;
	bool ins[16];
	cout << "Enter name of assembly file: ";
	getline(cin,name);
	ifstream ifile;
	ifile.open(name.c_str());
	if(ifile.fail())
	{
		cout<<"Invalid file!"<<endl;
		return 0;
	}
	ofstream ofile;
	string outfile;
	if(name.find(".asm") == name.length()-4)
	{
		outfile = name.substr(0,name.length()-4);
	}
	else
	{
		cout<<"Invalid file format!"<<endl;
		return 0;
	}
	outfile = outfile + ".hack";
	ofile.open(outfile.c_str());
	while(getline(ifile,line))
	{
		for(int i=0; i<16;i++)
			ins[i] = 0;
		l++;
		if(line.find("//") != -1)
		{
			stringstream s(line);
			getline(s,line,'/');
		}
		line = stripSpace(line);
		if(line.empty())
		{
			continue;
		}
		ic++;
		if(line[0] == '@')
		{
			addr = toInt(line);
			if(addr > 32767 || addr == -1)
			{
				cout<<"Invalid address at line "<<l<<endl;
				return 0;
			}
			toBin(ins,addr);
		}
		else
		{
			ins[0] = ins[1] = ins[2] = 1;
			if(line.find('=') != -1)
			{
				stringstream temp(line);
				getline(temp,t,'=');
				if(t.length()>3)
				{
					cout<<"Invalid destination instruction on line "<<l<<endl;
					return 0;
				}
				int a = t.find('A'),m = t.find('M'),d = t.find('D');
				if(a != -1)
				{
					ins[10] = 1;
				}
				if(m != -1)
				{
					ins[12] = 1;
				}
				if(d != -1)
				{
					ins[11] = 1;
				}
				int sum = ins[10] + ins[12] + ins[11];
				if(sum != t.length())
				{
					cout<<"Invalid destination instruction on line "<<l<<endl;
					return 0;
				}
				if(sum == 3)
				{
					if(!(a<m && m<d))
					{
						cout<<"Invalid destination instruction on line "<<l<<endl;
						return 0;
					}
				}
				else if(sum == 2)
				{
					if(!(a==0 || d==1))
					{
						cout<<"Invalid destination instruction on line "<<l<<endl;
						return 0;
					}
				}
				getline(temp,t);
				int tmp = comp(ins,t);
				if(tmp == -1)
				{
					cout<<"Invalid computation instruction at line "<<l<<endl;
					return 0;
				}
			}
			else if(line.find(';') != -1)
			{
				stringstream temp(line);
				getline(temp,t,';');
				int tmp = comp(ins,t);
				if(tmp == -1)
				{
					cout<<"Invalid computation instruction at line "<<l<<endl;
					return 0;
				}
				getline(temp,t);
				if(t == "JGT")
				{
					ins[15] = 1;
				}
				else if(t == "JEQ")
				{
					ins[14] = 1;
				}
				else if(t == "JGE")
				{
					ins[14] = ins[15] = 1;
				}
				else if(t == "JLT")
				{
					ins[13] = 1;
				}
				else if(t == "JNE")
				{
					ins[13] = ins[15] = 1;
				}
				else if(t == "JLE")
				{
					ins[13] = ins[14] = 1;
				}
				else if(t == "JMP")
				{
					ins[13] = ins[14] = ins[15] = 1;
				}
				else
				{
					cout<<"Invalid jump instruction on line "<<l<<endl;
					return 0;
				}
			}
			else
			{
				cout<<"Invalid instruction on line "<<l<<endl;
				return 0;
			}
		}
		if(ic > 1)
			ofile<<endl;
		for(int i=0; i<16;i++)
			ofile<<ins[i];
	}
	cout<<"Code Assembled Successfully!"<<endl;
	ifile.close();
	ofile.close();
	return 0;
}
