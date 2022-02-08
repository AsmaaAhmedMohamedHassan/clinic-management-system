#ifndef FILE_H
#define FILE_H



typedef unsigned char    u8  ;
typedef signed char      s8  ;
typedef unsigned short   u16 ;
typedef unsigned short   s16 ;
typedef unsigned int     u32 ;
typedef signed int       s32 ;
typedef float            f8  ;
typedef double           f32 ;


#define  admin       1
#define  user        2

#define  defaultPSW  1234
#define  LENGTH      20
#define  male        1
#define  female      2


u8 process;s32 id;u8 *Name[LENGTH];u32 Age;u8 gend ;


typedef enum
{
	exist=1,unique=0
	
}state;

typedef enum
{
	addNew=1,edit,reserveSlot,cancelReserve,existAdminMod
	
}adminProcess;

typedef enum
{
   viewpatient=1,viewTodayReservation,exitUserMod	
}userProcess;


typedef struct s
{
	s32 index;
	s32 id;
    struct s *link;
	
}slot;


typedef struct p
{
	s32 ID;
	u8 *name[LENGTH];
	u32 age;
	u8 gender ;
	struct p *link;
}patient;

typedef struct mod
{
	patient *p;
	slot    *r;
}userMod;


#endif