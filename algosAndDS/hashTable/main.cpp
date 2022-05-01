#include "hash.cpp"

int main(){
    hashTable myHash;
    myHash.addItem("Paul", "Locha");
    myHash.addItem("Kim", "Iced Mocha");
    myHash.addItem("Chan", "Boba");
    myHash.addItem("Lan", "Tea");
    myHash.addItem("Kai", "Sting");
    myHash.addItem("Han", "Red bull");
    myHash.addItem("Lee", "Milk");
    myHash.addItem("Phung", "Beer");
    myHash.addItem("Phuong", "Cocktail");
    myHash.addItem("Thu", "Wine");
    myHash.printTable();
    myHash.printItemsInIndex(9);
    return 0;
}