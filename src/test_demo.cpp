#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void AddToTail(ListNode **head, int val) {
    ListNode * nlist = new ListNode(val);
    if (*head == nullptr) {
        *head = nlist;
    } else {
        ListNode *p = *head;
        while (p->next) {
            p = p->next;
        }
        p->next = nlist;
    }
    delete nlist;
}

int main() {
    ListNode *L = new ListNode(5);
    AddToTail(&L, 10);
    ListNode *p = L;
    while (p->next) {
        p = p->next;
    }
    cout << "ListNode final value: " << p->val << endl;
    ListNode *L_next = L->next;
    delete L;
    cout << "L next: " << L_next->val << endl;
}