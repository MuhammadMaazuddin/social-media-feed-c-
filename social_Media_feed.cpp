#include<iostream>
#include<ctime>
#include<cstring>
using namespace std;
class node
{
    public:
        int id;
        string time;
        string post;
        node *nextF;
        node *nextB;
};
class linkedlist
{
    private:
        node *mainData;      // contains head data
        node *mainDataR;     // contains tail data
    public:
        linkedlist();
        void insert(node *node1);
        void print();      // to print data from head
        void printR();     // to print data from tail
        void del(int id);
        void chkByTxt(string text,string edit);
        bool checkId(int id);   // check id uniqueness
        void edit(int id, string text,string time);
};
linkedlist::linkedlist()
{
    mainData = NULL;
}

void linkedlist::insert(node *node1)
{
    if (mainData == NULL)
    {
        mainData = node1;
        node1->nextB = NULL;
    }
    else
    {
        node *temp = mainData;
        node *tempB;
        while (temp->nextF != NULL)
        {
            tempB = temp;
            temp = temp->nextF;
        }
        temp->nextF = node1;
        node1->nextB = temp;
        mainDataR = node1;
        
    }
}
void linkedlist::print()
{
    node *temp = mainData;
    while (temp != NULL)
    {
        cout<<"( oldest first )\n";
        cout << "id : " << temp->id << endl;
        cout << "text : " << temp->post << endl;
        cout << "last edit time : " << temp->time << endl;

        temp = temp->nextF;
    }
}
void linkedlist::printR()
{
    node *temp = mainDataR;
    while (temp != NULL)
    {
        cout<<"( latest first )\n";
        cout << "id : " << temp->id << endl;
        cout << "text : " << temp->post << endl;
        cout << "last edit time : " << temp->time << endl;

        temp = temp->nextB;
    }
}
void linkedlist::chkByTxt(string text,string edit)
{
    string timenow;
    node *temp = mainData;
    cout<<" All the posts containing the text are : ";
    while (temp != NULL)
    {
        if(temp->post.find(text) != string::npos)
        {
            cout<<" "<<temp->post<<" : with id : "<<temp->id<<endl;
            if(edit != "N" && edit != "del")
            {
                time_t currentTime;
                time(&currentTime);
                timenow = ctime(&currentTime);
                temp->time = timenow;
                temp->post = edit;

            }
            else if(edit == "del")
            {
                del(temp->id);
            }
        }
        temp = temp->nextF;
    }
}
bool linkedlist::checkId(int id)
{
    bool flag = false;
    node *temp = mainData;
    while (temp != NULL)
    {
        if(temp->id == id)
        {
            flag = true;
            break;
        }
        temp = temp->nextF;
    }
    return flag;
}
void linkedlist::edit(int id, string text,string time)
{
    node *temp = mainData;
    while (temp != NULL)
    {
        if(temp->id == id)
        {
            cout<<" your old post was : "<<temp->post<<endl;
            temp->post = text;
            temp->time = time;
        }
        temp = temp->nextF;
    }
}
void linkedlist::del(int id)
{
node *temp = mainData;
node *temp1;
node *temp2;
    while (temp != NULL)
    {
        if(temp->id == id)
        {
            if(temp->nextB == NULL && temp->nextF != NULL)
            {
                cout<<"  head node\n";
                temp1 = temp->nextF;
                temp1->nextB = NULL;
                mainData = temp1;
                delete temp;
            }
            else if(temp->nextB == NULL && temp->nextF == NULL)
            {
                cout<<" single node\n";
                delete temp;  
                mainData = NULL;
            }
            else if(temp->nextF == NULL && temp->nextB != NULL)
            {
                cout<<"  tail node\n";
                temp1 = temp->nextB;
                temp1->nextF = NULL;
                mainDataR = temp1;
                delete temp;
            }
            else if(temp->nextB != NULL && temp->nextF != NULL)
            {
                cout<<"  body node\n";
                temp1 = temp->nextF;
                temp2 = temp->nextB;
                temp2->nextF = temp1;
                temp1->nextB = temp2;
                delete temp;
            }
            break;
        }
        temp = temp->nextF;
    }
}
int main()
{
    linkedlist list1;
    int id;
    string timenow;
string post[10];
post[0] = "Hello World";
post[1] = "How is everyone doing today?";
post[2] = "world animation";
post[3] = "good bye world";
post[4] = "how are you";
post[5] = "see you tommorow";
post[6] = "well well well";
post[7] = "very well well very";
post[8] = "I should be going, see you guys";
post[9] = "Bye";
for(int i=0;i<10;i++)
{
    node * node1 = new node;
    node1->post = post[i];
    do 
    {
    id = rand() % 9000 + 1000;
    }while (list1.checkId(id) == true);
    node1->id = id;
    time_t currentTime;
    time(&currentTime);
    timenow = ctime(&currentTime);
    node1->time = timenow;
    node1->nextF = NULL;
    list1.insert(node1);

}
list1.chkByTxt("World","N");   // N means not edited
list1.chkByTxt("World","Hello guys");  // edited
list1.print();
list1.chkByTxt("guys","del"); // del means to delete node with post guys
list1.printR();











// if you want to check manually then uncomment the below code
//--------------------------------------------------------------

    // int userOption;
    // for(int i=0;i<100;i++)
    // {
    //     cout<<" _____________________________________________________________ \n";
    //     cout<<"| PRESS 1 if you want to add a new post                       |\n";
    //     cout<<"| PRESS 2 if uou want to edit a post                          |\n";
    //     cout<<"| PRESS 3 if you want to search post by text                  |\n";
    //     cout<<"| PRESS 4 if you want to delete a post                        |\n";
    //     cout<<"| PRESS 5 if you want to display all posts(latest first)      |\n";
    //     cout<<"| PRESS 6 if you want to display all posts(oldest first)      |\n";
    //     cout<<"| PRESS 7 if you want to quit                                 |\n";
    //     cout<<"|-------------------------------------------------------------|\n";
    //     cout<<"| ENTER your choice : ";cin>>userOption;
    //     cout<<"|_____________________________________________________________|\n\n";
    //     if(userOption == 1)
    //     {
            
    //         string post,timeNow;
    //         int id;
    //         cin.ignore();
    //         cout<<"  Enter your text for a post : ";getline(cin,post);
    //         do 
    //         {
    //         id = rand() % 9000 + 1000;
    //         }while (list1.checkId(id) == true);
    //         time_t currentTime;
    //         time(&currentTime);
    //         timeNow = ctime(&currentTime);
    //         node *node1 = new node;
    //         node1->id = id;
    //         node1->post = post;
    //         node1->time = timeNow;
    //         node1->nextF = NULL;
    //         list1.insert(node1);
    //         cout<<" _____________________________________________________________ \n";
    //         cout<<"| Your post is added successfully!                            |\n";
    //         cout<<"| Your id : "<<id<<"                                              |\n";
    //         cout<<"| Your post editing time is : "<<timeNow;
    //         cout<<"|_____________________________________________________________|\n";


    //     }
    //     else if(userOption == 2)
    //     {
    //         int id,usropt;
    //         string text,timeNow;
    //         cout<<" ---Enter your id : ";cin>>id;
    //         for(int i=0;i<5;i++)
    //         {
    //             if(list1.checkId(id) == true){break;}
    //             cout<<" ---The id does not exists\n ---PRESS 1 if you want to back,\n ---PRESS 2 if want to try again : ";
    //             cin>>usropt;
    //             if(usropt == 1){break;}
    //             else if(usropt == 2){cout<<" ---Enter your id : ";cin>>id;}
    //         }
    //         cin.ignore();
    //         cout<<" Enter your text : ";getline(cin,text);
    //         time_t currentTime;
    //         time(&currentTime);
    //         timeNow = ctime(&currentTime);
    //         list1.edit(id,text,timeNow);
    //         cout<<" Your post is edited successfully!\n";
    //     }
    //     else if(userOption == 3)Hello guys
    //     {
    //         string text;
    //         cout<<" Enter a text so i will show you all posts containing the text : ";
    //         cin.ignore();
    //         getline(cin,text);
    //         list1.chkByTxt(text,"N");
    //     }
    //     else if(userOption == 4)
    //     {
    //         int id,usropt;
    //         cout<<" Enter your id : ";cin>>id;
    //         for(int i=0;i<5;i++)
    //         {
    //             if(list1.checkId(id) == true){break;}
    //             cout<<" ---The id does not exists\n ---PRESS 1 if you want to back,\n ---PRESS 2 if want to try again : ";
    //             cin>>usropt;
    //             if(usropt == 1){break;}
    //             else if(usropt == 2){cout<<" ---Enter your id : ";cin>>id;}
    //         }
    //         list1.del(id);
    //         cout<<" Your id is deleted successfully!\n";
    //     }
    //     else if(userOption == 5)
    //     {
    //         list1.print();
    //     }
    //     else if(userOption == 6)
    //     {
    //         list1.printR();
    //     }
    //     else if(userOption == 7){break;}
    // }
    return 0;
}
