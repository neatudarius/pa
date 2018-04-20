### compiler

Recomandam sa instalati g++-7 pentru a va asigura exemplele de cod modificate sunt compatibile cu vmchecker.

```
darius@pc ~ $ sudo add-apt-repository ppa:jonathonf/gcc-7.2
darius@pc ~ $ sudo apt-get update
darius@pc ~ $ apt-cache search gcc-7
darius@pc ~ $ sudo apt-get install gcc-7 g++-7
darius@pc ~ $ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 20
darius@pc ~ $ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 20
darius@pc ~ $ g++ -v
gcc version 7.2.0 (Ubuntu 7.2.0-1ubuntu1~16.04)
```


### editor

Recomandam sa folositi `Sublime 3` / `Atom` pentru a putea accesa toate resursele din repo prin acelasi tool.

  *  instalare `Sublime 3`
   ```
   sudo add-apt-repository ppa:webupd8team/sublime-text-3
   sudo apt-get update
   sudo apt-get install sublime-text-installer
   ```
   
  *  instalare `Atom`
   ```
   sudo add-apt-repository ppa:webupd8team/atom
   sudo apt-get update
   sudo apt-get install atom
   ```

  *  rulare
  ` subl .` / `atom .`
 
  *  se poate da click pe orice fisier pentru deschidere, inclusiv poze!

