#define maxn 100 \

/*1:*/
#line 22 "./whirlpool2n-decode.w"

#include <stdio.h> 
#include <stdlib.h> 
int a[2*maxn];
int g[2*maxn];
int w[2*maxn];
int used[2*maxn];
main(int argc,char*argv[]){
register int i,j,k,n,nn,t,x,y,saven;
/*2:*/
#line 38 "./whirlpool2n-decode.w"

if(argc&1){
fprintf(stderr,"Usage: %s a1 a2 ... a(2n-1)\n",
argv[0]);
exit(-1);
}
nn= argc,n= saven= nn/2;
if(n> maxn){
fprintf(stderr,"Recompile me: This program has maxn=%d!\n",
maxn);
exit(-99);
}
for(k= 1;k<nn;k++){
if(sscanf(argv[k],"%d",
&g[k])!=1){
fprintf(stderr,"Bad perm element `%s'!\n",
argv[k]);
exit(-2);
}
if(g[k]<=0||g[k]>=nn){
fprintf(stderr,"Perm element `%d' out of range!\n",
g[k]);
exit(-3);
}
if(used[g[k]]){
fprintf(stderr,"Duplicate perm entry `%d'!\n",
g[k]);
exit(-4);
}
used[g[k]]= 1;
}
/*3:*/
#line 71 "./whirlpool2n-decode.w"

for(k= 2;k<nn;k+= 2){
if((g[k-1]<g[k])!=(g[k]<g[k+1])){
fprintf(stderr,"Not up-up-or-down-down! (%d %d %d)\n",
g[k-1],g[k],g[k+1]);
exit(-6);
}
}

/*:3*/
#line 69 "./whirlpool2n-decode.w"
;

/*:2*/
#line 31 "./whirlpool2n-decode.w"
;
/*4:*/
#line 82 "./whirlpool2n-decode.w"

a[0]= 1;
for(k= 1;k<nn;k++)used[k]= 0;
for(k= 2;k<nn;k+= 2){
x= g[k-1],y= g[k];
for(t= 0,j= 1;j<x;j++)if(used[j])t++;
g[k-1]-= t;
for(t= 0,j= 1;j<y;j++)if(used[j])t++;
g[k]-= t;
used[x]= used[y]= 1;
}
g[nn-1]= 1;

/*:4*/
#line 32 "./whirlpool2n-decode.w"
;
for(n= 1;n<saven;n++)
/*5:*/
#line 95 "./whirlpool2n-decode.w"

{
x= g[nn-n-n-1],y= g[nn-n-n];
t= y-(x<y?2:1)-a[0]+n+n;
for(k= n-1;k>=0;k--)
a[k+1]= (a[k]+t)%(n+n),
a[k+saven+1]= (a[k+saven]+t)%(n+n);
for(k= 1;k<=n;k++)a[k]+= (a[k]<x-1?1:2),a[k+saven]+= (a[k+saven]<x-1?1:2);
a[0]= x;
}

/*:5*/
#line 34 "./whirlpool2n-decode.w"
;
/*6:*/
#line 106 "./whirlpool2n-decode.w"

for(k= 0;k<nn;k++)printf(" %d",
a[k]);
printf("\n");

/*:6*/
#line 35 "./whirlpool2n-decode.w"
;
}

/*:1*/
