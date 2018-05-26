#include <iostream>

long Binom(const long &n, const long &k){
    long long denominator=1, molecular=1;
    for(int i=1; i<=k; ++i){
        molecular *= (n+1-i);
        denominator *= i;
        
        if (molecular % denominator == 0){ // avoid overflow
            molecular /= denominator;
            denominator = 1;
        }
    }
    return molecular;
}

long Catalan(const long &n){
    return Binom(2*n, n) / (n+1);
}

long Motzkin(const long &n){
    long terminate = n / 2;
    long motzkin = 0;
    for (int k=0; k<=terminate; ++k){
        motzkin += Binom(n, 2*k) * Catalan(k);
    }
    return motzkin;
}

int main(){
    std::cout << "====== Motzkin Numbers ======" << std::endl;
    for(int i=0; i<30; ++i){
        std::cout <<Motzkin(i) << std::endl;
    }
    std::cout << "====== Catalan Numbers ======" << std::endl;
    for(int i=0; i<30; ++i){
        std::cout << Catalan(i) << std::endl;
    }
}
