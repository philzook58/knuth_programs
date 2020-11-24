#define maxd 36
#define encode(v) ((v) <10?(v) +'0':(v) -10+'a')  \

/*1:*/
#line 28 "./motley-dlx.w"

#include <stdio.h> 
#include <stdlib.h> 
int m,n;
main(int argc,char*argv[]){
register int a,b,c,d,j,k;
/*2:*/
#line 43 "./motley-dlx.w"

if(argc!=3||sscanf(argv[1],"%d",
&m)!=1||sscanf(argv[2],"%d",
&n)!=1){
fprintf(stderr,"Usage: %s m n\n",
argv[0]);
exit(-1);
}
if(m> maxd||n> maxd){
fprintf(stderr,"Sorry, m and n must be at most %d!\n",
maxd);
exit(-2);
}
printf("| motley-dlx %d %d\n",
m,n);

/*:2*/
#line 34 "./motley-dlx.w"
;
/*3:*/
#line 65 "./motley-dlx.w"

for(j= 0;j<m;j++)for(k= 0;k<n;k++)
printf(" %c%c",
encode(j),encode(k));
for(a= 1;a<m;a++)printf(" 1:%d|x%c",
m-a,encode(a));
for(c= 1;c<n;c++)printf(" 1:%d|y%c",
n-c,encode(c));
printf(" |");
for(a= 0;a<m;a++)for(b= a+1;b<=m;b++)if(a!=0||b!=m)
printf(" x%c%c",
encode(a),encode(b));
for(c= 0;c<n;c++)for(d= c+1;d<=n;d++)if(c!=0||d!=n)
printf(" y%c%c",
encode(c),encode(d));
/*6:*/
#line 137 "./motley-dlx.w"

for(k= 1;k+k<n;k++)printf(" !%d",
k);

/*:6*/
#line 80 "./motley-dlx.w"
;
printf("\n");

/*:3*/
#line 35 "./motley-dlx.w"
;
for(a= 0;a<m;a++)for(b= a+1;b<=m;b++)if(a!=0||b!=m){
for(c= 0;c<n;c++)for(d= c+1;d<=n;d++)if(c!=0||d!=n){
/*5:*/
#line 117 "./motley-dlx.w"

if(a==m-1&&c+d> n)continue;
for(j= a;j<b;j++)for(k= c;k<d;k++)
printf(" %c%c",
encode(j),encode(k));
if(a==m-1&&c+d==n)printf(" !%d",
c);
if(b==1&&c+d>=n){
if(c+d!=n)for(k= 1;k+k<n;k++)printf(" !%d",
k);
else for(k= 1;k<c;k++)printf(" !%d",
k);
}
if(a)printf(" x%c",
encode(a));
if(c)printf(" y%c",
encode(c));
printf(" x%c%c y%c%c\n",
encode(a),encode(b),encode(c),encode(d));

/*:5*/
#line 38 "./motley-dlx.w"

}
}
}

/*:1*/
