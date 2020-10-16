#include "stdafx.h"
#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
};

Node* createNode(int n) {
	Node* ptr = new Node();
	ptr->data = n;
	ptr->next = nullptr;
	return ptr;
}

/* 在链表尾部插入 */
void appendNode(Node* p, int n) {
	if (p == nullptr) {
		p = createNode(n);
		return;
	}
	Node* cur = p;
	while (cur) {
		if (cur->next == nullptr) {
			cur->next = createNode(n);
			return;
		}
		cur = cur->next;
	}
	cout << "The head is null" << endl;
}

void printList(Node* p)
{
	if (!p) return;
	Node* cur = p;
	while (cur) {
		if (cur->next == nullptr) cout << cur->data;
		else {
			cout << cur->data << "->";
		}
		cur = cur->next;
	}
	cout << endl;
}

/* 删除头节点 */
Node* deleteNode(Node** head) {
	if (*head == nullptr) return nullptr;
	Node* p = *head;
	*head = p->next;
	delete p;
	p = nullptr;
	return *head;
}

/* 在头节点增加节点 */
Node* addNode(Node** head, int n) {
	Node* p = createNode(n);
	p->next = *head;
	*head = p;
	return *head;
}

/* 删除指定值的节点 */
void deleteOneNode(Node** head, Node* p) {
	Node* cur = *head;
	Node* pre = *head;
	if (p == *head) {
		*head = (*head)->next;
		return;
	}
	while (cur) {
		if (cur == p) {
			pre->next = cur->next;
			return;
		}
		
		pre = cur;
		cur = cur->next;
		
	}
}

/* 释放节点所指内存 */
void empty(Node** head) {
	if (*head == nullptr) return;
	Node* p = *head;
	Node* q = *head;
	while (p) {
		p = q->next;
		delete q;
		q = p;
	}
	cout << "all is deleted !" << endl;
	delete *head;
	*head = nullptr;
}

/* 删除链表中的重复节点 */
void removeDuplicateNode(Node** head) {
	Node* cur = *head;
	Node* iter;
	while (cur) {
		iter = cur->next;
		while (iter) {
			if (cur->data == iter->data) {
				deleteOneNode(head, iter);
			}
			iter = iter->next;
		}
		cur = cur->next;
	}
}

/* 指定某个节点开始循环，即尾部节点指向指定点 */
void makeCircleList(Node** head, int n) {
	if (*head == nullptr) return;
	Node* cur = *head;
	Node* temp = nullptr;
	while (cur) {
		if (cur->data == n) {
			temp = cur;
		}
		if (cur->next == nullptr) break;
		cur = cur->next;
	}
	if (temp) {
		cur->next = temp;
	}
	else {
		cout << "no integer " << n << endl;
	}
	
}


/* 找到循环链表的起始节点 */
int findBeginOfCircle(Node** head) {
	if (*head == nullptr || (*head)->next == nullptr) return -1;
	Node* cur = *head;
	Node* cur2 = *head;
	while (1) {
		cur = cur->next;
		if (cur2->next == nullptr) return -1;
		cur2 = cur2->next;
		if (cur2->next == nullptr) return -1;
		cur2 = cur2->next;
		if (cur == cur2) break;
	}
	cur = *head;
	while (1) {
		if (cur == cur2) return cur->data;
		cur = cur->next;
		cur2 = cur2->next;
	}

}

/* 将链表上的值转换成数值，如5->6->2 为562 */
int getNumber(Node** head) {
	int sum = 0;
	if (*head == nullptr) return sum;
	Node* cur = *head;
	while (cur) {
		sum *= 10;
		sum += cur->data;
		cur = cur->next;
	}
	return sum;
}


/* 将数字转换成字符数组 */
void i2a(int n, char s[]) {
	int i = 0;
	while (1) {
		s[i++] = n % 10 + '0';
		if ((n /= 10) == 0) break;
	}
	s[i] = '\0';
}

/* 获得两个链表数值之和并返回该链表 */
void getSumList(Node** head, Node* headA, Node* headB) {
	int sum = getNumber(&headA) + getNumber(&headB);
	char s[10];
	i2a(sum, s);
	
	for (int i = 0; i < strlen(s); i++) {
		addNode(head, s[i] - '0');
	}
}

/* 插入节点，从小到大插入 */
void insertNode(Node** head, int n) {
	if (*head == nullptr) {
		*head = createNode(n);
		return;
	}
	Node* newNode = createNode(n);
	Node* cur = *head;
	Node* pre = *head;

	while (cur) {
		if (cur->data >= n) {
			if (cur == *head) {
				newNode->next = *head;
				*head = newNode;
				return;
			}
			newNode->next = cur;
			pre->next = newNode;
			return;
		}
		pre = cur;
		cur = cur->next;
	}
	appendNode(*head, n);

}

/* 将一个无序链表排序 */
Node* sortList(Node** unsorted) {
	Node* res = nullptr;
	Node* cur = *unsorted;

	while (cur) {
		insertNode(&res, cur->data);
		cur = cur->next;
	}

	return res;
}

/* 找到链表的倒数第m个数值 */
Node* findmthToLast(Node** head, int mth)
{
	Node* cur = *head;
	for (int i = 0; i < mth; i++) {
		if (cur)
			cur = cur->next;
		else
			return nullptr;
	}
	Node* mbehind = *head;
	while (cur) {
		cur = cur->next;
		if(cur) mbehind = mbehind->next;
	}
	return mbehind;
}



int main() {
	Node* headA = createNode(5);
	
	appendNode(headA, 2);
	appendNode(headA, 3);
	appendNode(headA, 4);
	cout << "ListA is ";
	printList(headA);
	cout << "Sum of ListA is " << getNumber(&headA) << endl;

	Node* headB = createNode(7);
	appendNode(headB, 3);
	cout << "ListB is ";
	printList(headB);
	cout << "Sum of ListB is " << getNumber(&headB) << endl;

	Node* head = nullptr;
	getSumList(&head, headA, headB);
	cout << "SumList is ";
	printList(head);

	Node* sorted = sortList(&head);
	printList(sorted);

	cout << (findmthToLast(&sorted, 3))->data << endl;
	//head = deleteNode(&head);
	//printList(head);
	//head = addNode(&head, 500);
	//head = addNode(&head, 600);
	//printList(head);
	//removeDuplicateNode(&head);
	//printList(head);
	////makeCircleList(&head, 300);
	////cout << "The beginning of circlelist is " << findBeginOfCircle(&head) << endl;

	//empty(&head);
	////appendNode(head, 200);
	//printList(head);
}
