#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include<math.h>
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
vector<node*> getree()
{
    vector<node*>res;
    if(root == nullptr) return res;

    int maxIndex = 0;
    queue<node*> q_find_max;
    q_find_max.push(root);

    while(!q_find_max.empty())
    {
        node* p = q_find_max.front();
        q_find_max.pop();
        if(p->index > maxIndex) maxIndex = p->index;

        if(p->left) q_find_max.push(p->left);
        if(p->right) q_find_max.push(p->right);
    }

    res.resize(maxIndex + 1, nullptr); // Инициализация nullptr

    queue<node*> q_fill; // Используем новую очередь для заполнения
    q_fill.push(root);

    while(!q_fill.empty())
    {
        node* p = q_fill.front();
        q_fill.pop();


        res[p->index] = p;

        if(p->left) q_fill.push(p->left);
        if(p->right) q_fill.push(p->right);
    }
    return res;
}
/*queue<pair<bool,node*>> getree()
{
    queue<pair<bool,node*>> result;
    if(root == nullptr) return result;

    // --- ЭТАП 1: Расчет максимального индекса и глубины ---
    int maxindex = 0;
    queue<node*> t;
    t.push(root);

    // Обход для нахождения максимального индекса (корректно)
    while(!t.empty())
    {
        node* p = t.front();
        t.pop();
        if(p->index > maxindex) maxindex = p->index;
        if(p->left) t.push(p->left);
        if(p->right) t.push(p->right);
    }

    int stage = 0;
    // Находим минимальную глубину 'stage', на которой находится maxindex.
    // Используем битовый сдвиг (1 << stage) вместо pow(2, stage) для эффективности.
    for (; (1 << stage) <= maxindex; stage++);

    // Общее количество позиций (узлов) в полном дереве до глубины 'stage'.
    // Например, если maxindex=6, stage=3. Total nodes = 2^(3+1) - 1 = 15. Индексы 0-14.
    int total_nodes_to_process = (1 << (stage + 1)) - 1;

    // --- ЭТАП 2: Обход с заполнением фиктивными узлами (Объединенный BFS) ---
    queue<pair<bool,node*>> q;
    q.push({true, root});

    // Цикл выполнится ровно total_nodes_to_process раз, чтобы заполнить все позиции.
    for(int i = 0; i < total_nodes_to_process; i++)
    {
        if (q.empty()) break;

        pair<bool,node*> p = q.front();
        q.pop();

        result.push(p);

        // иктивные узлы (p.first == false) не должны генерировать потомков.
        // Это предотвращает экспоненциальный рост и бесконечный цикл.
        if (!p.first) {
            // Узел добавлен в result, переходим к следующему.
            // Примечание: p.second был создан через new node.
            continue;
        }

        // Индексы потомков
        int left_idx = p.second->index * 2 + 1;
        int right_idx = p.second->index * 2 + 2;

        // Создаем потомков, только если их индексы не превышают
        // максимальный индекс полного дерева (total_nodes_to_process - 1).

        // 1. Левый потомок
        if (left_idx < total_nodes_to_process) {
            if (p.second->left) {
                // Реальный узел существует
                q.push({true, p.second->left});
            } else {
                // Создаем и добавляем ФИКТИВНЫЙ узел
                node* lnode = new node;
                lnode->data = 0;
                lnode->index = left_idx;
                q.push({false, lnode});
            }
        }

        // 2. Правый потомок
        if (right_idx < total_nodes_to_process) {
            if (p.second->right) {
                // Реальный узел существует
                q.push({true, p.second->right});
            } else {
                // Создаем и добавляем ФИКТИВНЫЙ узел
                node* rnode = new node;
                rnode->data = 0;
                rnode->index = right_idx;
                q.push({false, rnode});
            }
        }
    }
    return result;
}

*/
};
/*string generateMermaidGraph(tree &t)
{
    string s;
    queue<pair<bool,node*> q = t.getree();


    queue<pair<bool,node*>> tmp = q;
    while (!tmp.empty()) {
        pair<bool,node*>p = tmp.front();
        tmp.pop();
        if(p.first==true)s += to_string(p.second->index) + "[\"" + to_string(p.second->data) + "\"]\n";
        else s += "H" + to_string(p.second->index) + "[\" \"]:::hidden\n";
    }
    queue<pair<bool,node*>> tmp2 = q;
    while (!tmp2.empty())
    {
        pair<bool,node*>p=tmp2.front();
        tmp2.pop();

        int i = p.second->index;

        int left_idx = i * 2 + 1;
        int right_idx = i * 2 + 2;

        if(p->left != nullptr&&p->right == nullptr)
        {
            s += to_string(i)+ "---" +to_string(p->left->index )+ "\n";
            s +=to_string(i) + "~~~H" + to_string(right_idx) + ":::hidden\n";
            cout<<"first"<<endl;
        }
        else if(p->left == nullptr&&p->right != nullptr)
        {
            s +=to_string(i) + "~~~H" + to_string(left_idx) + ":::hidden\n";
            s+= to_string(i) + "---" + to_string(p->right->index )+ "\n";
            cout<<"second"<<endl;
        }
        else if(p->left != nullptr&&p->right != nullptr)
        {
            s += to_string(i)+ "---" +to_string(p->left->index )+ "\n";
             s+= to_string(i) + "---" + to_string(p->right->index )+ "\n";
             cout<<"third"<<endl;
        }
    }
    s += "classDef hidden display: none;\n";
    return s;
}
string generateMermaidGraph(tree &t)
{
    string s;
    queue<pair<bool,node*>> q = t.getree();

    // 1️Находим максимальный индекс, чтобы построить полный массив
    int maxIndex = -1;
    queue<node*> tmp = q;
    while (!tmp.empty()) {
        node* p = tmp.front();
        tmp.pop();
        if (p->index > maxIndex) maxIndex = p->index;
    }

    // 2️Создаём все узлы (реальные и пустые)
    for (int i = 0; i <= maxIndex; i++) {
        node* p = nullptr;
        queue<node*> tmp2 = q;
        while (!tmp2.empty()) {
            node* n = tmp2.front();
            tmp.pop();
            if(n->index == i) p = n;
        }
        if (p)
            s += to_string(i) + "[\"" + to_string(p->data) + "\"]\n";
        else
            s += "H" + to_string(i) + "[\" \"]:::hidden\n";
    }

    // 3️Связываем все узлы
    for (int i = 0; i <= maxIndex; i++) {
        int left_idx = i * 2 + 1;
        int right_idx = i * 2 + 2;

        // Левая ветка
        if (left_idx <= maxIndex) {
            if (q.size() && any_node_has_index(q, left_idx)) // реальный левый
                s += to_string(i) + "---" + to_string(left_idx) + "\n";
            else
                s += (i < q.size() ? "H" : "") + to_string(left_idx) + ":::hidden\n";
        }

        // Правая ветка
        if (right_idx <= maxIndex) {
            if (q.size() && any_node_has_index(q, right_idx)) // реальный правый
                s += to_string(i) + "---" + to_string(right_idx) + "\n";
            else
                s += (i < q.size() ? "H" : "") + to_string(right_idx) + ":::hidden\n";
        }
    }

    s += "classDef hidden display: none;\n";
    return s;
}*/
string generateMermaidGraph(tree &t)
{
    string s;

    vector<node*> q = t.getree();///здесь ошибка

    //генерируем и определяем узлы
    vector<node*> tmp = q;

    i=0;
    for(node*p:tmp)
    {

        if(p!=nullptr)
        {
            if(p->left != nullptr&&p->right == nullptr)
            {
                s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]"+ "---" + to_string(p->left->index)+"[\""+to_string(p->left->data)+"\"]"+"\n";
                s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]" + "~~~" + to_string(i*2+2) + ":::hidden\n";
            }
            else if(p->left == nullptr&&p->right != nullptr)
            {
                s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]" + "~~~" + to_string(i*2+1) + ":::hidden\n";
                s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]"+ "---" + to_string(p->right->index)+"[\""+to_string(p->right->data)+"\"]"+"\n";
                cout<<"second"<<endl;
            }
            else if(p->left != nullptr&&p->right != nullptr)
            {
                s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]"+ "---" + to_string(p->left->index)+"[\""+to_string(p->left->data)+"\"]"+"\n";
                 s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]"+ "---" + to_string(p->right->index)+"[\""+to_string(p->right->data)+"\"]"+"\n";
                 cout<<"third"<<endl;
            }
            else
            {
                s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]" + "~~~" + to_string(i*2+1) + ":::hidden\n";
                s +=to_string(p->index)+"[\""+to_string(p->data)+"\"]" + "~~~" + to_string(i*2+2) + ":::hidden\n";
            }
        }

        i++;
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
