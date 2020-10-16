#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<iomanip>
#include<utility>
#include<queue>
#include<set>
#include<stack>
#include<exception>
using namespace std;
struct rule
{
	char start;//文法产生式的左部 
	string result;//文法产生式的右部 
};
struct go
{
  int state_begin;
  char input;
  int state_end;	
};
struct item
{
   char start;
   string left;
   string right;
   char search='#';
   bool operator==(const item t) const
   {
   	return (this->start==t.start)&&(this->left==t.left)&&(this->right==t.right)&&(this->search==t.search);
   }
   bool operator<(const item t) const
   {
   	  if(start<t.start)
   	     return true;
   	  if(start>t.start)
   	    return false;
   	  if(start==t.start)
   	  {
   	  	if(left<t.left)
   	  	  return true;
   	  	if(left>t.left)
   	  	  return false;
   	  	if(left==t.left)
   	  	{
   	  		if(right<t.right)
   	  		   return true;
   	  		if(right>t.right)
   	  		return false;
   	  		if(right==t.right)
   	  		{
   	  			if(search<t.search)
   	  			return true;
   	  			else
   	  			 return false;
   	  		}
   	  	}
   	  }
   }
   void show()
   {
   	cout<<setw(5)<<start<<setw(5)<<left<<setw(5)<<right<<setw(5)<<search<<endl;
   }
};
class  SyntaxAnalzyer{
private:     vector<char> VN;//非终结符集 
	         vector<char> VT;//终结符集合 
			 vector<rule> rules;//文法规则集 
			 vector< vector<char> > VN_first;//非终结符的first集 
			 vector< vector<char> > VN_follow;//非终结符的follow集 
			 vector< vector<item> > items;//项目集 
			 map<char,int> VNindex;//存放非终结符在向量中的序号 
			 map<char,int> VTindex;
			 vector< vector<item> >DFA;
			 vector<go> Go;
			 map<pair<int,char>,pair<int,int> > action;
			 map<pair<int,char>,int> GOTO;
			 stack<int> state_stack;
			 stack<char> ch_stack;
			 ofstream of;
	public: void readGrammer()//读文法，并拓广，初始化vn,vt和文法规则集合以及vnindex和vtindex 
	{   string str,line,temp;
	    ifstream  infile;
	    char state,ch;
	    stringstream sstream;
	    struct rule r;
	    while(true)
	    {
	    	cout<<"输入文法文件名:";
	    	cin>>str;
	    	infile.open(str.c_str());
	    	if(infile.fail())
	    	{
	    	   cout<<"打开失败";
	    	   infile.close();
	    	}
	    	else
	    	{   r.start='@';//文法拓广，用@表示S’ 
	    	    r.result='S';
	    	    addVN('@');
	    	    rules.push_back(r);
	    		while(getline(infile,line))
	    		  {sstream.clear();
	    		  	sstream<<line;
	    		  	sstream>>state>>ch>>ch>>temp;
	    		  	r.start=state;
	    		  	r.result=temp;
	    		  	rules.push_back(r);
	    		  	addVN(state);
	    		  	for(int i=0;i<temp.length();i++)
	    		  	{
	    		  		if(temp[i]>='A'&&temp[i]<='Z')
	    		  		addVN(temp[i]);
	    		  		else
	    		  		addVT(temp[i]);
	    		  	}
	    		  	
	    		  }
	    		  break;
	    	}
	    }
	}
	void addVN(char ch)//将ch加入vn中 
    {
    	bool flag=true;
    	for(int i=0;i<VN.size();i++)
    	{
    		if(VN[i]==ch)
    		{
    		  flag=false;
    		  break;
    	    }
    	    else
    	    continue;
    	}
    	if(flag)
    	VN.push_back(ch);
    }
    void addVT(char ch)//将ch加入vt中 
    {
    	bool flag=true;
    	for(int i=0;i<VT.size();i++)
    	{
    		if(VT[i]==ch)
    		  {
    		  flag=false;
    		  break;
    		  }
    		  else
    		  continue;
    	}
    	if(flag)
    	VT.push_back(ch);
    }
    void show()
    {   cout<<"非终结符如下"<<endl;
    	for(int i=0;i<VN.size();i++)
    	cout<<VN[i]<<" ";
		cout<<endl;
		cout<<"终结符如下"<<endl;
		for(int i=0;i<VT.size();i++)
		 cout<<VT[i]<<" ";
		 cout<<endl;
		 for(int i=0;i<rules.size();i++)
		  cout<<rules[i].start<<" "<<rules[i].result<<endl;
		  
		  cout<<"first集如下"<<endl;
		  for(int i=0;i<VN_first.size();i++)
		     {  cout<<VN[i]<<" ";
		     	for(int j=0;j<VN_first[i].size();j++)
		     	 cout<<VN_first[i][j];
		     	cout<<endl;
		     }
		  cout<<"follow集如下"<<endl;
		    for(int i=0;i<VN_follow.size();i++)
		     {  cout<<VN[i]<<" ";
		     	for(int j=0;j<VN_follow[i].size();j++)
		     	 cout<<VN_follow[i][j];
		     	cout<<endl;
		     }
		     /*
	  cout<<"项目如下"<<endl;
	  for(int i=0;i<items.size();i++)
    	{
    		for(int j=0;j<items[i].size();j++)
    		{
    			cout<<setw(5)<<items[i][j].start<<setw(5)<<items[i][j].left<<setw(5)<<items[i][j].right<<endl;
    		}
    	}*/
    }
    bool isInVN(char ch)//判断ch是否在vn中 
    {
    	for(int i=0;i<VN.size();i++)
    	  if(ch==VN[i])
    	   return true;
    	 return false;  
    }
    bool isInVT(char ch)//判断ch是否在vt中 
    {
    	for(int i=0;i<VT.size();i++)
    	  if(ch==VT[i])
    	    return true;
    	return false;
    }
    void indexInit()//初始化vnindex和vtindex 
    {
    	for(int i=0;i<VT.size();i++)
    	    VTindex[VT[i]]=i;
    	for(int i=0;i<VN.size();i++)
    	    VNindex[VN[i]]=i;
    }
    void VNfirstSetInit()//初始化非终结符的first集 
    {   vector<char> temp;
        temp.clear();
	    for(int i=0;i<VN.size();i++)
        {   
        	VN_first.push_back(temp); 
        }
        VN_first=setVNfirst(VN_first);
    }
    bool isInVector(vector<char> v,char ch)//判断ch是否在vector中 
    {
    	for(int i=0;i<v.size();i++)
    	    if(ch==v[i])
    	    return true;
    	return false;
    }
   vector< vector<char> > setVNfirst(vector< vector<char> > v1)//设置vnfirst集 
    {   vector< vector<char> > v2=v1;
        char ch1,ch2;
        int s,t=0;
    	for(int i=0;i<rules.size();i++)
    	{   ch1=rules[i].start;
            t=VNindex[ch1];
    		for(int j=0;j<rules[i].result.length();j++)
    		{   
    		    ch2=rules[i].result[j];
    			if(isInVT(ch2))
    			{
    				if(isInVector(v2[t],ch2))
    				{
    					break;
    				}
    				else
    				{
    					v2[t].push_back(ch2);
    					break;
    				}
    			}
    			else
    			{   s=VNindex[ch2];
    				if(isInVector(v2[s],'$'))
    				{   
    					v2[t]=plus(v2[t],v2[s]);
    					if(j==rules[i].result.length()-1)
    					  if(!isInVector(v2[t],'$'))
    					      v2[t].push_back('$');
    				    continue;
    				}
    				else
    				{
    					v2[t]=plus(v2[t],v2[s]);
    					break;
    				}
    			}
    		}
    	}
    	if(v2==v1)
    	   return v2;
    	else
    	return setVNfirst(v2);
    }
    vector<char> plus(vector<char>v1,vector<char>v2)//除去空串的向量相加 
    {
    	for(int i=0;i<v2.size();i++)
    	{
    		if(v2[i]=='$')
    		 continue;
    		 else
    		if(isInVector(v1,v2[i]))
    		 continue;
    		else
    		  v1.push_back(v2[i]);
    	}
    	return v1;
    }
    vector<char> plus2(vector<char>v1,vector<char>v2)//包括空串的向量相加 
    {
    	for(int i=0;i<v2.size();i++)
    	{
    		if(isInVector(v1,v2[i]))
    		 continue;
    		else
    		  v1.push_back(v2[i]);
    	}
    	return v1;
    }
    void VNfollowSetInit()//初始化vnfollow集 
    {
    	vector<char> temp;
    	temp.clear();
    	for(int i=0;i<VN.size();i++)
    	  VN_follow.push_back(temp);
    	VN_follow[VNindex['@']].push_back('#');//用@表示拓展文法中的S' 
    	VN_follow[VNindex['S']].push_back('#');
    	VN_follow=setVNfollowSet(VN_follow);
    }
    vector<char> getFirst(string str)//获取aBC等字符串的first集 
    {
    	vector<char> v1;
    	char ch;
    	int index=0;
    	for(int i=0;i<str.length();i++)
    	{  ch=str[i];
    	   if(isInVT(ch))
    	   {
    	   	if(!isInVector(v1,ch))
    	   	{
    	   		v1.push_back(ch);
    	   	}
    	   	break;
    	   }
    	   if(isInVN(ch))
    	   {
    	   	index=VNindex[ch];
			if(i!=str.length()-1)
			{
			    v1=plus(v1,VN_first[index]);
    	   		if(isInVector(VN_first[index],'$'))
    	   		{
    	   	   		continue;
    	   		}
    	   		else
    	   		{
    	   			break;
    	   		}
			}
			else
			{
				v1=plus(v1,VN_first[index]);
				if(isInVector(VN_first[index],'$'))
				{
					v1.push_back('$');
				}
			}
    	   }
		   if(ch=='#')
		   v1.push_back(ch);	
    	}
    	return v1;
    }
    vector< vector<char> > setVNfollowSet(vector< vector<char> > v1)
    {
    	vector< vector<char> >v2=v1;
    	vector<char> v3;
    	char ch1='\0',ch2='\0';
    	int a=0,b=0,j=0;
    	for(int i=0;i<rules.size();i++)
    	{
    		ch1=rules[i].start;
    		a=VNindex[ch1];
    		j=0;
    		while(j<rules[i].result.length())
    	    {   ch2=rules[i].result[j];
    	        if(isInVT(ch2))
    	        {
    	        	j++;
    	        	continue;
    	        }
    	    	if(isInVN(ch2))
    	    	{   b=VNindex[ch2];
    	    	    if(j!=rules[i].result.length()-1)
                     {
                      v3=getFirst(rules[i].result.substr(j+1));
                      v2[b]=plus(v2[b],v3);
                      if(isInVector(v3,'$'))
                      {
                      	v2[b]=plus(v2[b],v2[a]);
                      }
                     }
                     else
                     {
                     	v2[b]=plus(v2[b],v2[a]);
                     }
					j++; 
    	    	}
    	    }
			 		
    	}
		if(v1==v2)
			  return v2;
			else return setVNfollowSet(v2); 
    }
    void getItem()
    {   vector<item> s;
    	item temp;
    	char ch;
    	for(int i=0;i<rules.size();i++)
    	{
    		s.clear();
    		for(int j=0;j<rules[i].result.length()+1;j++)
    		{
    			temp.start=rules[i].start;
    			temp.left=rules[i].result.substr(0,j);
    			temp.right=rules[i].result.substr(j,rules[i].result.length()-j);
    			s.push_back(temp);
    		}
    		items.push_back(s);
    	}

    }
    vector<item> item_closure(item t)
    {
    	vector<item> v;
    	v.push_back(t);
    	if(t.right.length()==0)
    	  return v;
    	if(isInVT(t.right[0]))
    	{
    		return v;
    	}
    	return getClosure(v);
    }
    void plus3(vector<item> & v,item  & t)
    {
       bool flag=true;
	   for(int i=0;i<v.size();i++)
	   {  
	   	if((item)v[i]==t)
	   	 {
	   	 	flag=false;
	   	 	break;
	   	 }
	   }
	   if(flag)
	    v.push_back(t);	
    }
    vector<item> getClosure(vector<item> v)
    {
    	vector<item> v2=v;
    	for(int i=0;i<v.size();i++)
    	{
    		if(v[i].right.length()==0)
    		 continue;
    		if(isInVT(v[i].right[0]))
    		 continue;
    		char ch=v[i].right[0];
    		string str=v[i].right.substr(1)+v[i].search;
    		vector<char> search_set=getFirst(str);
    		for(int j=0;j<items.size();j++)
    		{
    			if(items[j][0].start==ch)
    			{   item temp=items[j][0];
    				for(int k=0;k<search_set.size();k++)
    				{
    					temp.search=search_set[k];
    					plus3(v,temp);
    				} 
    			}
    			else
    			 continue;
    		}
    	}
    	if(v2==v)
    	 return v;
    	else
    	return getClosure(v);
    }
    void itemVectorSort(vector<item> & v)
    {
    	int size=v.size();
    	item temp;
    	for(int i=0;i<size;i++)
    	{
    		for(int j=0;j<size-i-1;j++)
    		{
    			if(!(v[j]<v[j+1]))
    			{
    				temp=v[j+1];
    				v[j+1]=v[i];
    				v[i]=temp;
    			}
    		}
    	}
    }
    item nextitem(item t)
    {
    	item t2;
    	char ch=t.right[0];
    	t2.start=t.start;
    	t2.left=t.left+ch;
    	t2.right=t.right.substr(1);
    	t2.search=t.search;
    	return t2;
    }
    int  isInDFA(vector<item> v)
    {
    	for(int i=0;i<DFA.size();i++)
    	{
    		if(isVectorEqual(DFA[i],v))
    		 return i;
    	}
    	return -1;
    }
     void makeItemSet()
     {  
     	int index=0,now;//index记录已生成项目集族编号的最大值,now记录队列队首的项目集族编号 
     	vector<item> temp,temp2;
     	item t1,t2;
     	vector<bool> helper; 
     	queue<int> set_queue;
		temp.push_back(items[0][0]);
	    temp=getClosure(temp);
		//itemVectorSort(temp);
		set_queue.push(index);
		DFA.push_back(temp);
		while(!set_queue.empty())
		{   
			now=set_queue.front();
			set_queue.pop();
			temp=DFA[now];
			helper.clear();
			for(int i=0;i<temp.size();i++)
			{
			   helper.push_back(false);
			}
			for(int i=0;i<temp.size();i++)
			{   temp2.clear();
				if(helper[i]==true)
				 continue;
				if(temp[i].right.length()==0)
				{
					helper[i]=true;
					continue;
				}
				helper[i]=true;
				char ch=temp[i].right[0];
				if(ch=='$')	 
				 {helper[i]=true;
				  continue;
				 }
				temp2.push_back(nextitem(temp[i]));
				for(int j=i+1;j<temp.size();j++)
				{
					if(helper[j]==true)
					 continue;
					if(temp[j].right.length()==0)
					{
						helper[j]=true;
						continue;
					}
					if(temp[j].right[0]==ch)
					{
						temp2.push_back(nextitem(temp[j]));
						helper[j]=true;
					}
					else
					{
						continue;
					}
				}
				temp2=getClosure(temp2);
				//itemVectorSort(temp2);
				if(isInDFA(temp2)==-1)
				{
					index++;
				    set_queue.push(index);
				    DFA.push_back(temp2);
				    go g;
				    g.state_begin=now;
				    g.input=ch;
				    g.state_end=index;
				    Go.push_back(g);
				}
				else
				{
					go g;
					g.state_begin=now;
					g.input=ch;
					g.state_end=isInDFA(temp2);
					Go.push_back(g); 
				}
			}
		} 

     }
bool isVectorEqual(vector<item> v1,vector<item> v2)
{
	if(v1.size()!=v2.size())
	  return false;
	set<item> s1,s2;
	for(int i=0;i<v1.size();i++)
	{
		s1.insert(v1[i]);
		s2.insert(v2[i]);
	}
	 return s1==s2;
} 
void makeTable()
{   
    for(int i=0;i<Go.size();i++)
    {   int begin=Go[i].state_begin;
    	char ch=Go[i].input;
    	int end=Go[i].state_end;
    	if(isInVN(Go[i].input))
    	{
    	   pair<int,char> p=make_pair(begin,ch);
    	   GOTO[p]=end;
    	}
    	else
    	{
    		pair<int, char> p1=make_pair(begin,ch);
    		pair<int,int> p2=make_pair(end,1);
    		action[p1]=p2;
    	}
    }
    for(int i=0;i<DFA.size();i++)
    {
    	for(int j=0;j<DFA[i].size();j++)
    	{
    		if(DFA[i][j].right.length()!=0)
    		{   if(DFA[i][j].right[0]=='$')
    		    {
    		    pair<int,char> p1=make_pair(i,DFA[i][j].search);
    		    pair<int,int> p2=make_pair(findRule(DFA[i][j].start,DFA[i][j].right),2);
    		    action[p1]=p2;
    		    }
    		    else
    			continue;
    		}
    		else
    		{
    		  if(DFA[i][j].left=="S"&&DFA[i][j].search=='#')
    		   {
    		    pair<int,char> p1=make_pair(i,'#');
    		    pair<int,int> p2=make_pair(0,3);
    		    action[p1]=p2;
    		   }
    		   else
    		   {
    		    pair<int,char> p1=make_pair(i,DFA[i][j].search);
    		    pair<int,int> p2=make_pair(findRule(DFA[i][j].start,DFA[i][j].left),2);
    		    action[p1]=p2;
    		   }
    		}
    		
   	     }
    } 
   
}
string kindToStr(int a,int b)
{    stringstream s1;
     string s2;
     s1<<a;
     s1>>s2;
	if(b==1)
	{
     return "S"+s2;
	}
	if(b==2)
	{
		return "r"+s2;
	}
	if(b==3)
	 return "acc";
}  
int findRule(char ch,string str)
{
	for(int i=0;i<rules.size();i++)
	{
		if(ch==rules[i].start&&str==rules[i].result)
		 return i;
	}
}
void analyzer()
{   int state;
	ifstream infile;
	string file_name;
	while(true)
	{	cout<<"输入要分析的token串文件名";
	    cin>>file_name;
	    infile.open(file_name.c_str());
	    if(infile.fail())
	    {
	    	cout<<"打开失败,请重新输入";
			infile.clear();
			infile.close();
			continue; 
	    }
	    else
	    break;
	}
	state_stack.push(0);
	ch_stack.push('#');
	string str="",line,str2;
	stringstream stream;
	char ch;
	int count=0;
	while(getline(infile,line))
	{   stream<<line;
	    stream>>str2>>str2>>str2>>ch;
		str=str+ch;
	}
	str=str+'#';
	cout<<str;
	
	of.clear();
	of.open("result.txt");
	try{
	  for(int i=0;i<str.length();i++)
    {   writefile();
    	ch=str[i];
    	state=state_stack.top();
    	pair<int,char> pair1=make_pair(state,ch);
    	if(action.count(pair1)==0)
    	  {
    	  	of<<"N"<<" "<<i+1;
    	  	
    	  	break;
    	  }
    	  else
    	  {
    	  	pair<int,int> pair2=action[pair1];
    	  	if(pair2.second==3)
    	  	{  if(i==str.length()-1)
				 {
				 	of<<"Y";
				 	break;
				 }
    	  	   else
    	  	   {
				 of<<"N"<<" "<<i+1;
				 break;
    	  	   }
    	  	}
    	  	if(pair2.second==1)
    	  	{
    	  		ch_stack.push(ch);
    	  		state_stack.push(pair2.first);
    	  	}
    	  	if(pair2.second==2)
    	  	{   if(rules[pair2.first].result=="$")
                {
                	ch_stack.push(rules[pair2.first].start);
                	pair<int,char> pair3=make_pair(state_stack.top(),ch_stack.top());
    	  		    state_stack.push(GOTO[pair3]);
    	  		     i--;
                }
                else
                {
                
    	  		for(int j=0;j<rules[pair2.first].result.length();j++)
    	  		{
    	  			ch_stack.pop();
					state_stack.pop();
    	  		}
    	  		ch_stack.push(rules[pair2.first].start);
    	  		
    	  		pair<int,char> pair3=make_pair(state_stack.top(),ch_stack.top());
    	  		state_stack.push(GOTO[pair3]);
    	  		i--;
    	  	    }
    	  	}
    	  }
        }
    }catch(exception e)
    {
    	cout<<e.what();
    }
    of.close();
    
}
void writefile()
{
	stack<char> s1=ch_stack;
	vector<char> v1;
	stack<int> s2=state_stack;
	vector<int> v2;
	while(!s1.empty())
	{
		v1.push_back(s1.top());
		s1.pop();
	}
	for(int i=v1.size()-1;i>=0;i--)
	{
		of<<v1[i]<<" ";
	}
	of<<'\n';
	while(!s2.empty())
	{
		v2.push_back(s2.top());
		s2.pop();
	}
	for(int i=v1.size()-1;i>=0;i--)
	{
		of<<v2[i]<<" ";
	}
	of<<'\n';
}
/*void test()
     {
     	set<item> s1,s2;
     	s1.insert(items[0][0]);
     	s1.insert(items[0][1]);
     	s2.insert(items[0][1]);
     	s2.insert(items[0][0]);
     	cout<<(s1==s2)<<endl;
     }*/
    void writefile2()
    {
    	ofstream ofs;
    	ofs.open("result2.txt");
    	ofs<<"非终结符如下:\n";
    	for(int i=0;i<VN.size();i++)
    	ofs<<VN[i]<<" ";
    	ofs<<'\n';
    	ofs<<"终结符如下:\n";
    	for(int i=0;i<VT.size();i++)
    	{
    		ofs<<VT[i]<<" ";
    	}
    	ofs<<'\n';
    	ofs<<"first集如下:\n";
    	for(int i=0;i<VN_first.size();i++)
    	{
    		ofs<<VN[i]<<":";
    		for(int j=0;j<VN_first[i].size();j++)
    		{
    			ofs<<VN_first[i][j]<<" ";
    		}
    		ofs<<'\n';
    	}
        ofs<<"follow集如下"<<'\n';
		    for(int i=0;i<VN_follow.size();i++)
		     {  ofs<<VN[i]<<":  ";
		     	for(int j=0;j<VN_follow[i].size();j++)
		     	 ofs<<VN_follow[i][j]<<" ";
		     	 ofs<<'\n'; 
		    }
	   ofs<<"DFA:"<<'\n';
		for(int i=0;i<DFA.size();i++)
		{   ofs<<"状态"<<i<<":"<<'\n';
			for(int j=0;j<DFA[i].size();j++)
			{
				ofs<<DFA[i][j].start<<"->"<<DFA[i][j].left<<"."<<DFA[i][j].right<<"   "<<DFA[i][j].search<<'\n';
			}
		}
		ofs<<"go函数"<<endl;
		for(int i=0;i<Go.size();i++)
		 ofs<<Go[i].state_begin<<" "<<Go[i].input<<" "<<Go[i].state_end<<'\n';
		
    ofs<<"action表如下:\n";
    ofs<<"          ";
    for(int i=0;i<VT.size();i++)
      ofs<<setw(10)<<VT[i];
     ofs<<setw(10)<<"#\n";
    for(int i=0;i<DFA.size();i++)
    {   ofs<<setw(10)<<i;
    	for(int j=0;j<VT.size();j++)
    	{   pair<int,char> p1=make_pair(i,VT[j]);
    	    if(action.count(p1)==0)
    	    {
    	    	ofs<<setw(10)<<-1;
    	    }
    	    else
    	    {
    	    	pair<int,int> p2=action[p1];
    	    	ofs<<setw(10)<<kindToStr(p2.first,p2.second);
    	    }
    	}
    	pair<int,char> p1=make_pair(i,'#');
    	if(action.count(p1)==0)
    	    {
    	    	ofs<<setw(10)<<-1;
    	    }
    	    else
    	    {
    	    	pair<int,int>p2=action[p1];
    	    	ofs<<setw(10)<<kindToStr(p2.first,p2.second);
    	    }  
    	ofs<<'\n';
    }
    ofs<<"goto表如下:\n";
    ofs<<"     ";
    for(int i=0;i<VN.size();i++)
    ofs<<setw(5)<<VN[i];
    ofs<<'\n';
    for(int i=0;i<DFA.size();i++)
    {  ofs<<setw(5)<<i;
    	for(int j=1;j<VN.size();j++)
    	{
    		pair<int ,char> p1=make_pair(i,VN[j]);
    		if(GOTO.count(p1)==0)
    		{
    			ofs<<setw(5)<<"-1"; 
    		}
    		else
    		{
    			ofs<<setw(5)<<GOTO[p1];
    		}
    	}
    	ofs<<'\n';
    }
    ofs.close();
    }
};
