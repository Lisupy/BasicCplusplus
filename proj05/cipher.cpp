#include <string>
#include <cstring>
#include <iostream>

using std::string;

const char BASE = 'a';


inline size_t CellToIndex(size_t x, size_t y){
    return x + 5 * y;
}

inline size_t IndexToCellX(size_t index){
    return index % 5;
}

inline size_t IndexToCellY(size_t index){
    return index / 5;
}


/* Create a flatten encode matrix*/
string CreateSquare(const string &keyword){
    bool record_arr[26];
    string flatten_square;
    std::memset(record_arr, false, sizeof(record_arr));
    for(const auto &item: keyword){
        if(record_arr[item-BASE] == false){
            record_arr[item-BASE] = true;
            flatten_square+=item;
        }
    } 
    for(size_t i=0; i != 26; ++i){
        if(record_arr[i] == false){
            char letter = char(BASE + i);
            if (letter == 'j')
                continue;
            flatten_square += letter;
        }
    }
    return flatten_square;
}

string EncodeString(const string &plaintext, const string &keyword){
    auto square = CreateSquare(keyword);
    string ciphertext = plaintext;
    if (ciphertext.length() % 2)
        ciphertext += 'x';

    for(auto it = ciphertext.begin(); it != ciphertext.end(); ++it){
        auto letter1 = it;
        auto letter2 = ++it;
        if (*letter1 == *letter2)
            *letter2 = 'x';
        if(*letter1 == 'j')
            *letter1 = 'i';
        if(*letter2 == 'j')
            *letter2 = 'i';
        
        auto index_letter1 = square.find(*letter1);
        auto index_letter2 = square.find(*letter2);
        
        auto x_letter1 = IndexToCellX(index_letter1);
        auto y_letter1 = IndexToCellY(index_letter1);
        auto x_letter2 = IndexToCellX(index_letter2);
        auto y_letter2 = IndexToCellY(index_letter2);
        
        size_t target1 = 0, target2 = 0;
        if (x_letter1 == x_letter2){
            auto col1 = ++y_letter1 % 5;
            auto col2 = ++y_letter2 % 5;
            target1 = CellToIndex(x_letter1, col1);
            target2 = CellToIndex(x_letter2, col2); 
        }
        else if(y_letter1 == y_letter2){
            auto row1 = ++x_letter1 % 5;
            auto row2 = ++x_letter2 % 5;
            target1 = CellToIndex(row1, y_letter1);
            target2 = CellToIndex(row2, y_letter2);
        }
        else{
            target1 = CellToIndex(x_letter1, y_letter2);
            target2 = CellToIndex(x_letter2, y_letter1);
        }
        *letter1 = square[target1];
        *letter2 = square[target2];
    }
    return ciphertext;
}

string DecodeString(const string &ciphertext, const string &keyword){
    auto square = CreateSquare(keyword);
    string plaintext = ciphertext;
    for (auto it  = plaintext.begin(); it != plaintext.end(); ++it){
        auto letter1 = it;
        auto letter2 = ++it;
         
        auto index_letter1 = square.find(*letter1);
        auto index_letter2 = square.find(*letter2);
        
        auto x_letter1 = IndexToCellX(index_letter1);
        auto y_letter1 = IndexToCellY(index_letter1);
        auto x_letter2 = IndexToCellX(index_letter2);
        auto y_letter2 = IndexToCellY(index_letter2);

        size_t target1 = 0, target2 = 0;
        if (x_letter1 == x_letter2){
            auto col1 = (--y_letter1+5) % 5;
            auto col2 = (--y_letter2+5) % 5;
            target1 = CellToIndex(x_letter1, col1);
            target2 = CellToIndex(x_letter2, col2); 
        }
        else if(y_letter1 == y_letter2){
            auto row1 = (--x_letter1+5) % 5;
            auto row2 = (--x_letter2+5) % 5;
            target1 = CellToIndex(row1, y_letter1);
            target2 = CellToIndex(row2, y_letter2);
        }
        else{
            target1 = CellToIndex(x_letter1, y_letter2);
            target2 = CellToIndex(x_letter2, y_letter1);
        }
        *letter1 = square[target1];
        *letter2 = square[target2];
    }
    return plaintext;
}


//int main(){
    //std::string keyword = "squarecipher";
    //std::cout << CreateSquare(keyword) << std::endl;
    //std::string plaintext = "runfast";
    //std::string ciphertext = EncodeString(plaintext, keyword);
    //std::string recover = DecodeString(ciphertext, keyword);
    //std::cout << ciphertext << std::endl;
    //std::cout << recover << std::endl;
//}
