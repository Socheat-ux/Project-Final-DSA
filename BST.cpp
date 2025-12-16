#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int studentId;
    string name;
    int age;
    Node* left;
    Node* right;
    
    Node(int id, string n, int a) : studentId(id), name(n), age(a), left(NULL), right(NULL) {}
};

// Structure for storing student data (for sorting)
struct Student {
    int studentId;
    string name;
    int age;
    
    Student(int id, string n, int a) : studentId(id), name(n), age(a) {}
};

// Function to create a new node
Node* createNode(int studentId, string name, int age) {
    Node* newNode = new Node(studentId, name, age);
    return newNode;
}

// Insert a student node
Node* insertNode(Node* node, int studentId, string name, int age) {
    if (node == NULL) {
        cout << "Enrolled: " << studentId << " - " << name << " (Age: " << age << ")" << endl;
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

//Print tree Root->Left->Right
void printAllStudent(Node* root){
    if(root == NULL) return;
    cout << root->studentId << "-" << root->name << root->age << endl;
    printAllStudent(root->left);
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
            delete(node);
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

//5. Print all remaining students’ IDs in ascending order
void printInOrder(Node* node){
    if(node == NULL){
        return;
    }
    printInOrder(node->left);
    cout << node->studentId << " - " << node->name << " (Age: " << node->age << ")" << endl;
    printInOrder(node->right);
}

// Count total students
int countNodes(Node* node) {
    if (node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Convert BST to vector for sorting
void treeToVector(Node* node, vector<Student>& students) {
    if (node == NULL) return;
    students.push_back(Student(node->studentId, node->name, node->age));
    treeToVector(node->left, students);
    treeToVector(node->right, students);
}

// Merge function - combines two sorted halves by student ID
void merge(vector<Student>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of left subarray
    int n2 = right - mid;      // Size of right subarray
    
    // Create temporary vectors
    vector<Student> leftArray, rightArray;
    
    // Copy data to temporary vectors
    for (int i = 0; i < n1; i++)
        leftArray.push_back(arr[left + i]);
    for (int i = 0; i < n2; i++)
        rightArray.push_back(arr[mid + 1 + i]);
    
    // Merge the temporary vectors back into arr[left..right]
    int i = 0;     // Initial index of left subarray
    int j = 0;     // Initial index of right subarray
    int k = left;  // Initial index of merged subarray
    
    while (i < n1 && j < n2) {
        if (leftArray[i].studentId <= rightArray[j].studentId) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of leftArray, if any
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of rightArray, if any
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

// Merge Sort function - recursively sorts by student ID
void mergeSort(vector<Student>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;
        
        // Sort first half
        mergeSort(arr, left, mid);
        
        // Sort second half
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Display sorted students
void displaySortedStudents(vector<Student>& students) {
    for (int i = 0; i < students.size(); i++) {
        cout << students[i].studentId << " - " << students[i].name 
             << " (Age: " << students[i].age << ")" << endl;
    }
}

// Cleanup memory
void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Enroll a single student
void enrollStudent(Node* root, int studentId, string name, int age) {
    root = insertNode(root, studentId, name, age);
}


//Display Choice
void displayMenu() {
    cout << "----- Register Office ------" << endl;
    cout << "1. View Student List" << endl;
    cout << "2. Enroll New Student" <<endl;
    cout << "3.Search Student by ID" <<endl;
    cout << "4.Remove Student by ID" <<endl;
    cout << "5.Sort Students by ID (Merge Sort)" << endl;
    cout << "0.Exit" <<endl;
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
                break;
            }
            case 2: {
                cout << "\nEnter Student ID: ";
                cin >> studentId;
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, name);
                cout << "Enter Student Age: ";
                cin >> age;
                node = insertNode(node, studentId, name, age);
                break;
            }
            
            case 3: {
                cout << "\nEnter Student ID to search: ";
                cin >> studentId;
                Node* result = search(node, studentId);
                if (result != NULL) {
                    cout << "Student Found: " << result->studentId << " - " 
                         << result->name << " (Age: " << result->age << ")" << endl;
                } else {
                    cout << "Student with ID " << studentId << " not found." << endl;
                }
                break;
            }
            
            case 4: {
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
                break;
            }
            
            case 5: {
                cout << "\nStudents Sorted by ID (Merge Sort)" << endl;
                vector<Student> students;
                treeToVector(node, students);
                if (students.size() > 0) {
                    mergeSort(students, 0, students.size() - 1);
                    displaySortedStudents(students);
                } else {
                    cout << "No students to sort." << endl;
                }
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