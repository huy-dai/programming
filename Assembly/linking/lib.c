int factorial(int base) {
    int res = 1, i = 1;
    if(base == 0) {
        return 1;
    }
    while (i <= base){
        res *= i;
        i++;
    }

    return res;
}