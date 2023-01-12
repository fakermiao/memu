/*
 * @Author: 苗金标
 * @Date: 2023-01-11 11:09:27
 * @LastEditors: 苗金标
 * @LastEditTime: 2023-01-12 11:15:36
 * @Description: 二叉树节点模板
 * 数据结构为：
 * parent | lc  | rc
 *     data
 * height | npl | color
 * color用于红黑树构造，为枚举类型
 * 包含的方法为：size、insertAsLc（e）、insertAsRc（e），succ（）（获取当前节点的直接后继）
 *              travLevel、travPre、travIn、travPost
 */
#include<iostream>
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1);
typedef enum { RB_RED,RB_BLACK} RBColor;
#include <stack>
#include <queue>

template <typename T> struct BinNode
{
    T data;
    BinNodePosi(T) parent;BinNodePosi(T) lc;BinNodePosi(T) rc;
    int height;
    int npl;
    RBColor color;
    BinNode() :
        parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
    BinNode(T e,BinNodePosi(T) p = NULL,BinNodePosi(T) lc = NULL,BinNodePosi(T) rc = NULL,int h = 0,
            int l = 1,RBColor c = RB_RED) :
        data (e),parent (p),lc (lc),rc (rc),height (h),npl (l),color (c) {} 
    //操作接口
    int size(); //统计当前节点后代个数
    BinNodePosi(T) insertAsLc (T const&);   //作为当前节点的左孩子插入新节点
    BinNodePosi(T) insertAsRc (T const&);   //作为当前节点的右孩子插入新节点
    BinNodePosi(T) succ();  //取当前节点的直接后继
    template <typename VST> void travLevel (VST&); //子树层次遍历
    template <typename VST> void travPre (VST&); //子树先序遍历
    template <typename VST> void travIn (VST&); //子树中序遍历
    template <typename VST> void travPost (VST&); //子树后序遍历
    
    bool operator< (BinNode const& bn) {return data < bn.data;}
    bool operator== (BinNode const& bn) {return data == bn.data;}
};
template <typename T> BinNodePosi(T) BinNode<T>::insertAsLc(T const& e){
    return lc = new BinNode(e,this);
}
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRc(T const& e){
    return rc = new BinNode(e,this);
}

template <typename T> template <typename VST>
void BinNode<T>::travIn (VST& visit){
    switch (rand() % 5)
    {
    case 1: break;
    case 2: break;
    case 3: break;
    case 4: break; 
    default: break;
    }
}

template <typename T,typename VST>
void travPre_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    visit(x->data);
    travPre_R(x->lc,visit);
    travPre_R(x->rc,visit);
}
template <typename T,typename VST>
void travPost_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travPost_R(x->lc,visit);
    travPost_R(x->rc,visit);
    visit(x->data);
}
template <typename T,typename VST>
void travIn_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travIn_R(x->lc,visit);
    visit(x->data);
    travIn_R(x->rc,visit);
}
/**
 * @description:迭代版先序遍历的一种实现，在travPre函数中随机选择用于测试和比较它们的区别
 * @return {void}
 */
template <typename T,typename VST>
static void visitAlongLeftBranch (BinNodePosi(T) x,VST& visit,std::stack<BinNodePosi(T)>& S){
    while (x)
    {
        visit(x->data);
        S.push(x->rc);
        x = x->lc;
    }
    
}
template <typename T,typename VST>
void travPre_I1 (BinNodePosi(T) x, VST& visit){
    std::stack<BinNodePosi(T)> S;
    while (true)
    {
        visitAlongLeftBranch(x,visit,S);
        if(S.empty()) break;
        x = S.pop();
    }
    
}
/**
 * @description:迭代版中序遍历版本1 
 * @return {void}
 */
template <typename T>
static void goAlongLeftBranch(BinNodePosi(T) x,std::stack<BinNodePosi(T)>& S){
    while (x)
    {
        S.push(x);
        x = x->lc;
    }   
}
template <typename T,typename VST>
void travIn_i1(BinNodePosi(T) x,VST& visit){
    std::stack<BinNodePosi(T)> S;
    while (true)
    {
        goAlongLeftBranch(x,S);
        if(S.empty()) break;
        x = S.pop();visit(x->data);
        x = x->rc;
    }
}

/**
 * @description:直接后继及其定位 
 * @return {*}
 */
template <typename T> BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) s = this;
    if(rc){
        s = rc;
        while (HasLchild)
        {
            s  = s->lc;
        }
    }else {
        while (isRChild(*s))
        {
            s = s->parent;
        }
        s = s->parent;
    }
    return s;
}

template <typename T,typename VST>
void travIn_I2 (BinNodePosi(T) x,VST& visit){
    std::stack<BinNodePosi(T)> S;
    while (true)
    {
        /* code */
        if(x){
            S.push(x);
            x = x->lc;
        }else if(!S.empty()){
            x = S.pop();
            visit(x->data);
            x = x->rc;
        }else
            break;
    }   
}

/**
 * @description:迭代版后序遍历 
 * @return {void}
 */
template <typename T>
static void gotoHLVFL (std::stack<BinNodePosi(T)>& S) {
    while(BinNodePosi(T) x = S.top()){
        if( HasLChild(*x)){
            if(HasRChild (*x)) S.push(x->rc);
            S.push(x->lc);
        }else{
            S.push(x->rc);
        }
    }
    S.pop();
}

template <typename T,typename VST>
void travPost_I (BinNodePosi(T) x,VST& visit){
    std::stack<BinNodePosi(T)> S;
    if( x ) S.push(x);
    while(!S.empty()){
        if(S.top != x->parent)
            gotoHLVFL(S);
        x = S.pop();visit(x->data);
    }
}
/**
 * @description:层次遍历 
 * @return {*}
 */
template <typename T> 
template <typename VST>
void BinNode<T>::travLevel (VST& visit){
    std::queue<BinNodePosi(T>) Q;
    Q->push(this);
    while(!Q->empty()){
        BinNodePosi(T) x = Q->pop();
        visit(x->data);
        if(HasLChild(*x)) Q->push(x->lc);
        if(HasRChild(*x)) Q->push(x->rc);
    }
}

