//vector pair
        vector<pair<int,int>> vp(n);
for (int i = 0; i < n; ++i)
        {
          cin>>vp[i].second;
        
        }
        for (int i = 0; i < n; ++i)
        {
          cin>>x;
          vp[i].first=abs(x);
        }

_________________________________________________________________
      cout << "The number with 3 decimal places is: ";

  cout << fixed << setprecision(3) << num;
output : 1.000
________________________________________________________________________
