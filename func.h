int MAX(int a, int b, int c){
    int ret;
    if(a >= b) ret = a;
    else       ret = b;
    if(ret < c) ret = c;

    return ret;
}

double calcTrust(int id, int *h, int round, int n){
    double ret = 30.0;
    int i = 1;

    while(round > i){
        if(i > n) break;
        ret -= *(h+2*(round-i)+(id^1));
        i++;
    }
    return (ret /= (double)n);
}

int isSippe(int *h, int round, int ID){
    int sippe;
    
}