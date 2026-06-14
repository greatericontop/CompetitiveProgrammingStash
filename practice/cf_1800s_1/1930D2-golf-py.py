r=range
I=input
i=int
for x in r(i(I())):
 n=i(I());s=I();d=[0]*(n+5)
 for j in r(n-1,-1,-1):d[j]=d[j+1]if s[j]=='0'else n-j+d[j+3]
 print(sum(d))