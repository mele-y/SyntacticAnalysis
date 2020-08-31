#include<iostream>
using namespace std;
#include<vector>
#include<iomanip>
class f{
	private:char state_now;
	        char input;
	        char state_target;
    public: f(char state,char ch,char target)
    {
    	   state_now=state;
    	   input=ch;
    	   state_target=target;
    	   
    }
       char getstate_now()
       {
       	return state_now;
       }
       char getInput()
       {
       	return input;
       }
       char getstate_target()
       {
       	return state_target;
       }
      bool equal(f temp)
      {
      	return  (state_now==temp.getstate_now())&&(input==temp.getInput())&&(state_target==temp.getstate_target());
      }
      void show()
      {
      	cout<<setw(5)<<state_now<<setw(5)<<input<<setw(5)<<state_target<<endl;
      }
};
class NFA{
	private:vector<char> state_set;
	        vector<char> input_set;
	        vector<f>  f_set;
	        char state_start='S';
	        char state_final='Z';
	public: 
	vector<char> getinput_set(){
		return input_set;
	}
	void setinput_set(vector<char> v1)
	{
		input_set=v1;
	}
	bool isNewState(char state)
	{
		bool flag=true;
		for(int i=0;i<state_set.size();i++)
		{
			if(state==state_set[i])
			{
				flag=false;
				break;
			}
		} 
		return flag;
	}
	  bool isNewInput(char ch)
	  {
	  	bool flag=true;
	  	for(int i=0;i<input_set.size();i++)
	  	{
	  		if(ch==input_set[i])
	  		{
	  			flag=false;
	  			break;
	  		}
	  	}
	  	return flag;
	  }
	void addState(char state){
		if(isNewState(state))
		{
			state_set.push_back(state);
		}
	}
	void addInputCh(char ch)
	{
		if(isNewInput(ch))
		{
			input_set.push_back(ch);
		}
	}
    void addFSET(char state,char ch,char target)
	{
		    f temp(state,ch,target);
		    bool flag=true;
		    for(int i=0;i<f_set.size();i++)
		    {
		    	if(f_set[i].equal(temp))
		    	{
		    	flag=false;
		    	break;
		        }
		    }
		    if(flag)
			f_set.push_back(temp);
		
	}
	void show(){
		cout<<"状态集如下："<<endl;
		for(int i=0;i<state_set.size();i++)
		cout<<state_set[i]<<" ";
		cout<<endl;
		cout<<"符号集如下："<<endl;
		for(int i=0;i<input_set.size();i++)
		cout<<input_set[i]<<" ";
		cout<<endl;
	}
	bool isIn(vector<char> state, char ch)
	{
		bool flag=false;
		for(int i=0;i<state.size();i++)
		{
			if(state[i]==ch)
			 {
			 	flag=true;
			 	break;
			 }
		}
		return flag;
	}
	vector<char> closure(vector<char> state)
	{  vector<char> closure_set=state;
	   vector<char> closure_set2=state;
	   char ch;
	    for(int i=0;i<state.size();i++)
	    {   ch=state[i];
	    	for(int j=0;j<f_set.size();j++)
	    	{
	    		if((f_set[j].getstate_now()==ch)&&(f_set[j].getInput()=='$'))
	    		 {
	    		 	char target=f_set[j].getstate_target();
	    		 	if(!isIn(closure_set,target))
	    		 	 closure_set.push_back(target);
	    	     }
	       }
	    7y
	    }
	    if(closure_set==closure_set2)
		return closure_set;
		else
		return closure(closure_set);
    }
	vector<char> move(vector<char> T,char ch)
	{   char temp;
	    vector<char> result;
		for(int i=0;i<T.size();i++)
		{
			temp=T[i];
			for(int j=0;j<f_set.size();j++)
			{
				if((f_set[j].getstate_now()==temp)&&(f_set[j].getInput()==ch))
				{
					char target=f_set[j].getstate_target();
					if(!isIn(result,target))
					 result.push_back(target); 
				}
			}
		}
	    return result;
	}
} ;
