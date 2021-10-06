//https://contest.yandex.ru/contest/29403/problems/E/

#include "funcs.h"
#include <bits/stdc++.h>

struct TreeNode{
    TreeNode * left = nullptr, * right = nullptr, * parent = nullptr;
    explicit TreeNode(TreeNode * parent):
        parent(parent){};
};

struct HaffmanTree{
    TreeNode * root = nullptr;

    void getNodeCodes(TreeNode * node, std::string prefix, std::vector<std::string > & codes){
        bool leaf = true;
        if(node->left != nullptr){
            leaf = false;
            prefix.push_back('0');
            getNodeCodes(node->left,prefix,codes);
            prefix.pop_back();
        }
        if(node->right != nullptr){
            leaf = false;
            prefix.push_back('1');
            getNodeCodes(node->right,prefix,codes);
            prefix.pop_back();
        }
        if(leaf)
            codes.push_back(prefix);
    }

    void printCodes(std::ostream & output){
        std::vector<std::string > codes;
        std::string prefix;
        if(root != nullptr)
            getNodeCodes(root,"",codes);

        output << codes.size()<<'\n';
        std::copy(codes.begin(),codes.end(),
                  std::ostream_iterator<std::string &>(output, "\n"));
    }
};

HaffmanTree * parseHaffmanTree(std::string & code){
    auto ans = new HaffmanTree;
    TreeNode ** curNode = &ans->root;
    for(auto & c : code){
        switch (c) {
            case 'D':{
                if(*curNode == nullptr)
                    *curNode = new TreeNode(nullptr);
                (*curNode)->left = new TreeNode(*curNode);
                curNode = &(*curNode)->left;
                break;
            }
            case 'U':{

                while ((*curNode) == (*curNode)->parent->right){
                    curNode = &(*curNode)->parent;
                }

                //if( (*curNode) == (*curNode)->parent->left ){
                    (*curNode)->parent->right = new TreeNode((*curNode)->parent);
                    curNode = &(*curNode)->parent->right;
                //}
                break;
            }
            default:
                break;
        }
    }
    return ans;
}

void parseFile(std::istream & input, std::ostream & output){

    int n;
    input >> n;
    input.get();
    std::string line;
    for(int i = 0; i< n; ++i){
        std::getline(input,line);
        auto tree = parseHaffmanTree(line);
        tree->printCodes(output);
    }
}
