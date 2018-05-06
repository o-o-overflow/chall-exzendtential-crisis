<?php

session_start();

if (isset($_GET['source']))
{
   show_source(__FILE__);
   exit();
}

if (!isset($_SESSION['userid']))
{
   header("Location: /index.php");
   exit();
}

if (isset($_POST['essay']))
{
   $dirname = "upload/${_SESSION['userid']}/";
   mkdir($dirname, 0770, true);

   $fname = $dirname . bin2hex(random_bytes(10));
   file_put_contents($fname, $_POST['essay']);
   header("Location: /essays.php");
   exit();
}

if (isset($_GET['preview']))
{
   $dirname = "upload/${_SESSION['userid']}/";
   $fname = $_GET['name'];

   if (check_fname($fname) === False)
   {
	  header("Location: /essays.php");
	  exit();
   }
   $content = file_get_contents($dirname . $fname);
   echo "<h1>Your essay submission</h1>";
   echo "<pre>";
   echo $content;
   echo "</pre>";
   echo "<br>";
   echo "<a href='essays.php'>back</a>";
   exit();
}

function check_fname($fname)
{
   $bad = ["flag", "proc", "\x90"];
   foreach ($bad as $b)
   {
	  if (strpos($fname, $b) !== false)
	  {
		 return False;
	  }
   }
   return True;
}

?>
<html>

<form action="/essays.php" method=POST>
<textarea name=essay required>
</textarea><br>
<input type=submit value="Submit Essay For Grading">   
</form>

   <h1>Preview your submissions awaiting grading</h1>
<ul>   
<?php
$dirname = "upload/${_SESSION['userid']}/";

if (is_dir($dirname))
{

$files = scandir($dirname);
foreach ($files as $f)
{
   if ($f == "." || $f == "..")
   {
	  continue;
   }
   ?>
   <li>
	  <a href="essays.php?preview&name=<?php echo urlencode(basename($f)); ?>"><?php echo basename($f); ?></a>
   </li>
<?php
}
}
?>
</ul>
</html>