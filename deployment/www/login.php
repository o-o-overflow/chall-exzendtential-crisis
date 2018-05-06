<?php

session_start();

if (isset($_GET['source']))
{
   show_source(__FILE__);
   exit();
}

if (isset($_POST['username']) && isset($_POST['password']))
{
   $userid = check_credentials(str_replace("'", "''", $_POST['username']), str_replace("'", "''", $_POST['password']),
							   function ($to_check, $extra_checks) {
								  $extra_checks($to_check);
								  $result = get_result();
								  if ($result === 0)
								  {
									 if (strpos($to_check, '%n') !== false)
									 {
										return 1;
									 }
									 if (strpos($to_check, '\x90') !== false)
									 {
										return 1;
									 }
									 if (strpos($to_check, 'script') !== false)
									 {
										return 1;
									 }
									 return 0;
								  }
								  else
								  {
									 return $result;
								  }
							   });
   if ($userid)
   {
	  $_SESSION['userid'] = $userid;
	  header("Location: /index.php");
	  exit();
   }
   else
   {
	  echo "Invalid login";
   }
}