#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"



userMod * enterAdminMod    ( userMod *u);
userMod * enterUserMod     (userMod *);
patient * findPatient      (patient *list,s32 id);
state     existedID        (patient *list,s32 id);
patient * addpatient       (patient *list,patient *new);
void      displayAvailable (slot    *listOfReserve);	
slot    * reserve          (slot    *listOfReserve,s32 sNumber,s32 id);
slot    * cancel           (slot    *listOfReserve,s32 id);
void      viewPatientInfo  (patient *list,s32 id);
void      viewReservations (slot    * listOfReserve);
slot    * init             (slot *listOfReserve);

void main(void)
{
    slot *listOfReserve = (slot *)malloc(sizeof(slot));
    listOfReserve=NULL;
    listOfReserve=init(listOfReserve);
    patient *list       = (patient *)malloc(sizeof(patient));
    list=NULL;
	userMod *u =(userMod *)malloc(sizeof(userMod));
	u->p =list;
	u->r =listOfReserve;
	
   while(1)
   {
    s32 mod,password;
	printf("choose mod 1 for admin or 2 for user\n ");
	scanf("%d",&mod);
	switch(mod)
	{
		case admin :
		  printf("enter password:\n");
		  scanf("%d",&password);
		  if(password != defaultPSW)
		  {
			  for(u8 i=0 ; i<2 && password != defaultPSW ;i++)
			  {
				 printf("incorrect password please enter again\n");
			     scanf("%d",&password);

			  }
			   if(password != defaultPSW)
			   {
				 printf("incorrect password please enter again\n");
				   
			   }
		  }
		  if(password == defaultPSW)
		  {
		 u= enterAdminMod(u);
		  }
		  break;
	  case user :
	     u= enterUserMod(u);
		  break;
	}
	
}
}
userMod * enterAdminMod(userMod *u)
{
	
	do{
	printf("choose a process:\n 1 for addNew\n2 for edit\n3 for reserveSolt\n4 for cancelReserve\n5 for exist from admin mod\n");
	scanf("%d",&process);
	switch(process)
	{
		case addNew :
		  printf("enter new patient information\n");
		  printf("enter the name\n");
		  scanf("%s",Name);
		  printf("enter age\n");
		  scanf("%d",&Age);
		  printf("choose the gender: 1 for male,2 for female\n");
		  scanf("%d",&gend);
		  printf("enter ID\n");
		  scanf("%d",&id);
	      if( existedID(u->p,id) == exist )
		  {
			  printf("not accepted entry\n");
		  }	
         else	
		 {		 
		  patient *new =(patient *)malloc(sizeof(patient));  
		  *(new->name) =*Name;
		  new->age     =Age;
		  new->gender  =gend;
		  new->ID      =id;
		  u  ->p       =addpatient(u->p,new); 
		 }
		break;
	  case edit :
        printf("enter id of the patient:\n");
        scanf("%d",&id);
		if(existedID(u->p,id))
		{
			printf("new name:\n");
			scanf("%s",Name);
			printf("new age:\n");
			scanf("%d",&Age);
			printf("edit gender:\n");
			scanf("%d",&gend);
			patient *editpat = findPatient(u->p,id); 
            *(editpat->name) =*Name;
			editpat->age     =Age;
			editpat->gender  =gend;
			
		}
		else
			printf("incorrect ID\n");
		break;
	case reserveSlot :
        displayAvailable(u->r);	
		s32 sNumber;
		printf("choose slot from available and enter the ID\n");
		scanf("%d , %d",&sNumber,&id);
	    u->r = reserve(u->r,sNumber,id);
		break;
	case cancelReserve :
       printf("enter id to cancel reservation:\n");
	   scanf("%d",&id);
	   u->r= cancel(u->r,id);
	   break;
		
	}
	
	}while(process != existAdminMod);
	return u ;
}

userMod *    enterUserMod     (userMod *u)
{
	do{
	printf("choose process: 1 for viewpatient, 2 for viewTodayReservation\n3 for exitUserMod\n");
	scanf("%d",&process);
	
	switch (process)
	{
		case viewpatient :
		 printf("enter patient id to view:\n");
		 scanf("%d",&id);
		 viewPatientInfo(u->p,id);
		 break;
		 
		case  viewTodayReservation :
		 viewReservations(u->r);
		 break;
		
	}
	}while(process != exitUserMod);
	return u;
}

patient * findPatient      (patient *list,s32 id)
{
	if(list == NULL)
	{
		return list;
	}
	else
	{
		patient *ptr =list;
		while(ptr !=NULL && ptr->ID !=id)
		{
			ptr=ptr->link;
		}
		if(ptr != NULL)
		{
			return ptr;
		}
		else
			return NULL ;
	}
}


state     existedID        (patient *list,s32 id)
{
      patient *ptr =list;
      while(ptr !=NULL)
	  {
		  if( ptr->ID == id )
		  {
			  return exist;
		  }
		  ptr=ptr->link ;
	  }		  
      if(ptr == NULL)
	  {
		  return unique;
	  }
}


patient * addpatient       (patient *list,patient *new)
{
	new->link =NULL;
	if(list != NULL)
	{ 
	 patient *ptr =list;
	 while(ptr->link != NULL)
	 {
		ptr=ptr->link ;
	 }
	 ptr->link = new;
	}
	else
	{
		list = new;
	}
	 return list;
}


void      viewPatientInfo      (patient *list,s32 id)
{
	patient *ptr =list;
	while(ptr !=NULL)
	{
		if(ptr->ID == id)
		{
			printf("patient name is %s\n",ptr->name);
			printf("patient age is %d\n",ptr->age);
			printf("patient ID is %d\n",ptr->ID);
			if(ptr->gender == male)
			printf("patient gender is male\n");
		    else
			printf("patient gender is female\n");
		    break;
		}
		ptr=ptr->link;
	}
}

void      viewReservations (slot *listOfReserve)
{
	slot *ptr =listOfReserve;
	while(ptr !=NULL)
	{
		if(ptr->id != 0)
		{
			printf("patient with ID %d reserve slot%d\n",(ptr->id),(ptr->index));
		}
		ptr =ptr->link;
	}
	
}


slot    * reserve          (slot    *listOfReserve,s32 sNumber,s32 id)
{
	slot *ptr =listOfReserve;
	while(ptr != NULL)
	{
		if(ptr->index == sNumber)
		{
			ptr->id = id;
			break;
		}
		ptr =ptr->link;
	}
     
    return listOfReserve;
}


void  displayAvailable (slot    *listOfReserve)
{
	slot * ptr=listOfReserve;

	for(u8 i=1;i<=5;i++)
	{
		if(ptr->id == 0)
		{
			printf("slot%d is available\n",i);
		}
		ptr =ptr->link;
	}

}

slot    * cancel           (slot    *listOfReserve,s32 id)
{
	
	slot *ptr = listOfReserve;
	while(ptr != NULL)
	{
		if(ptr->id == id)
		{
			ptr->id =0;
			break;
		}
		ptr =ptr->link;
	}
	return listOfReserve ;
	
}


slot    * init            (slot *listOfReserve)
{
	
	slot *p =(slot *)malloc(sizeof(slot)) ;
	p->index=1;
	p->id   =0;
	p->link =NULL;
	listOfReserve =p;
	for(u8 i=2;i<=5;i++)
	{
	   slot *ptr =(slot *)malloc(sizeof(slot)) ;
	   ptr->index=i;
	   ptr->id   =0;
	   ptr->link =NULL;
	   while(p->link !=NULL)
	   {
		   p=p->link;
	   }
	   p->link   =ptr;
	}
    return listOfReserve;	
}

