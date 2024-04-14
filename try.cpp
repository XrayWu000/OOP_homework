#include <bits/stdc++.h>
using namespace std;

struct node{
    int id;
    struct node *next;
};

int main() {
    int i, x = 0, y = 0;
    struct node *head, *temp;
    head = new node;
    head->id = 0;
    temp = head;
    for(i = 1; i < 4; i++){
        temp->next = new node;
        temp = temp->next;
        temp->id = i;
    }

    temp->next = head;

    for(temp=head; x != 2; temp = temp->next){
        if(temp == head){
            x++;
        }
        if(temp == head->next){
            cout<<y<<endl;
            y++;
        }
    }
    cout<<i<<endl;
    cout<<y<<endl;
    return 0;
}
