#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct TreeNode {
    string name;        
    int page_count;       
    vector<TreeNode*> children;  

    TreeNode(string n, int pages) : name(n), page_count(pages) {}
};

class Book {
private:
    TreeNode* root;  

    int countChapters(TreeNode* node) {
        if (node == nullptr) return 0;
        int count = (node->children.empty() ? 1 : 0); 
        for (auto child : node->children) {
            count += countChapters(child);
        }
        return count;
    }

    int findLongestChapter(TreeNode* node, string &longest_chapter) {
        if (node == nullptr) return 0;
        int max_pages = node->page_count;
        longest_chapter = node->name;

        for (auto child : node->children) {
            string temp_chapter;
            int child_max = findLongestChapter(child, temp_chapter);
            if (child_max > max_pages) {
                max_pages = child_max;
                longest_chapter = temp_chapter;
            }
        }

        return max_pages;
    }

    bool deleteNode(TreeNode* &node, const string &name) {
        if (node == nullptr) return false;
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            if ((*it)->name == name) {
                delete (*it);  
                node->children.erase(it);  
                return true;
            }
        }

        for (auto &child : node->children) {
            if (deleteNode(child, name)) {
                return true;
            }
        }

        return false;  
    }

public:
    Book(string root_name) {
        root = new TreeNode(root_name, 0);
    }  
    
    TreeNode* getRoot() {
        return root;
    }  
    
    void addChapter(TreeNode* parent, string name, int pages) {
        parent->children.push_back(new TreeNode(name, pages));
    }

    int getChapterCount() {
        return countChapters(root);
    }

    void findLongestChapter() {
        string longest_chapter;
        int max_pages = findLongestChapter(root, longest_chapter);
        cout << "Longest chapter is: " << longest_chapter << " with " << max_pages << " Page." << endl;
    }

    void deleteChapter(string name) {
        if (deleteNode(root, name)) {
            cout << "Deleted: " << name << endl;
        } else {
            cout << "Not found: " << name << endl;
        }
    }

    void printBook(TreeNode* node, int depth = 0) {
        if (node == nullptr) return;
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << node->name << " - " << node->page_count << " Page" << endl;
        for (auto child : node->children) {
            printBook(child, depth + 1);
        }
    }

    void printBook() {
        printBook(root);
    }

    ~Book() {
        delete root;  
    }
};

int main() {
    Book book("Book");

    TreeNode* chapter1 = new TreeNode("Chapter 1", 30);
    book.addChapter(book.getRoot(), "Chapter 1", 30);
    book.addChapter(book.getRoot(), "Chapter 2", 40);
    book.addChapter(book.getRoot(), "Chapter 3", 50);
    book.addChapter(book.getRoot(), "Chapter 4", 25);

    book.addChapter(chapter1, "Part 1.1", 10);
    book.addChapter(chapter1, "Part 1.2", 20);

    cout << "Book structure: " << endl;
    book.printBook();

    cout << "No of chapter: " << book.getChapterCount() << endl;

    book.findLongestChapter();

    book.deleteChapter("Part 1.1");

    cout << "Structure after delete: " << endl;
    book.printBook();

    return 0;
}
