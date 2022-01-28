


### Installation for Ubuntu in WSL

(also see the `INSTALL` file inside the systemc source)


- install g++-4.8 (with old ubuntu apt repository)
	+ **temporarily** add the line `deb <link> bionic main universe` to `/etc/apt/sources.list`
		* e.g. `deb http://archive.ubuntu.com/ubuntu/ bionic main universe` to `/etc/apt/sources.list`
	+ `sudo apt update`
	+ `sudo apt install g++-4.8`
	+ remove the line from `/etc/apt/sources.list`
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



