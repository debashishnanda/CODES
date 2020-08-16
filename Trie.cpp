#include <bits/stdc++.h>
using namespace std;

struct Trienode
{
    char val;
    int count;
    int endsHere;
    Trienode *child[26];
};

//--------------------------------------------CREATING A NEW NODE--------------------------------------------------//

Trienode *getNode(int index)
{
    Trienode *newnode = new Trienode;
    newnode->val = 'a'+index;
    newnode->count = newnode->endsHere = 0;
    for(int i=0;i<26;++i)
        newnode->child[i] = NULL;
    return newnode;
}
Trienode *root = getNode('*');

//------------------------------------------INSERTING WORDS TO TRIE------------------------------------------------//

void insert(string word) {
    Trienode *curr = root;
    int index;
    for(int i=0;word[i]!='\0';++i)
    {
        index = word[i]-'a';
        if(curr->child[index]==NULL)
            curr->child[index] = getNode(index);
        curr->child[index]->count +=1;
        curr = curr->child[index];
    }
    curr->endsHere +=1;
}

//------------------------------------------CHECK IF WORD IS PRESENT-----------------------------------------------//

bool search(string word) {
    Trienode *curr = root;
    int index;
    for(int i=0;word[i]!='\0';++i)
    {
        index = word[i]-'a';
        if(curr->child[index]==NULL)
            return false;
        curr = curr->child[index];
    }
    return (curr->endsHere > 0);
}

//--------------------------------FUNCTION TO PRINT ALL WORDS WITH GIVEN PREFIX------------------------------------//
/**
 * WHEN TYPING FOR EXAMPLE =====>  a..
 * print                    ====>  a, any, answer
 * 
 * 
 *                          ====>  t..
 *                          ====>  the, their, there
 */

void display(Trienode* curr, string str) 
{ 
    if (curr->endsHere > 0)
        cout << str << endl; 
  
    int i; 
    for (i = 0; i < 26; i++)  
    { 
        if (curr->child[i])  
        { 
            display(curr->child[i], str+char(i+'a')); 
        } 
    } 
} 

bool startsWith(string prefix) {
    Trienode *curr = root;
    int index;
    for(int i=0;prefix[i]!='\0';++i)
    {
        index = prefix[i]-'a';
        if(curr->child[index]==NULL)
            return false;
        curr = curr->child[index];
    }
    display(curr,prefix);
    return (curr->count > 0);
}

//--------------------------------------------------MAIN FUNCTION--------------------------------------------------

int main() 
{ 
    vector<string> words = { "the", "a", "there", "answer", "any", "by", "bye", "their" }; 
    for (int j = 0; j < words.size(); j++) 
        insert(words[j]);
    
    cout<<startsWith("t");
    return 0;
} 