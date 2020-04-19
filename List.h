//
// Created by mayfl on 08/05/2019.
//

#ifndef WET1_LIST_H
#define WET1_LIST_H

#include <iostream>

struct ListNode{
    int data;
    ListNode* next;
    ListNode* prev;
    ListNode (): data(0), next(NULL), prev(NULL){}
};


class List{
    ListNode* head;
    ListNode* tail;
    ListNode* bottom;
    bool listIsFull;
public:
    List(){
        head=NULL;
        tail=NULL;
        listIsFull= false;
    }

    ListNode* insertTop (int x){
        ListNode* node = new ListNode();
        node->data = x;
        node->prev = NULL;
        node->next = head;
        if(head !=  NULL)
            head->prev = node;
        if(!tail && !head){ //first node in the list case
            head=node;
            tail=node;
        }
        head = node;
        return node;
    }

    ListNode* insertBottom(int x){
        ListNode* node = new ListNode();
        node->data = x;
        node->prev = tail;
        node->next = NULL;
        if(tail !=  NULL)
            tail->next= node;
        if(!tail && !head){ //first node in the list case
            head=node;
            tail=node;
        }
        tail = node;
        return node;
    }

    int getData (ListNode* address ){
        if (!address)return -1;
        return address->data;
    }

    void pushNodeToTheEnd (ListNode* address){
        if (!address)return;
        if(address == bottom && bottom==head && !listIsFull){
            listIsFull=true;
        }
        if (address==bottom && bottom!=NULL){
            bottom=bottom->prev;
        }
        if (address==tail){
            return;
        }
        address->next->prev=address->prev;
        if(address!=head){
            address->prev->next=address->next;
        } else head=address->next;
        tail->next=address;
        address->prev=tail;
        address->next=NULL;
        tail=address;
    }

    void pointBottomToTail(){
        bottom=tail;
    }

    void pushNodeToTheStart (ListNode* address){
        if (!address)return;
        if (address==bottom && bottom!=NULL){
            bottom=bottom->prev;
        }
        if(listIsFull){
            listIsFull= false;
            bottom=address;
        }
        if (address==head){
            return;
        }
        address->prev->next=address->next;
        if(address!=tail){
            address->next->prev=address->prev;
        }else tail=address->prev;
        head->prev=address;
        address->next=head;
        address->prev=NULL;
        head=address;
    }

    bool isBottom (ListNode* node){
        return (node==bottom);
    }

    ListNode* getFirst(){
        return head;
    }

    ListNode* getNext (ListNode* node){
        if (!node) return NULL;
        return node->next;
    }


    ~List(){
        ListNode* temp=head;
        ListNode* current=NULL;
        while (temp!= NULL){
            current=temp;
            temp=temp->next;
            delete current;
        }
    }

    void display()
    {
        ListNode *temp= head;
        while(temp!=NULL)
        {
            std::cout<<temp->data<< std::endl;
            temp=temp->next;
        }
    }

    void displayAddress()
    {
        ListNode *temp= head;
        while(temp!=NULL)
        {
            std::cout<<temp<< std::endl;
            temp=temp->next;
        }
    }


};

#endif //WET1_LIST_H
