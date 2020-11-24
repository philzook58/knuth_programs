#define gsize 1000
#define m 10000
#define nsize (1<<14) 
#define nmax (32*nsize)  \

#define mhmartin 0x07dcd629 \

/*1:*/
#line 45 "./ulam.w"

#include <stdio.h> 
unsigned int ubit[nsize+1],vbit[nsize+1];
char decode[64];
int count[gsize],example[gsize];

main()
{
register unsigned int j,jj,k,kk,kq,kr,del,c,n,u,prevu,gap;
/*5:*/
#line 119 "./ulam.w"

for(k= 0,j= 1;j;k++,j<<= 1)decode[(mhmartin*j)>>27]= k;

/*:5*/
#line 54 "./ulam.w"
;
gap= 1;
ubit[0]= 0x6,kr= n= prevu= 2,kq= 0,kk= 4;
while(1){
/*2:*/
#line 85 "./ulam.w"

for(j= c= 0,jj= j+kq;j<kq;j++,jj++){
if(jj>=nsize)goto update_done;
del= (ubit[j]<<kr)+c;
c= (ubit[j]>>(31-kr))>>1;
/*3:*/
#line 102 "./ulam.w"

u= (ubit[jj]^del)&~vbit[jj];
vbit[jj]|= ubit[jj]&del;
ubit[jj]= u;

/*:3*/
#line 90 "./ulam.w"
;
}
if(jj>=nsize)goto update_done;
u= ubit[kq]&(kk-1);
del= (u<<kr)+c,c= (u>>(31-kr))>>1;
/*3:*/
#line 102 "./ulam.w"

u= (ubit[jj]^del)&~vbit[jj];
vbit[jj]|= ubit[jj]&del;
ubit[jj]= u;

/*:3*/
#line 95 "./ulam.w"
;
if(c!=0){
jj++,del= c;
/*3:*/
#line 102 "./ulam.w"

u= (ubit[jj]^del)&~vbit[jj];
vbit[jj]|= ubit[jj]&del;
ubit[jj]= u;

/*:3*/
#line 98 "./ulam.w"
;
}
update_done:

/*:2*/
#line 58 "./ulam.w"
;
/*4:*/
#line 107 "./ulam.w"

u= ubit[kq]&-(kk+kk);
while(!u){
if(++kq>=nsize)goto done;
u= ubit[kq];
}
kk= u&-u;
kr= decode[(mhmartin*kk)>>27];
n++;

/*:4*/
#line 59 "./ulam.w"
;
k= kr+(kq<<5);
del= k-prevu;
count[del]++,example[del]= k;
if(del> gap){
if(del>=gsize){
fprintf(stderr,"Unexpectedly large gap (%d)! Recompile me...\n",del);
return-666;
}
gap= del;
printf("New gap %d: U_%d=%d, U_%d=%d\n",gap,n-1,prevu,n,k);
fflush(stdout);
}
prevu= k;
if((n%m)==0){
printf("U_%d=%d is about %.5g*%d\n",n,k,((double)k)/n,n);
fflush(stdout);
}
}
done:/*6:*/
#line 122 "./ulam.w"

for(j= 1;j<=gap;j++)if(count[j])
printf("gap %d occurred %d time%s, last was %d\n",
j,count[j],count[j]==1?"":"s",example[j]);

/*:6*/
#line 78 "./ulam.w"
;
printf("There are %d Ulam numbers less than %d.\n",n,nmax);
}

/*:1*/
