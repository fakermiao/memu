/*
 * @Author: 苗金标
 * @Date: 2023-01-12 14:12:42
 * @LastEditors: 苗金标
 * @LastEditTime: 2023-01-12 16:10:54
 * @Description: 
 * 数据结构为：
 * parent | lc  | rc
 *     data
 * height | npl | color
 * color用于红黑树构造，为枚举类型
 * 包含的方法为：size、insertAsLc（e）、insertAsRc（e），succ（）（获取当前节点的直接后继）
 *              travLevel、travPre、travIn、travPost
 */
#define BinNodePosi(T) myBinNode<T>*
typedef enum {RB_RED,RB_BLACK}RBColor;
using namespace std;
#include <queue>

template <typename T> struct myBinNode
{
    T data;
    BinNodePosi(T) parent,lc,rc;
    int height,npl;
    RBColor color;
    myBinNode(){}
    myBinNode(T data,BinNodePosi(T) parent = NULL,BinNodePosi(T) lc = NULL,BinNodePosi(T) rc = NULL, int height = 0,
                int npl = 0,RBColor color = RB_RED):data(data),parent(parent),lc(lc),rc(rc),height(height),npl(npl),color(color){}
    int size();
    BinNodePosi(T) insertAsLc(T const& e);
    BinNodePosi(T) insertAsRc(T const& e);
    BinNodePosi(T) succ();
    template <typename VST> void tracLevel(VST&);
    template <typename VST> void travPre(VST&);
    template <typename VST> void travIn(VST&);
    template <typename VST> void travPost(VST&);

    bool operator<(myBinNode const& bn){
        return data < bn.data;
    }
    bool operator=(myBinNode const& bn){
        return data == bn.data;
    }
};
template <typename T>
BinNodePosi(T) myBinNode<T>::insertAsLc(T const& e){
    return lc = new myBinNode(e,this);
}
template <typename T>
BinNodePosi(T) myBinNode<T>::insertAsRc(T const& e){
    return rc = new myBinNode(e,this);
}
/**
 * @description:层次遍历 
 * @return {void}
 */
template <typename T>
template <typename VST>
void myBinNode<T>::tracLevel(VST& visit){   
    queue<BinNodePosi(T)> Q;
    Q.push(this);
    while (!Q.empty())
    {
        /* code */
        BinNodePosi(T) x = Q.pop();
        visit(x->data);
        if(HasLcChild(*x)) Q.push(x->lc);
        if(HasRcChild(*x)) Q.push(x->rc);
    }
}

/**
 * @description: 前序遍历
 * @return {*}
 */
template <typename T,typename VST>
void travPre_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    visit(x->data);
    travPre_R(x->lc,visit);
    travPre_R(x->rc,visit);
}
template <typename T>
template <typename VST>
void myBinNode<T>::travPre(VST& visit){
    travPre_R(this,visit);
}
/**
 * @description:中序遍历 
 * @return {*}
 */
template <typename T,typename VST>
void travIn_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travIn_R(x->lc,visit);
    visit(x->data);
    travIn_R(x->rc,visit);
}
/**
 * @description:后序遍历 
 * @return {*}
 */
template <typename T,typename VST>
void travPost_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travPost_R(x->lc,visit);
    travPost_R(x->rc,visit);
    visit(x->data);
}

















