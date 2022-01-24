


### Installation for Ubuntu in WSL

(also see the `INSTALL` file inside the systemc source)


- install g++-4.8 (with old ubuntu apt repository)
	+ (stackoverflow)[https://askubuntu.com/questions/371171/terminal-commands-for-installing-g-4-8]
- download systemc-2.3.1a.tar.gz from https://accellera.org/downloads/standards/systemc
- `mv systemc-2.3.1a.tar.gz /home/user/`
- `tar -zxvf systemc-2.3.1a.tar.gz`
- `cd systemc-2.3.1a`
- `mkdir objdir`
- `cd objdir`
- `export GXX="g++-4.8"`
- `../configure`
- `make`
- `make install`

Inside all lab projects, in the Makefile change the line:

`SYSTEMC = /courses/TDTS07/sw/systemc`

to

`SYSTEMC = /home/simon/systemc-2.3.1a`



