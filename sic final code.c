#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void pass2();
int main()
{
char st[30],mneumonics[30],oper[30],lb[30],f[30];
int i,address,start,locctr,flag=0,flag1=0,n,num,len,opcode,size;
FILE *fp1,*fp2,*fp3,*fp4,*fp5;
fp1=fopen("input.txt","r");
fp2=fopen("symtab.txt","w");
fp3=fopen("intermediate.txt","w");
fscanf(fp1,"%s %s %x",st,mneumonics,&address);
if(strcmp(mneumonics,"START")==0)
{
start=address;
locctr=start;
fprintf(fp3,"%s\t%s\t%s\t%x\n","-",st,mneumonics,locctr);
fscanf(fp1,"%s %s %s",lb,mneumonics,oper);
}
else
{
locctr=0;
}
while(strcmp(mneumonics,"END")!=0)
{
fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,lb,mneumonics,oper);
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
fp5=fopen("Length.txt","w");
fprintf(fp5,"%x",n);
fclose(fp5);
fclose(fp3);
fclose(fp1);
fclose(fp2);
fclose(fp4);
pass2();
return 0;
}
void pass2()
{
    char add[50],label[50],mn[50],oper[50];//intermediate
char slab[50],soper[50],sop[50];//symtab
char omn[50],osize[50],oop[50],op[50];//optab
char nw[50],nww[50],nwo[50];
char start[50],str[50],opcode[50],omne[50],oadd[50],ooadd[50];
int i,j,l,leoc,len,flag,flag1,f,check,size;
char sstr[10],strg[10];

FILE *fin,*fsym,*fopt;
FILE *flen;
FILE *fout;
FILE *flist;
FILE *fopcode;

fin=fopen("Intermediate.txt","r");
fsym=fopen("Symtab.txt","r");
flen=fopen("Length.txt","r");
flist=fopen("Listing.txt","w");
fout=fopen("Output.txt","w");
fopcode=fopen("Opcode.txt","w");
fscanf(fin,"%s %s %s %s",add,label,mn,oper);
fscanf(flen,"%x",&len);

if(strcmp(mn,"START")==0)
{
    strcpy(start,oper);
    fprintf(flist,"%s\t%s\t%s\t%s\n",add,label,mn,oper);
    fprintf(fout,"H^%s^%06s^%06x",label,start,len);
    fscanf(fin,"%s %s %s %s",add,label,mn,oper);
}



while(strcmp(mn,"END")!=0)
{
    flag=flag1=0;
    fopt=fopen("optab.txt","r");
    while(!feof(fopt))
    {
        fscanf(fopt,"%s %s %s",omn,osize,oop);
        if(strcmp(mn,omn)==0)
        {
            flag=1;
            strcpy(op,oop);
            break;
        }
    }
    fclose(fopt);

    if(flag==1)
    {
        fsym=fopen("symtab.txt","r");
        while(!feof(fsym))
        {
            fscanf(fsym,"%s %s",slab,soper);
            if(strcmp(slab,oper)==0)
            {
            sprintf(nw,"%s%s",oop,soper);
            fprintf(fopcode,"%s\t%s\t%s\n",add,mn,nw);
            fprintf(flist,"%s\t%s\t%s\t%s\t%s\n",add,label,mn,oper,nw);
            break;
            }
        }
        fclose(fsym);
    }
    if((strcmp(mn,"BYTE")==0)||(strcmp(mn,"WORD")==0))
    {
            if(strcmp(mn,"WORD")==0)
            {
                int hex=atoi(oper);
                fprintf(fopcode,"%s\t%s\t%06x\n",add,mn,hex);
                fprintf(flist,"%s\t%s\t%s\t%s\t%06x\n",add,label,mn,oper,hex);
            }
            else
            {
                l=strlen(oper);
                char b[3],p[3];
                b[0]='\0';
                p[0]='\0';
                for(i=2;i<(l-1);i++)
                {
                    p[0]=oper[i];
                    p[1]='\0';
                    strcat(b,p);
                }
                b[i]='\0';
                if(oper[0]=='X')
                {
                fprintf(fopcode,"%s\t%s\t%s\n",add,mn,b);
                fprintf(flist,"%s\t%s\t%s\t%s\t%s\n",add,label,mn,oper,b);
                }
                else if(oper[0]=='C')
                {
                fprintf(fopcode,"%s\t%s\t%s\n",add,mn,"454F46");
                fprintf(flist,"%s\t%s\t%s\t%s\t%s\n",add,label,mn,oper,"454F46");
                }
            }
    }

    if(strcmp(mn,"RSUB")==0)
    {
        fopt=fopen("optab.txt","r");
        while(!feof(fopt))
        {
            fscanf(fopt,"%s %s %s",omn,osize,oop);
            if(strcmp(mn,omn)==0)
            {
            strcpy(nwo,oop);
            fprintf(fopcode,"%s\t%s\t%s0000\n",add,mn,oop);
            fprintf(flist,"%s\t%s\t%s\t%s\t%s0000\n",add,label,mn,oper,nwo);
            }
        }
        fclose(fopt);
    }
    if((strcmp(mn,"RESW")==0)||(strcmp(mn,"RESB")==0))
    {
        fprintf(fopcode,"%s\t%s\t%s\n",add,mn,"-");
        fprintf(flist,"%s\t%s\t%s\t%s\n",add,label,mn,oper);
    }
    fscanf(fin,"%s %s %s %s",add,label,mn,oper);

}
fprintf(fopcode,"%s\t%s\t-\n",add,mn);//end while END
fclose(fopcode);




fopcode=fopen("opcode.txt","r");



while(!feof(fopcode))
{
    if(strcmp(omne,"END")==0)
    {


    }

    check=0;

    while(!feof(fopcode))
{

    if(check>0)
    {
        fprintf(fout,"%x",check);

    }

fscanf(fopcode,"%s %s %s",oadd,omne,opcode);
if((strcmp(omne,"RESW")==0 || strcmp(omne,"RESB")==0)|| strcmp(omne,"END")==0)
{

    check=0;
    break;
}



else if(check>27)
{
    check=0;
    break;
}
else
{

    if(check==0)
    {
        fprintf(fout,"\nT^%06s^",oadd);

    }

    fprintf(fout,"%s^",opcode);

    size=strlen(opcode)/2;
    check=check+size;

}

}
}
fclose(fopcode);

fprintf(fout,"\nE^%06s",start);

fclose(fout);
fclose(fin);
fclose(fsym);
fclose(flist);
fclose(fopt);
fclose(flen);
fclose(fopcode);
}
