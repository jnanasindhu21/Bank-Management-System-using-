#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// changes
struct customer
{
    char nm[30];
    char fnm[30];            //father's name
    char mnm[30];           //mother's name
    char ad[100];          //address
    char dob[20];         //date of birth
    char gender[10];
    char acc_no[400];
    int age;
    long phno;              //phone number
    double amt;
};
typedef struct customer cus;

struct node
{
    cus d;
    struct node *link;
};
typedef struct node sll;


void createAcc(sll* ,FILE **);
void deposit(sll* ,FILE **);
void debit(sll* ,FILE **);
void balance(sll* ,FILE **);
void delete_acc(sll* ,FILE **);
void report(sll* ,FILE **);
void transfer_money(sll* ,FILE **);

int main()
{
    sll header = { .link = 0 };
    int ch;
    FILE *fp;
    fp=fopen("account.txt","a");
    for(;;)
    {
        printf("\n******************************************************\n");
        printf("\n1.Creat account\n2.Deposit Money\n3.Debit Money\n4.Check balance\n5.Delete Account\n6.report\n7.transfer money from one account to another\n8.Exit\n");
        printf("\nEnter the choice : ");
        scanf("%d",&ch);
        printf("\n******************************************************\n");
        
        switch(ch)
        {
            case 1:createAcc(&header,&fp);
                break;
            case 2:deposit(&header,&fp);
                break;
            case 3:debit(&header,&fp);
                break;
            case 4:balance(&header,&fp);
                break;
            case 5:delete_acc(&header,&fp);
                break;
            case 6:report(&header,&fp);
                break;
            case 7:transfer_money(&header,&fp);
                break;
            default:exit(0);
        }
    }
}

void createAcc(sll *h,FILE **fp)
{
    sll *t;
    char a[100],b[100],c[4]="XYZ";
    int n,l = 10000,u = 99999;
    
    t = (sll*)malloc(sizeof(sll));              //accept name
    t->link = 0;
    printf("Enter your name          : ");
    scanf(" %[^\n]s",(t->d).nm);
    
    printf("Enter your father's name : ");
    scanf(" %[^\n]s",(t->d).fnm);
    
    printf("Enter your mother's name : ");
    scanf(" %[^\n]s",(t->d).mnm);
    
    printf("Enter your address       : ");
    scanf(" %[^\n]s",(t->d).ad);
    
    printf("Enter your date of birth : ");
    scanf(" %[^\n]s",(t->d).dob);
    
    printf("Enter your gender        : ");
    scanf(" %[^\n]s",(t->d).gender);
    
    printf("Enter your age           : ");
    scanf("%d",&((t->d).age));
    
    printf("Enter your Ph.No         : ");
    scanf("%ld",&((t->d).phno));
    
    srand(time(NULL));                  //generate random number
    
    n=rand() % (u-l+1);
    
    
   
    /*
    strncpy(a,(t->d).nm,2);             //copy 1st 2 char
    a[2]='\0';
    sprintf(b,"%d",n);
    strcpy((t->d).acc_no, strcat(b,a));         
    strcpy((t->d).acc_no,strcat(c,(t->d).acc_no));
    */
    
    strncpy(a,(t->d).nm,2);             //copy 1st 2 char
    a[2]='\0';
    
    snprintf((t->d).acc_no, sizeof((t->d).acc_no),"%s%d%s",c,n,a);
    
    
    printf("\nACCOUNT CREATED SUCCESSFULLY\n");
    printf("\nNAME           : %s\nFATHER'S NAME  : %s\nMOTHER'S NAME  : %s\nADDRESS        : %s\nDOB            : %s\nGENDER         : %s\nAGE            : %d\nPHONE NUMBER   : %ld\n",(t->d).nm,(t->d).fnm,(t->d).mnm,(t->d).ad,(t->d).dob,(t->d).gender,(t->d).age,(t->d).phno);
    fprintf((*fp),"\nNAME           : %s\nFATHER'S NAME  : %s\nMOTHER'S NAME  : %s\nADDRESS        : %s\nDOB            : %s\nGENDER         : %s\nAGE            : %d\nPHONE NUMBER   : %ld\n",(t->d).nm,(t->d).fnm,(t->d).mnm,(t->d).ad,(t->d).dob,(t->d).gender,(t->d).age,(t->d).phno);
    
    printf("Account number : %s\n",(t->d).acc_no);
    fprintf((*fp),"Account number : %s\n", (t->d).acc_no);
    t->link=h->link;
    h->link = t;
}

void deposit(sll *h,FILE **fp)
{

    sll *p;
    char a[100];
    
    
    printf("Enter acc no:");
    scanf("%s",a);
    
    
    
    
    for(p=h->link; p!=0; p=p->link)
    {
        if( strcmp( ((p->d).acc_no),a ) == 0 )          //deposit
        {
            double cash;
            printf("Enter the amount you want to deposit\n");
            scanf("%lf",&cash);
            fprintf((*fp),"\namount deposited to account number %s is %lf\n",(p->d).acc_no,cash);
            (p->d).amt = (p->d).amt + cash;
            printf("successfully deposited\n");
            return;
        }
    }
    printf("\n Account not found\n");
}

void debit(sll *h,FILE **fp)
{

    sll *p;
    char a[100];
    
    
    printf("Enter acc no:");
    scanf("%s",a);

    for(p=h->link; p!=0; p=p->link)
    {
        if( strcmp( ((p->d).acc_no),a ) == 0 )          //deposit
        {
            double cash;
            printf("Enter the amount you want to debit\n");
            scanf("%lf",&cash);
    
            if( cash > (p->d).amt)
                printf("Insufficient balance\n");
            
            (p->d).amt = (p->d).amt - cash;
            fprintf((*fp),"\namount debited from acoount number %s is:%lf\n",(p->d).acc_no,cash);
            return;
        }
    }
    printf("\n Account not found\n");
}

void balance(sll *h,FILE **fp)
{
    sll *t;
    char a[100];
    
    
    printf("Enter acc no:");
    scanf("%s",a);
    
    for(t=h->link; t!=0; t=t->link)
    {
        if( strcmp( ((t->d).acc_no),a ) == 0 )          //deposit
        {
            printf("\n\nName    : %s\nBalance : %lf\n\n",(t->d).nm,(t->d).amt);
            fprintf((*fp),"\n\nName    : %s\nBalance : %lf\n\n",(t->d).nm,(t->d).amt);
            return;
        }
    }
    printf("Account not found!!");
    
}

void delete_acc(sll *h,FILE **fp)
{
    sll *t,*p;
    char a[100];
    
    
    printf("Enter acc no:");
    scanf("%s",a);
    

    for(p=0,t=h->link; t!=0; p=t,t=t->link)
    {
        if( strcmp( ((t->d).acc_no),a ) == 0 )          
        {
            if(t->link == 0)
            {
                printf("\n\nName = %s\nAccNo = %s\nBalance = %lf\nACCOUNT DELETED SUCCESSFULLY\n\n",(t->d).nm,(t->d).acc_no,(t->d).amt);
                fprintf((*fp),"\n\nName = %s\nAccNo = %s\nBalance = %lf\nACCOUNT DELETED SUCCESSFULLY\n\n",(t->d).nm,(t->d).acc_no,(t->d).amt);
                h->link = 0;
                free(h->link);
                return;
            }
            printf("\n\nName = %s\nAccNo = %s\nBalance = %lf\nACCOUNT DELETED SUCCESSFULLY\n\n",(t->d).nm,(t->d).acc_no,(t->d).amt);
            fprintf((*fp),"\n\nName = %s\nAccNo = %s\nBalance = %lf\nACCOUNT DELETED\n\n",(t->d).nm,(t->d).acc_no,(t->d).amt);
            p->link = t->link;
            free(t);
            return;
        }
    }
    printf("Account not found!!");
}





void report(sll *h,FILE **fp)
{
    sll *t;
    for(t=h->link; t!=0; t=t->link)
    {
        printf("\n.............................................\nName = %s\nAccNo = %s\nBalance = %lf\n.............................................\n",(t->d).nm,(t->d).acc_no,(t->d).amt);
        fprintf((*fp),"\n.............................................\nName = %s\nAccNo = %s\nBalance = %lf\n.............................................\n",(t->d).nm,(t->d).acc_no,(t->d).amt);
    }
}
void transfer_money(sll *h,FILE **fp)
{
    sll *to, *t; 
    sll *p;//from , to , temp
    
    char frm[15], tc[15];
    double cash;
    
    printf("Enter your Account number : ");
    scanf("%s",frm);
    
    for( t=h->link; t != 0; t=t->link)
    {
        if( strcmp( frm, (t->d).acc_no ) == 0 )
        {
            printf("Enter the Account number to transfer money : ");
            scanf("%s",tc);
            
            for( to=h->link; to != 0; to = to->link)
            {
                if( strcmp( tc, (to->d).acc_no ) == 0 )
                {
                    printf("Enter the amount you want to transfer : ");
                    scanf("%lf",&cash);
                    if( cash > (t->d).amt )
                    {
                        printf("Insufficient balance\n");
                        return;
                    }
                    fprintf((*fp),"\nmoney transferred from %s to %s:%lf\n ",frm,(t->d).acc_no,cash);
                    (to->d).amt = (to->d).amt + cash;
                    (t->d).amt = (t->d).amt - cash;
                    printf("\nMoney transferred successfully from %s to %s\n%lf Rs\n ",frm,tc,cash);
                    return;
                }
                
            }
            
        }
        else
            printf("Account not found !!!");
        
    }
}
