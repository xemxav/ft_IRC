# ft_IRC

Network project of the 42 curriculum.

The aim of this project is to code an IRC client and an IRC server.

**The main take away of the projects are the following :** 

* Understanding and use of sockets in C
* Use of the **select** function
* Parsing
* Serveur and client management

**How to make it work ?**

Git clone the project and inside this repo git clone my [42 library](https://github.com/xemxav/libft), then
`make`

First launch the server :

```
./serveur
Usage :./serveur <port>
./serveur 8888
```

In a different terminal launch several clients :
```./client```
or
```./client localhost 8888```

You can now discuss between clients.

The available commands are : 

```/nick``` : displays your nickname
```/nick yournick``` : changes your nickname to 'yournick'
```/join <channel name>``` : joins the channel or create it
```/write <channel name>``` : in order to write on a joined channel you must select it first as your ```/write``` channel.
```/join <channel name>``` : leaves a channel. /!\ you cannot leave your write channel
```/who``` : lists the user on your ```/write``` channel
```/list``` : lists all the channels on the server. By default, the server is launch with the channel ```Public_Chatroom``` and a new client connects to it.
```/msg <nick> <message>``` : sends a message to a specified user.
```/connect [<adress> <port>]``` : connects to a different server.
