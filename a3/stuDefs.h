typedef struct {
  char first[32];
  char last[32];
  int  age;
} PersonType;

typedef struct {
  PersonType basicInfo;
  char       stuNumber[12];
  float      gpa;
} StudentType;

typedef struct{
	char system[MAX_STR];
	int  numPlayers;
	char genre[MAX_STR];
	char finished;
} GameType;

typedef struct{
	char busNum;
	char direction[MAX_STR];
	int  fare;
} BusType;

typedef struct{
	PersonType basicInfo;
	int        employeeNum;
	int        salary;
} WorkType;

typedef struct{
	char city[MAX_STR];
	char teamName[MAX_STR];
	int  numGames;
	int  wins;
	int  losses;
} TeamType;

typedef struct{
	char  name[MAX_STR];
	char  productType[MAX_STR];
	float price;
}ProductType;
