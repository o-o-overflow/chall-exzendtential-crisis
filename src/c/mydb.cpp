#include <phpcpp.h>

#define DEBUG 0

extern "C"
{
   #include "mydb-backend.h"
}

static int num_hashes = 20;
static Php::Value check_creds_callback = 0;


Php::Value hash_that_pass(std::string password)
{
   Php::Value curr_pass = password + "saltyadamd";
   for (int i = 0; i < num_hashes; i++)
   {
	  curr_pass = Php::call("hash", "sha256", curr_pass);
   }
   return curr_pass;
}

static int the_result = 1;

Php::Value get_result (Php::Parameters &params)
{
   return the_result;
}

int check_hacking_attempt(char* checking, char* username)
{
   // don't let the dirty hackers use their fancy overflows
   if (strlen(username) >= 150)
   {
	  return 1;
   }   

   // copy over the value to be checked
   strcpy(checking, username);

   Php::Function our_check([](Php::Parameters &params) -> Php::Value
						   {
							  if (params.size() == 0) return nullptr;
							  
							  // one parameter is passed to the function
							  std::string param = params[0];

							  if (param.find("SELECT") != std::string::npos)
							  {
								 the_result = 1;
							  }
							  else if (param.find("select") != std::string::npos)
							  {
								 the_result = 1;
							  }
							  else if (param.find("`") != std::string::npos)
							  {
								 the_result = 1;
							  }
							  else
							  {
								 the_result = 0;
							  }
							  return nullptr;
						   });
	
   return (int)check_creds_callback(Php::Value(checking), our_check);
}



Php::Value check_credentials(Php::Parameters &params)
{
   std::string username = params[0];
   std::string password = hash_that_pass(params[1]);
   check_creds_callback = params[2];
   
   int user_id;

   user_id = get_user_id((char*) username.c_str(), (char*) password.c_str(), check_hacking_attempt);
   check_creds_callback = 0;
   if (user_id == USER_NOT_FOUND)
   {
	  return Php::Value(0);
   }
   else if (user_id <= 0)
   {
	  throw Php::Exception("Error in checking credentials.");
   }
   return Php::Value(user_id);
}

Php::Value create_user(Php::Parameters &params)
{
   std::string username = params[0];
   std::string password = hash_that_pass(params[1]);
   int result;

   result = add_user((char*) username.c_str(), (char*) password.c_str());

   if (result == USER_ALREADY_EXISTS)
   {
	  throw Php::Exception("User already exists!");
   }
   else if (result == USER_NOT_CREATED)
   {
	  throw Php::Exception("User not created for some reason. That is weird.");
   }
   else if (result <= 0)
   {
	  throw Php::Exception("Some other error occured that is not supposed to.");
   }
   return result;
}


/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension myExtension("mydb", "1.0");

		myExtension.add<check_credentials>("check_credentials", {
			  Php::ByVal("username", Php::Type::String),
			  Php::ByVal("password", Php::Type::String),
			  Php::ByVal("check_hacking", Php::Type::Callable),				 
		});

		myExtension.add<create_user>("create_user", {
			  Php::ByVal("username", Php::Type::String),
			  Php::ByVal("password", Php::Type::String),
		});

		myExtension.add<get_result>("get_result", {
		   });

        // return the extension
        return myExtension;
    }
}
