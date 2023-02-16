#include "Trie.h"


TrieNode* Trie::getNewNode(void)
{
    
    struct TrieNode* pNode = new TrieNode;
    
    pNode->isEndOfWord = false;
    
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;
    return pNode;
}

TrieNode* Trie::getRoot()
{
    return root;
}

void Trie::insert(TrieNode* root, std::string& key)
{
    TrieNode* currentNode = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = key.at(i) - 'a';
        if (currentNode->children[index] == NULL)
        { 
            currentNode->children[index] = getNewNode(); 
            currentNode->children[index]->freq = 1;
        }
        else
        {
            currentNode->children[index]->freq++;
        }
        currentNode = currentNode->children[index];
    }
    
    currentNode->isEndOfWord = true;
    return;
}

bool Trie::search(struct TrieNode* root, std::string key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

bool Trie::isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
        {
            return false;
        }
    return true;
}

TrieNode* Trie::remove(TrieNode* root, std::string key, int depth = 0)
{
    if (!root)
        return nullptr;
   
    if (depth == key.size()) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;
       
        if (isEmpty(root)) 
        {
            delete (root);
            root = nullptr;
        }
        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
   
    if (isEmpty(root) && root->isEndOfWord == false) 
    {
        delete (root);
        root = nullptr;
    }
    return root;
}

std::string Trie::searchWordByPrefix(std::string prefix)
{
    std::string result;
    TrieNode* node = root;
    for (int i = 0; i < prefix.size(); i++)
    {
        int index = prefix[i] - 'a';

        if (!node->children[index])
            return "";

        result += prefix[i];
        node = node->children[index];
    }
    
    while (!node->isEndOfWord)
    {
        char ch = 0; 
        while (node->children[ch] == NULL) 
        {
            ch++;
        }
        result += ch + 'a';
        node = node->children[ch];
    }
    return result;
}

std::string Trie::completeWordByPrefix(std::string prefix)
{
    TrieNode* node = root;
    for (int i = 0; i < prefix.size(); i++)
    {
        int index = prefix[i] - 'a';

        if (!node->children[index])
            return "";

        node = node->children[index];
    }
    
    std::string result;

    while (!node->isEndOfWord) 
    {
        char ch = 0;
        while (node->children[ch] == NULL) 
        {
            ch++;
        }
        result += ch + 'a';
        node = node->children[ch];
    }
    return result;
}