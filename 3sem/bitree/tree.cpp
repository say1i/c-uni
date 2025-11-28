#include <iostream>
#include <queue>
#include <fstream>
#include <string>
using namespace std;


struct node {
    int data;
    int index;
    node*left=nullptr;
    node*right=nullptr;
    node*parent=nullptr;
};


class tree
{
public:
    node*root=nullptr;
    void fixIndexes(node* n, int index)
    {
        if(!n) return;
        n->index = index;
        fixIndexes(n->left, index*2 + 1);
        fixIndexes(n->right, index*2 + 2);
    }
    void push(int x)
    {
        if(root==nullptr)
        {
            root=new node;
            root->data=x;
            root->index=0;
            return;
        }
        node*temp=root;
        while(true)
        {
            if(x<=temp->data)
            {
                if(temp->left==nullptr)
                {
                    temp->left=new node;
                    temp->left->data=x;
                    temp->left->index=temp->index*2+1;
                    temp->left->parent=temp;
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
                    temp->right->index=temp->index*2+2;
                    temp->right->parent=temp;
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
         while(temp)
         {
             if(x<temp->data) temp=temp->left;
             else if(x>temp->data) temp=temp->right;
             else return true;
         }
         return false;
    }
    bool eliminate(int x)
    {
        node*temp=root;
        while(temp!=nullptr && temp->data!=x)
        {
            if(x<temp->data)temp=temp->left;
            else temp=temp->right;
        }
        if(temp==nullptr)return false;

        //узел без потомков
        if(temp->left==nullptr && temp->right==nullptr)
        {
            if(temp==root) root=nullptr;
            else if(temp->parent->left==temp) temp->parent->left=nullptr;
            else temp->parent->right=nullptr;
            delete temp;
        }
        //узел с одним потомком
        else if(temp->left==nullptr || temp->right==nullptr)
        {
            node*child=temp->left!=nullptr?temp->left:temp->right;
            if(temp==root)
            {
                root=child;
                child->parent=nullptr;
            }
            else
            {
                if(temp->parent->left==temp) temp->parent->left=child;
                else temp->parent->right=child;
                child->parent=temp->parent;
            }
            delete temp;
        }
        //узел с двумя потомками
        else
        {
            node*pred=temp->left;
            while(pred->right!=nullptr) pred=pred->right;

            // Замена данных
            temp->data=pred->data;

            // Удаление предшественника (pred всегда имеет не более одного левого потомка)
            node*child=pred->left;
            node*parent=pred->parent;

            if(parent->left==pred) parent->left=child;
            else parent->right=child;

            if(child!=nullptr) child->parent=parent;
            delete pred;
        }
        fixIndexes(root, 0);
        return true;
    }
    void show()
    {
        if(root == nullptr) return;

        queue<node*> q;
        q.push(root);

        while(!q.empty())
        {
            node* p = q.front();
            q.pop();
            cout<<"index "<<p->index<<" data "<<p->data<<endl;

            if(p->left) q.push(p->left);
            if(p->right) q.push(p->right);
        }
    }
    queue<node*> getree()
    {
        queue<node*> result;
        if(root == nullptr) return result;

        queue<node*> q;
        q.push(root);

        while(!q.empty())
        {
            node* p = q.front();
            q.pop();

            result.push(p);

            if(p->left) q.push(p->left);
            if(p->right) q.push(p->right);
        }
        return result;
    }
};

string generateMermaidGraph(tree &t)
{
    string s;
    queue<node*> q = t.getree();

    //генерируем и определяем узлы
    queue<node*> tmp = q;
    queue<node*> def_q = tmp;
    while (!def_q.empty()) {
        node* p = def_q.front();
        def_q.pop();
        s+= to_string(p->index)+"[\""+to_string(p->data)+"\"]\n";
    }

    //связываем узлы и создаем пустые блоки
    while (!tmp.empty())
    {
        node*p=tmp.front();
        tmp.pop();

        int i = p->index;

        int left_idx = i * 2 + 1;
        int right_idx = i * 2 + 2;
        if(p->left != nullptr&&p->right == nullptr)
        {
            s += to_string(i)+ "---" +to_string(p->left->index )+ "\n";
            s +=to_string(i) + "~~~H" + to_string(right_idx) + ":::hidden\n";
        }
        if(p->left == nullptr&&p->right != nullptr)
        {
            s+= to_string(i) + "---" + to_string(p->right->index )+ "\n";
            s +=to_string(i) + "~~~H" + to_string(left_idx) + ":::hidden\n";
        }
        if(p->left != nullptr&&p->right != nullptr)
        {
            s += to_string(i)+ "---" +to_string(p->left->index )+ "\n";
             s+= to_string(i) + "---" + to_string(p->right->index )+ "\n";
        }
    }
    s += "classDef hidden display: none;\n";
    return s;
}

void appendHtmlBlock(ofstream& htmlFile, tree& t, int operation, int value) {

    //генерация заголовка
    htmlFile << "<div align=\"center\">\n";
    if (operation == 1) {
        htmlFile << "В дерево добавлен элемент " << value << "\n";
    } else if (operation == 2) {
        htmlFile << "Из дерева удален элемент " << value << "\n";
    }
    htmlFile << "</div>\n";

    //генерация блока мермаид
    htmlFile << "<div class=\"mermaid\" align=\"center\" style=\"padding-bottom: 10px; margin-bottom: 10px; border-bottom: 2px solid black\">\n";
    htmlFile << "graph TD\n";
    htmlFile << generateMermaidGraph(t);
    htmlFile << "\n</div>\n";

    htmlFile.flush(); //для немедленной записи в файл принудительно вызываем из буфера и не ждем его сброса
}

string getHtmlHeader() {
    return R"(<!DOCTYPE html>
            <html lang="ru">
            <head>
            <meta charset="UTF-8">
            <title>Дерево поиска</title>
            <script type="module">
            import mermaid from "https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs";
            mermaid.initialize({
                startOnLoad: true,
                flowchart: {
                    useMaxWidth: false,
                    curve: 'linear',
                    nodeSpacing: 30,
                    rankSpacing: 30
                }
            });
            </script>
            </head>
            <body>
            <div id="tree-history">
            )";
}

string getHtmlFooter() {
    return R"(</div>
        </body>
        </html>)";
}
int main()
{

    ofstream html("output.html");
    tree t;

    html << getHtmlHeader();


    int v = -1;
    while(v != 0)
    {
        cout << "\nвыбери операцию" << endl;
        cout << "1-добавление" << endl;
        cout << "2-удаление" << endl;
        cout << "3-поиск" << endl;
        cout << "0-выход" << endl;

        if (!(cin >> v)) {
            cerr << "Ошибка ввода. Выход." << endl;
            break;
        }

        switch (v)
        {
            case 1:
            {
                int x;
                cout << "введи элемент" << endl;
                cin >> x;
                t.push(x);
                appendHtmlBlock(html, t, 1, x);
                t.show();
                break;
            }

            case 2:
            {
                int x;
                cout << "введи элемент" << endl;
                cin >> x;
                    if(t.eliminate(x)){
                        appendHtmlBlock(html, t, 2, x);
                    } else {
                        cout << "Элемент не найден для удаления." << endl;
                    }

                break;
            }

            case 3:
            {
                int x;
                cout << "введи элемент" << endl;
                cin >> x;
                cout << "Результат поиска: " << (t.lookfor(x) ? "1 (Найден)" : "0 (Не найден)") << endl;
                break;
            }

            case 0:
            {
                break;
            }

            default:
            {
                cout << "Неверный выбор операции. Пожалуйста, введите число от 0 до 3." << endl;
                break;
            }
        }
    }
    html << getHtmlFooter();
    html.close();

    return 0;
}
