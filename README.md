# System Monitoring Library

This is a quite a simple library designed to provide some of the system information.
It's not cross-platform and runs only on Linux.
Currently supports two methods:

`long get_core_num()` - returns the number of cores on the current machine;  
`double get_core_temp_by_idx(int i)` - provides with a core temperature given a valid core index.  

It was made exclusively for training purposes. If you have any suggestions, code comments or willing to make it more
sophisticated - I will gladly accept your help.