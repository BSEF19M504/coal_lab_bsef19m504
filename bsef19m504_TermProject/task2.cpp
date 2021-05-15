#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

class dictionary{
	private:
		string *key;
		int *value;
		int size;
		int ind;
		void expand()
		{
			string *tmpk = new string[size];
			int *tmpv = new int[size];
			for(int i = 0; i < size; i++)
			{
				tmpk[i] = key[i];
				tmpv[i] = value[i];
			}
			delete [] key;
			delete [] value;
			key = new string[size + 100];
			value = new int[size + 100];
			for(int i = 0; i < size; i++)
			{
				key[i] = tmpk[i];
				value[i] = tmpv[i];
			}
			delete [] tmpk;
			delete [] tmpv;
			size += 100;
		}
		int search(string k)
		{
			bool p=false;
			int i;
			for(i=0; i<ind; i++)
			{
				if(key[i] == k)
				{
					p=true;
					break;
				}
			}
			if(p)
				return i;
			else
				return -1;
		}
	public:
		dictionary()
		{
			size = 100;
			key = new string[100];
			value = new int[100];
			ind = 0;
		}
		dictionary(int n)
		{
			key = new string[n];
			value = new int[n];
			size = n;
			ind = 0;
		}
		~dictionary()
		{
			delete [] key;
			delete [] value;
		}
		int& operator [](string k)
		{
			int *n = new int;
			*n = -1;
			int t = search(k);
			if(t!=-1)
			{
				return value[t];
			}
			else
			{
				return *n;
			}
		}
		void append(string k, int v)
		{
			if(ind == size)
			{
				expand();
			}
			key[ind] = k;
			value[ind] = v;
			ind++;
		}
};

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
	int addr,l=0,ic=0,var=16;
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
	dictionary symbol;
	symbol.append("R0",0);
	symbol.append("R1",1);
	symbol.append("R2",2);
	symbol.append("R3",3);
	symbol.append("R4",4);
	symbol.append("R5",5);
	symbol.append("R6",6);
	symbol.append("R7",7);
	symbol.append("R8",8);
	symbol.append("R9",9);
	symbol.append("R10",10);
	symbol.append("R11",11);
	symbol.append("R12",12);
	symbol.append("R13",13);
	symbol.append("R14",14);
	symbol.append("R15",15);
	symbol.append("SCREEN",0x4000);
	symbol.append("KBD",0x6000);
	symbol.append("SP",0);
	symbol.append("LCL",1);
	symbol.append("ARG",2);
	symbol.append("THIS",3);
	symbol.append("THAT",4);
	outfile = outfile + ".hack";
	ofile.open(outfile.c_str());
	while(getline(ifile,line))
	{
		string sym;
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
		if(line[0] == '(' && line[line.length()-1] == ')')
		{
			sym = line.substr(1,line.length()-2);
			ic--;
			symbol.append(sym,ic);
		}
	}
	ifile.close();
	ic=0;
	ifile.open(name.c_str());
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
		if(line[0] == '(')
		{
			ic--;
			continue;
		}
		else if(line[0] == '@')
		{
			line = line.substr(1,line.length()-1);
			if(!isNumeric(line))
			{
				if(symbol[line] == -1)
				{
					symbol.append(line,var);
					addr = symbol[line];
					var++;
				}
				else
				{
					addr = symbol[line];
				}
			}
			else
			{
				addr = toInt(line);
			}
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
