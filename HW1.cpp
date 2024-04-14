#include <bits/stdc++.h>
using namespace std;

class PQB
{
public:
  PQB *col;

  int getlqbID() const {
    return lqbID;
  }

  void setlqbID(int value) {
    lqbID = value;
  }

  int getID() const {
    return ID;
  }

  void setID(int value) {
    ID = value;
  }

  PQB() : ID(0), col(nullptr) {}

private:

  int lqbID, ID;
};

class gate
{
public:
  void setID(int ID1, int ID2) {
    ID[0] = ID1;
    ID[1] = ID2;
  }
  int getID(int num){
    return ID[num];
  }
private:
  int ID[2];
};

class precedence
{
  public:
    precedence *next, *pre;
    int gid;
    int postgid;

    precedence (int ID, int idpost) : gid(ID), postgid(idpost), next(nullptr), pre(nullptr) {}
};

int findSmallestSwap(){

}

int main(){
  int logQubits, gatesNum, precNum, phyQubits, phyLinks;
  precedence *head, *tempprec;
  PQB *temp;
  int i, x, y, z, flag, id;

  cin >> logQubits >> gatesNum >> precNum >> phyQubits >> phyLinks;
  vector<PQB> pqb(phyQubits);
  vector<gate> gates(gatesNum);

  for(i = 0; i < 6; i++){
    cin >> x >> y >> z;
    gates[i].setID(y, z);
  }

  cin >> x >> y >> z;
  head = new precedence(y, z);
  tempprec = new precedence(z, -1);
  head->next = tempprec;
  tempprec->pre = head;
  for(i = 1; i < precNum; i++){//for precedence
    cin >> x >> y >> z;
    x = 0;//flag
    tempprec = nullptr;
      cout << "{1";
    for(precedence *curr = head; curr != nullptr; curr = curr->next){
      if(curr->gid == y)//flag
        tempprec = curr;
      if(curr->gid == z){//往前塞
        cout << "2";
        if(tempprec != nullptr){//純做新限制
          cout << "3";
          tempprec->postgid = z;
          tempprec->next->pre = tempprec->pre;//移動到新限制的附近比較不會有奇怪的影響
          tempprec->pre->next = tempprec->next;
          curr->pre->next = tempprec;
          tempprec->pre = curr->pre;
          tempprec->next = curr;
          curr->pre = tempprec;
          break;
        }
        if(curr->pre != nullptr){
          cout << "4";
          curr->pre->next = new precedence(y, z);
          curr->pre->next->pre = curr->pre;//把新增的的pre接去上一個
          curr->pre->next->next = curr;
          curr->pre = curr->pre->next;
        }
        else {
          curr->pre = new precedence(y, z);
          curr->pre->next = curr;
        }
        x = 1;
      }
      cout << "5";
      if(x == 1 && curr->gid == y){//如果對已加入過的有新限制，以刪掉的方式解決重複的
        delete curr;
        break;
      }
    }
      cout << "6";
    if(x == 0){//沒找到後限制的時候
      for(precedence *curr = head; curr != nullptr; curr = curr->next){
      cout << "7";
        if(curr->gid == y){//往後塞
          if(curr->postgid == -1){
            curr->postgid == z;
            curr->next = new precedence(z, -1);
          }
          else {
            curr->next->pre = new precedence(y, z);
            curr->next->pre->next = curr->next;
            curr->next = curr->next->pre;
          }
          curr->next->pre = curr;
          break;
        }
      }
    }
    cout << "8}" << endl;
  }//少1 1 3, 2 2 3, 3 4 5

  for(i = 0; i < phyLinks; i++){//for links
    cin >> x >> y >> z;
    y--;
    z--;
    PQB *curr1 = nullptr, *curr2 = nullptr;
    for(temp = pqb[y].col; temp != nullptr; temp = temp->col)
      curr1 = temp;
    if(curr1 == nullptr){
      pqb[y].col = new PQB();
      pqb[y].col->setID(z);
    }
    else {
      curr1->col = new PQB();
      curr1->col->setID(z);
    }
    for(temp = pqb[z].col; temp != nullptr; temp = temp->col)
      curr2 = temp;
    if(curr2 == nullptr){
      pqb[y].col = new PQB();
      pqb[y].col->setID(z);
    }
    else {
      curr2->col = new PQB();
      curr2->col->setID(z);
    }
  }
  for(i = 0; i < phyQubits; i++)
    pqb[i].setlqbID(i + 1);

  /*for(i = 0; i < gatesNum; i++){
    cout << "{" << i << ", " << gates[i].getID(0) << ", " << gates[i].getID(1) << "} ";
  }
  cout << endl;*/
  i = head->postgid;
  for(tempprec = head; tempprec->postgid == i; tempprec = tempprec->next){
    x = tempprec->gid - 1;
    y = gates[x].getID(0);
    z = gates[x].getID(1);
    flag = 0;
    for(temp = &pqb[y]; temp != nullptr; temp = temp->col){
      if(temp->getlqbID() == z){
        if(tempprec != head){
          precedence *curr;
          for(curr = head; curr->next != tempprec; curr = curr->next);
          curr->next = tempprec->next;
        }
        else
          head = tempprec->next;
        delete tempprec;
        flag = 1;
        break;
      }
    }
    if(flag == 1)
      break;
  }
  if(flag == 0){
    //findSmallestSwap()
    flag = 1;
  }
  for(i = 0; i < phyQubits; i++)
    cout << i + 1 << " " << pqb[i].getlqbID()<< endl;
  cout << "CNOT q" << y << " q" << z << endl;

  return 0;
}