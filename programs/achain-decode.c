/*1:*/
#line 5 "./achain-decode.w"

#include <stdio.h> 
main()
{
register int c,h,i,j,k,n;
for(n= 1,h= 0;;n++){
if(!h){
c= fgetc(stdin);
if(c==EOF)break;
h= 3;
}else h--,c>>= 2;
for(i= j= 0,k= n;k;k>>= 1,j++)i+= k&1;
for(i--;i;j++)i>>= 1;
putchar((c&3)+j+(' '-1));
}
}

/*:1*/
