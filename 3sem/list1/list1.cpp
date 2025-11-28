#include<iostream>
using namespace std;
class node
{
    friend class listok;
    int val;
    node*next;
    node():val(0),next(this){}
    node(int num):val(num),next(nullptr){}
};
class listok
{
    node base;
    node*cur;
public:
    listok():cur(&base){base.next=&base;}
    int add(int x)
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
    int get(int*x)
    {
        if(cur==&base)return -1;
        *x=cur->val;
        return 0;
    }
    int change(int x)
    {
        if(cur==&base)return -1;
        cur->val=x;
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
        int f=0;
        if(atBeg()==0)
        {
            cout<<"current->";
            f=1;
        }
        while(temp!=&base)
        {
            cout<<temp->val<<" ";
            if(f==0)if(temp==cur)cout<<"current->";
            temp=temp->next;
        }
        cout<<endl;
    }
    listok(const listok&other):cur(&base)
    {
        base.next=&base;
        node*last=&base;
        for(node*temp=other.base.next;temp!=&other.base;temp=temp->next)
        {
            node*obb=new(nothrow)node(temp->val);
            if(!obb)exit(1);
            last->next=obb;
            obb->next=&base;
            last=obb;
            if(temp==other.cur)cur=obb;
        }
    }
    listok&operator=(listok&other)
    {

        if(&other==this)return*this;
        gotoBeg();
        while(!isEmpty())rmv();
        if(other.isEmpty())return*this;
        base.next=&base;
        cur=&base;
        node*last=&base;
        for(node*temp=other.base.next;temp!=&other.base;temp=temp->next)
        {
            node*obb=new(nothrow)node(temp->val);
            if(!obb)exit(1);
            last->next=obb;
            obb->next=&base;
            last=obb;
            if(temp==other.cur)cur=obb;
        }
        return*this;
    }
};
int main()
{
    listok l;
    for(int i=0;i<6;i++)
    {
        l.add(i);
    }
    l.stepFw();
     for(int i=0;i<6;i++)
    {
        l.add(i);
    }
    l.gotoBeg();
    l.show();
}
