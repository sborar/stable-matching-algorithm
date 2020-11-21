/******************************************************************************
  Aalto University
  CS-E3190 Principles of Algorithmic Techniques
  Autumn 2020
  Exercise: Stable matching
  Description:
  This exercise asks you to implement an algorithm that computes a stable
  matching between $n$ applicants and $n$ positions. Each applicant
  $i=0,1,\ldots,n-1$ has preferences for each position $j=0,1,\ldots,n-1$,
  and vice versa. These preferences are given as input in two $n^2$-element
  arrays `a_pref` and `b_pref` so that applicant $i=0,1,\ldots,n-1$ prefers
  the $n$ available positions in order
  ``a_pref[i*n+0] > a_pref[i*n+1] > ... > a_pref[i*n+n-1]``,
  where `a_pref[i*n+0]` is the most preferred position, `a_pref[i*n+1]` is
  the next most preferred position, and so forth until the least preferred
  position `a_pref[i*n+n-1]`. Dually, position $j=0,1,\ldots,n-1$ prefers
  the applicants in order
  ``b_pref[j*n+0] > b_pref[j*n+1] > ... > b_pref[j*n+n-1]``,
  where `b_pref[j*n+0]` is the most preferred applicant, `b_pref[i*n+1]` is
  the next most preferred applicant, and so forth until the least preferred
  applicant `b_pref[i*n+n-1]`.
  The stable matching is output via the array `s` such that each applicant
  $i=0,1,\ldots,n-1$ is matched to the position `s[i]`. Accordingly,
  the entries `s[0],s[1],...,s[n-1]` must form a permutation of the
  integers $0,1,\ldots,n-1$. Furthermore, for all $i,j=0,1,\ldots,n-1$ such
  that $j\neq s[i]$ it must be that applicant $i$ prefers position $s[i]$
  over position $j$ or position $j$ prefers applicant $s^{-1}[j]$ over
  applicant $i$; indeed, otherwise the pair $(i,j)$ is unstable. Here we
  write $s^{-1}$ for the inverse permutation of $s$.
  **Your task** in this exercise is to complete the subroutine
  ``void solver(int n, const int *a_pref, const int *b_pref, int *s)``
  which should compute the array `s` from the given inputs `n`, `a_pref`, and
  `b_pref`. To locate the subroutine quickly, you can search for "`???`" in
  the source file. You may assume that $0\leq n\leq 2048$. The source file
  contains many subroutines that you may find useful in preparing your solution.
  For example, the subroutine `perm_inv` computes the inverse of a permutation.
  *Grading*. This exercise awards you up to 100 points in
  the course grading. The number of points awarded is the maximum points times
  the number of tests passed over the total number of tests, rounded up. To
  successfully complete a test, your implementation must use no more than
  3 seconds of wall clock time and 100 MiB of memory. Each test
  will in general require the successful solution of one or more problem
  instances. In each batch of scaling tests, the first failed test will
  cause all subsequent tests in the batch to be skipped.
******************************************************************************/

#include <iostream>
#include <queue>

// check whether the current candidate is better than the previous candidate
int check_if_better_candidate(const int * b_pref,int old_applicant, int current_applicant
        ,int  preferred_company, int n ){
    int position_pref_list_start_index = preferred_company * n + 0;
    int position_pref_list_end_index = position_pref_list_start_index + n;
    int better_candidate = 0;
    for(int i = position_pref_list_start_index; i < position_pref_list_end_index; i++ ){
        if(b_pref[i] == current_applicant){
            better_candidate = current_applicant;
            break;
        }
        else if(b_pref[i] == old_applicant){
            better_candidate = old_applicant;
            break;
        }
    }
    if(better_candidate == current_applicant){
        return true;
    }
    else{
        return false;
    }
}
void solver(int n, const int *a_pref, const int *b_pref, int *s)
{
//a_pref applicants preference
//b_pref positions preference
    std::vector<int> appForPos;
    for(int i = 0 ; i < n ; i++){
        appForPos.push_back(-1);
    }
    std::queue<int> applicantQueue;
    // initialise the applicant queue
    for(int i = 0 ; i < n ; i++){
        applicantQueue.push (i);
    }
    //  create a queue for each applicants preferences
    std::vector<std::queue<int>> forEachAppPref ;
    std::vector<std::queue<int>>::iterator queueListIt;
    for(int i = 0 ; i < n ; i++){
        std::queue<int> appPrefQueue;
        for(int pref_no = 0 ; pref_no < n ; pref_no++){
            appPrefQueue.push(a_pref[i * n + pref_no]);
        }
        forEachAppPref.push_back(appPrefQueue);
    }
    //this loop runs till stable match is obtained
    while(!applicantQueue.empty()) {
        int currentApplicant = applicantQueue.front();
        applicantQueue.pop();
        int preferredCompany = forEachAppPref[currentApplicant].front();
        forEachAppPref[currentApplicant].pop();
        int oldApplicant = appForPos[preferredCompany];
        if (oldApplicant == -1){
            appForPos[preferredCompany] = currentApplicant;
        }
        else if (check_if_better_candidate(b_pref, oldApplicant, currentApplicant, preferredCompany, n)) {
            appForPos[preferredCompany] = currentApplicant;
            applicantQueue.push(oldApplicant);
        }
        else{
            applicantQueue.push(currentApplicant);
        }
    }
    for(int i = 0 ; i < n ; i++){
        int applicant = appForPos[i];
        int company = i;
        s[applicant] = company;
    }
    std::cout<<" ";
}

int main()
{
    int n = 3;
    const int a_pref [9] = {2,1,0,2,1,0,2,1,0};
    const int b_pref [9] = {1,2,0,1,2,0,1,2,0};
    int s [3];
    solver(n, a_pref, b_pref, s);
    std::cout<<s[0]<<s[1]<<s[2];
    return 0;


}