#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mydb-backend.h"

static int get_user_callback(void *NotUsed, int argc, char **argv, char **azColName);
static int default_callback(void *NotUsed, int argc, char **argv, char **azColName);
static int get_user_id_callback(void *NotUsed, int argc, char **argv, char **azColName);

static int check_password(char *password);

static void execute_sql_cmd(char *cmd, void *callback);
static int check_username(char *username);

static Users current_user;
static int last_user_id;

char const *db_name = "/var/lib/mydb/mydb.db";

int default_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   return 0;
}


int get_user_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i = 0; i<argc; i++)
   {
	  if((strcmp(azColName[i],"username") == 0))
	  {
		 strncpy(current_user.username, argv[i], USERNAME_SIZE);
		 current_user.username[USERNAME_SIZE] = '\0';
	  }
	  else if((strcmp(azColName[i],"password") == 0))
	  {
		 strncpy(current_user.password, argv[i], PASSWORD_SIZE);
		 current_user.password[PASSWORD_SIZE] = '\0';
	  }
	  else if((strcmp(azColName[i],"rowid") == 0))
	  {
		 sscanf(argv[i], "%d", &(current_user.user_id));
	  }
   }

   return 0;
}


Users get_user(char *username, char *password)
{
	char table_name[100];
    char cmd[300];

    memset(&current_user, 0, sizeof(Users));

	strcpy(table_name, "users");

    snprintf(cmd, sizeof(cmd), "select rowid, username, password from %s where username = '%s' and password = '%s';", table_name, username, password);

    execute_sql_cmd(cmd, get_user_callback);

    return current_user;
}

int get_user_id_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++)
   {
	  if((strcmp(azColName[i],"rowid") == 0))
	  {
		 sscanf(argv[i], "%d", &last_user_id);
	  }
   }

   return 0;
}


int check_username(char *username)
{
   last_user_id = USER_NOT_FOUND;

   char table_name[100];
   char cmd[305];

   strcpy(table_name, "users");
	
   snprintf(cmd, sizeof(cmd), "select rowid from %s where username = '%s';", table_name, username);

   execute_sql_cmd(cmd, get_user_id_callback);

   return last_user_id;
}

int check_password(char *password)
{
   last_user_id = USER_NOT_FOUND;

   char table_name[100];
   char cmd[305];


   strcpy(table_name, "users");

   snprintf(cmd, sizeof(cmd), "select rowid from %s where password = '%s';", table_name, password);

   execute_sql_cmd(cmd, get_user_id_callback);

   return last_user_id;
}

int get_user_id(char *username, char *password, int (*check_hacking_attempt)(char*, char*))
{
   char username_check[100];
   char table_name[100];   
   char cmd[305];
   int hacking_attempt;

   last_user_id = USER_NOT_FOUND;

   strcpy(table_name, "users");
   hacking_attempt = check_hacking_attempt(username_check, username);
	
   if (hacking_attempt == 1)
   {
	  return USER_NOT_FOUND;
   }

   snprintf(cmd, sizeof(cmd), "select rowid from %s where username = '%s' and password = '%s';", table_name, username, password);

   execute_sql_cmd(cmd, get_user_id_callback);

   return last_user_id;
}

int dummy_check(char* checking, char* username)
{
   return 0;
}

int add_user(char *username, char *password)
{
   int user_id = check_username(username);

   if(user_id == USER_NOT_FOUND)
   {
	  char table_name[100];
	  char cmd[305];

	  strcpy(table_name, "users");

	  snprintf(cmd, sizeof(cmd), "insert into %s (username, password) values ('%s', '%s');", table_name, username, password);

	  execute_sql_cmd(cmd, default_callback);

	  return get_user_id(username, password, dummy_check);

   }
   else
   {
       return USER_ALREADY_EXISTS;
   }
   return USER_NOT_CREATED;
}

void execute_sql_cmd(char *cmd, void *callback)
{
   sqlite3 *db;
   char *zErrMsg = NULL;

   int rc = sqlite3_open(db_name, &db);
   if( rc )
   {
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  sqlite3_close(db);
   }
   else
   {
	  rc = sqlite3_exec(db, cmd, callback, 0, &zErrMsg);
	  if( rc != SQLITE_OK )
	  {
		 fprintf(stderr, "SQL error: %s\n", zErrMsg);
		 sqlite3_free(zErrMsg);
		 sqlite3_close(db);
		 return;
	  }
	  sqlite3_close(db);
   }
   sqlite3_free(zErrMsg);
}

