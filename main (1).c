#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct Employee* create_node(struct Employee* );
struct Employee* insert(struct Employee* , struct Employee *);
struct Employee* delnode(struct Employee*,char *);
struct Employee *search(struct Employee * , char *, struct Employee **);
void display(struct Employee *);
struct Employee* create_list();
int isValid(char *);
int isValidPIN(int );
void Details(struct Employee *);
void updateCity(struct Employee *);
void updateContact(struct Employee *);
//"%lld

struct address
{
    char city[20];
    long long int contact;
};

struct Employee
{
    char name[15];
    char id[10];
    struct address add;
    char qualification[20];
    struct Employee *left_child;
    struct Employee *right_child;

};
struct Employee* create_node(struct Employee *root)
{
    struct Employee *p,*parent,*temp;
    p = malloc(sizeof(struct Employee));
    parent = p;
    printf("\n\t\t\t Enter the name of Employee : ");
    fflush(stdin);
    gets(p->name);

    while(1)
    {
        printf("\n\t\t\t Enter the id of Employee Format(e.g. 19BCE246 )  : ");
        gets(p->id);
        int k = isValid(p->id);
        if(k==0)
        {

            printf("\n\t\t\t Enter valid id !!");
        }
        else
        {
            temp = search(root,p->id,&parent);
            if(temp == NULL)
                   break;
            else
                {
                    printf("\n\t\t\t The user with above id already exists.");
                    printf("\n\t\t\t Enter new ID");
                }

        }
    }
    printf("\n\t\t\t Enter the address of Employee ");
    printf("\n\t\t\t City : ");
    gets(p->add.city);

    do
    {
        printf("\n\t\t\t Enter the CONTACT in the format 9640010451[only a 10-digit number]: ");
        fflush(stdin);
        scanf("%lld",&p->add.contact);
        if(isValidContact(p->add.contact))
            break;
        else
            printf("\n\t\t\t Contact Number should be exactly 10-digit number !!");
    }while(1);
    printf("\n\t\t\t Qualification : ");
    fflush(stdin);
    gets(p->qualification);
    fflush(stdin);


    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}
struct Employee *insert(struct Employee *root,struct Employee *New)
{
    int priority = strcmpi(root->id,New->id);
    if(priority>0)
    {
        if(root->left_child == NULL)
            root->left_child = New;
        else
            insert(root->left_child , New);

    }
    else if(priority<0)
    {
        if(root->right_child == NULL)
            root->right_child = New;
        else
            insert(root->right_child , New);
    }

}

struct Employee *delnode(struct Employee *root, char *id)
{


    struct Employee *temp,*parent,*temp_succ;

    temp = search(root,id,&parent);
    if(temp == NULL)
    {
     printf("\n\t\t\t Sorry the Employee with the following id does not exist.");
     return root;
    }
    else if(temp->left_child !=NULL && temp->right_child != NULL)
    {
        parent = temp;
        temp_succ = temp->left_child;

        while(temp_succ->left_child!=NULL)
        {
            parent = temp_succ;
            temp_succ = temp_succ->left_child;
        }

        strcpy(temp->name,temp_succ->name);
        strcpy(temp->id,temp_succ->id);
        strcpy(temp->add.city,temp_succ->add.city);
        temp->add.contact = temp_succ->add.contact;
        strcpy(temp->qualification,temp_succ->qualification);
        parent->left_child  = NULL;
        printf("\n\t\t\t Deleted Successfully");
        return root;
    }

    else if(temp->left_child != NULL && temp->right_child == NULL)
    {
        if(temp == root)
        {
            root = temp -> left_child;
        }
        else if(parent->left_child == temp)
            parent->left_child = temp->left_child;
        else
            parent->right_child = temp->left_child;
        temp = NULL;
        free(temp);
        printf("\n\t\t\t Deleted Successfully");
        return root;

    }

    else if(temp->left_child == NULL && temp->right_child != NULL)
    {
        if(temp == root)
        {
            root = temp -> right_child;
        }
        else if(parent->left_child == temp)
            parent->left_child = temp->right_child;
        else
            parent->right_child = temp->right_child;
        temp = NULL;
        free(temp);
        printf("\n\t\t\t Deleted Successfully");
        return root;

    }

    else // if(temp->left_child == NULL && temp->right_child == NULL)
    {
        if(temp == root)
            root = NULL;
        else if(parent->left_child == temp)
            parent->left_child = NULL;
        else
            parent->right_child = NULL;
        printf("\n\t\t\t Deleted Successfully");
        return root;
    }
}


//This function is to find that if the entered ID by the user is valid [return 1] or not [return 0] according to the given conditions.
//For each and every invalidity, a proper message is printed along with returning the value 0

int isValid(char *id)
{
    if(strlen(id)!=8)                                                           //If the entered ID length is not 8, it is invalid and a proper message is printed
    {
        printf("\n\t\t\t Not enough numbers of characters in the ID No.");
        return 0;
    }
    if(isdigit(id[0]) && isdigit(id[1])){}                                      //The entered ID should have numbers at index 0 and 1
    else
    {
        printf("\n\t\t\t First 2 spaces of the ID needs to be integer.");
        return 0;
    }
    if(isupper(id[2]) && isupper(id[3]) && isupper(id[4]))                      //The entered ID should have uppercase letters at index 2, 3 and 4
    {
        if(id[2]=='B' || id[2]=='M'){}                                          ////The entered ID should have B or M at index 2
        else
        {
            printf("\n\t\t\t4th character of the ID can be either 'B' or 'M'.");
            return 0;
        }
    }
    else
    {
        printf("\n\t\t\t Space number 3, 4 and 5 need to be UpperCase alphabets.\n");
        return 0;
    }
    if(isdigit(id[5]) && isdigit(id[6]) && isdigit(id[7])){}                    //The entered ID should have numbers at index 5, 6 and 7
    else
    {
        printf("\n\t\t\t Space number 6, 7 and 8 need to be numbers.\n");
        return 0;
    }
    return 1;                                                                   //If all conditions are satisfied, returned value is 1 i.e. ID is correct
}

//This function checks if the Contact Number entered by the user is valid[10-digit number] or not.

int isValidContact(long long int n)
{
    int c = 0;
    //long long int k = 10;                                                            //c counts the number of digits
    while(n!=0)                                                                 //Unless the contact number is 0, the loop will continue
    {
        n/=10;                                                                   //Every time the loop is run, Contact Number is divided by 10
        c++;                                                                    //Every time the loop is run, counter is incremented by 1
    }
    if(c==10)                                                                   //If number of digits counted is 10, returned value is 1
        return 1;
    else                                                                        //Else the contact number is not valid
        return 0;
}

//This function performs the task to find a searched node and return the pointer to the searched node or a NULL pointer if no ID id found

struct Employee *search(struct Employee *root , char *s, struct Employee **parent)
{
    struct Employee *temp;
    temp = root;                                                                           //temporary node pointing to the Root of the BST
    while(temp!=NULL)                                                                      //Unless temp is NULL, loop will continue
    {
        if(strcmpi(temp->id , s)== 0)
        {
            printf("\n\t\t\t The name of the Employee is :  %s",temp->name);              //If the ID of a particular Employee matches the searched ID, it returns the pointer to the Employee Node it matched
            return temp;
        }
        *parent = temp;

        if(strcmpi(temp->id , s)> 0)
            temp = temp->left_child;                                                         //If searched ID is lesser than the current node ID, it will navigate to the left node
        else if(strcmpi(temp->id , s)< 0)                                                    //If searched ID is greater than the current node ID, it will navigate to the right node
            temp = temp->right_child;
    }
    return NULL;                                                                             //If no ID is matched in the BST, NULL pointer is returned
};



//This function performs the task to search for an employee in the Employee list and also displays the info about the employee

void Details(struct Employee *root)
{
    struct Employee *temp,*parent;
    char id_key[10];
    printf("\n\t\t\t Enter the id of the Employee : ");                         //ID of the Employee to be searched
    fflush(stdin);
    gets(id_key);                                                               //ID scanned
    int k = isValid(id_key);                                                    //To check if the format of the ID is correct
    if(k==0)                                                                    //If not correct,
        printf("\n\t\t\t Enter valid id !!");                                   //Appropriate message is printed
    else                                                                        //ELSE
    {
        temp = search(root,id_key,&parent);                                             //ID is being searched from the BST
        if(temp == NULL)                                                        //If ID is not found, a proper message is printed
        {
            printf("\n\t\t\t Sorry the Employee with the following id does not exist.");
        }
        else                                                                    //If ID is found
        {
            printf("\n\t\t\t        Employee details");                         //All the details of the employee is printed
            printf("\n\t\t------------------------------------------\n");
            printf("\n\t\t\t  Name          : %s",temp->name);
            printf("\n\t\t\t  Id            : %s",temp->id);
            printf("\n\t\t\t  City          : %s",temp->add.city);
            printf("\n\t\t\t  Contact       : %lld",temp->add.contact);
            printf("\n\t\t\t  Qualification : %s",temp->qualification);
        }
    }
}


//This function is used to display the details of all the employees in ascending order according to their IDs.
//It displays all the nodes according to the InOrder Display.
//It follows the process of Recursion using the Stack.
//As per the ascending order of the IDs -> Name, ID, City, Contact No. and Qualification of the employee will be displayed.

void display(struct Employee *temp)
{
    if(temp!=NULL)
    {
        display(temp->left_child);                                              //This function calls the left child of the current node.
        printf("\n\t\t------------------------------------------\n");           //This 6 lines prints Name, ID, City, Contact No. and Qualification of the employee.
        printf("\n\t\t\t  Name          : %s",temp->name);
        printf("\n\t\t\t  Id            : %s",temp->id);
        printf("\n\t\t\t  City          : %s",temp->add.city);
        printf("\n\t\t\t  Contact       : %lld",temp->add.contact);
        printf("\n\t\t\t  Qualification : %s",temp->qualification);
        display(temp->right_child);                                             //This function calls the right child of the current node.
    }
}

//This function updates the residing city of the employee

void updateCity(struct Employee *root)
{
    char id_key[10];
    struct Employee *parent;
    printf("\n\t\t\t Enter the id of the Employee whose City is to be updated : ");     //The ID of the Employee is inputted
    fflush(stdin);                                                                      //Clears the input channel
    gets(id_key);                                                                       //City of the employee with this ID will be updated
    int k = isValid(id_key);                                                            //To check if the entered ID of the employee is valid or not
    if(k==0)                                                                            //If invalid
        printf("\n\t\t\t Enter valid id !!");                                           //a proper message is displayed
    else                                                                                //If Valid
    {
        struct Employee *node = search(root,id_key,&parent);                             //Node with the entered ID is searched
        if(node==NULL)                                                                  //If ID does not exist a NULL value will lead to termination of the function with an appropriate message.
        {
            printf("\n\t\t\tID does not exist.");
            return;
        }                                                                               //ELSE
        printf("\n\t\t\tEnter you new residential city :   ");                          //New city is inputted
        scanf("%s",node -> add.city);                                                            //New City is scanned
        printf("\n\t\t\tNew city updated successfully.");                               //At the end , a valid message is printed
    }
}

//This function updates the contact number of the employee

void updateContact(struct Employee *root)
{
    char id_key[10];
    struct Employee *parent;
    printf("\n\t\t\t Enter the id of the Employee whose Contact is to be updated : ");     //The ID of the Employee is inputted
    fflush(stdin);                                                                      //Clears the input channel
    gets(id_key);                                                                       //Contact of the employee with this ID will be updated
    int k = isValid(id_key);                                                            //To check if the entered ID of the employee is valid or not
    if(k==0)                                                                            //If invalid
        printf("\n\t\t\t Enter valid id !!");                                           //a proper message is displayed
    else                                                                                //If Valid
    {
        struct Employee *node = search(root,id_key,&parent);                             //Node with the entered ID is searched
        if(node==NULL)                                                                  //If ID does not exist a NULL value will lead to termination of the function with an appropriate message.
        {
            printf("\n\t\t\tID does not exist.");
            return;
        }                                                                               //ELSE
        printf("\n\t\t\tEnter you new contact number :   ");                            //New contact is inputted

        scanf("%lld", &node->add.contact);                                                            //New Contact is scanned
                                                               //New contact is assigned with the old contact
        printf("\n\t\t\tNew Number updated successfully.");                               //At the end , a valid message is printed
    }
}

void main()
{
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =               Employee Record             =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
    system("cls");

    printf("\t\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Employee Record Management System Project in C  ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");

    printf("\n\t\t\t----------------------------------------------------------------------------");




    struct Employee *root,*New,*parent,*temp;
    root = NULL;
    char id_key[10];

    while(1)
    {
        int n;
        printf("\n\t\t\t     MAIN MENU  \n");
        printf("\n\t\t\t 1 : Add an Employee");
        printf("\n\t\t\t 2 : Delete an Employee");
        printf("\n\t\t\t 3 : Display the Existing list");
        printf("\n\t\t\t 4 : View Employee detail");
        printf("\n\t\t\t 5 : Update Employee detail");
        printf("\n\t\t\t 0 : exit the program");
        printf("\n\n\t\t\t   Enter your choice : ");

        scanf("%d",&n);


        switch(n)
        {

        case 1 :
               if(root == NULL)
                  root = create_node(root);
               else
                {
                    New = create_node(root);
                   insert(root,New);
                }
               break;


        case 2 :
            if(root == NULL)
            {
                printf("\n\t\t\t No record exists !! ");
            }
            else
            {
                printf("\n\t\t\t Enter the id of Employee you wish to delete : ");
                    fflush(stdin);
                    gets(id_key);
                    int k = isValid(id_key);
                    if(k==0)
                        printf("\n\t\t\t Enter valid id !!");
                    else
                    {
                      root = delnode(root,id_key);
                    }
            }
            break;


        case 3 :
            if(root == NULL)
                printf("\n\t\t\t Record is not created ");
            else
            {
                printf("\n\t\t\t Employee details are as follows ");
                printf("\n\t*******************************************************");
               display(root);
            }
            break;

        case 4 :
            if(root == NULL)
            {
                printf("\n\t\t\t Create a list first (i.e. select option 1 to make the first entry).");
                break;
            }
            else
            {
                Details(root);
            }
            break;

        case 5 :
            if(root == NULL)
            {
                printf("\n\t\t\tNo employee details to be updated.");
                break;
            }
            int z;
            printf("\n\t\t\t 1.  To update your Residential City");
            printf("\n\t\t\t 2.  To update your Contact Number");
            printf("\n\t\t\t     Enter your choice :   ");
            scanf("%d",&z);
            switch(z)
            {
                case 1:

                    updateCity(root);
                    break;
                case 2:
                    updateContact(root);
                    break;
                default:
                    printf("\n\t\t\tInvalid choice.");
                    break;
            }
            break;
        case 0 :
            printf("\n\n\n\n\n");
            printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
            printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            printf("\n\t\t\t        =                Thank you                  =");
            printf("\n\t\t\t        =                    :)                     =");
            printf("\n\t\t\t        =                Visit Again                =");
            printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            printf("\n\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");

            exit(0);
            break;
        default :
            printf("\n\t\t\t   Wrong Input\n\t\t\t  :( \n\t\t\t  Try again\n\n");
            fflush(stdin);
       }

       printf("\n-----------------------------------------------------------------------\n");
     }
}
