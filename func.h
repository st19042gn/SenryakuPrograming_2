int MAX(int a, int b, int c){
    int ret;
    if(a >= b) ret = a;
    else       ret = b;
    if(ret < c) ret = c;

    return ret;
}