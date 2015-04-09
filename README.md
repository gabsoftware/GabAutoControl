# GabAutoControl

Keyboard and mouse complete automation tool

It's a command line tool that can be used to automate actions in Windows by scripting.

#Usage
```
Syntax : gabac <target> <action> [<param1> [<param2> [...]]]
Where <target> is :
* mouse
* keyboard
* wait
```


#Mouse automation
```
Syntax : gabac mouse <action> [param1 [param2 [...]]]
Where <action> is :
* move <x> <y>
* click <button>
* scroll <direction>
```

```
Syntax 1 : gabac mouse move <x> <y>
Where <x> and <y> represent the new cursor coordinates in the screen (x,y)
```

```
Syntax 2 : gabac mouse click <button>
Where <button> is :
* left : left button
* middle : middle button
* right : right button
```

```
Syntax 3 : gabac mouse scroll <direction> [<distance>]
Where <direction> is :
* up
* down
* left
* right
And where <distance> (optional) is the non-zero number of wheel clicks (default=500)
```

#Keyboard automation
```
Syntax 1 : gabac keyboard <sequence>
Where <sequence> is a sequence of keyboard input codes.
For a list of all available keyboard input codes, type :
gabac keyboard --verbose
```

#Waiting and pauses
```
Syntax 1 : gabac wait <duration>
Where <duration> is the non-zero number of milliseconds to wait
```
