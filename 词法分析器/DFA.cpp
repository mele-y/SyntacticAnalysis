#include<iostream>
#include<vector>
using namespace std;
#include<iomanip>
#include<sstream>
class f_d{
	 private:string start_state;
	         char input_ch;
	         string target_state;
     public: f_d(string s1,char ch,string s2)
     {
     	start_state=s1;
     	input_ch=ch;
     	target_state=s2;
     }
     void print()
     {
     	cout<<setw(5)<<start_state<<setw(5)<<input_ch<<setw(5)<<target_state<<endl;
     }
     string getStartState()
     {
     	return start_state;
     }
     char getInput()
     {
     	return input_ch;
     }
     string getTargetState(){
     	return target_state;
     }
};
class DFA{
    private:vector<string> state_set;
    vector< vector<char> > T;
    vector<char> input_ch_set;
    string start_state;
    vector<string> final_state;
    vector<f_d> f_set;
    public: void setInputSet(vector<char> v1)
    {
    	for(int i=0;i<v1.size();i++)
    	{
    		if(v1[i]!='$')
    		{
    			input_ch_set.push_back(v1[i]);
    		}
    		else
    		continue;
    	}
    }
    void addF(f_d item)
    {
    	f_set.push_back(item);
    }
    void addFinalState(string str)
    {
    	final_state.push_back(str);
    }
    void show()
    {   
        for(int i=0;i<T.size();i++)
        {
        	cout<<"T"+intToString(i)+"={";
        	  for(int j=0;j<T[i].size();j++)
        	  {
        	  	cout<<T[i][j]<<" ";
        	  }
        	  cout<<"}";
        	  cout<<endl;
        }
    	for(int i=0;i<f_set.size();i++)
    	  f_set[i].print();
    }
    void updateT(vector< vector<char> > v)
    {
    	T=v;
    }
    string intToString(int n)
	{
		stringstream s;
		s<<n;
		return s.str();
	}
	string nextState(string state,char ch)
	{
		for(int i=0;i<f_set.size();i++)
		{
			if(f_set[i].getStartState()==state&&f_set[i].getInput()==ch)
			  return f_set[i].getTargetState();
		}
		 return "-1";
	}
	bool isFinalState(string str)
	{
		for(int i=0;i<final_state.size();i++)
		{
			if(str==final_state[i])
			  return true;
		}
		return false;
	}
	bool isAccepted(string str)
	{
		string DFAstate="T0";
		string DFAstate2;
		for(int i=0;i<str.length();i++)
		{
			DFAstate2=nextState(DFAstate,str[i]);
			if(DFAstate2=="-1")
			{
				return false;
			}
			DFAstate=DFAstate2;
		}
		if(isFinalState(DFAstate2))
		return true;
		else
		return false;
	}
}; 
