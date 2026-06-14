r=range
I=input
i=int
for x in r(i(I())):
 n=i(I());s=I();d=[0]*(n+5)
 for j in r(n):d[j]=d[j-1]if s[n-1-j]=='0'else j+1+d[j-3]
 print(sum(d))