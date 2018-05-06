<?php

session_start();

if (isset($_GET['source']))
{
   show_source(__FILE__);
   exit();
}

if (isset($_POST['username']) && isset($_POST['password']))
{
   $userid = create_user(str_replace("'", "''", $_POST['username']), str_replace("'", "''", $_POST['password']));

   if ($userid > 0)
   {
	  echo "user successfully created";
   }
   else
   {
	  echo "user not created successfully"; 
   }

}