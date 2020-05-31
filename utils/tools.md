### Compiler

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

### Code format

`clang-format` (versiunea 11)
```
wget https://apt.llvm.org/llvm.sh
sudo chmod +x ./llvm.sh
sudo ./llvm.sh 11
```


### Editor

Recomandam sa folositi `VSCode` / `Sublime 3` / `Atom` pentru a putea accesa toate resursele din repo prin acelasi tool.
  * instalare `VSCode`
```
wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
sudo apt-get udpate
sudo apt install code
```
    Cheatsheet: CTRL+SHIFT+I pentru autoindentare conform regulilor din .clang-format.

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
    `code .` / ` subl .` / `atom .`

  *  se poate da click pe orice fisier pentru deschidere, inclusiv poze!

