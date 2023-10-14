#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Car {
    long int carData[512];
    long int max;
};

struct Station {
    long int stationID;
    int numVehicles;
    struct Car* cars;
    struct Station* next;
};

struct percorso{
    long int stationID;
    struct percorso* next;
};

struct Car* createCar(int numVehicles) {
    struct Car* newCar = (struct Car*)malloc(sizeof(struct Car));
    if (newCar == NULL) {
        perror("errore");
        exit(1);
    }
    newCar->max = -1;
    return newCar;
}


struct Station* createStation(long int stationID, int numVehicles) {
    struct Station* newStation = (struct Station*)malloc(sizeof(struct Station));
    if (newStation == NULL) {
        perror("Failed");
        exit(1);
    }
    newStation->stationID = stationID;
    newStation->numVehicles = numVehicles;
    newStation->cars = createCar(numVehicles);
    if (numVehicles > 0) {
        for (int i = 0; i < numVehicles; i++) {
            newStation->cars->carData[i] = 0;
            if(scanf("%ld", &newStation->cars->carData[i]));
            if(newStation->cars->carData[i] > newStation->cars->max)
                newStation->cars->max = newStation->cars->carData[i];
        }
    }
    newStation->next = NULL;
    return newStation;
}

struct Station* insertSorted(struct Station* head, struct Station* newStation) {
    if (head == NULL || head->stationID > newStation->stationID) {
        newStation->next = head;
        return newStation;
    }

    struct Station* current = head;
    while (current->next != NULL && current->next->stationID < newStation->stationID) {
        current = current->next;
    }

    newStation->next = current->next;
    current->next = newStation;

    return head;
}

void printReverse(struct Station* currentStation) {
    if (currentStation == NULL) {
        return;
    }
    printReverse(currentStation->next);
    printf("Station ID:%ld\n", currentStation->stationID);
    printf("max %ld\n",currentStation->cars->max);
    for (int i = 0; i < currentStation->numVehicles; i++) {
        printf(" V: %d-Car %ld\n", i + 1, currentStation->cars->carData[i]);
    }
}

struct Station* search(struct Station* head, long int key){

    struct Station* curr = head;
    while(curr != NULL && curr->stationID<=key)
    {
        if(curr->stationID == key)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int dio(struct Station* head, long int y, int auti)
{
    int flag = -1;
    struct Station* curr = head;
    struct Station* found = NULL;
    found = search(curr,y);
    if(found == NULL)
        return flag;
    found->cars->carData[found->numVehicles] = auti;
    found->numVehicles += 1;
    if(auti>found->cars->max)
        found->cars->max = auti;
    flag = 1;
    return flag;
}

int pianifica(struct Station* partenza, struct Station* destinazione, long int* percorso, int i, long int dest)
{
    struct Station * curr = partenza;
    int j = 0;
    if(destinazione == partenza)
    {
        for(int k = i-1; k>=0; k--)
        {
            printf("%ld ",percorso[k]);
            //printf("%ld", destinazione);
        }
        printf("%ld\n", dest);
        return 1;
    }
    while(curr != destinazione)
    {
        if((curr->cars->max + curr->stationID)>= destinazione->stationID)
        {
            percorso[i] = curr->stationID;
            break;
        }
        curr = curr->next;
    }
    if(curr == destinazione)
        return 0;
    else
    {
        j = i+1;
        if(pianifica(partenza, curr, percorso,j,dest)){
            return 1;
        }
    }
    if(destinazione != partenza)
        return 0;
    return 0;

}
struct Station* ritornafar(struct Station *head, struct Station* nodo)
{
    struct Station *curr = head;
    struct Station *var = NULL;
    if(nodo->cars->max <=0)
    {
        return var;
    }
    while(curr != NULL)
    {
        if((curr->stationID) >= (nodo->stationID - nodo->cars->max))
        {
            //printf("sto guardando %ld e la diff vale %ld\n",curr->stationID,(nodo->stationID - nodo->cars->max));
            var = curr;
            return var;
        }
        curr = curr->next;
    }
    return var;
}

struct percorso* createPercorso(long int id)
{
    struct percorso* newnode = (struct percorso*)malloc(sizeof(struct percorso));
    if (newnode == NULL) {
        perror("Failed");
        exit(1);
    }
    newnode->stationID = id;
    newnode->next = NULL;
    return newnode;
}

struct percorso* insert(struct percorso* head, struct percorso* node)
{

    if (head == NULL ) {
        node->next = head;
        return node;
    }
    struct percorso* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
    return head;
}

void prin(struct percorso* head)
{
    struct percorso* curr = head;
    int flag = 0;
    //printf("salti\n");
    while(curr!=NULL){
        if(flag == 0)
        {
            printf("%ld",curr->stationID);
            flag = 1;
        }
        else
        {
            printf(" %ld",curr->stationID);
        }
        curr = curr->next;
    }
    printf("\n");
}


long int find_salto(struct Station* head, long int start, long int last, int *flag)
{
    struct Station * curr = head;
    *flag = 0;
    long int maxdistance = 0;
    while(curr!=NULL  && curr->stationID < last)
    {
        if(curr->stationID >= start)
        {
        if(*flag == 0 && (curr->stationID >= start))
        {
            maxdistance = (curr->stationID - curr->cars->max);
            //printf("sto guardando %ld e dist %ld\n", curr->stationID, (curr->stationID - curr->cars->max));
            *flag = 1;
        }
        else if((curr->stationID - curr->cars->max) < maxdistance && (curr->stationID >= start) )
        {
            //printf("sto guardando %ld\n", curr->stationID);
            maxdistance = (curr->stationID - curr->cars->max);
            //printf("sto aggiornando %ld e dist %ld\n", curr->stationID, (curr->stationID - curr->cars->max));
        }
        }
        curr = curr->next;
    }
    //printf("sto:  %ld\n", maxdistance);
    return maxdistance;
}

long int pianificareverse(struct Station*head, long int start ,long int fine, long int destinazione)
{
    struct Station *curr = head;
    while(curr!=NULL)
    {
        if(curr->stationID >= start && curr->stationID <= fine)
        {
            if((curr->stationID-curr->cars->max) <= destinazione)
            {
                return curr->stationID;
            }
        }
        curr = curr->next;
    }
    return -1;
}

void pri(struct percorso* head, struct Station* head_st)
{
    long int aux = -1;
    if(head->next->next == NULL)
        return;
    pri(head->next,head_st);
    //printf("%ld\n",head->stationID);
    aux = pianificareverse(head_st,head->next->stationID,head->stationID,head->next->next->stationID);
    if(aux != -1)
        head->next->stationID = pianificareverse(head_st,head->next->stationID,head->stationID,head->next->next->stationID);
}

struct Station* deleteNode(struct Station* head, long int key) {
    struct Station* current = head;
    struct Station* prev = NULL;

    if (current != NULL && current->stationID == key) {
        head = current->next;
        current = NULL;
        printf("demolita\n");
        return head;
    }

    while (current != NULL && current->stationID != key) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("non demolita\n");
        return head;
    }

    prev->next = current->next;
    current = NULL;
    printf("demolita\n");
    return head;
}


void aggiornamax(struct Station * nodo)
{
    for(int i = 0;i<nodo->numVehicles; i++)
    {
    	if(nodo->cars->carData[i] > nodo->cars->max)
    	{
    		nodo->cars->max = nodo->cars->carData[i];
    	}
    }
}

int main() {
    struct Station* head = NULL;
    char buffer[18];
    //int k;
    int number_station = 0;
    while(scanf("%s",buffer) != EOF) {
        long int stationID,partenza,destinazione;
        int numVehicles;
        int done = 0;
        if(buffer[9] == 's')
        {
            if (scanf("%ld", &stationID));
            if(search(head,stationID) != NULL)
            {
                done = 1;
            }
            if(scanf("%d", &numVehicles));
            struct Station* newStation = createStation(stationID, numVehicles);
            if(done == 0)
            {
                head = insertSorted(head, newStation);
                number_station += 1;
                printf("aggiunta\n");
            }
            else
                printf("non aggiunta\n");
        }else if(buffer[0] == 'd')
        {
            long int rem;
            //printf("Abilito demolisci\n");
            if(scanf("%ld",&rem));
            //printf("sono: %d\n",number_station);
            head = deleteNode(head,rem);
            //printf("sono: %d\n",number_station);

        }else if(buffer[0] == 'r')
        {
            long int storm;
            long int autotorm;
            int pos = -1,i;
            struct Station * found = NULL;
            //printf("rottama auto\n");
            if(scanf("%ld",&storm));
            if(scanf("%ld",&autotorm));
            found = search(head,storm);
            if(found == NULL)
            {
                printf("non rottamata\n");
            }
            else if(found->numVehicles == 0 || found->cars == NULL)
            {
                printf("non rottamata\n");
            }
            else
            {
                for(i = 0; i<found->numVehicles && pos == -1; i++)
                {
                    //printf("sono %ld, sto confrontando con %ld e i vale %d e pos %d \n",found->cars->carData[i], autotorm,i,pos);
                    if(found->cars->carData[i] == autotorm)
                    {
                        pos = i;
                    }
                }
                if(pos == -1)
                {
                    printf("non rottamata\n");
                }
                else
                {
                    for(i=pos;i<found->numVehicles -1;i++)
                    {
                        found->cars->carData[i] = found->cars->carData[i+1];
                    }
                    found->numVehicles = found->numVehicles -1;
                    printf("rottamata\n");
                    if(found->numVehicles > 0 && found->cars->max == autotorm)
                    {
                    	found->cars->max = -1;
                    	aggiornamax(found);
                    }
                    else if(found->numVehicles == 0)
                    	found->cars->max = -1;
                }
            }

        }else if(buffer[0] == 'p')
        {
            long int array[number_station];
            struct Station * last_raggiungibile = NULL;
            struct percorso * head_percorso = NULL;
            //printf("pianifica percorso\n");
            if(scanf("%ld",&partenza));
            if(scanf("%ld",&destinazione));
            if(partenza <= destinazione)
            {
                if(pianifica(search(head,partenza),search(head,destinazione),array, 0,destinazione))
                {
                }
                else
                    printf("nessun percorso\n");
            }
            else
            {
                //long int newsalto = 0;
                //printf("PIANIFICA REVERSE\n");
                //while(last_raggiungibile->stationID != destinazione)
                //{
                last_raggiungibile = ritornafar(head,search(head,partenza));
                //printf("last %ld %ld\n", last_raggiungibile->stationID, last_raggiungibile->cars->max);
                if(last_raggiungibile == NULL || last_raggiungibile->stationID == partenza || last_raggiungibile->cars->max <=0 || last_raggiungibile->numVehicles <= 0)
                    printf("nessun percorso\n");
                else if(last_raggiungibile->stationID <= destinazione && last_raggiungibile != NULL)
                {
                    printf("%ld %ld\n",partenza,destinazione);
                }
                else
                {
                    //printf("%ld",last_raggiungibile->stationID);
                    if(last_raggiungibile != NULL)
                    {
                        struct percorso* newnode = createPercorso(partenza);
                        head_percorso = insert(head_percorso,newnode);
                        newnode = createPercorso(last_raggiungibile->stationID);
                        head_percorso = insert(head_percorso,newnode);
                        long int newsalto = partenza;
                        long int max_salto = partenza;
                        long int min_salto = last_raggiungibile->stationID;
                        int boolean = 0;
                        int boolean1 = 0;
                        int flag;
                        struct percorso* node = NULL;
                        while(newsalto > destinazione)
                        {
                            newsalto = find_salto(head,min_salto,max_salto,&flag);
                            //printf("ciao %ld\n", newsalto);
                            if(newsalto == min_salto || flag == 0)
                            {
                                //printf("nessun percorso\n");
                                boolean1 = 1;
                                break;

                            }
                                //printf("ciao %ld\n", newsalto);
                            else if(newsalto <= destinazione && boolean1 == 0)
                            {
                                node = createPercorso(destinazione);
                                head_percorso = insert(head_percorso,node);
                                boolean = 1;
                                //printf("sono dest percorso\n");
                            }
                            else if(boolean1 == 0 || boolean == 0)
                            {
                                node = createPercorso(newsalto);
                                head_percorso = insert(head_percorso,node);
                                max_salto = min_salto;
                                min_salto = newsalto;
                                //printf("%ld %ld\n",max_salto,min_salto);
                                //printf("daje ancora\n");
                            }

                        }
                        if(boolean == 1 && boolean1 == 0)
                        {
                            //prin(head_percorso);
                            pri(head_percorso,head);
                            prin(head_percorso);
                            //printf("\n");
                            boolean = 0;
                            boolean1 = 0;
                        }
                        else
                            printf("nessun percorso\n");

                    }
                    //}
                }
            }
        }else if(buffer[9] == 'a')
        {
            long int stoadd;
            int autotoadd;
            //printf("aggiungi auto\n");
            if(scanf("%ld",&stoadd));
            if(scanf("%d",&autotoadd));
            if(dio(head,stoadd,autotoadd)==-1)
            {
                printf("non aggiunta\n");
            }
            else
                printf("aggiunta\n");
        }
    }
    //printReverse(head);
    return 0;
}
