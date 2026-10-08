#include "Combi.h"  
#include <algorithm> 
#define NINF  ((short)0x8000) 

namespace combi { 

    //подмножества

    void subset::reset() {
        this->sn = 0;    
        this->mask = 0;   
    }

    
    subset::subset(short n) {
        this->n = n;               
        this->sset.resize(n);       
        this->reset();              
    }

    short subset::getfirst() {
        long long buf = this->mask; 
        this->sn = 0;                
        for (short i = 0; i < n; i++) { 
            if (buf & 0x1) {          
                this->sset[this->sn++] = i; 
            }
            buf >>= 1;                 
        }
        return this->sn;               
    }

    short subset::getnext() {
        int rc = -1;       
        this->sn = 0;      
        if (++this->mask < this->count()) { 
            rc = getfirst();                 
        }
        return rc;         
    }

    short subset::ntx(short i) {
        return this->sset[i]; 
    }

    unsigned long long subset::count() {
        return (unsigned long long)(1 << this->n); 
    }




    //сочетания

    xcombination::xcombination(long long n, long long m) {
        this->n = n;               
        this->m = m;               
        this->sset.resize(m + 2);   
        this->reset();              
    }

    void xcombination::reset() {
        this->nc = 0;                         
        for (int i = 0; i < this->m; i++) {   
            this->sset[i] = i;
        }
        this->sset[m] = this->n;               
        this->sset[m + 1] = 0;                 
    }

    long long xcombination::getfirst() {
        
        return (this->n >= this->m) ? this->m : -1;
    }

    long long xcombination::getnext() {
        long long rc = getfirst(); 
        if (rc > 0) {              
            long long j;
            for (j = 0; this->sset[j] + 1 == this->sset[j + 1]; j++) {
                this->sset[j] = j; 
            }
            if (j >= this->m) {     
                rc = -1;
            }
            else {                   
                this->sset[j]++;
                this->nc++;         
            }
        }
        return rc;                   
    }

    long long xcombination::ntx(short i) {
        return this->sset[i];
    }

    unsigned long long fact(unsigned long long x) {
        return (x == 0) ? 1 : (x * fact(x - 1));
    }

    unsigned long long xcombination::count() {
        return (this->n >= this->m) ? fact(this->n) / (fact(this->n - this->m) * fact(this->m)) : 0;
    }




    //перестановки

    permutation::permutation(short n) {
        this->n = n;               
        this->sset.resize(n);       
        this->dart.resize(n);       
        this->reset();             
    }

    void permutation::reset() {
        this->getfirst(); 
    }

    long long permutation::getfirst() {
        this->np = 0;                      
        for (int i = 0; i < this->n; i++) {
            this->sset[i] = i;               
            this->dart[i] = L;                
        }
        return (this->n > 0) ? this->np : -1; 
    }

    short permutation::ntx(short i) {
        return this->sset[i];
    }

    
    long long permutation::count() {
        return fact(this->n);
    }

   
    long long permutation::getnext() {
        long long rc = -1;          
        short maxm = NINF;           
        short idx = -1;              

        
        for (int i = 0; i < this->n; i++) {

            if (i > 0 && this->dart[i] == L && this->sset[i] > this->sset[i - 1] &&
                maxm < this->sset[i]) {
                maxm = this->sset[idx = i]; 
            }
            if (i < (this->n - 1) && this->dart[i] == R && this->sset[i] > this->sset[i + 1] &&
                maxm < this->sset[i]) {
                maxm = this->sset[idx = i];
            }
        }

        if (idx >= 0) { 
            std::swap(this->sset[idx], this->sset[idx + (this->dart[idx] == L ? -1 : 1)]);

            bool temp = dart[idx];
            bool temp2 = dart[idx + (dart[idx] == L ? -1 : 1)];
            dart[idx + (dart[idx] == L ? -1 : 1)] = temp;
            dart[idx] = temp2;

            for (int i = 0; i < this->n; i++) {
                if (this->sset[i] > maxm) {
                    this->dart[i] = !this->dart[i];
                }
            }

            rc = ++this->np; 
        }
        return rc; 
    }




    //размещения

    accomodation::accomodation(short n, short m) {
        this->n = n;                    
        this->m = m;                     
        this->cgen = new xcombination(n, m); 
        this->pgen = new permutation(m);     
        this->sset.resize(m);              
        this->reset();                     
    }

    void accomodation::reset() {
        this->na = 0;          
        this->cgen->reset();   
        this->pgen->reset();   
        this->cgen->getfirst();
    }

    short accomodation::getfirst()
    {
        short rc = (this->n >= this->m) ? this->m : -1; 
        if (rc > 0) 
        {
            for (int i = 0; i < this->m; i++)
                this->sset[i] = this->cgen->sset[this->pgen->ntx(i)];
        }
        return rc; 
    }
//
    short accomodation::getnext()
    {
        short rc;
        this->na++; 

        if ((this->pgen->getnext()) > 0)
            rc = this->getfirst(); 
        else if ((rc = this->cgen->getnext()) > 0)
        {
            this->pgen->reset();   
            rc = this->getfirst(); 
        }
        return rc;
    }

    short accomodation::ntx(short i)
    {
        return this->sset[i];
    }

    unsigned long long accomodation::count()
    {
        return (this->n >= this->m) ? fact(this->n) / fact(this->n - this->m) : 0;
    }

} 