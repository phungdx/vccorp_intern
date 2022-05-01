#include"hash.h"


hashTable::hashTable(){
	for(int i = 0; i < tableSize; ++i){
		Buckets[i] = new item;
		Buckets[i]->name = "empty";
		Buckets[i]->drink = "empty";
		Buckets[i]->next = NULL;
	}
}


hashTable::~hashTable(){
   item* curr;
   for(int i = 0;i < tableSize; i++)
   {
      while(Buckets[i] != NULL)
      {
	    curr = Buckets[i];
	    Buckets[i] = Buckets[i]->next;
	    delete curr;
      }
   }
}

int hashTable::hashFunc(string key){
	int hashVal = 0;
	int index;

	int n = key.length();

	for(int i = 0; i < n; ++i){
		hashVal += (int)key[i];
	}

	index = hashVal % tableSize;
	return index;

}

void hashTable::addItem(string name, string drink){
	int index = hashFunc(name);
	if(Buckets[index]->name == "empty"){
		Buckets[index]->name = name;
		Buckets[index]->drink = drink;
	}

	else{

		item* curr = Buckets[index];
		item* newItem = new item;
		newItem->name = name;
		newItem->drink = drink;
		newItem->next = NULL;
		while(curr->next)
			curr = curr->next;

		curr->next = newItem;
	}
}

int hashTable::numberOfItemsInIndex(int index){
	int count = 0;

	if(Buckets[index]->name == "empty") return count;

	item* curr = Buckets[index];
	while(curr->next){
		++count;
		curr = curr->next;
	}
	return count + 1;

}

void hashTable::printTable(){
	int number;
	for(int i = 0; i < tableSize; ++i){
		number = numberOfItemsInIndex(i);
		cout << "-----------------------\n";
		cout << "index = " << i << '\n';
		cout << Buckets[i]->name << '\n';
		cout << Buckets[i]->drink << '\n';
		cout << "Number of items: " << number << '\n';
		cout << "-----------------------\n";
	}
}

void hashTable::printItemsInIndex(int index){
	item* curr = Buckets[index];
	if(curr->name == "empty"){
		cout << "Bucket " << index << " is empty" << '\n';
		return;
	}
	cout << "Bucket " << index << " contains the following items:" << '\n';
	while(curr){
		cout << "--------------\n";
		cout << curr->name << '\n';
		cout << curr->drink << '\n';
		cout << "--------------\n";
		curr = curr->next;
	}
}