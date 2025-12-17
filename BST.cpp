#include <iostream>
#include <string>
using namespace std;

struct Node {
    int studentId;
    string name;
    int age;
    Node* left;
    Node* right;

    Node(int id, string n, int a) : 
        studentId(id), 
        name(n), 
        age(a), 
        left(NULL), 
        right(NULL) {}
};

// Function to create a new node
Node* createNode(int studentId, string name, int age) {
    Node* newNode = new Node(studentId, name, age);
    return newNode;
}

// Insert a student node
Node* insertNode(Node* node, int studentId, string name, int age) {
    if (node == NULL) {
        cout << "Insert: " << studentId << " - " << name << " (Age: " << age << ")" << endl;
        return createNode(studentId, name, age);
    }
        
    if (studentId < node->studentId) {
        node->left = insertNode(node->left, studentId, name, age);
    }
    else if (studentId > node->studentId) {
        node->right = insertNode(node->right, studentId, name, age);
    }
    else {
        cout << "Student ID " << studentId << " already exists!" << endl;
    }
        
    return node;
}

//Print tree Left->Root->Right
void printAllStudent(Node* root){
    if(root == NULL) return;
    printAllStudent(root->left);
    cout << root->studentId << " - " << "Name: " << root->name << "    Age: "<< root->age << endl;
    printAllStudent(root->right);
}

//3. Search Student
Node* search(Node* node, int id){
    if (node == NULL){
        return NULL;
    }

    if(id == node->studentId){
        return node;
    }
    else if (id < node->studentId){
        return search(node->left, id);
    }
    else {
        return search(node->right, id);
    }
} 

// Find minimum node in a subtree (for inorder successor)
Node* findMin(Node* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 4. Delete Operation
Node* deleteStudent(Node* node, int studentId) {
    // Base case: empty tree
    if (node == NULL) {
        return NULL;
    }
    
    if (studentId < node->studentId) {
        node->left = deleteStudent(node->left, studentId);
    }
    else if (studentId > node->studentId) {
        node->right = deleteStudent(node->right, studentId);
    }
    else {
        // CASE: Leaf node (no children)
        if (node->left == NULL && node->right == NULL) {
            return NULL;
        }
        
        // CASE: One child (only right)
        else if (node->left == NULL) {
            cout << "One child (right child only)" << endl;
            Node* temp = node->right;
            delete(node);
            return temp;
        }
        
        // CASE: One child (only left)
        else if (node->right == NULL) {
            cout << "One child (left child only)" << endl;
            Node* temp = node->left;
            delete(node);
            return temp;
        }
        
        // CASE: Two children
        else {
            cout << "\nCase Two Children" << endl;
            Node* temp = findMin(node->right);
            node->studentId = temp->studentId;
            node->name = temp->name;
            node->age = temp->age;
            node->right = deleteStudent(node->right, temp->studentId);
        }
    }
    
    return node;
}

// Count total students
int countNodes(Node* node) {
    if (node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Cleanup memory
void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

//Display Choice
void displayMenu() {
    cout << "----- Register Office ------" << endl;
    cout << "1. View Student List" << endl;
    cout << "2. Total Student" <<endl;    
    cout << "3. Insert New Student" <<endl;
    cout << "4. Search Student by ID" <<endl;
    cout << "5. Remove Student by ID" << endl;
    cout << "0. Exit" <<endl;
    cout << "Enter choice: ";
}

int main() {

    //Create Node with Id and name
    Node* node = createNode(20250050, "Anna", 17);
    node->left = createNode(20250020, "Bora", 18);
    node->right = createNode(20250080, "Chenda", 18);
    node->left->left = createNode(20250010, "Dara", 19);
    node->left->right = createNode(20250030, "Eang", 20);
    node->right->left = createNode(20250070, "Fara", 20);
    node->right->right = createNode(20250090, "Linda", 21);

    int choice;
    int studentId;
    string name;
    int age;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: {
                cout << "\n=== Student List ===" << endl;
                printAllStudent(node);
                cout << "\n";
                break;
            }
            case 2: {
                cout << "\n---The total student: " << countNodes(node) << " Student---" << "\n";
                cout << "\n";
                break;
            }

            case 3: {
                cout << "\nEnter Student ID: ";
                cin >> studentId;
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, name);
                cout << "Enter Student Age: ";
                cin >> age;
                node = insertNode(node, studentId, name, age);
                cout << "\n";
                break;
            }
            
            case 4: {
                cout << "\nEnter Student ID to search: ";
                cin >> studentId;
                Node* result = search(node, studentId);
                if (result != NULL) {
                    cout << "Student Found: " << result->studentId << " - " 
                         << result->name << " (Age: " << result->age << ")" << endl;
                } else {
                    cout << "Student with ID " << studentId << " not found." << endl;
                }
                cout << "\n";
                break;
            }
            
            case 5: {
                cout << "\nEnter Student ID to remove: ";
                cin >> studentId;
                Node* result = search(node, studentId);
                if (result != NULL) {
                    cout << "Removing: " << result->studentId << " - " << result->name << endl;
                    node = deleteStudent(node, studentId);
                    cout << "Student removed successfully!" << endl;
                } else {
                    cout << "Student with ID " << studentId << " not found." << endl;
                }
                cout << "\n";
                break;
            }

            case 0: {
                cout << "\nExiting Student Registry System. Goodbye!" << endl;
                break;
            }
            
            default: {
                cout << "\nInvalid choice. Please try again." << endl;
            }
        }
        
    } while (choice != 0);
    
    // Clean up memory before exiting
    deleteTree(node);
    
    return 0;
}