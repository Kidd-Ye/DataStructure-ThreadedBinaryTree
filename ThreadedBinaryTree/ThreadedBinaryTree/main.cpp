//
//  main.cpp
//  ThreadedBinaryTree
//
//  Created by kidd on 2018/6/29.
//  Copyright © 2018年 Kidd. All rights reserved.
//

#include <iostream>
using namespace std;

enum TBT{ child = 0, thread}; //线索二叉树结点的指针是指向孩子还是前驱后继

typedef struct tbt{
    struct tbt *lchild;
    enum TBT ltag;
    char data;
    enum TBT rtag;
    struct tbt* rchild;
}TBTreeNode, *pTBTree;

int CreateThreadedBinaryTree(pTBTree &root){
    
    char data;
    if(cin >> data){
        if ('#' == data) {
            root = NULL;
            return -1;
        }else{
            root = new TBTreeNode();
            root->data = data;
            CreateThreadedBinaryTree(root->lchild);
            CreateThreadedBinaryTree(root->rchild);
        }
    }
    return 0;
}

static TBTreeNode *pre = NULL;//定义一个指针指向中序遍历当前访问结点的前一个访问结点

void InOrderThreadingBinaryTree(const pTBTree &root){
    if (NULL == root) {
        return;
    }
    InOrderThreadingBinaryTree(root->lchild);//中序遍历左子树
    
    if (NULL == root->lchild) { //如果左子树为空，就可以把指针域用来线索化，指向前驱
        root->lchild = pre;
        root->ltag = thread;
    }
    if (NULL != pre && NULL == pre->rchild) {
        pre->rchild = root;
        pre->rtag = thread;
    }
    pre = root;
    InOrderThreadingBinaryTree(root->rchild);
}

void InOrderThreadedBinaryTreeTraversal(pTBTree root){
    if (NULL == root) {
        return;
    }
    while (NULL != root) {
        while (NULL != root->lchild && child == root->ltag) {
            root = root->lchild;
        }
        cout << root->data << "";
        while (thread == root->rtag) {
            cout << root->rchild->data << "";
            root = root->rchild;
        }
        root = root->rchild;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    TBTreeNode *root = NULL;
    int result = CreateThreadedBinaryTree(root);
    if (0 == result) {
        cout << "二叉树线索化" << endl;
        InOrderThreadingBinaryTree(root);
        cout << "线索二叉树中序遍历" << endl;
        InOrderThreadedBinaryTreeTraversal(root);
        cout << endl;
        
    }
    return 0;
}
