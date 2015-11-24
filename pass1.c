#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
char st[30],mneumonics[30],oper[30],lb[30],f[30];
int i,address,start,locctr,flag=0,flag1=0,n,num,len,opcode;
FILE *fp1,*fp2,*fp3;
fp1=fopen("Input.txt","r");
fp2=fopen("Symtab.txt","w");
fp3=fopen("Intermediate.txt","w");
fscanf(fp1,"%s %s %x",st,mneumonics,&address);
if(strcmp(mneumonics,"START")==0)
{
start=address;
locctr=start;
fprintf(fp3,"%s\t%s\t%s\t%x\n","-",st,mneumonics,locctr);
printf("%s\t%s\t%s\t%x\n","-",st,mneumonics,locctr);
fscanf(fp1,"%s %s %s",lb,mneumonics,oper);
}
else
{
locctr=0;
}
while(strcmp(mneumonics,"END")!=0)
{
fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,lb,mneumonics,oper);
printf("%x\t%s\t%s\t%s\n",locctr,lb,mneumonics,oper);
if(strcmp(lb,"-")!=0)
{
fp2=fopen("symtab.txt","r");
flag=0;
for(;!feof(fp2);)
{
fscanf(fp2,"%s",f);
if(strcmp(f,lb)==0)
{
flag=1;
break;
}
}
fclose(fp2);
if(flag==1)
{
printf("\nError in Code\n");
exit(0);
}
else
{
fp2=fopen("symtab.txt","a");
fprintf(fp2,"%s\t%x\n",lb,locctr);
fclose(fp2);
}
}
FILE *fp4;
fp4=fopen("optab.txt","r");
flag1=0;
for(;!feof(fp4);)
{
fscanf(fp4,"%s\t%x\t%x",f,&n,&opcode);
if(strcmp(f,mneumonics)==0)
{
flag1=1;
break;
}
}
fclose(fp4);
if(flag1==1)
{
locctr=locctr+n;
}
else if(strcmp(mneumonics,"BYTE")==0)
{
if(oper[0]=='X')
{
len=strlen(oper)-3;
num=len/2;
locctr=locctr+num;
}
else
{
len=strlen(oper)-3;
locctr=locctr+len;
}
}
else if(strcmp(mneumonics,"RESB")==0)
{
sscanf(oper,"%d",&num);
locctr=locctr+num;
}
else if(strcmp(mneumonics,"RESW")==0)
{
sscanf(oper,"%d",&num);
locctr=locctr+(3*num);
}
else if(strcmp(mneumonics,"WORD")==0)
locctr=locctr+3;
else
{
printf("\nError in mneumonic\n");
exit(0);
}
fscanf(fp1,"%s %s %s",lb,mneumonics,oper);
}
n=(locctr-start);
fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,lb,mneumonics,oper);
printf("%x\t%s\t%s\t%s\n",locctr,lb,mneumonics,oper);
FILE *fp5;
fp5=fopen("Length.txt","w");
fprintf(fp5,"%x",n);
fclose(fp5);
return 0;
}
