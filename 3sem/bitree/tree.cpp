#include <iostream>
#include <queue>
#include <fstream>
using namespace std;
struct node {
    int data;
    node*left=nullptr;
    node*right=nullptr;
    node*parent=nullptr;

};
class tree
{
    node*root=nullptr;
    public:
        void push(int x)
        {
            if(root==nullptr)
            {
                root=new node;
                root->data=x;
                return;
            }
            node*temp=root;
            while(1)
            {
                if(x<=temp->data)
                {
                    if(temp->left==nullptr)
                    {
                        temp->left=new node;
                        temp->left->data=x;
                        temp->left->parent=temp;
                        temp=temp->left;
                        break;
                    }
                    temp=temp->left;
                }
                else
                {
                    if(temp->right==nullptr)
                    {
                        temp->right=new node;
                        temp->right->data=x;
                        temp->right->parent=temp;
                        temp=temp->right;
                        break;
                    }
                    temp=temp->right;
                }
            }
        }
        bool lookfor(int x)
        {
            if(root==nullptr)return false;
            node*temp=root;
            while(1)
            {
                if(x<temp->data)
                {
                    if(temp->left==nullptr)return false;
                    temp=temp->left;
                }
                else if(x>temp->data)
                {
                    if(temp->right==nullptr)return false;
                    temp=temp->right;
                }
                else return true;
            }
        }
        queue<node*> show()
        {

            queue<node*>q;
            if(root==nullptr)return q;
            q.push(root);
            while (!q.empty())
            {
                node*temp = q.front();
                q.pop();
                cout << temp->data << " ";
                if (temp->left != nullptr)q.push(temp->left);
                if (temp->right != nullptr)q.push(temp->right);
            }
            return q;
        }
       bool eliminate(int x)
        {
            node*temp=root;
            while(temp!=nullptr&&temp->data!=x)
            {
                if(x<temp->data)temp=temp->left;
                else temp=temp->right;
            }
            if(temp==nullptr)return false;

            if(temp->left==nullptr&&temp->right==nullptr)
            {
                if(temp==root)root=nullptr;
                else
                {
                    if(temp->parent->left==temp)temp->parent->left=nullptr;//очищает родство
                    else temp->parent->right=nullptr;
                }
                delete temp;
                return true;
            }
            if(temp->left==nullptr||temp->right==nullptr)
            {
                node*child=temp->left!=nullptr?temp->left:temp->right;
                if(temp==root)
                {
                    root=child;
                    child->parent=nullptr;
                }
                else
                {
                    if(temp->parent->left==temp)temp->parent->left=child;
                    else temp->parent->right=child;
                    child->parent=temp->parent;
                }
                delete temp;
                return true;
            }
            node*pred=temp->left;
            while(pred->right!=nullptr)pred=pred->right;
            temp->data=pred->data;

            node* child = pred->left;//потому что двигались до упора вправо
            node* parent = pred->parent;

            if (parent->left==pred)parent->left=child;//связывает левые потомки предшественника с его родителем тк сам он удаляется
            else parent->right = child;

            if (child != nullptr)child->parent = parent;

            delete pred;
            return true;
        }
};
string htmlMaker(tree t)
{
    string s = R"(<!DOCTYPE html>
                    <html lang="ru">
                    <head>
                    <meta charset="UTF-8">
                    <title>Дерево поиска</title>
                    <script type="module">
                    import mermaid from "https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs";
                    mermaid.initialize({ startOnLoad: true,
                    flowchart: {
                    useMaxWidth: false,
                    curve: 'linear',
                    nodeSpacing: 30,
                    rankSpacing: 30
                    }
                    });
                    </script>
                    </head>
                    <body>)";
    queue<node*>q=t.show();
    for(int i=0;i<q.size();i++)
    {
        q.pop();
    }
    s+=R"(</body>
          </html>)";
    return s;
}
int main()
{
    tree t;
    t.push(1);
    cout<<t.lookfor(0)<<endl;
    t.push(3);
    t.push(0);
    t.push(-1);
    t.show();
    t.eliminate(1);
    cout<<endl;
    t.show();
    /*ofstream html("output.html");
    tree t;
    //html <<


    cout << "HTML файл создан!" << endl;
    int v;
    while(v!=0)
    {
        cout<<"выбери операцию"<<endl;
        cout<<"1-добавление"<<endl;
        cout<<"2-удаление"<<endl;
        cout<<"3-поиск"<<endl;
        cout<<"0-выход"<<endl;
        cin>>v;
        if(v==1)
        {
            int x;
            cout<<"введи элемент"<<endl;
            cin>>x;
            t.push(x);
        }
        if(v==2)
        {
            int x;
            cout<<"введи элемент"<<endl;
            cin>>x;
            t.eliminate(x);
        }
        if(v==3)
        {
            int x;
            cout<<"введи элемент"<<endl;
            cin>>x;
            cout<<t.lookfor(x)<<endl;
        }
    }
    html.close();*/
}
