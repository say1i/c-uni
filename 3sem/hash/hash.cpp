#include <iostream>
#include<string>
using namespace std;
class node
{
    friend class listok;
     friend class hashik;
    string val;
    node*next;
    node():val(""),next(this){}
    node(string num):val(num),next(nullptr){}
};
class listok
{
    friend class hashik;
    node base;
    node*cur;
public:
    listok():cur(&base){base.next=&base;}
    int add(string x)
    {
        node*temp=new(nothrow)node(x);
        if(!temp)return -1;
        temp->next=cur->next;
        cur->next=temp;
        return 0;
    }
    int rmv()
    {
        if(cur->next==&base)return-1;
        node*temp=cur->next;
        cur->next=temp->next;
        delete temp;
        return 0;
    }
    int get(string*x)
    {
        if(cur==&base)return -1;
        *x=cur->val;
        return 0;
    }
    int stepFw()
    {
        if(cur->next==&base)return-1;
        cur=cur->next;
        return 0;
    }
    void gotoBeg(){cur=&base;}
    int atBeg()
    {
        if(cur==&base)return 0;
        return 1;
    }
    int isEmpty(){return &base==base.next;}
    void show()
    {
        node*temp=base.next;
        while(temp!=&base)
        {
            cout<<temp->val<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
};
class hashik
{
    int p;
    listok*table;
public:
    hashik(int x)
    {
        p=x;
        table=new(nothrow)listok[p];
        if(!table)exit(1);
    }
    int func(string s)
    {
        int x=0;
        for(char el:s)
        {
            x+=el;
        }
        return x%p;;
    }
    bool add(string s)
    {
        int hc=func(s);
        table[hc].gotoBeg();
        while (table[hc].stepFw()!=-1)if(table[hc].cur->val==s)return false;
        table[hc].add(s);
        return true;
    }
    bool rmv(string s)
    {
        int hc=func(s);
        if(table[hc].isEmpty())return false;
        table[hc].gotoBeg();
        do
        {
            if(table[hc].cur->next==&table[hc].base)return false;
            if(table[hc].cur->next->val==s)
            {
                table[hc].rmv();
                return true;
            }
        }
        while(table[hc].stepFw()!=-1);
        return false;
    }
    bool lookfor(string s)
    {
        int hc=func(s);
        if(table[hc].isEmpty())return false;
        table[hc].gotoBeg();
        while(table[hc].stepFw()!=-1)if(table[hc].cur->val==s)return true;
        return false;
    }
    void show()
    {
        for(int i=0;i<p;i++)
        {
            table[i].gotoBeg();
            cout<<i<<":";
            table[i].show();
            cout<<endl;
        }
    }
};
int main()
{
    hashik h(3);
    int x;
    while(1)
    {
        cout<<"1:add\n2:remove\n3:find\n4:show\n0:exit"<<endl;
        cin>>x;
        if(x==0)break;
        switch(x)
        {
            case(1):
            {
                string s;
                cout<<"type in string"<<endl;
                cin>>s;
                if(h.add(s))cout<<"good"<<endl;
                else cout<<"bad"<<endl;
                break;
            }
            case(2):
            {
                string s;
                cout<<"type in string"<<endl;
                cin>>s;
                if(h.rmv(s))cout<<"good"<<endl;
                else cout<<"bad"<<endl;
                break;
            }
            case(3):
            {
                string s;
                cout<<"type in string"<<endl;
                cin>>s;
                if(h.lookfor(s))cout<<"found"<<endl;
                else cout<<"not found"<<endl;
                break;
            }
            case(4):
            {
                h.show();
                break;
            }
            default:
                cout<<"wrong number"<<endl;
                break;
        }
    }
}
