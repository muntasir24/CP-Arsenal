
strcasecmp(s1, s2)  // compare string without case sensitive 
____________________________________________________________________________________________________________________________________________________________________________________________

s1.compare(s2)      //compare string with case sensitive 
____________________________________________________________________________________________________________________________________________________________________________________________

s.erase(0, 1)        // remove 1 char from postion 0  moon-> oon
____________________________________________________________________________________________________________________________________________________________________________________________

transform(s.begin(), s.end(), s.begin(), ::tolower)  //convert string to lowercase  BAC->bac
 ____________________________________________________________________________________________________________________________________________________________________________________________

reverse(s.begin(), s.end())                         // reverse string  BAC-> CAB
____________________________________________________________________________________________________________________________________________________________________________________________

sort(s.begin(), s.end())                               // sort_string  bac-> abc
____________________________________________________________________________________________________________________________________________________________________________________________

if (s1.find(s2) != string::npos) cout<<"YES"<<'\n';     //check s2 strings element have in s1, check substring s1=moon s2=oo return yes
____________________________________________________________________________________________________________________________________________________________________________________________

char ch = '3'; int num = ch- '0';    //convert a string char to number
____________________________________________________________________________________________________________________________________________________________________________________________

s.erase(unique(s.begin(), s.end()), s.end())     //remove duplicate charecter from string if "moon" then it'll "mon"
____________________________________________________________________________________________________________________________________________________________________________________________

s2 = to_string(n);        //number to string
____________________________________________________________________________________________________________________________________________________________________________________________

int cur = count(s.begin(), s.end(), 'o')  //how many 'o' moon->2 
____________________________________________________________________________________________________________________________________________________________________________________________

   