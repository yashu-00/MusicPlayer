#include<stdio.h>
#include <string.h>
#include<stdlib.h>
struct song 
{
	char song_name[20];
	char singer[20];
	char genre[20];
};
struct node
{
	struct song *data;
	struct node* next;
	struct node* prev;
};
int circ=1;
char pname[5][10];
int dltplay(struct node *Head[],int c)
{
	int j,i=0,sel;
	while(pname[i][0]!='\0')
	{
		printf("\n%d. %s Playlist",i+1,pname[i]);
		i++;
	}
	if(i==0){
	    printf("\nYou Don't Have Any Playlist");
	    return c;
	}
	else
	    printf("\nEnter playlist's number : ");
	scanf("%d",&sel);
	sel-=1;
	Head[sel]=NULL;
	pname[sel][0]='\0';
	for(j=0;j<i;j++)
	{
		if(pname[j][0]=='\0' && pname[j+1][0]!='\0')
		{
			strcpy(pname[j],pname[j+1]);
			pname[j+1][0]='\0';
			Head[j]=Head[j+1];
			Head[j+1]=NULL;
		}
	}
	if(sel==c)
    	return -1;
    else if(sel<c)
        return c-1;
    else 
        return c;
}
int allplaylists(struct node *head[])
{
	printf("\n1. Main playlist");
	int i=0,select;
	while(pname[i][0]!='\0')
	{
		printf("\n%d. %s playlist",i+2,pname[i]);
		i++;
	}
	if(i==0){
	    printf("\nYou Have only MAIN Playlist");
	    return -1;
	}
	else
	    printf("\nEnter playlist's number : ");
	do{
		scanf("%d",&select);
		if(select<1 || select>i+2)
		printf("\n~ Invalid playlist number , Enter again : ");
	}while(select<1 || select>i+2);
	return ( select-2 );
}
int createlist(struct node *head[])
{
	int p=0;
	while(head[p]!=NULL && pname[p][0]!='\0')
	    p++;
	printf("Enter Playlist Name : ");
	scanf("%s",&pname[p]);
	return p;
}
struct node* deleteSong(char c[],struct node **head,struct node **head2,int circ)
{
	if(*head==NULL)
	{
		printf("~List is Empty\n");
		return NULL;
	}
	struct node *t=*head;
	if(strcmp(t->data->song_name,c)==0)
	{
		if(*head2==*head)
		    *head2=t->next;
		*head=t->next;
		if(*head!=NULL)
		    t->next->prev=NULL;
		return t;
	}
	while(t!=NULL)
	{
		if(t->next==NULL)
		{
			printf("~Song doesn't exsist in List\n");
			return NULL;
		}
		if(strcmp(t->next->data->song_name,c)==0)
		{
			struct node *te=t->next;
			if(t->next==*head2&&circ==1)
			{
				if(te->next==NULL)
				*head2=*head;
				else
				*head2=te->next;
			}
			else if(te==*head2)
			{
				if(te->next==NULL)
				*head2=te->prev;
				else
				*head2=te->next;
			}
			t->next=t->next->next;
			if(te!=NULL)
			te->prev=t;
			return te;
		}
		t=t->next;
	}
}
struct node* changePos(struct node **head)
{
	if((*head)==NULL)
	{
		printf("~List is Empty\n");
		return *head;
	}
	if((*head)->next==NULL)
	{
		printf("~You have enter more than one Song\n");
		return *head;
	}
	struct node *t=*head;
	char c[20];
	int x=0,pos;
	printf("Enter song name: ");
	scanf("%s",c);
	while(t!=NULL)
	{
		x++;
		if(strcmp(t->data->song_name,c)==0)
		{
			break;
		}
		t=t->next;
	}
	if(t==NULL)
	{
		printf("~Song doesn't exsist in List\n");
		return *head;
	}
	printf("Enter pos where you place the Song: ");
	scanf("%d",&pos);
	if(pos==0)
	{
		printf("~Invalid Input\n");
		return *head;
	}
	if(pos==x)
	{
		return *head;
	}
	struct node *te=t,*tu=t->next;
	if(t==*head)
	{
		(*head)=(*head)->next;
		(*head)->prev=NULL;	
	}
	else
	{
		t->prev->next=t->next;
		if(tu!=NULL)
		tu->prev=t->prev;
	}
	if(pos==1)
	{
		(*head)->prev=te;
		te->next=(*head);
		(*head)=te;
		(*head)->prev=NULL;
		return *head;
	}
	int i;
	t=(*head);
	for(i=1;i<pos;i++)
	{
		if(t==NULL)
		{
			printf("~Invalid position Input\nEnter pos again :");
			scanf("%d",&pos);
			while(pos==0)
			{
				printf("~Invalid position Input\nEnter pos again :");
				scanf("%d",&pos);
			}
			i=0;
			t=*head;
			continue;
		}
		else if(i==pos-1)
		{
			te->next=t->next;
			te->prev=t;
			t->next=te;
			if(te->next!=NULL)
			{
				t=t->next->next;
				t->prev=te;
			}
			return *head;
		}
		t=t->next;
	}
}
struct node* playParticular(struct node **head,struct node *head2)
{
	if(*head==NULL)
	{
		printf("~List is Empty\n");
		return head2;
	}
	char c[20];
	printf("Enter song name: ");
	scanf("%s",c);
	struct node *t=*head;
	while(t!=NULL)
	{
		if(strcmp(t->data->song_name,c)==0)
		{
			head2=t;
			printf("\n*********************************************\n");
			printf("\tNow playing \"%s\" song",head2->data->song_name);
			printf("\n*********************************************\n");
			return head2;
		}
		if(t->next==NULL)
		{
			printf("~Song doesn't exist in list\n");
		}
		t=t->next;
	}
	return head2;
}
struct node* playNext(struct node *head,struct node* head2,int circ)
{
	if(head==NULL)
	{
		printf("~List is Empty\n");
		return NULL;
	}
	if(head->next==NULL){
		printf("~you have only one song in list\n\n");
	    return NULL;
	}
	if(head2==NULL)
	{
		printf("~First play any song\n");
		return NULL;
	}
	if(head2->next==NULL)
	{
		if(circ==1)
		{
			head2=head;
		}
		else
		{
			printf("~Their is no next Song in the List\n");
			return head2;
		}
	}
	else
	head2=head2->next;
	printf("\n*********************************************\n");
	printf("\tNow playing \"%s\" song",head2->data->song_name);
	printf("\n*********************************************\n");
	return head2;
}
struct node* playPrev(struct node* head,struct node* head2,int c)
{
	if(head==NULL)
	{
		printf("~List is Empty\n");
		return NULL;
	}
	if(head->next==NULL){
		printf("~you have only one song in list\n\n");
	    return NULL;
	}
	if(head2==NULL)
	{
		printf("~First play any Song\n");
		return NULL;
	}
	if(head2->prev==NULL)
	{
		if(c==0)
		{
			printf("~Their is no privious Song in the List\n");
		}
		else
		{
			struct node* t=head;
			while(t->next!=NULL)
			{
				t=t->next;
			}
			head2=t;
			printf("\n*********************************************\n");
			printf("\tNow playing \"%s\" song",head2->data->song_name);
			printf("\n*********************************************\n");
		}
	}
	else
	{
		head2=head2->prev;
		printf("\n*********************************************\n");
		printf("\tNow playing \"%s\" song",head2->data->song_name);
		printf("\n*********************************************\n");
	}
	return head2;
}
struct node* playFirst(struct node *Head,struct node *Head2)
{
	if(Head==NULL)
	{
		printf("\n~Playlist is Empty\n");
		return NULL;
	}
	Head2=Head;
	printf("\n*********************************************\n");
	printf("\tNow playing \"%s\" song",Head2->data->song_name);
	printf("\n*********************************************\n");
	return Head2;
}
void display(struct node *Head,int i)
{
	printf("\n*********************************************\n");
	i>=0?printf("%s playlist active -\n",pname[i]):printf("Main playlist active -\n");
	struct node *t=Head;
	if(Head==NULL)
	{
		printf("     Empty Songs List\n");
	}
	else{
		int x=1;
		while(t!=NULL)
		{
			printf("     %d. %s by %s General %s\n",x++,t->data->song_name,t->data->singer,t->data->genre);
			t=t->next;
		}
    }
	printf("*********************************************\n");
	return ;
}
void addSong(struct node **Head,struct node **main,int c)
{
	struct node *newdata=(struct node*)malloc(sizeof(struct node));
	struct node* t=*main;
	newdata->next=NULL;
	newdata->prev=NULL;
	char sn[10];
	int s;
	if(*main==NULL)
	{
		printf("\n~ First insert songs to MAIN playlist~");
		return ;
	}
	display(*main,-1);
	printf("Enter song name: ");
	fflush(stdin);
	gets(sn);
	s=0;
	while(t!=NULL)
	{
		if(strcmp(sn,t->data->song_name)==0)
		{
			newdata->data=t->data;
			s=1;
			break;
		}
		else
		{
		    t=t->next;
		}
	}
	if(s==0){
		printf("~ Song doesn't exist in Main playlist ~");
		return ;
    }
	t=*Head;
	while(t!=NULL)
	{
		if(strcmp(sn,t->data->song_name)==0)
		{
			printf("~ song already exist ~");
			return ;
		}
		t=t->next;
	}
	newdata->next=*Head;
	newdata->prev=NULL;
	if(*Head!=NULL)
	{
		(*Head)->prev=newdata;
	}
	*Head=newdata;
	display(*Head,c);
}
struct song* create_song(struct node* Head)
{
	struct song *newdata=(struct song*)malloc(sizeof(struct song));
	struct node* t=Head;
	printf("Enter song name: ");
	fflush(stdin);
	gets(newdata->song_name);
	if(Head!=NULL)
	{
		while(t!=NULL)
		{
			if(strcmp(newdata->song_name,t->data->song_name)==0)
			{
				printf("Enter differnt song name: ");	
				fflush(stdin);
				gets(newdata->song_name);
				t=Head;
			}
			else
			t=t->next;
		}
	}
	printf("Enter singer name: ");
	gets(newdata->singer);
	printf("Enter general: ");
	gets(newdata->genre);
	return newdata;
}
void insertSong(struct node **Head)
{
	struct node *t=*Head;
	struct node *newdata=(struct node*)malloc(sizeof(struct node));
	newdata->data=create_song(t);
	newdata->next=*Head;
	newdata->prev=NULL;
	if(*Head!=NULL)
	{
		t->prev=newdata;
	}
	*Head=newdata;
	display(*Head,-1);
}
int main()
{
	int c,flag=0,act=-1,i=0;
	char name[20];
	struct node* head=NULL;
	struct node* phead[5]={NULL,NULL,NULL,NULL,NULL};
	struct node* head2=NULL;
	for(i=0;i<5;i++)
	    pname[i][0]='\0';
	while(1)
	{
		(flag==0)?printf("\n|| Main Playlist is Active ||\n"):printf("\n|| %s Playlist is Active ||\n",pname[act]);
		(flag==0)?printf("Enter 1 for insert a new song\n"):printf("Enter 1 for add a song to playlist\n");
		printf("Enter 2 for play first song\n");
		printf("Enter 3 for play next song\n");
		printf("Enter 4 for play previous song\n");
		printf("Enter 5 for play particular song\n");
		printf("Enter 6 for change position of a song\n");
		printf("Enter 7 for delete a song\n");
		printf("Enter 8 for delete all songs\n");
		(circ==1)?printf("Enter 9 for repeatation - OFF\n"):printf("Enter 9 for repeatation - ON\n");
		printf("Enter 10 for Create a New Playlist\n");
		printf("Enter 11 for Play a particular Playlists\n");
		printf("Enter 12 for delete a playlist\n");
		printf("Enter 13 for delete all playlists\n");
		printf("Enter 14 for display all songs\n");
		printf("Enter 0 for exit\n:- ");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				if(flag==0)
				    insertSong(&head);
				else{
				    addSong(&phead[act],&head,act);
				}
				break;
			case 2:
				if(flag==0)
			        head2=playFirst(head,head2);
			    else
			        head2=playFirst(phead[act],head2);
				break;
			case 3:
				if(flag==0)
					head2=playNext(head,head2,circ);
				else
					head2=playNext(phead[act],head2,circ);
				break;
			case 4:
				if(flag==0)
			    	head2=playPrev(head,head2,circ);
			    else
			    	head2=playPrev(phead[act],head2,circ);
				break;
			case 5:
				if(flag==0)
					head2=playParticular(&head,head2);
				else
					head2=playParticular(&phead[act],head2);
				break;
			case 6:
				if(flag==0){
					head=changePos(&head);
					display(head,act);
			    }
			    else{
					head=changePos(&phead[act]);
					display(phead[act],act);
			    }
				break;
			case 7:
				printf("Enter song name: ");
				fflush(stdin);
				scanf("%s",name);
				if(flag==0){
					deleteSong(name,&head,&head2,circ);
					i=0;
					while(phead[i]!=NULL)
					{
						printf("\n%d NOT NULL",i);
						deleteSong(name,&phead[i],&head2,circ);
					    i++;
					}
					display(head,act);
			    }
			    else{
					deleteSong(name,&phead[act],&head2,circ);
					display(phead[act],act);
			    }
				break;
			case 8:
				if(flag==0){
				    head=NULL;
				    for(i=0;i<5;i++){
				        phead[i]=NULL;
				    }
					display(head,act);
				}
				else{
				    phead[act]=NULL;
					display(phead[act],act);
				}
				break;
			case 9:
				circ=((circ==0)?(1):(0));
				break;
			case 10:
				act=createlist(&phead[0]);
				printf("\nAdd Songs to Playlist");
				addSong(&phead[act],&head,act);
				flag=1;
				break;
			case 11:
				i=allplaylists(&phead[0]);
				if(i<0){
					flag=0;
					act=-1;
				}
				else{
					flag=1;
					act=i;
				}
				break;
			case 12:{
			    if(flag==0)
				    dltplay(&phead[0],-1);
				else
				{
				    flag=dltplay(&phead[0],act);
				    if(flag==-1){
				    	flag=0;
				    	act=-1;
					}
					else{
						act=flag;
						flag=1;
					}
				}
				break;
			}
			case 13:{
				printf("~You can't delete MAIN playlist~");
				for(i=0;i<5;i++){
				        phead[i]=NULL;
				        pname[i][0]='\0';
				    }
				flag=0;
				break;
			}
			case 14:
				if(flag==0)
				    display(head,act);
				else
				    display(phead[act],act);
				break;
			case 0:
				printf("\n\t~ Exit ~\n");
				break;
			default:
				printf("~ Invalid Input\n");
		}
		if(c==0)
		break;
	}
	return 0;	
}
