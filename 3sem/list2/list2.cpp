#include <iostream>
using namespace std;
class node
{
    int val;
    node*prev,*next;
    friend class listok;
    node():val(0),prev(this),next(this){}
    node(int x):val(x),prev(nullptr),next(nullptr){}
};
class listok
{
    public:
    node base;
    node*before,*after;
    listok():before(&base),after(&base){}
    int insBefore(int x)
    {
        node*temp=new(nothrow)node(x);
        if(!temp)return-1;
        temp->prev=before;
        temp->next=after;
        before->next=temp;
        after->prev=temp;
        before=temp;
        return 0;
    }
    int insAfter(int x)
    {
        node*temp=new(nothrow)node(x);
        if(!temp)return-1;
        temp->next=after;
        temp->prev=before;
        after->prev=temp;
        before->next=temp;
        after=temp;
        return 0;
    }
    int delBefore()
    {
        node*temp=before;
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        before=temp->prev;
        delete temp;
        return 0;
    }
    int delAfter()
    {
        node*temp=after;
        temp->prev->next=after->next;
        temp->next->prev=temp->prev;
        after=temp;
        delete temp;
        return 0;
    }
    int getBefore(int*num)
    {
        *num=before->val;
        return 0;
    }
    int getAfter(int*num)
    {
        *num=after->val;
        return 0;
    }
    int setBefore(int num)
    {
        before->val=num;
        return 0;
    }
    int setAfter(int num)
    {
        after->val=num;
        return 0;
    }
    int stepFw()
    {
        before=after;
        after=after->next;
        return 0;
    }
    int stepBw()
    {
        after=before;
        before=before->prev;
        return 0;
    }
    void gotoBegin()
    {
        before=&base;
        after=base.next;
    }
    void gotoEnd()
    {
        before=base.prev;
        after=&base;
    }
    bool atBeg()
    {
        return before==&base;
    }
    bool atEnd()
    {
        return after==&base;
    }
    bool isEmpty()
    {
        return base.next==&base;
    }
    void show()
    {
        if(isEmpty())cout<<"spisok pust"<<endl;
        node*current=base.next;
        while(current!=&base)
        {
            cout<<current->val<<" ";
            if(current==before)cout<<"<-before ";
            if(current==after)cout<<"<-after ";
            current=current->next;
        }
        cout<<endl;
    }
    listok(const listok&other):after(&base),before(&base)
    {
        int i=0;
        for (node* temp = other.base.next; temp != &other.base; temp = temp->next)i++;
        gotoEnd();
        for(node*temp=other.base.next;temp!=&other.base;temp=temp->next)
        {
            if(insAfter(temp->val)==-1)exit(1);
        }
        gotoBegin();
        for(int j=0;j<i&&!atEnd();j++)stepFw();
    }
    listok&operator=(listok&other)
    {
        if(&other==this)return*this;
        gotoBegin();
        while(!isEmpty())delAfter();
        if(other.isEmpty())
        {
            before=after=&base;
            return*this;
        }
        int i =0;
        for(node*temp=other.base.next;temp!=&other.base&&temp!=other.before;temp=temp->next)i++;
        gotoEnd();
        for(node*temp=other.base.next;temp!=&other.base;temp=temp->next)
        {
            if(insAfter(temp->val)==-1)
            {
                gotoBegin();
                while(!isEmpty())delAfter();
                before=after=&base;
                return*this;
            }
        }
        gotoBegin();
        for(int j=0;j<i&&!atEnd();j++)stepFw();
        return*this;
    }
};
int main()
{
    listok l;
    l.insAfter(3);
    l.show();
    l.insBefore(6);
    l.show();
    l.insAfter(3);
    l.show();
    l.stepFw();
    l.show();

}
