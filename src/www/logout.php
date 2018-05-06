<?php

session_start();

if (isset($_GET['source']))
{
   show_source(__FILE__);
   exit();
}
unset($_SESSION['userid']);
header("Location: /index.php");