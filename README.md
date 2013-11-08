converter_OcTree
=================

This is a RSB converter for (de)serializing OctTree data.
The main programm is a simple chatter which sends the OcTree to /pointcloud and simultaneosly receives its own message via /pointcloud.
The sendmessage will be written to 'input.bt' and the receivemessage to 'output.bt'.
For compairsion use 'octovis' or 'diff'.


Some helpfull links which helped me
-----------------------------------

* [Convert ostream into standart string for serialization of the OcTree->string](http://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string)

Get an istream from a char* for deserialization of the string->OcTree:

http://stackoverflow.com/questions/7781898/get-an-istream-from-a-char

octomap documentation:

http://octomap.github.io/octomap/doc/

Manual for writing converters for RSB:

http://docs.cor-lab.org/rsb-manual/trunk/html/examples-writing-converters.html#tutorial-writing-converters
