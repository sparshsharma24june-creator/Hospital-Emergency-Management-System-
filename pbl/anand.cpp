#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Patient
{
    int id;
    char name[50];
    int priority;
    struct Patient* next;
};

struct Patient* front=NULL;

char* getLevel(int p)
{
    if(p==1) return "Critical";
    if(p==2) return "Serious";
    if(p==3) return "Moderate";
    return "Normal";
}

void addPatient()
{
    struct Patient* newPatient;
    newPatient=(struct Patient*)malloc(sizeof(struct Patient));

    if(newPatient==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d",&newPatient->id);

    printf("Enter Patient Name: ");
    scanf(" %49[^\n]",newPatient->name);

    printf("Priority: 1.Critical 2.Serious 3.Moderate 4.Normal: ");
    scanf("%d",&newPatient->priority);

    if(newPatient->priority<1 || newPatient->priority>4)
    {
        printf("Invalid priority!\n");
        free(newPatient);
        return;
    }

    newPatient->next=NULL;

    if(front==NULL || newPatient->priority<front->priority)
    {
        newPatient->next=front;
        front=newPatient;
    }
    else
    {
        struct Patient* temp=front;

        while(temp->next!=NULL &&
              temp->next->priority<=newPatient->priority)
        {
            temp=temp->next;
        }

        newPatient->next=temp->next;
        temp->next=newPatient;
    }

    printf("Patient added successfully!\n");
}

void treatPatient()
{
    if(front==NULL)
    {
        printf("No patients in queue.\n");
        return;
    }

    struct Patient* temp=front;

    printf("Patient being handled:\n");
    printf("ID: %d\n",temp->id);
    printf("Name: %s\n",temp->name);
    printf("Priority: %s\n",getLevel(temp->priority));

    front=front->next;
    free(temp);
}

void displayQueue()
{
    struct Patient* temp=front;

    if(front==NULL)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nEmergency Queue:\n");

    while(temp!=NULL)
    {
        printf("ID: %d | Name: %s | Priority: %s\n",
        temp->id,temp->name,getLevel(temp->priority));

        temp=temp->next;
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n--- Hospital Emergency Queue ---\n");
        printf("1. Add Patient\n");
        printf("2. Handle Highest Priority Patient\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                treatPatient();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                printf("Exiting Emergency Queue.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    }while(choice!=4);

    while(front!=NULL)
    {
        struct Patient* temp=front;
        front=front->next;
        free(temp);
    }

    return 0;
}