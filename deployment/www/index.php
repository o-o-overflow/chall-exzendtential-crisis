<?php

session_start();

if (isset($_GET['source']))
{
   show_source(__FILE__);
   exit();
}


?>

<html>

<form action="login.php" method=POST>
username <input type=text name=username required><br>
password <input type=password name=password required><br>
   <input type=submit value=Login>   
</form>

<form action="register.php" method=POST>
username <input type=text name=username required><br>
password <input type=password name=password required><br>
   <input type=submit value=Register>   
</form>

<a href="?source">debug me</a> <br>
   
<?php

if (isset($_SESSION['userid']))
{
?>
<a href="flag.php">can you get the flag?</a><br>
<a href="essays.php">who is your favorite existentialist?</a><br>
<a href="logout.php">logout</a>
<?php
}

  

?>   

</html>