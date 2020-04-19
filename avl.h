//
// Created by User on 01/05/2019.
//

#ifndef WET1_AVL_H
#define WET1_AVL_H

#endif //WET1_AVL_H
#include <iostream>
#include <math.h>

template <class T,class S>
struct Node{
    S key;
    T* data;
    int height;
    struct Node* left;
    struct Node* right;

    Node<T,S> ():data(NULL), height(0), left(NULL),
                 right(NULL){}

    Node<T,S> (S key,  T* data):key(key), height(0), left(NULL),
                                right(NULL){
        if(!data){
            this->data=NULL;
        }
        else {
            this->data=new T();
            *this->data=*data;
        }
    }
    ~Node<T,S>(){
        if (!data)return;
        delete data;
    }
    Node<T,S> (const Node<T,S>& node): key(node.key),height(node.height),left
            (node.left),right(node.right){
        data= new T(*node.data);
    }
    Node<T,S> &operator=(const Node<T,S> &node){
        if (this == &node){
            return *this;
        }
        if (!node.data){
            this->data=NULL;
        }
        else {
            delete data;
            data = new T();
            *data = *node.data;
        }
        key=node.key;
        height=node.height;
        left=node.left;
        right=node.right;
        return *this;
    }
};


template <class T,class S>
class AvlTree{
    int getHeight(Node<T,S> *node){
        if(!node) return -1;
        else return node->height;
    }
    int maxHeight(int a,int b){
        return (a>b)?a:b;
    }
    int findBf(Node<T,S>* node){
        if (!node) return 0;
        return getHeight(node->left)-getHeight(node->right);
    };
    Node<T,S>* rotateLL(Node<T,S>* B){
        if(root->key == B->key){
            root=B->left;
        }
        Node<T,S>* A=B->left;
        Node<T,S>* Ar=A->right;
        A->right=B;
        B->left=Ar;
        B->height=1+maxHeight(getHeight(B->left),getHeight(B->right));
        A->height=1+maxHeight(getHeight(A->left),getHeight(A->right));
        return A;
    }

    Node<T,S>* rotateRR(Node<T,S>* B){
        if(root->key == B->key){
            root=B->right;
        }
        Node<T,S>* A=B->right;
        Node<T,S>* Al=A->left;
        A->left=B;
        B->right=Al;
        B->height=1+maxHeight(getHeight(B->left),getHeight(B->right));
        A->height=1+maxHeight(getHeight(A->left),getHeight(A->right));
        return A;
    }

    Node<T,S>* rotateRL(Node<T,S>* C){
        C->right=rotateLL(C->right);
        return rotateRR(C);
    }

    Node<T,S>* rotateLR(Node<T,S>* C){
        C->left=rotateRR(C->left);
        return rotateLL(C);
    }
    Node<T,S>* balanceTree(Node<T,S>* node){

        int bf =findBf(node);
        int bfL =findBf(node->left);
        int bfR = findBf(node->right);
        if (bf==2&&bfL>=0){
            return rotateLL(node);
        }
        if (bf==2&&bfL==-1){

            return rotateLR(node);
        }
        if (bf==-2&&bfR<=0){
            return rotateRR(node);
        }
        if (bf==-2&&bfR==1){
            return rotateRL(node);
        }
        return node;

    }
    /*Node<T>* newNode(int key,T* data,Node<T>* father){
        Node<T>* node =new Node<T>;
        node->right= NULL;
        node->left= NULL;
        node->father=father;
        node->key=key;
        node->data=data;
        node->height=0;
        return node;
    }*/
/*    bool search(int key, Node* node){
        if(root== nullptr) {
            return false;
        }
        if(key==node->key) {
            return true;
        }else if(key < node->key){
            return search(key,node->left);
        }else return search(key,node->right);
    }*/
    Node<T,S>* insertAvl(S key, T *data, Node<T, S> *node){
        if(node!= NULL) {
            if(key<node->key){
                node->left=insertAvl(key,data,node->left);
            }else {
                node->right=insertAvl(key,data,node->right);
            }
            node->height=1+maxHeight(getHeight(node->left),getHeight(node->right));
            int bf= findBf(node);
            if(bf==2||bf==-2){
                return balanceTree(node);
            }
            return node;
        }else{
            node= new Node<T,S>(key,data);
            return node;
        }
    }

    void printTreeInArray(S* arr,Node<T,S>* node, int* i){
        if (node== NULL) return;
        printTreeInArray(arr,node->left,i);
        arr[*i]=node->key;
        *i=*i+1;
        printTreeInArray(arr,node->right,i);
    }



public:
    Node<T,S>* root;
    AvlTree(){
        root= NULL;
    }
    bool isExsist(S key){
        if (root == NULL) {
            return false;
        }
        return searchKey(key, root);
    }
    // void Insert(int key,T* data){
    //       InsertAvl(key, data, root, nullptr);
    //}
    void insert(S key,T* data){
        if (!root) {
            Node<T,S>* node=new Node<T,S>(key,data);
            root=node;
        }else{
            insertAvl(key, data, root);
        }
    }
    void remove (S keyToRemove){
        if (root->key == keyToRemove && root->height ==0){
            delete root;
            root= NULL;
            return;
        }
        removeKey(keyToRemove,root);

    }

    Node<T, S> *removeKey(S key, Node<T, S> *node) {
        if (node == NULL) {
            return NULL;
        } else if (key < node->key) {
            node->left = removeKey(key, node->left);
        } else if (key > node->key) {
            node->right = removeKey(key, node->right);
        } else {
            if (!node->left || !node->right) {
                Node<T, S> *temp = node->left;
                if (!temp) {
                    if (!node->right) {
                        temp = node;
                        node = NULL;
                    } else temp = node->right;
                }
                if (node != NULL) {
                    node->data = temp->data;
                    temp->data = NULL;
                    node->key = temp->key;
                    node->left = temp->left;
                    node->right = temp->right;
                    //*node=*temp;
                }
                // delete temp->data;
                delete temp;
                //temp= nullptr;
            } else {
                Node<T, S> *temp = node->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                swap(node, temp);
                node->right = removeKey(key, node->right);
            }
        }
        if (node == NULL) {
            return node;
        }
        node->height = 1 + maxHeight(getHeight(node->left), getHeight(node->right));
        int bf = findBf(node);
        if (bf == 2 || bf == -2) {
            return balanceTree(node);
        }
        return node;
    }

    void swap (Node<T,S>* n1,Node<T,S>* n2) {
        S temp = n1->key;
        T *tempData = n1->data;
        n1->data = n2->data;
        n1->key = n2->key;
        n2->data = tempData;
        n2->key = temp;
        return;
    }
    T* searchAvlData (S key){
        if (!isExsist(key)){
            return NULL;
        }
        Node<T,S>* node = searchAvl(key);
        return  (node->data);
    }

    Node<T,S>* searchAvl (S key){
        return search(key,root);
    }

    Node<T,S>* search(int key,Node<T,S>* node){
        if(node== NULL) {
            return NULL;
        }
        if(key==node->key) {
            return node;
        }else if(key < node->key){
            return search(key,node->left);
        } return search(key,node->right);
    }

    bool searchKey(S key, Node<T,S>* node){
        if(node== NULL) {
            return false;
        }
        if(key==node->key) {
            return true;
        }else if(key < node->key){
            return searchKey(key,node->left);
        } return searchKey(key,node->right);
    }

    int countNodesInTree(){
        if(root== NULL){
            return 0;
        }else return countNodesInTreeAvl(root);
    }
    int countNodesInTreeAvl(Node<T,S>* node){
        if(node== NULL){
            return 0;
        }

        return countNodesInTreeAvl(node->left)+1+ countNodesInTreeAvl(node->right);
    }

    void inOrder(Node<T,S>* node){
        if (node== NULL) return;
        inOrder(node->left);
        std::cout << node->key << std::endl;
        inOrder(node->right);
    }

    void printTreeInArray(S* arr){
        if (root== NULL) return;
        int i=0;
        printTreeInArray(arr,root,&i);
    }

    void printTreeInArray(S* arr,Node<T,S>* node){
        if (node== NULL) return;
        int i=0;
        printTreeInArray(arr,node,&i);
    }

    bool checkIfBalanced(Node<T,S>* node){
        return findBf(node) > -2 && findBf(node) < 2;
    }

    bool checkIfAvl(){
        if(root== NULL) return true;
        bool isAvl=true;
        checkIfAvl(root,&isAvl);
        return isAvl;
    }

    void checkIfAvl(Node<T,S>* node,bool* isAvl){
        if(node== NULL) return;
        checkIfAvl(node->left,isAvl);
        if (!checkIfBalanced(node)){
            *isAvl= false;
        }
        checkIfAvl(node->right,isAvl);
    }



    // AvlTree<T,S> &operator=(const AvlTree<T,S> &avl);
    // AvlTree<T,S> (const AvlTree<T,S>& avl);
    ~AvlTree(){
        avlDestroy(root);
    }

    void avlDestroy(Node<T,S>* node ){
        if (!node)return;
        avlDestroy(node->left);
        avlDestroy(node->right);
        delete node;
    }

    Node<T,S>* turnToAvlInSize(Node<T,S> *node,int* numLeafsToErase){
        if(*numLeafsToErase==0) return node;
        else{
            if(node->right!=NULL) {
                node->right=turnToAvlInSize(node->right, numLeafsToErase);
            }
            if(node->left==NULL&&node->right==NULL){
                *numLeafsToErase=*numLeafsToErase-1;
                delete(node);
                return NULL;
            }
            if(node->left!=NULL){
                node->left=turnToAvlInSize(node->left, numLeafsToErase);
            }
            node->height=1+maxHeight(getHeight(node->left),getHeight(node->right));
            return node;

        }
    }

    Node<T,S>* CreateEmptyFulTree(Node<T,S>* node,int height){
        if(height==-1) return NULL;
        node=new Node<T,S>();
        if(root==NULL) root=node;
        node->left=CreateEmptyFulTree(node->left,height-1);
        node->right=CreateEmptyFulTree(node->right,height-1);
        node->height=height;
        return node;
    }

    void CreateEmptyAvlTree(int size){
        int height=ceil(log2(size));
        if(pow(2,height)==size) height++;// when size is a integer power of too
        this->CreateEmptyFulTree(root,height-1);
        int numLeafsToErase=pow(2,height)-size-1;
        this->turnToAvlInSize(root,&numLeafsToErase);
    }

    void EnterKeysToTreeFromArray(Node<T,S>* node,S* arr,int* i){
        if(node==NULL) return;
        EnterKeysToTreeFromArray(node->left,arr,i);
        node->key=arr[*i];
        (*i)++;
        EnterKeysToTreeFromArray(node->right,arr,i);
    }

    void mergeArray(S*newArray,S* arr1,S* arr2,int size1,int size2){
        int j1=0;
        int j2=0;
        bool j1ExceedSize1= false;
        bool j2ExceedSize2= false;
        for(int i=0;i<(size1+size2);i++){
            if(j1>=size1) j1ExceedSize1=true;
            if(j2>=size2) j2ExceedSize2=true;
            if((arr1[j1]<arr2[j2]||j2ExceedSize2)&&!j1ExceedSize1){
                newArray[i]=arr1[j1];
                j1++;
            } else{
                newArray[i]=arr2[j2];
                j2++;
            }

        }
    }


    void mergeTrees(Node<T,S>* root1,Node<T,S>* root2){
        int size1=countNodesInTreeAvl(root1);
        int size2=countNodesInTreeAvl(root2);
        S* arr1= new S[size1];
        S* arr2= new S[size2];
        S* newArray=new S[size1+size2];
        printTreeInArray(arr1,root1);
        printTreeInArray(arr2,root2);
        mergeArray(newArray,arr1,arr2,size1,size2);
        this->CreateEmptyAvlTree(size1+size2);
        int index=0;
        this->EnterKeysToTreeFromArray(root,newArray,&index);
        delete[]arr1;
        delete[]arr2;
        delete[]newArray;
    }

    void changeData (S key, T* newData){
        Node<T,S>* nodeToChange = searchAvl(key);
        if (!nodeToChange->data) {
            nodeToChange->data=newData;
            return;
        }
        delete nodeToChange->data;
        nodeToChange->data=newData;
    }

    AvlTree<T, S> &operator=(const AvlTree<T, S> &tree) {
        if (this == &tree) {
            return *this;
        }
        if (!tree.root) {
            this->avlDestroy(this->root);
            this->root = NULL;
            return (*this);
        }
        this->avlDestroy(this->root);
        copyTree(tree.root);
        return (*this);

    }

    void copyTree (Node<T,S> *node){
        if ( node != NULL){
            this->insert(node->key,node->data);
            copyTree(node->left);
            copyTree(node->right);
        }
    }

    AvlTree<T, S>(const AvlTree<T, S> &tree) {
        if (!tree.root) {
            this->root = NULL;
        }
        root=NULL;
        copyTree(tree.root);
    }
};
