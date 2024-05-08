#include <stdio.h>
#include <stdlib.h>

typedef struct Processus
{
    int id;
    int tarr;
    int tex;
    int tres;
    int trep;
    int tatt;
    int tfin;
    int priorite;
    struct Processus *suiv;
}Processus;

Processus* create_processus(int id,int tarr,int priority,int tex);
Processus* add_priority(Processus* File1, Processus* processus);
Processus* add_end(Processus* File1, Processus* process);
Processus* remove_first(Processus** File1);

Processus* File1 = NULL;  //(1,2,3)
Processus* File2 = NULL;  //(4,5,6)
Processus* File3 = NULL;  //(7,8,9,10)
int Quantum1 = 1;
int Quantum2 = 2;
int Quantum3 = 3;

Processus* create_processus(int id,int tarr,int priorite,int tex)
{
    Processus* processus=malloc(sizeof(Processus));
    processus->id=id;
    processus->tarr=tarr;
    processus->tex=tex;
    processus->tres=tex;
    processus->trep=0;
    processus->tatt=0;
    processus->tfin=0;
    processus->priorite=priorite;
    processus->suiv=NULL;
    return processus;
}

void create_AND_add_to_list(Processus** processus_array,int size)
{
    for(int i=0;i<size;i++)
    {
        Processus* processus=processus_array[i];

        if(processus->tex>=1 && processus->tex<=3)
        {
            File1=add_priority(File1,processus);
        }
        else if(processus->tex>=4 && processus->tex<=6)
        {
            File2=add_priority(File2,processus);
        }
        else if(processus->tex>=7 && processus->tex<=10)
        {
            File3=add_priority(File3,processus);
        }
    }
}

int return_size_File1(Processus* File1)
{
    int i = 0;
    Processus* this=File1;

    while(this!=NULL)
    {
        i++;
        this=this->suiv;
    }

    return i;
}

Processus* add_priority(Processus* File1,Processus* processus)
{
    if(File1==NULL)
    {
        return processus;
    }

    if(processus->priorite < File1->priorite)
    {
        processus->suiv=File1;
        return processus;
    }
    else
    {
        Processus* this=File1;

        while(this->suiv!=NULL && this->suiv->priorite <= processus->priorite)
        {
            this=this->suiv;
        }

        processus->suiv=this->suiv;
        this->suiv=processus;
    }

    return File1;
}


Processus* add_end(Processus* File1,Processus* processus)
{
    if(File1==NULL)
    {
        return processus;
    }

    Processus* this=File1;

    while(this->suiv!=NULL)
    {
        this=this->suiv;
    }

    this->suiv=processus;
    return File1;
}


Processus* remove_first(Processus** File1)
{
    if(*File1==NULL)
    {
        return NULL;
    }

    Processus* temp=*File1;
    *File1=(*File1)->suiv;
    temp->suiv=NULL;
    return temp;
}

int return_min_tarr(Processus** processus_array,int size)
{
    int min_tarr=processus_array[0]->tarr;

    for (int i=1;i<size;i++)
    {
        if(processus_array[i]->tarr < min_tarr)
        {
            min_tarr=processus_array[i]->tarr;
        }
    }

    return min_tarr;
}

void execution(Processus** processus_array,int size)
{
    int TA[size];
    int TE[size];

    for(int j=0;j<size;j++)
    {
        TA[j]=processus_array[j]->tarr;
        TE[j]=processus_array[j]->tex;
    }

    int this_File1=1;
    int time = return_min_tarr(processus_array,size);
    float somme_tatt = 0.0;
    float somme_trep = 0.0;
    create_AND_add_to_list(processus_array,size);

    while(File1!=NULL || File2!=NULL || File3!=NULL)
    {
        Processus* this_processus=NULL;
        int File1_size;
        int runtime;

        if(this_File1==1)
        {
            if(File1!=NULL)
            {
                File1_size=return_size_File1(File1);

                for(int i=0;i<File1_size;i++)
                {
                    if(File1->tarr > time)
                    {
                        this_processus=remove_first(&File1);
                        File1=add_end(File1,this_processus);
                    }
                    else
                    {
                        break;
                    }
                }

                if(File1->tarr > time)
                {
                    this_File1++;
                    continue;
                }

                this_processus=remove_first(&File1);
                if(this_processus!=NULL)
                {
                    if(this_processus->tres > Quantum1)
                    {
                        runtime=Quantum1;
                    }
                    else
                    {
                        runtime=this_processus->tres;
                    }

                    time+=runtime;
                    this_processus->tres -= runtime;

                    if(this_processus->tres > 0)
                    {
                        File1=add_end(File1,this_processus);
                    }
                    else
                    {
                        processus_array[this_processus->id-1]->tfin=time;

                        int trep=time - this_processus->tarr;
                        int tatt=trep - this_processus->tex;

                        processus_array[this_processus->id-1]->trep=trep;
                        processus_array[this_processus->id-1]->tatt=tatt;
                        somme_trep += trep;
                        somme_tatt += tatt;
                        free(this_processus);
                    }
                }
            }
            this_File1++;
            continue;
        }
        else if(this_File1==2)
        {
            if(File2 != NULL)
            {
                File1_size=return_size_File1(File2);

                for(int i=0;i<File1_size;i++)
                {
                    if(File2->tarr > time)
                    {
                        this_processus=remove_first(&File2);
                        File2=add_end(File2,this_processus);
                    }
                    else
                    {
                        break;
                    }
                }

                if(File2->tarr > time)
                {
                    this_File1++;
                    continue;
                }

                this_processus=remove_first(&File2);
                if(this_processus!=NULL)
                {
                    if(this_processus->tres > Quantum2)
                    {
                        runtime=Quantum2;
                    }
                    else
                    {
                        runtime=this_processus->tres;
                    }

                    time += runtime;
                    this_processus->tres -= runtime;

                    if(this_processus->tres > 0)
                    {
                        File2=add_end(File2, this_processus);
                    }
                    else
                    {
                        processus_array[this_processus->id-1]->tfin = time;

                        int trep=time - this_processus->tarr;
                        int tatt=trep - this_processus->tex;

                        processus_array[this_processus->id-1]->trep = trep;
                        processus_array[this_processus->id-1]->tatt = tatt;
                        somme_trep += trep;
                        somme_tatt+= tatt;
                        free(this_processus);
                    }
                }
            }
            this_File1++;
            continue;
        }
        else if(this_File1==3)
        {
            if(File3!=NULL)
            {
                File1_size=return_size_File1(File3);

                for (int i=0;i<File1_size;i++)
                {
                    if(File3->tarr > time)
                    {
                        this_processus=remove_first(&File3);
                        File3 = add_end(File3,this_processus);
                    }
                    else
                    {
                        break;
                    }
                }

                if(File3->tarr > time)
                {
                    this_File1 = 1;
                    continue;
                }

                this_processus=remove_first(&File3);
                if(this_processus!=NULL)
                {
                    if (this_processus->tres > Quantum3) {
                        runtime=Quantum3;
                    }
                    else
                    {
                        runtime=this_processus->tres;
                    }

                    time += runtime;
                    this_processus->tres -= runtime;

                    if(this_processus->tres > 0)
                    {
                        File3=add_end(File3,this_processus);
                    }
                    else
                    {
                        processus_array[this_processus->id-1]->tfin = time;

                        int trep=time - this_processus->tarr;
                        int tatt=trep - this_processus->tex;

                        processus_array[this_processus->id-1]->trep = trep;
                        processus_array[this_processus->id-1]->tatt = tatt;
                        somme_trep += trep;
                        somme_tatt += tatt;
                        free(this_processus);
                    }
                }
            }
            this_File1=1;
            continue;
        }
    }

  float moy_tatt;
  float moy_trep;
  moy_tatt=somme_tatt/size;
  moy_trep=somme_trep/size;
  printf("\nProcessus | T_darrivee | T_fin | Priorite | T_dexecution | T_dattente | T_reponse |\n");
for (int i=0;i<size;i++)
{
    printf("\nP%d            %d        %d        %d           %d           %d           %d\n",
        i+1,
        TA[i],
        processus_array[i]->tfin,
        processus_array[i]->priorite,
        TE[i],
        processus_array[i]->tatt,
        processus_array[i]->trep);
}
        printf("\nTemps moyen dattente : %.2f", moy_tatt);
        printf("\tTemps moyen de reponse : %.2f\n", moy_trep);

}

int main()
{
    int n,i;
    printf("Enter the number of processes : ");
    scanf("%d",&n);

    while(n<=0)
    {
        printf("\nThe number should be superuier than 0\n");
        printf("\nEnter the number of processes : ");
        scanf("%d",&n);
    }

    Processus* processus_array[n];

    for(i=0;i<n;i++)
    {
        int ta,priority,te;
        printf("\nProcessus %d:\n",i+1);

        printf("Temps d arrivee : ");
        scanf("%d",&ta);
        while (ta < 0)
        {
            printf("Temps darrivee should be greater or equal 0.");
            scanf("%d",&ta);
        }

        printf("Priorite : ");
        scanf("%d",&priority);
        while (priority <= 0)
        {
            printf("Priorite should be greater than 0.");
            scanf("%d",&priority);
        }

        printf("Temps d execution : ");
        scanf("%d",&te);
        while (te <= 0)
        {
            printf("Temps d execution should be greater than 0.");
            scanf("%d",&te);
        }
        processus_array[i]=create_processus(i+1,ta,priority,te);
    }
    execution(processus_array,n);

    return 0;
}
