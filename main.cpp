#include <iostream>
#include <cstring>
#include "SHA1.hpp"
#include "SHA1.cpp"
#define MAX 1000
using namespace std;

struct Block { // here is the structure of block
    string Data;  // The data that the user wants to enter(store)
    int Number; // the index of the blocks
    string p_hash; // previous hash value
    string hash; // hash value
};

struct Blockchain{ // here is the structure of blockchain which is including blocks
    struct Block BlockArray[MAX]; // By default, 1000 blocks can be added
    int m_Size;
};

void showMenu(){ // display the menu
    cout << "******************************************************************************************" << endl;
    cout << "**************************************** Blockchain **************************************" << endl;
    cout << "********* This is the blockchain menu, you can run related functions by number ***********" << endl;
    cout << "*                                  1. Add a new block                                    *" << endl;
    cout << "*                                  2. Search block by given information                  *" << endl;
    cout << "*                                  3. Check the integrity of the data                    *" << endl;
    cout << "*                                  0. Exit the program                                   *" << endl;
    cout << "******************************************************************************************" << endl;
    cout << endl;
}

void addBlocks(Blockchain * blo){ // This is the function to add blocks
    if (blo -> m_Size == MAX) { // Blocks cannot be added if they reach 1000
        cout << "Adding failure!" << endl;
        return;
    }
    else{
        cout << "Enter the number of blocks you want to add: ";
        int addNum = 0; // Initialize the number of blocks that user want to add
        cin >> addNum;
        if (addNum > 0){
            // Calculate the new space size, the adding number should not be negative
            int newSize; // 0
            newSize = blo->m_Size + addNum;
            string data = ""; // Initialize the data of block
            string p_hash = ""; // Initialize the previous hash of block
            
            if (blo->m_Size != 0){
                p_hash = blo->BlockArray[blo->m_Size - 1].hash; // in case previous hash become the initialize value
            }
            
            for (int i = blo->m_Size; i < newSize; i++) { // i = 0, i < 2
                cout << endl;
                cout<<"***** Please enter the information of block No."<<i+1<<" *****"<<endl;
                cout<<"\tPlease enter the data: "; cin >> data;
                cout << endl;
                
                string input(data);
                SHA1 checksum;
                checksum.update(input);
                char hash[41];
                strcpy(hash, checksum.final().c_str());
                
                blo -> BlockArray[i].Data = data;
                blo -> BlockArray[i].Number = i+1;
                blo -> BlockArray[i].p_hash = p_hash;
                blo -> BlockArray[i].hash = hash;
                
                p_hash = hash;
                blo -> m_Size++; // the size of block could plus 1 after adding 1 block.
            }
            cout << "You have added " << addNum << " block(s) successfully!!!" << endl;
            
        }
        else{
        cout << "Incorrect input!" << endl;
        }
    }
    
}

void findBlock(Blockchain * blo){   // display the chain data in a number of ways
                                    // by block number
                                    // the data of the whole chain
                                    // the hash values of a particular block
    
    if (blo->m_Size == 0){ // if the size of block is zero, output Empty!
        cout << "Empty!!" << endl;
    }
    else{
        cout << "1.Search by block number" << endl;
        cout << "2.Search by the data of the whole chain" << endl;
        cout << "3.Search by the hash values of a particular block" << endl;
        cout << endl;
        cout << "Please enter the search method: ";
        int select;
        int S_number; // initialize the block number that user will input
        string data;
        string hash;
        cin >> select;
        if (select == 1) { // Search by block number
            cout << endl;
            cout << "Please enter the block number you are looking for: ";
            cin >> S_number; // let user input the block number they want to search
            if (blo->m_Size == 0){
                cout << "Empty!!" << endl;
            }
            else{ // Display the informations of the block that the user wants to see according to the block number entered by the user
                cout << "************************************************************************" << endl;
                cout << "***************** Here is the information of block " << S_number << " *****************" << endl;
                cout << "*                                                                      *" << endl;
                cout << "\tNumber: " << blo->BlockArray[S_number-1].Number << endl;
                cout << "\tData: " << blo->BlockArray[S_number-1].Data << endl;
                cout << "\tHash value: " << blo->BlockArray[S_number-1].hash << endl;
                cout << "\tPrevious hash value: " << blo->BlockArray[S_number-1].p_hash << endl;
                cout << "*                                                                      *" << endl;
                cout << "************************************************************************" << endl;
            }
            cout << endl;
            
        }
        else if (select == 2){ // Search by the data of the whole chain
            cout << endl;
            cout << "Please enter the data of the block you are looking for: ";
            cin >> data;
            if (blo->m_Size == 0){ // if the size of block is zero, output Empty!
                cout << "Empty!!" << endl;
            }
            else {
                // Display the informations of the block that the user wants to see according to the block data entered by the user
                for (int i = 0; i < blo->m_Size; i++){
                    if (blo->BlockArray[i].Data == data) {
                        cout << "************************************************************************" << endl;
                        cout << "***************** Here is the information of block " << i+1 << " *****************" << endl;
                        cout << "*                                                                      *" << endl;
                        cout << "\tNumber: " << blo->BlockArray[i].Number << endl;
                        cout << "\tData: " << blo->BlockArray[i].Data << endl;
                        cout << "\tHash value: " << blo->BlockArray[i].hash << endl;
                        cout << "\tPrevious hash value: " << blo->BlockArray[i].p_hash << endl;
                        cout << "*                                                                      *" << endl;
                        cout << "************************************************************************" << endl;
                    }
                        
                }
            }
            
        }
        else if (select == 3){ // Search by the hash values of a particular block
            cout << endl;
            cout << "Please enter the hash value of the block you are looking for: ";
            cin >> hash;
            if (blo->m_Size == 0){ // if the size of block is zero, output Empty!
                cout << "Empty!!" << endl;
            }
            else {
                // Display the informations of the block that the user wants to see according to the hash values of a particular block entered by the user
                for (int i = 0; i < blo->m_Size; i++){
                    if (blo->BlockArray[i].hash == hash) {
                        cout << "************************************************************************" << endl;
                        cout << "***************** Here is the information of block " << i+1 << " *****************" << endl;
                        cout << "*                                                                      *" << endl;
                        cout << "\tNumber: " << blo->BlockArray[i].Number << endl;
                        cout << "\tData: " << blo->BlockArray[i].Data << endl;
                        cout << "\tHash value: " << blo->BlockArray[i].hash << endl;
                        cout << "\tPrevious hash value: " << blo->BlockArray[i].p_hash << endl;
                        cout << "*                                                                      *" << endl;
                        cout << "************************************************************************" << endl;
                    }
                }
            }
            
        }
        
        else{
            cout << "Input wrong or empty information!" << endl;
        }
    }
    
    
}

void Check_integrity(Blockchain * blo){ // Check the integrity of the data
    
    if (blo->m_Size == 0){ // if the size of block is zero, output Empty!
        cout << "Empty!!" << endl;
    }
    else {
        bool check = true; // Initialize a Boolean value
        for (int i = 0; i < blo->m_Size-1; i++) { // Check all hash values, compare with their previous hash values
            if (blo->BlockArray[i+1].p_hash != blo->BlockArray[i].hash) {
                check = false;
            }
        }
        cout << endl;
        if (check) { // output the integrity according to the Boolean value
            cout << "\tThe blocks are integral" << endl;
        }
        else{
            cout << "\tThe blocks are NOT integral!!!" << endl;
        }
        cout << endl;
        cout << "Below is all hash value of the blockchain: " << endl; // display all the hash values and previous hash values to user for better understanding of the integrity of the blockchain
        for (int i = 0; i < blo->m_Size; i++){
            cout << "\tHash value: " << blo->BlockArray[i].hash << endl;
            cout << "\tPrevious hash value: " << blo->BlockArray[i].p_hash << endl;
            cout << endl;
        }
    }
}

int main(){
    Blockchain blo; // naming structure
    blo.m_Size = 0; // Initialize the size of blocks
    int select = 0;
    while (true){
        showMenu();
        cout << "Enter the number of the Menu number: "; cin >> select;
        switch (select) {
            case 1:
                addBlocks(&blo); // This is the function to add blocks
                break;
            case 2:
                findBlock(&blo); // display the chain data in a number of ways by block number, the data of the whole chain or the hash values of a particular block
                break;
            case 3:
                Check_integrity(&blo); // check the integrity of the blocks
                break;
            case 0: // enter 0 to end the program
                cout << "Thank you for using." << endl;
                return 0;
                break;
                
            default:
                cout << "Please enter correct a number!" << endl;
        }
    }

    return 0;
}


