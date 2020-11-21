# stable-matching-algorithm
Stable matching using queues

Problem definition: Implement an algorithm that computes a stable
  matching between n applicants and n positions. 
  
  Each applicant
  i=0,1,.....,n-1 has preferences for each position j=0,1,....,n-1,
  and vice versa. These preferences are given as input in two n^2-element
  arrays `a_pref` and `b_pref` so that applicant i=0,1,....,n-1 prefers
  the n available positions in order
  
  ``a_pref[i*n+0] > a_pref[i*n+1] > ... > a_pref[i*n+n-1]``,
  
  where `a_pref[i*n+0]` is the most preferred position, `a_pref[i*n+1]` is
  the next most preferred position, and so forth until the least preferred
  position `a_pref[i*n+n-1]`. Dually, position j=0,1,....,n-1 prefers
  the applicants in order
  
  ``b_pref[j*n+0] > b_pref[j*n+1] > ... > b_pref[j*n+n-1]``,
  
  where `b_pref[j*n+0]` is the most preferred applicant, `b_pref[i*n+1]` is
  the next most preferred applicant, and so forth until the least preferred
  applicant `b_pref[i*n+n-1]`.
  
  
  The stable matching is output via the array `s` such that each applicant
  i=0,1,....,n-1 is matched to the position `s[i]`. Accordingly,
  the entries `s[0],s[1],...,s[n-1]` must form a permutation of the
  integers 0,1,....,n-1. Furthermore, for all i,j=0,1,....,n-1 such
  that j\neq s[i] it must be that applicant i prefers position s[i]
  over position j or position j prefers applicant s^{-1}[j] over
  applicant i; indeed, otherwise the pair (i,j) is unstable. Here we
  write s^{-1} for the inverse permutation of s.
  
  Algorithm:
  
  Create a queue for each applicants prefrences.
  Create a applicant queue.
  Go through applicant queue, pop the first applicant.
  Find the preference queue of the applicant and pop the first preference.
  
  If another applicant was already selected for the position then we check which applicant is preffered by the company, if not we assign this applicant to the company position.
  We follow this approach till the applicant queue is empty to get a stable matching.
  
Just run main.cpp and change the arguments in main to get stable matching for your own example.
