<?php

$quotes = array("It disturbs me no more to find men base, unjust, or selfish than to see apes mischievous, wolves savage, or the vulture ravenous.", "To believe is to know you believe, and to know you believe is not to believe.", "If you are lonely when you're alone, you are in bad company.", "Existence precedes essence", "What is that to exist? To drink without thirst", "Anxiety is the dizziness of freedom", "You can always make something of what has made us", "Not choosing is a choice", "Choice and consciousness are one and the same thing", "Actually, we are a freedom which chooses, but we do not choose to be free: we are condemned to freedom", "I build the universal in choosing me, I build it by understanding the project from any other man, whatever time it is", "Being condemned to be free, it means you can not find my limits freedom of others than herself", "Being condemned to be free, it means you can not find my limits freedom of others than herself", "Being conscious is explode to the world", "The consciousness is itself at the same time as she is aware of the other", "Conscience is really a consciousness of consciousness, because to be aware of world consciousness must be consciousness of itself", "The Other, is it me who is not me", "My original sin is the existence of others", "There is oppression than freedom from freedom", "The body is not united with consciousness, it is entirely psychological", "The consciousness exists in his body", "Love is, in essence, the project to be loved", "One love, a career, a revolution, as many companies as we begin ignoring their outcome", "That is the essence of the joy of love, when it exists: we feel justified to exist", "Love is the project to be loved", "The ideal of love is now alienated freedom: everyone wants the freedom to alienate the other", "Violence is not a means among others to reach the end, but a deliberate choice to reach the end by any means", "The war we do not: it is that makes us", "I want to leave, to go somewhere where I should be really in my place, where I would fit in… but my place is nowhere; I am unwanted", "Anything, anything would be better than this agony of mind, this creeping pain that gnaws and fumbles and caresses one and never hurts quite enough.", "Everything has been figured out, except how to live", "Three o’clock is always too late or too early for anything you want to do");

session_start();

if (isset($_GET['source']))
{
   echo "lol, good try.";
   exit();
}

if (isset($_SESSION['userid']))
{
   if ($_SESSION['userid'] === 1)
   {
	  echo "welcome, as Sarte might say: ooo{IMHO, Hell is other people AND other people's code}";
   }
   else
   {
	  echo "Only sarte knows the flag. You are not him. Enjoy a quote though:<br>";
	  echo $quotes[array_rand($quotes)];
   }
}
else
{
   header("Location: /index.php");
   exit();
}