#define bufsize 80 \

#define encode(d) ((d) <10?'0'+(d) :'a'+(d) -10)  \

/*1:*/
#line 57 "./sudoku-general-dlx.w"

#include <stdio.h> 
#include <stdlib.h> 
char buf[bufsize];
int pos[32][32];
int row[32][32];
int col[32][32];
int box[32][32];
int rowcount[32],colcount[32],boxcount[32];
int c;
int bc;
int cells;
unsigned int inbox[32][32];
main(){
register int d,i,j,k,kk,n,x;
/*2:*/
#line 78 "./sudoku-general-dlx.w"

for(n= k= kk= 0;;kk++){
if(!fgets(buf,bufsize,stdin))break;
/*3:*/
#line 98 "./sudoku-general-dlx.w"

if(!n){
for(n= 0;buf[n]&&buf[n]!='\n';n++);
if(n==0){
fprintf(stderr,"the length of the first line (n) is zero!\n");
exit(-1);
}
if(n> 32){
fprintf(stderr,"the length of the first line (%d) exceeds 32!\n",
n);
exit(-2);
}
cells= n*n;
for(j= 0;j<n;j++)rowcount[j]= colcount[j]= n;
}
else{
k= kk%n;
for(j= 0;j<n;j++)if(buf[j]=='\n'){
fprintf(stderr,"input line %d has fewer than %d characters!\n",
kk,n);
exit(-3);

}
if(buf[j]!='\n'){
fprintf(stderr,"input line %d has more than %d characters!\n",
kk,n);
exit(-4);
}
}

/*:3*/
#line 81 "./sudoku-general-dlx.w"
;
if(kk<n)/*4:*/
#line 130 "./sudoku-general-dlx.w"

for(j= 0;j<n;j++){
if(buf[j]> '0'&&buf[j]<='9')pos[k][j]= d= buf[j]-'0';
else if(buf[j]>='a'&&buf[j]<='w')pos[k][j]= d= buf[j]-'a'+10;
else if(buf[j]=='#')pos[k][j]= -1,cells--,rowcount[k]--,colcount[j]--;
else pos[k][j]= 0;
if(pos[k][j]> 0){
if(row[k][d-1]){
fprintf(stderr,"digit %c appears in columns %c and %c of row %c!\n",
encode(d),encode(row[k][d-1]-1),encode(j),encode(k));
exit(-10);
}
row[k][d-1]= j+1;
if(col[j][d-1]){
fprintf(stderr,"digit %c appears in rows %c and %c of column %c!\n",
encode(d),encode(col[j][d-1]-1),encode(k),encode(j));
exit(-11);
}
col[j][d-1]= k+1;
c++;
}
}

/*:4*/
#line 82 "./sudoku-general-dlx.w"

else/*5:*/
#line 153 "./sudoku-general-dlx.w"

for(j= 0;j<n;j++){
if(buf[j]=='.')continue;
if(buf[j]>='0'&&buf[j]<='9')x= buf[j]-'0';
else if(buf[j]>='a'&&buf[j]<='v')x= buf[j]-'a'+10;
else{
fprintf(stderr,
"line %d of box-definition group %d has the invalid character %c!\n",
k,kk/n,buf[j]);
exit(-7);
}
d= pos[k][j];
if(d> 0){
if(box[x][d-1]){
fprintf(stderr,"digit %c appears in rows %c and %c of box %c!\n",
encode(d),encode(box[x][d-1]-1),encode(k),encode(x));
exit(-12);
}
box[x][d-1]= k+1;
}
if(boxcount[x]==0)bc++;
if(inbox[k][j]&(1<<x)){
fprintf(stderr,"box %c already contains the cell in row %c, column %c!\n",
encode(x),encode(k),encode(j));
exit(-13);
}
inbox[k][j]|= 1<<x,boxcount[x]++;
if(boxcount[x]> n){
fprintf(stderr,"box %c contains more than %d cells!\n",
encode(x),n);
exit(-13);
}
}

/*:5*/
#line 83 "./sudoku-general-dlx.w"
;
}
if(kk<n){
fprintf(stderr,"There were fewer than %d lines of input!\n",
n);
exit(-5);
};
if(k+1<n){
fprintf(stderr,"Box-definition group %d had fewer than %d lines of input!\n",
kk/n,n);
exit(-6);
}
fprintf(stderr,"OK, I've got n=%d, with %d boxes and %d clues in %d cells.\n",
n,bc,c,cells);

/*:2*/
#line 72 "./sudoku-general-dlx.w"
;
/*6:*/
#line 187 "./sudoku-general-dlx.w"

printf("|sudoku");
for(i= 0;i<n;i++){
printf("!");
for(j= 0;j<n;j++)fprintf(stdout,"%c",
pos[i][j]<0?'#':pos[i][j]> 0?encode(pos[i][j]):'.');
}
fprintf(stdout,"\n");

/*:6*/
#line 73 "./sudoku-general-dlx.w"
;
/*7:*/
#line 200 "./sudoku-general-dlx.w"

for(i= 0;i<n;i++)for(j= 0;j<n;j++)if(pos[i][j]==0)
printf("p%c%c ",
encode(i),encode(j));
for(i= 0;i<n;i++)for(d= 0;d<n;d++)if(rowcount[i]==n&&!row[i][d])
printf("r%c%c ",
encode(i),encode(d+1));
for(j= 0;j<n;j++)for(d= 0;d<n;d++)if(colcount[j]==n&&!col[j][d])
printf("c%c%c ",
encode(j),encode(d+1));
for(x= 0;x<32;x++)for(d= 0;d<n;d++)if(boxcount[x]==n&&!box[x][d])
printf("b%c%c ",
encode(x),encode(d+1));
printf("|");
for(i= 0;i<n;i++)for(d= 0;d<n;d++)
if(rowcount[i]&&rowcount[i]<n&&!row[i][d])
printf(" r%c%c",
encode(i),encode(d+1));
for(j= 0;j<n;j++)for(d= 0;d<n;d++)
if(colcount[j]&&colcount[j]<n&&!col[j][d])
printf(" c%c%c",
encode(j),encode(d+1));
for(x= 0;x<32;x++)for(d= 0;d<n;d++)
if(boxcount[x]&&boxcount[x]<n&&!box[x][d])
printf(" b%c%c",
encode(x),encode(d+1));
printf("\n");

/*:7*/
#line 74 "./sudoku-general-dlx.w"
;
/*8:*/
#line 228 "./sudoku-general-dlx.w"

for(i= 0;i<n;i++)for(j= 0;j<n;j++)for(d= 0;d<n;d++){
if(pos[i][j]!=0||row[i][d]!=0||col[j][d]!=0)continue;
for(x= 0;x<32;x++){
if((inbox[i][j]&(1<<x))==0)continue;
if(box[x][d]!=0)break;
}
if(x<32)continue;
printf("p%c%c r%c%c c%c%c",
encode(i),encode(j),encode(i),encode(d+1),encode(j),encode(d+1));
for(x= 0;x<32;x++){
if((inbox[i][j]&(1<<x))==0)continue;
printf(" b%c%c",
encode(x),encode(d+1));
}
printf("\n");
}

/*:8*/
#line 75 "./sudoku-general-dlx.w"
;
}

/*:1*/
