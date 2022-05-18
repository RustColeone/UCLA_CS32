// Return false if the somePredicate function returns true for at
// least one of the array elements; return true otherwise.
bool allFalse(const string a[], int n)
{
    if (n <= 0)
        return true;
    bool status = allFalse(a + 1, n - 1);
    if (somePredicate(*a)) {
        return status && false;
    }
    return status && true;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    if (n <= 0)
        return 0;
    int counted = countFalse(a + 1, n - 1);
    if (!somePredicate(*a)) {
        return 1 + counted;
    }
    return counted;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    if (n <= 0)
        return -1;
    int position = firstFalse(a + 1, n - 1);
    if (position == -1) {
        if (somePredicate(*a)) {
            //if nothing encountered continue
            return -1;
        }
        else {
            //Start counting backwards
            return 0;
        }
    }
    if (somePredicate(*a)) {
        //if we did not encounter a false but did in the past, count up
        return position + 1;
    }
    //if encounter a false, reset and start counting again
    return 0;
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no strings are to
// be considered in the array, return -1.
int positionOfLeast(const string a[], int n)
{
    if (n <= 0)
        return -1;

    if (n == 1)
        return 0;
    //BST is king!
    int minL = positionOfLeast(a, n / 2);
    int minR = positionOfLeast(a + n / 2, n - n / 2) + n / 2;
    if (a[minL] < a[minR]) {
        return minL;
    }
    else {
        return minR;
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "merida" "tiana" "raya" "belle" "tiana" "raya" "moana"
// then the function should return true if a2 is
//    "tiana" "belle" "moana"
// or
//    "tiana" "raya" "raya"
// and it should return false if a2 is
//    "tiana" "moana" "belle"
// or
//    "merida" "belle" "belle"
bool has(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0) {
        return true;
    }
    if (n1 < n2) {
        return false;
    }
    if (a1[0] == a2[0]) {
        return has(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    return has(a1 + 1, n1 - 1, a2, n2);
}