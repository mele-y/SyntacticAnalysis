#include<iostream>
using namespace std;
#include<fstream> 
#include<vector>
#include<sstream>
#include"NFA.cpp"
#include"DFA.cpp"
class TOKEN{
	   private:int index;
	           string type;
	           string value;
	           //string value;
	   public:TOKEN(int index,string type,string value){
	   	this->index=index;
	   	this->type=type;
	   	//this.name=name;
	   	this->value=value;
	   }
	   TOKEN(){
	   }
	   void set(int index,string type,string value){
	   	this->index=index;
	   	this->type=type;
	   	//this.name=name;
	   	this->value=value;
	   }
	   void print()
	   {
	   	
	   	cout<<index<<" "<<type<<" "<<value<<endl;
	   }
	   string getType()
	   {
	   	return type;
	   }
	   string getValue()
	   {
	   	return value;
	   }
	   int getIndex()
	   {
	   	return index;
	   }
};
class LexAnalyzer{
	private: string source_file_name;
	         ifstream infile;//��ȡ�ļ��ļ��� 
	         ofstream outfile;//����ļ��ļ��� 
	         string grammer_file_name;//�ķ��ļ��� 
	         const string reserve_word[15]={"int","main","float","char","bool","if","else","while","continue","break","return","true","flase","cout","cin"};//������ 
	         char delimters[9]={',',';','.','(',')','{','}','[',']'};//�ֽ�� 
	         char single_operator[12]={'+','-','*','/','=','&','|','!','?','>','<',':'};//���ַ������� 
             const string double_operator[11]={"==",">=","<=","&&","||","!=","++","--","+=","-=","<<"};//˫�ַ������� 
             int num_of_reserve_word=15;//��������Ŀ 
             int num_of_delimters=9;
             int num_of_single_op=12;
             int num_of_double_op=11;
	         char start_state='S';//�Զ�����̬ 
	         char final_state='Z';//�Զ�����̬ 
	         NFA nfa;
	         DFA dfa;
	         stringstream s;
	         vector<TOKEN> result;
	public :char ToCh(string str)
	      {
	      	  if(str=="int")
	      	     return 't';
	      	  if(str=="main")
	      	     return 'm';
	      	  if(str=="float")
	      	  return 'f';
			  if(str=="char")
			   return 'c';
			  if(str=="bool")
			    return 'b';
			  if(str=="if")
			   return 'i'; 
			  if(str=="else")
			   return 'e';
			  if(str=="while")
			   return 'w';
			  if(str=="continue")
		       return 'o';
		      if(str=="break")
		       return 'k';
		      if(str=="return")
		       return 'u';
		      if(str=="true")
		       return 'x';
		      if(str=="flase")
		        return 'y'; 
			 if(str=="cout")
			    return 'p';
			  if(str=="cin")
			   return 'q' ;
			  if(str=="++")
			   return '0';
			  if(str=="+=")
			   return '1';
			  if(str=="==")
			  return '2';
			  if(str=="<=")
			   return '3';
			  if(str=="!=")
			  return '4';
			  if(str=="&&")
			  return '5';
			  if(str=="||")
			   return '6';
			  if(str=="<<")
			  return '7';  
	      }
	void readSourceFile(){
		//infile.clear();
		char ch;
		
		while(true)
		{
		
		cout<<"����Դ�ļ�����";
		cin>>source_file_name;
		infile.open(source_file_name.c_str());
		if(infile.fail())
		{
			cout<<"��ʧ��"<<endl;
			infile.close();
		}
		else
		{  
           precompile();
           infile.close();
           break;
		}
       }
	}
	void precompile()
	{   ostringstream strstream;
		int state=0;
		char ch1,ch2;
		vector<char> v1;
		/*while(infile.get(ch1))
		{   
			v1.push_back(ch1);
		}*/
    
		cout<<"Ԥ����������:"<<endl; 
		while(infile.get(ch1))
		{
			switch(state){
				case 0: infile.get(ch2);
						if(ch1=='#'){state=1;infile.putback(ch2);continue;}
				 		if((ch1=='/')&&(ch2=='/')){state=2;continue;}
				 		if((ch1=='/')&&(ch2=='*')){state=3;continue;}
				 		strstream<<ch1;
				 		infile.putback(ch2);
				 		continue;
				case 1: if(ch1=='\n'){strstream<<ch1;state=0;continue;}else{state=1;continue;}
				case 2: if(ch1=='\n'){strstream<<ch1;state=0;continue;}else{state=2;continue;}
				case 3: infile.get(ch2);
				        if((ch1=='*')&&(ch2=='/')){
				        	state=0;
				        	continue;
				        }
				        else{
				        	state=3;
				        	infile.putback(ch2);
				        	continue;
				        }
				} 
			}
			s<<strstream.str();
            cout<<strstream.str();
		}
		void readGrammer(){
			while(true){
			
			cout<<"���������ķ��ļ���:";
			cin>>grammer_file_name;
			infile.open(grammer_file_name.c_str());
			if(infile.fail())
			{
				cout<<"�޷���,��������"<<endl;
				infile.close();
			}
			else{
				nfa=GrammerToNFA();
				nfa.show();
				break;
			}
		    }
		}
	NFA GrammerToNFA()
	{     string line;
	      stringstream tempStream;
	      char state,ch1,ch2,ch,target_state;
	      string str;
	      NFA nfa;
		  while(getline(infile,line))
		  {
		  	tempStream<<line;
		  	tempStream>>state>>ch1>>ch2>>str;
		  	if(str.length()>1)
		  	{
		  	      nfa.addState(state);
				  nfa.addInputCh(str[0]);
				  nfa.addFSET(state,str[0],str[1]);
				    	  	      
		  	}
		  	else
		  	     {
		  	      nfa.addState(state);
				  nfa.addInputCh(str[0]);
				  nfa.addFSET(state,str[0],'Z');
		  	     } 	
		  	tempStream.clear();
		  }
		  return nfa;
	}
	string intToString(int n)
	{
		stringstream s;
		s<<n;
		return s.str();
	}
	int isAllMark(vector<bool> flag){
	   int index=-1;	
		for(int i=0;i<flag.size();i++)
		{
			if(!flag[i])
			{
				index=i;
				break;
			}
		}
		return index;
	}
	int isIn(vector< vector<char> > T,vector<char> temp)
	{
		int flag=-1;
		for(int i=0;i<T.size();i++)
		{
			if(T[i]==temp)
			{
				flag=i;
				break;
			}
		}
		return flag;
	}
	bool isContainZ(vector<char> temp)
	{
		for(int i=0;i<temp.size();i++)
		{
			if(temp[i]=='Z')
			return true; 
		} 
		return false;
	}
	void printVector(vector<char> v1)
	{
		for(int i=0;i<v1.size();i++)
		 cout<<v1[i]<<"  ";
		cout<<endl;
	}
	void NFAtoDFA()
	{   dfa.setInputSet(nfa.getinput_set());
        int count=0;
        int index,index2;
        string state_name="T";
		vector< vector<char> > T;
		vector<bool> flag;
		vector<char> temp;
		temp.push_back('S');
		temp=nfa.closure(temp);
		T.push_back(temp);
		flag.push_back(false);
		while((index=isAllMark(flag))!=-1)
		{
			flag[index]=true;
			for(int i=0;i<nfa.getinput_set().size();i++)
			{   char ch=nfa.getinput_set()[i];
			    //cout<<ch<<endl;
			    if(ch!='$'){			    
				temp=nfa.closure(nfa.move(T[index],ch));
				if(temp.size()==0)
				continue;
				if((index2=isIn(T,temp))==-1)
				{
					T.push_back(temp);
					if(isContainZ(temp))
					    dfa.addFinalState(state_name+intToString(count+1));
					flag.push_back(false);
					f_d item(state_name+intToString(index),nfa.getinput_set()[i],state_name+intToString(count+1));
					count++;
					dfa.addF(item);
				}
				else{
					f_d item(state_name+intToString(index),nfa.getinput_set()[i],state_name+intToString(index2));
					dfa.addF(item);
				}
			   }
			   else
			    continue;
			}
		}
		dfa.updateT(T);
		dfa.show();
	}  
	bool isDelimter(char ch)
	{
		for(int i=0;i<num_of_delimters;i++)
		   if(ch==delimters[i]) 
		   return true;
		return false;
	}
	bool isSingleOp(char ch)
	{
		for(int i=0;i<num_of_single_op;i++)
		{
			if(ch==single_operator[i])
			return true;
		}
		return false;
	}
	bool isDoubleOp(string str)
	{
		for(int i=0;i<num_of_double_op;i++)
		{
			if(str==double_operator[i])
			  return true;
		}
		return false;
	}
	bool isDigit(char ch)
	{
		return (ch>='0')&&(ch<='9');
	}
	bool isLetter(char ch)
	{
		return ((ch>='a')&&(ch<='z'))||(ch=='_')||((ch>='A')&&(ch<='Z'));
	}
  bool isReserveWord(string str)
   {
   	   for(int i=0;i<num_of_reserve_word;i++)
   	   {
   	   	if(str==reserve_word[i])
   	   	 return true;
   	   }
   	   return false;
   }
   void analyze()
   {  char ch;
      int state=0;
	  string token;
	  //vector<TOKEN> result;
	  TOKEN item;
	  int count=0;
	  string DFAstate;
	  string DFAstate2;
      string str=s.str();
      int i=0;
      while(i<=str.length())
      {  if(i!=str.length()) 
      	  ch=str[i];
      	  else
      	   ch=' ';
      	 switch(state)
      	 {
      	 	 case 0:token="";
				    if(ch==' '||ch=='\n'||ch=='\t'||ch=='\r'||ch=='\0'){i++;continue;}
				    else
      	 	        if(isDelimter(ch)){state=1;token=token+ch;continue;}
      	 	        else
      	 	        if(isSingleOp(ch))
      	 	        {
      	 	        	 state=2;token=token+ch;continue;
      	 	        }
      	 	        else
      	 	        if(isDigit(ch))
      	 	        {
					     DFAstate="T0";
      	 	        	 state=3;
      	 	        	 continue;
      	 	        	 
      	 	        }
      	 	        else
      	 	        if(isLetter(ch))
      	 	        {
      	 	        	state=4;
      	 	        	token=token+ch;
      	 	        	i++;
      	 	        	continue;
      	 	        }
      	 	        else
      	 	        {    token=token+ch;
      	 	        	item.set(++count,"����",token);
      	 	        	i++;
      	 	        	state=0;
      	 	        	continue;
      	 	        }
      	 	case 1: item.set(++count,"�ֽ��",token);
      	 	        state=0;
      	 	        i++;
      	 	        result.push_back(item);
      	 	        continue;
      	 	case 2: if(isDoubleOp(token+str[i+1]))
			        {
			    	state=0;
			    	token=token+str[i+1];
			    	 item.set(++count,"������",token);
			    	 result.push_back(item);
			    	 i=i+2;
			    	 continue;
			         }
					 else
					 {
					 	state=0;
					 	item.set(++count,"������",token);
					 	result.push_back(item);
					 	i++;
					 	continue;
					 } 
		     case 3:DFAstate2=dfa.nextState(DFAstate,ch);
			        if(DFAstate2=="-1")
					{
						if(dfa.isFinalState(DFAstate))
						  {
						  	item.set(++count,"����",token);
						  	result.push_back(item);
						  	//i++;
						  	state=0;
						  	continue;
						  }
						  else
						  {
						  	item.set(++count,"����",token);
						  	result.push_back(item);
						  	i++;
						  	state=0;
						  	continue;;
						  }
					}
					else
					{
						state=3;
						DFAstate=DFAstate2;
						i++;
						token=token+ch;
						continue;
					}
			case 4:	if(isLetter(ch)||isDigit(ch))
			        {
				        token=token+ch;
				        i++;
				        state=4;
			          }
			          else
			          {
			          	if(isReserveWord(token))
			          	{
			          		item.set(++count,"�ؼ���",token);
			          		result.push_back(item);
			          		state=0;
			          		continue;
			          	}
			          	else
			          	{
			          		if(dfa.isAccepted(token))
			          		  {
			          		  	item.set(++count,"��ʶ��",token);
			          		  	result.push_back(item);
			          		  	state=0;
			          		  	continue;
			          		  }
			          		  else
			          		  {
			          		  	item.set(++count,"����",token);
			          		  	result.push_back(item);
			          		  	state=0;
			          		  	continue;
			          		  }
			          	}
			          	  
			          }

			        
			        	 
      }

     }
     for(int j=0;j<result.size();j++)
        result[j].print();
     } 
     void saveResult()
     {  
        string str;  
	    ofstream outfile;
        while(true)
        {
        cout<<"����Ҫ���������ļ���:";
        cin>>str;
        outfile.open(str.c_str());
        if(outfile.fail())
        {
        	cout<<"��ʧ��"<<endl;
        }
        else
        break;
         }
       for(int i=0;i<result.size();i++)
	   {
	   	  if(result[i].getType()=="����")
	   	   {
	   	   cout<<"�ʷ�����������д��󣬲��ܱ���"<<endl;
	   	   outfile.clear();
	   	   outfile.close();
	   	   break;
	       }
	       if(result[i].getType()=="�ؼ���")
	       {
	       	outfile<<result[i].getIndex()<<" "<<result[i].getType()<<" "<<result[i].getValue()<<" "<<ToCh(result[i].getValue());
	       	outfile<<'\n';
	       	continue;
	       }
	       if(result[i].getType()=="��ʶ��")
	       {
	       	outfile<<result[i].getIndex()<<" "<<result[i].getType()<<" "<<result[i].getValue()<<" "<<"a";
	       	outfile<<'\n';
	       	continue;
	       }
	       if(result[i].getType()=="����")
	       {
	       	outfile<<result[i].getIndex()<<" "<<result[i].getType()<<" "<<result[i].getValue()<<" "<<"z";
	       	outfile<<'\n';
	       	continue;
	       }
	       if(result[i].getType()=="�ֽ��")
	       {
	       	outfile<<result[i].getIndex()<<" "<<result[i].getType()<<" "<<result[i].getValue()<<" "<<result[i].getValue();
	       	outfile<<'\n';
	       }
	       if(result[i].getType()=="������")
	       {
	       	if(result[i].getValue().length()==1)
	       	{outfile<<result[i].getIndex()<<" "<<result[i].getType()<<" "<<result[i].getValue()<<" "<<result[i].getValue();
	       	outfile<<'\n';
	       	} 
	       	 else
              {
              outfile<<result[i].getIndex()<<" "<<result[i].getType()<<" "<<result[i].getValue()<<" "<<ToCh(result[i].getValue());
              outfile<<'\n';
              }
	       }
	   } 
	   outfile.close();
     }
};

