#include <iostream>
#include <cstring>
using namespace std;

typedef struct Node{
    int studentId;
    char name[50];
    Node* right;
    Node* left;
    
}Node;

// Function to create a new node
Node* createNode(int id, const char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->studentId= id;
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// //insert node
// Node* insertNode(Node* root, int value){
//     if (root == NULL){
//         return createNode(value);
//     }
//     else
//     {
//         if(value > root->studentId){
//             root->right = insertNode(root->right, value);
//         }
//         else{
//             root->left = insertNode(root->left, value);
//         }
//     }
// }

//Print tree Root->Left->Right
void printNode(struct Node* root){
    if(root == NULL) return;
    cout << root->studentId<< "-" << root->name << endl;
    printNode(root->left);
    printNode(root->right);
}

//3. Search Student
struct Node* search(struct Node* root, int id, int& cmp){
    if (root == NULL){
        return NULL;
    }
    cmp++;

    if(id == root->studentId){
        return root;
    }
    else if (id < root->studentId){
        return search(root->left, id, cmp);
    }
    else {
        return search(root->right, id, cmp);
    }
} 

// Find minimum node in a subtree (for inorder successor)
Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 4. Delete Operation
Node* deleteNode(Node* root, int id) {
    // Base case: empty tree
    if (root == NULL) {
        return NULL;
    }
    
    if (id < root->studentId) {
        root->left = deleteNode(root->left, id);
    }
    else if (id > root->studentId) {
        root->right = deleteNode(root->right, id);
    }
    else {
        // CASE: Leaf node (no children)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // CASE: One child (only right)
        else if (root->left == NULL) {
            cout << "One child (right child only)" << endl;
            Node* temp = root->right;
            free(root);
            return temp;
        }
        
        // CASE: One child (only left)
        else if (root->right == NULL) {
            cout << "One child (left child only)" << endl;
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // CASE: Two children
        else {
            cout << "\nCase Two Children" << endl;
            
            // Find inorder successor (smallest in right subtree)
            Node* successor = findMin(root->right);
            cout << "Inorder Successor: " << successor->studentId << "-" << successor->name << endl;
            
            // Copy successor's data to current node
            root->studentId = successor->studentId;
            strcpy(root->name, successor->name);
            
            // Delete the successor
            root->right = deleteNode(root->right, successor->studentId);
        }
    }
    
    return root;
}

//5. Print all remaining students’ IDs in ascending order
void printInOrder(Node* root){
    if(root == NULL){
        return;
    }
    printInOrder(root->left);
    cout << root->studentId << "-" << root->name <<endl;
    printInOrder(root->right);
}

int main() {

    //Create Node with Id and name
    Node* root = createNode(20250050, "Anna");
    root->left = createNode(20250020, "Bora");
    root->right = createNode(20250080, "Chenda");
    root->left->left = createNode(20250010, "Dara");
    root->left->right = createNode(20250030, "Eang");
    root->right->left = createNode(20250070, "Fara");


    //Print Tree
    cout <<"----Tree----"<<endl;
    printNode(root);


    int cmp1 = 0;
    Node* found1 = search(root, 20250030, cmp1);
    if(found1){
        cout <<"\nFound: " << found1->studentId << "-" << found1->name << "\nComparision: " << cmp1 <<endl;
    }
    else {
        cout <<"Not found!" <<endl;
    }

    int cmp2 = 0;
    Node* found2 = search(root, 20250099, cmp2);
    if(found2){
        cout <<"Found: " << found2->studentId << "-" << found2->name << "\nComparision: " << cmp2 << endl;
    }
    else {
        cout <<"ID Not found!\n" <<endl;
    }

    root = deleteNode(root, 20250020);
    cout << "\nTree after deletion:" << endl;
    printNode(root);

    root = deleteNode(root, 20250050);
    cout << "\nTree after deletion:" << endl;
    printNode(root);
    
    cout <<"\n----Print in ascending order----" <<endl;
    printInOrder(root);

    return 0;
}