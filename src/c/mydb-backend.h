#ifndef mydb
#define mydb

#define USER_NOT_CREATED     -1
#define USER_NOT_FOUND		 -2
#define USER_ALREADY_EXISTS  -3
#define USER_DELETED         -4
#define USER_NOT_DELETED     -5

#define USERNAME_SIZE 35
#define PASSWORD_SIZE 20

typedef struct {
   char  username[USERNAME_SIZE + 1];
   char  password[PASSWORD_SIZE + 1];
   int   user_id;
}Users;


int get_user_id(char *username, char *password, int (*check_hacking_attempt)(char*, char*));
int add_user(char *username, char *password);




#endif
