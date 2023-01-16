#include <stdio.h>
#include <stdlib.h>

#define f_name "record.bin"

typedef struct account_card
{
    int acc_no,pin;
    int balance;
    
}card;

void check_balance(card *account)
{
    system("clear");
    printf("\n\tBalance: %d\n",account->balance);
}

void withdraw_money(card *account)
{
    system("clear");
    int amount;
    printf("\n\tCurrent Balance: %d\n",account->balance);
    printf("\n\tEnter the amount to withdraw: ");
    scanf("%d",&amount);
    if (amount > account->balance)
        printf("\tNot enough money to withdraw!\n");
    else
    {
        account->balance -= amount;
        printf("\tAmount Withdraw Successfully....\n");
        printf("\n\tUpdated Balance: %d\n",account->balance);
    }
}

void diposite_money(card *account)
{
    system("clear");
    int amount;
    printf("\n\tCurrent Balance: %d\n",account->balance);
    printf("\n\tEnter the amount to deposite: ");
    scanf("%d",&amount);
    account->balance += amount;
    printf("\tAmount Deposite Successfully....\n");
    printf("\n\tUpdated Balance: %d\n",account->balance);
}

void change_pin(card *account)
{
    system("clear");
    int pin,c_pin;
    printf("Enter new 4-digit PIN: ");
    scanf("%d",&pin);
    if (pin>9999 || pin<=999)
        printf("\n\tPIN must of 4-digits !\n");
    else if(pin == account->pin)
        printf("\n\tCurrent PIN is not acceptable !");
    else
    {
        printf("Re-enter your PIN to confirm: ");
        scanf("%d",&c_pin);
        if(c_pin == pin)
        {
            account->pin = c_pin;
            printf("\n\tPIN changed successfully...\n");
        }
        else
            printf("\n\tConfirm PIN doesnot matches with the original PIN !");
    }
    
}

void quit(card *account){}

void Back(void)
{
    getchar();
    printf("\n\nBACK (Press ENTER)");
    getchar();
}

int main()
{
    FILE *fptr = fopen(f_name,"rb");
    card *data = (card*)malloc(sizeof(card)*5); 
    void (*ptr[5])(card*) = {check_balance,withdraw_money,diposite_money,change_pin,quit};
    int op,index=0,flag=0,i;
    char ch;
    card bot;
    if (fptr == NULL)
    {
        for(i=0;i<5;i++)
        {
            data[i].acc_no = 1000000000+i;
            data[i].pin = 4321;
            data[i].balance=0;
        }

        fptr = fopen(f_name,"wb");
        for(i=0;i<5;i++)
            fwrite(&data[i],sizeof(data[i]),1,fptr);
        fclose(fptr);
    }

    while(1)
    {   
        flag = 0;
        
        fptr = fopen(f_name,"rb");
        for(i=0;i<5;i++)
            fread(&data[i],sizeof(data[i]),1,fptr);
        fclose(fptr);

        printf("Existing Account numbers:\n");
        for(int i=0;i<5;i++)
            printf("%d. %d\n",i+1,(data+i)->acc_no);
        printf("\n");

        printf("Enter account number: ");
        scanf("%d",&bot.acc_no);
        for(i=0;i<5;i++)
        {
            if(bot.acc_no == (data+i)->acc_no)
            {
                index = i;
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            printf("Enter the account pin: ");
            scanf("%d",&bot.pin);
            if(bot.pin != data[index].pin)
            {
                printf("\n\tInvalid Pin !\n");
                index=0;
                Back();
            }
            else
            {   
                while(1)
                {
                    bot = data[index];
                    system("clear");
                    printf("\tLogged In....\n\n");
                    printf("Operations:\n-----------\n");
                    printf("1.Check Balance\n2.Withdraw\n3.Deposite\n4.Change PIN\n5.Logout\n\n");
                    printf("Enter your choice: ");
                    scanf("%d",&op);
                    ptr[op-1](&bot);
                    if (op >= 5)
                        break;
                    Back();
                    if(bot.pin != data[index].pin)
                    {
                        system("clear");
                        data[index] = bot;
                        printf("\n\tPIN is changed logging out !\n");
                        printf("\n\nBACK (Press ENTER)");
                        getchar();
                        break;
                    }
                    data[index] = bot;
                }
                fptr = fopen(f_name,"wb");
                for(i=0;i<5;i++)
                    fwrite(&data[i],sizeof(data[i]),1,fptr);
                fclose(fptr);                
            }
        }
        else
        {
            printf("\n\tInvalid Account number !\n");
            index = 0;
            Back();
        }
        printf("\n");
        system("clear");
    }
    free(data);
    return 0;
}