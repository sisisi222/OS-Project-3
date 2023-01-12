To compile the program:
using this command:  make
then using this command: ./rwmain


PROJECT 3: READER/WRITER LOCKS

In this project, you are to:
a. Design and implement a readers/writers lock using semaphores that do not starve the
readers and do not starve the writers;
b. Write the main C program that uses Reader/Writer locks;
c. Come up with a set of input scenarios that shows the behavior of your non-starving lock
compared to the starving lock.
The readers/writers problem is presented in section 31.5 of the textbook along with the readers/writers lock that starves writers. There may be solutions published in articles over the years – feel free to consult and cite them. It is not acceptable to use code that implements this solution from the Internet or other sources other than your own work. It is acceptable to use the code from the textbook as your starter code, if useful.
This is an individual project.
The output of this project includes:
• A report (in PDF) that includes:
o Your name.
o Ashortdescriptionoftheproblemyouaddress(hopefullynotcut-and-pastedfrom
this project but written in your own words).
o A description in plain English and pseudocode of your solution. o An estimation of the time you spent working on the project.
This is likely to be a very short report – do not try to make it longer than it needs. But do make it neater than usual.
• A tar file that includes:
o A makefile for easy compilation. The target executable should be rwmain.
o A README file that describes how to run your project (arguments, etc).
o ACprogram,namedreaderwriter.c,thatimplementsthenonstarvinglocks. o A C program, named main.c, that uses the locks and shows their functionality.
Note that the reading/writing parts of the code are only simulated: you do not have to read or write a particular data structure; instead, you might want to pretend to do it, and take some time such as:
reading_writing(){
int x=0, T = rand()%10000;
                 for(i = 0; i < T; i++)
                            for(j = 0; j < T; j++)x=i*j;
}
This function is only meant to waste time for a variable amount of time. Feel free to adjust this code as you see fit (or ignore all together if not useful in your solution).
There are no required inputs to this program. You may use inputs if useful and explain use in the readme file. Output messages useful for testing and debugging.
o An input file, named scenarios.txt, that proves that your lock:
▪ Is a correct readers/writers lock.
▪ Does not starve the writers.
▪ Does not starve the readers.
▪ Eachscenariotakesoneline(as the traces file in last project)▪Anexample and interpretation of this file is below:
rwrrrrwrr wwrrrrwr
This file contains two scenarios:
1. One in which one reader arrives first, then a writer, then four more readers, another writer, then two more readers.
2. And the second in which two writers arrive first, then four readers, one more writer, and one more reader.
▪ You want these scenarios to test corner cases that are relevant for the point of your design: specifically, that writers will not starve. Thus, you design these test scenarios to make it possible for writers to starve. You do not need lots of readers/writers to make the case. You might want to limit each scenario to 10--15 readers and writers at the very most.
To ease the task of grading, please name your files as requested and put all these files in the same folder. In addition, please hardcode the file name for scenarios.txt with the relative path (not the absolute path) in your main.c code, e.g.:
FILE* ptr = fopen("scenarios.txt ","r");



