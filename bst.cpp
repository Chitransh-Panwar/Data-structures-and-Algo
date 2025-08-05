#include<iostream>
#include<queue>
using namespace std;

class Node {
    public:
        int data;
        Node* left;
        Node* right;
        Node(int d) {
            this->data=d;
            this->left=nullptr;
            this->right=nullptr;
        }
};

Node* insertintoBST(Node* &root,int d) {
    if(root==NULL) {
        root=new Node(d);
        return root;
    }

    if(d>root->data) {
        root->right=insertintoBST(root->right,d);
    } else {
        root->left=insertintoBST(root->left,d);
    }
    return root;
}

Node* deletefromBST(Node* root,int val) {
    if(root==NULL) {
        return root;
    }

    if(root->data==val) {
        //0child
        if(root->left==NULL&&root->right==NULL) {
            delete root;
            return NULL;
        }

        //1 child
        if(root->left!=NULL&&root->right==NULL) {
            Node* temp=root->left;
            delete root;
            return temp;
        }

        if(root->left==NULL&&root->right!=NULL) {
            Node* temp=root->right;
            delete root;
            return temp;
        }

        //2 child
        if(root->left!=NULL&&root->right!=NULL) {
            int mini=minimum(root->right)->data;
            root->data=mini;
            root->right=deletefromBST(root->right,mini);
            return root;
        }
    } else if(root->data>val) {
        root->left=deletefromBST(root->left,val);
        return root; 
    } else{
        root->right=deletefromBST(root->right,val);
        return root;
    }
}


void inorder(Node* root) {
    if(root==NULL) return;
    if(root->left) inorder(root->left);
    cout<<root->data<<" ";
    if(root->right) inorder(root->right);
}
void preorder(Node* root) {
    if(root==NULL) return;
    cout<<root->data<<" ";
    if(root->left) preorder(root->left);
    
    if(root->right) preorder(root->right);
}
void postorder(Node* root) {
    if(root==NULL) return;
    if(root->left) postorder(root->left);
    
    if(root->right) postorder(root->right);
    cout<<root->data<<" ";
}
//Floor Value Node: Node with the greatest data lesser than or equal to the key value.
int floorOfBST(Node* root,int key) {
            int floor=-1;
            while(root) {
                if(root->data==key) {
                    floor=key;
                    return floor;
                }
                if(key>root->data ) {
                    floor=root->data;
                    root=root->right;
                } else {
                    
                    root=root->left;
                }
            }
            return floor;
        }
//Ceil Value Node: Node with the smallest data larger than or equal to the key value.
 int CeilOfBST(Node* root,int key) {
            int ceil=-1;
            while(root) {
                if(root->data==key) {
                    ceil=root->data;
                    return ceil;
                }
                if(key>root->data) {
                    root=root->right;
                } else {
                    ceil=root->data;
                    root=root->left;
                }

            }
            return ceil;
        }

void levelordertransversal(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while(!q.empty()) {
        Node* temp=q.front();
        q.pop();
        if(temp==NULL) {
            cout<<endl;
            if(!q.empty()) {
                q.push(NULL);
            }
        } else {
            cout<<temp->data<<" ";
            if(temp->left) q.push(temp->left);
            if(temp->right) q.push(temp->right);
        }
    }
}
void takeinput(Node* &root) {
    int data;
    cin>>data;

    while(data!=-1) {
        root=insertintoBST(root,data);
        cin>>data;

    }
}

bool searchinBST(Node* root,int x) {
    if(root==NULL) return false;

    if(root->data==x) return true;

    if(root->data>x) {
        return searchinBST(root->left,x);
    } else {
        return searchinBST(root->right,x);
    }
}

Node* minimum(Node* root) {
    Node* temp = root;
    while(temp->left!=NULL) {
        temp=temp->left;
    }
    return temp;
}

Node* maximum(Node* root) {
    Node* temp=root;
    while(temp->right!=NULL) {
        temp=temp->right;

    }
    return temp;
}

int main() {
    Node* root=NULL;
    cout<<"enter data for BST"<<endl;
    takeinput(root);
    cout<<"level order"<< endl;
    levelordertransversal(root); 
    cout<<"preorder"<<endl;
    preorder(root);
    cout<<"inorder"<<endl;
    inorder(root);
    cout<<"postorder"<<endl;
    postorder(root);

    cout<<"min"<<endl;
    Node* min =minimum(root);
    cout<<min->data;
    cout<<"max"<<endl;
    Node* max =maximum(root);
    cout<<max->data;
    return 0;
}
