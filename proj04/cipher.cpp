#include <string>
using std::string;

const char BASE = 'a';

char EncodeLetter(char plain, char key){
    char temp1 = plain - BASE;
    char temp2 = key - BASE;
    return (temp1 + temp2) % 26 + BASE;
}

char DecodeLetter(char cipher, char key){
    char temp1 = cipher - BASE;
    char temp2 = key - BASE;
    return (26 + temp1 - temp2) % 26 + BASE;
}

string EncodeString(const string &plaintext, const string &keyword){
    string encode = plaintext;
    auto keyword_it = keyword.begin();
    for(auto it = encode.begin(); it != encode.end(); ++it){
        *it = EncodeLetter(*it, *keyword_it);
        ++keyword_it;
        if(keyword_it == keyword.end())
            keyword_it = keyword.begin();
    }
    return encode;
}

string DecodeString(const string &ciphertext, const string &keyword){
    string decode = ciphertext;
    auto keyword_it = keyword.begin();
    for(auto it = decode.begin(); it != decode.end(); ++it){
        *it = DecodeLetter(*it, *keyword_it);
        ++keyword_it;
        if (keyword_it == keyword.end())
            keyword_it = keyword.begin();
    }
    return decode;
}

