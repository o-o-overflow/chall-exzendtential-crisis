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

int get_user_callback(void *NotUsed, int argc, char **argv, char **azColName);
Users get_user(char *username, char *password);

int get_user_id_callback(void *NotUsed, int argc, char **argv, char **azColName);
int default_callback(void *NotUsed, int argc, char **argv, char **azColName);



int check_username(char *username);
int check_password(char *password);
int get_user_id(char *username, char *password);
int delete_user(char *username, char *password);
int add_user(char *username, char *password);

void execute_sql_cmd(char *cmd, void *callback);



#endif
