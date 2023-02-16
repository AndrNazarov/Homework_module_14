#pragma once
#include<iostream>

#define ALPHABET_SIZE 26

struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
	int freq; 
};

class Trie
{
	TrieNode* getNewNode(void);
	TrieNode* root;

public:
	Trie() 
	{
		root = getNewNode();
	}

	~Trie() {};

	TrieNode* getRoot();

	void insert(TrieNode* root, std::string& key);

	bool search(struct TrieNode* root, std::string key);

	bool isEmpty(TrieNode* root);

	TrieNode* remove(TrieNode* root, std::string key, int depth);

	std::string searchWordByPrefix(std::string prefix);

	std::string completeWordByPrefix(std::string prefix);
};