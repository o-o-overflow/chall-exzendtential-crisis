# chall-exzendtential-crisis

A very simple website. A place for folks to ponder existence.

Intended solution:

The first vuln relies on users being able to leak any file, particularly the `mydb.so` extension that queries the DB. First, get the `php.ini` to see that there's an extension (plus the name of the challenge). Then, leak the `mydb.so`.

There is a buffer overflow vulnerability in the mydb.so that allows you to overflow into a SQL injection. 

Check [exploit.py](exploit.py) for info.

I am curious if there are other ways to solve it. 

`deployment` has the Vagrantfile and ansible script necessary.

`exploit` has the exploit that works.

`src` has the source for the zend extension and the php files.

TAGS: web, pwn

LEVEL: med/hard

STATUS: ready to deploy

AUTHOR: adamd

TESTED BY: nobody. 
