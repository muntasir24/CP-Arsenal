
1.  strcasecmp(s1, s2)  // compare string without case sensitive 
____________________________________________________________________________________________________________________________________________________________________________________________

2.  s1.compare(s2)      //compare string with case sensitive 
____________________________________________________________________________________________________________________________________________________________________________________________

3.  s.erase(0, 1)        // remove 1 char from postion 0  moon-> oon
____________________________________________________________________________________________________________________________________________________________________________________________

4.  transform(s.begin(), s.end(), s.begin(), ::tolower)  //convert string to lowercase  BAC->bac
 ____________________________________________________________________________________________________________________________________________________________________________________________

5.  reverse(s.begin(), s.end())                         // reverse string  BAC-> CAB
____________________________________________________________________________________________________________________________________________________________________________________________

6.  sort(s.begin(), s.end())                               // sort_string  bac-> abc
____________________________________________________________________________________________________________________________________________________________________________________________

7.  if (s1.find(s2) != string::npos) cout<<"YES"<<'\n';     //check s2 strings element have in s1, check substring s1=moon s2=oo return yes
____________________________________________________________________________________________________________________________________________________________________________________________

8.  char ch = '3'; int num = ch- '0';    //convert a string char to number
____________________________________________________________________________________________________________________________________________________________________________________________

9.  s.erase(unique(s.begin(), s.end()), s.end())     //remove duplicate charecter from string if "moon" then it'll "mon"
____________________________________________________________________________________________________________________________________________________________________________________________

10. s2 = to_string(n);        //number to string
____________________________________________________________________________________________________________________________________________________________________________________________

11. int cur = count(s.begin(), s.end(), 'o')  //how many 'o' moon->2 
____________________________________________________________________________________________________________________________________________________________________________________________

12. 
    for (int i = 0; i <26; ++i)
    {
          cout<<char('a'+i);
        //if starting from i=1 then 'a'+i-1                     }
    
    cout<<char('A'+0)<<endl; -> A

    cout<<char('a'+0)<<endl; -> a
____________________________________________________________________________________________________________________________________________________________________________________________
13.
    cout<<s.substr(5,2)<<endl;        // muntasir ->>si "s is in 5 number postion and we want  total 2 word so (5,2)"si"
____________________________________________________________________________________________________________________________________________________________________________________________
14.  s.pop_back()   // muntasir; -> muntasir   last ; removed
_____________________________________________________________________________________________________________________________________________________________________________________________
1499B. cin>>s;
int i=s.find("11");
int j=s.find("00");
cout<<(i!=-1 and j!=-1 and i<j ? "NO":"YES")<<endl;



